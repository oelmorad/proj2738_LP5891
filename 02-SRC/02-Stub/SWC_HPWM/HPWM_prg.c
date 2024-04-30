/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HPWM                                                    */
/* !Description     : Pulse width modulation driver                           */
/*                                                                            */
/* !Module          : HPWM_prg.c                                              */
/* !Revision        : 2.6                                                     */
/* !Date            : 27 Dec 2020                                             */
/*                                                                            */
/* !Scope           : Program                                                 */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : STD                                                     */
/* !Target          : STD                                                     */
/*                                                                            */
/* !COPYRIGHT 2016 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/*    Author   --     Date    --          Modification                        */
/* Ahmed Assaf -- 24 OCT 2016 -- Initial Creation                             */
/* MDESOKY     -- 03 MAR 2017 -- Add calculations of PWM and ICU              */
/* mohamed gharib 30 Aug 2018    fix of ICU duty cycle calculation            */
/*             --             -- after UTD tests                              */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Ahmed Abdelmageed                                                          */
/*                 25/ 2 / 2019   update the inclusion of SchM_HPWM.h to be   */
/*                                included only if BSW_HPWM_IN is defined     */
/*                                [artf267815]                                */
/*                 26/ 2 / 2019   added private function                      */
/*                                vidCalculateInPeriodandDuty to reduce STMIF */
/*                                of the function HPWM_vidRunnable[artf327887]*/
/*                 28/ 2 / 2019   changed private function 'vidUpdateInPeriod'*/
/*                                name to be 'vidUpdateInFilteredPeriod'      */
/* Soha Wagdy  --  14/3/2019   -- Update AUTOSAR headers inclusion            */
/* Ahmed Abdelmageed                                                          */
/*                 08/ 4 / 2019   added conditional macros to protect against */
/*                                unused variable compiler warnings           */
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Soha Wagdy  --  8 Sep 2020  -- [artf1042890] Init local variables          */
/* Ahmed Ramadan-- 8 Nov 2020  -- Min frequency detection ACR [artf1104778 ]  */
/* Soha Wagdy  --  17 Dec 2020 -- Close cross review points [artf1138952]     */
/* Soha Wagdy  --  27 Dec 2020 -- Fixing APR [artf1162990] for Mean Filter    */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 24 OCT 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 24 OCT 2016 */
/*                                                                            */
/******************************************************************************/

#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HPWM
/******************************************************************************/
/*                          Header Files included                             */
/******************************************************************************/
#include "LBTY_int.h"
#include "LMATH_int.h"
#include "LFIL_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HPWM.h"
#include "HFIC_IoHwAb.h"
#endif

#include "MFIC.h"
#include "SFIC.h"

#include "HPWM_int.h"
#include "HPWM_priv.h"
#include "HPWM_cfg.h"

#if HPWM_u8VARIANT_NB > 1U
   #include "SVAR_int.h"
#endif

/******************************************************************************/
/*                              zone variable                                 */
/******************************************************************************/






/******************************************************************************/
/* Variables specific for PWM output                                          */
/******************************************************************************/
#ifdef BSW_PWM_OUT
/******************************************************************************/
/* Software active variant pointer for Output Channels                        */
/******************************************************************************/
static HPWM_tstrOutCompConfig* HPWM_pstrOutSwVariant;
/******************************************************************************/
/* Buffer contains output PWM channels values                                 */
/******************************************************************************/
static u16 HPWM_au16OutPwmDutyVal[HPWM_u8OUT_NB];

#endif

/******************************************************************************/
/* Variables specific for PWM input                                           */
/******************************************************************************/
#ifdef BSW_PWM_IN

/******************************************************************************/
/* Software active variant pointer for Input Channels                         */
/******************************************************************************/
static HPWM_tstrInCompConfig* HPWM_pstrInSwVariant;

/******************************************************************************/
/* Buffer contains Input PWM channels values                                  */
/******************************************************************************/
static u8 HPWM_au8PwmInChStatus[HPWM_u8IN_NB];

#if HPWM_MIN_RUNNABLES_COUNT > 1U
/******************************************************************************/
/* Buffer contains input PWM runnable counter                                 */
/******************************************************************************/
static u8 HPWM_au8PwmInCount[HPWM_u8IN_NB];
#endif

/* Buffer contains Input PWM channels values                                  */
/******************************************************************************/
static HPWM_tstrInPwmCh HPWM_astreInPwmUnfiltered[HPWM_u8IN_NB];

/******************************************************************************/
/* Buffer contains Input PWM channels filtered duty cycle values              */
/******************************************************************************/
static LFIL_tstrFilterData HPWM_astreInPwmDutyFiltred[HPWM_u8IN_NB];

/******************************************************************************/
/* Buffer contains Input PWM channels filtered period values                  */
/******************************************************************************/
static LFIL_tstrFilterData HPWM_astreInPwmPeriodFiltred_us[HPWM_u8IN_NB];
static LFIL_tstrFilterData HPWM_astreInPwmPeriodFiltred_ms[HPWM_u8IN_NB];

/******************************************************************************/
/* Buffer contains Input PWM channels filtered period types                   */
/******************************************************************************/
static LFIL_tstrFilterData HPWM_astreInPwmTypeFiltred[HPWM_u8IN_NB];

#endif /* BSW_PWM_IN */

/******************************************************************************/
/*                              zone function                                 */
/******************************************************************************/

/******************************************************************************/
/* !Description : Initialize component parameters                             */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_001-V02                                                            */
/******************************************************************************/
void HPWM_vidInit(void)
{
   /* Software active variant Number                                             */
   u8 u8SwVariantLoc = 0;

   /* Loop Index */
   u8 u8IdxLoc;

#ifdef BSW_PWM_IN
   /* Variable to hold the return status of any function */
   u8 enuErrorStatusLoc = LBTY_u8MIN_VALUE;

#endif /* BSW_PWM_IN */

#if HPWM_u8VARIANT_NB > 1U
   u8SwVariantLoc = SVAR_u8GetActiveVariant();

   /* if the variant is not correct use the default variant and report error */
   if( u8SwVariantLoc < HPWM_u8VARIANT_NB )
   {
      /* Variant is correct, do nothing */
   }
   else
   {
      /* Use default variant */
      u8SwVariantLoc = HPWM_u8DEFAULT_VARIANT;
      /* Report error */
   }
#else
      u8SwVariantLoc = 0;
#endif


#ifdef BSW_PWM_OUT

  /* !Comment : set configurations to load according to sw variant returned */
  HPWM_pstrOutSwVariant = &HPWM_astrOutVariantConfig[u8SwVariantLoc];

   /* Initialize the local array for pwm out values */
#if HPWM_REFRESH_DUTY_ENABLE == HPWM_REFRESH_ENABLED
   /* !Comment : loop for all channels */
   for (u8IdxLoc = 0; u8IdxLoc < HPWM_pstrOutSwVariant->HPWM_ku8OutChNbrPerVariant; u8IdxLoc++)
   {
      /* Initialize Duty cycle for pwm out values */
      HPWM_au16OutPwmDutyVal[u8IdxLoc] =(HPWM_pstrOutSwVariant->HPWM_pstrOutChRefreshConfig)[u8IdxLoc].u16InitialDutyCycle;
   }
#endif
#endif

#ifdef BSW_PWM_IN

  /* !Comment : set configurations to load according to sw variant returned */
  HPWM_pstrInSwVariant = &HPWM_astrInVariantConfig[u8SwVariantLoc];

  /* !Comment : loop for all channels */
  for (u8IdxLoc = 0; u8IdxLoc < HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant; u8IdxLoc++)
  {
     /* !Comment : Initialize un-filtered buffer */
      HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_us = LBTY_u16MIN_VALUE;
      HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_ms = LBTY_u16MIN_VALUE;
      HPWM_astreInPwmUnfiltered[u8IdxLoc].u16DutyCycle = LBTY_u16MIN_VALUE;
      HPWM_astreInPwmUnfiltered[u8IdxLoc].enuPeriodUnit = HPWM_us;

     /* !Comment : Initialize filtered and duty cycle value */
     enuErrorStatusLoc = (u8)LFIL_enuInitFilSamples( &HPWM_astreInPwmDutyFiltred[u8IdxLoc],
                             HPWM_astreInPwmUnfiltered[u8IdxLoc].u16DutyCycle,
                             ((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxLoc]).u8NumOfSamples);

     /* !Comment : check on returned status error */
     if((u8)LBTY_OK != enuErrorStatusLoc)
     {
        /* report an Error */
     }
     else
     {
        /* do nothing */
     }

      /* !Comment : Initialize filtered and frequency value (microseconds unit) */
      enuErrorStatusLoc = (u8)LFIL_enuInitFilSamples( &HPWM_astreInPwmPeriodFiltred_us[u8IdxLoc],
         HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_us,
         ((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxLoc]).u8NumOfSamples);

      /* !Comment : Initialize filtered and frequency value (milliseconds unit) */
      enuErrorStatusLoc = (enuErrorStatusLoc | (u8)LFIL_enuInitFilSamples( &HPWM_astreInPwmPeriodFiltred_ms[u8IdxLoc],
         HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_ms,
         ((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxLoc]).u8NumOfSamples));

      /* !Comment : Initialize Majority buffer for filtered input period type */
      enuErrorStatusLoc = (enuErrorStatusLoc | (u8)LFIL_enuInitFilSamples( &HPWM_astreInPwmTypeFiltred[u8IdxLoc],
         (u16)HPWM_astreInPwmUnfiltered[u8IdxLoc].enuPeriodUnit,
         ((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxLoc]).u8NumOfSamples));

    /* !Comment : check on returned status error */
    if((u8)LBTY_OK != enuErrorStatusLoc)
    {
       /* report an Error */
    }
    else
    {
       /* do nothing */
    }

    /* !Comment : Initialize channel state */
    HPWM_au8PwmInChStatus[u8IdxLoc] = MFIC_ICU_CH_IDLE_STATE;
    
#ifdef AUTOSAR_USED
    /* !Comment : Enable signal measurement of current channel */
  /*  Icu_StartSignalMeasurement(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChNbr);*/
    MFIC_enuIcuStartSignalMeasurement(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChNbr);
#endif /* AUTOSAR_USED */
  }
#endif   /* BSW_PWM_IN */

}

#ifdef BSW_PWM_IN
/******************************************************************************/
/* !Description : update input PWM value and apply filtration                 */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_002-V04                                     */
/******************************************************************************/
void HPWM_vidRunnable(void)
{

   /* !Comment : Local Error status  */
     u8 u8ErrStatusLoc = LBTY_u8MIN_VALUE;
     /* Loop Index */
     u8 u8IdxLoc = LBTY_u8MIN_VALUE;
     /* !Comment : Duty cycle holder */
     MFIC_tstrDutyCycleValues strPwmCh;

     /* for all input channels */
     for (u8IdxLoc = LBTY_u8MIN_VALUE; u8IdxLoc < HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant; u8IdxLoc++)
     {
        /* !Comment : Check if Duty Cycle needed to be updated */
        if(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChMode == HPWM_u8IN_CH_MODE_DUTY_CYCLE)
        {
           /* !Comment : Call get Duty Cycle */
           u8ErrStatusLoc = (u8)MFIC_enuIcuGetDutyCycle(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChNbr
                                                           , &strPwmCh);
        }
        else
        {
           /* !Comment : Call get Time Elapsed */
           u8ErrStatusLoc = (u8)MFIC_enuIcuGetTimeElapsed(((
                  HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChNbr , &(strPwmCh.MFIC_u32IcuPeriodTime));
        } /* !Comment :  ToDo -> assess the need to check on the return of MFIC_enuIcuGetTimeElapsed  */

        /* !Comment : Get Channel status */
        u8ErrStatusLoc = (u8ErrStatusLoc | (u8)MFIC_enuIcuGetInputState(((
                   HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChNbr, &HPWM_au8PwmInChStatus[u8IdxLoc]));

        /* !Comment : Check if error status returned is LBTY_OK ? */
        if( (u8ErrStatusLoc == (u8)LBTY_OK))
        {
           /* !Comment : Check if input pwm channel is in idle state ? */
         if(HPWM_au8PwmInChStatus[u8IdxLoc] == MFIC_ICU_CH_IDLE_STATE )
         {
#if HPWM_MIN_RUNNABLES_COUNT > 1U
            /* !Comment : increase counter by 1 */
            HPWM_au8PwmInCount[u8IdxLoc]++;

            /* !Comment : Check if counter is less than minimum threshold ? */
            if(HPWM_au8PwmInCount[u8IdxLoc] <= HPWM_MIN_RUNNABLES_COUNT)
            {
               /* !Comment : Do nothing */
            }
            else
            {
               /* !Comment : call private function to calculate period and duty */
               vidCalculateInPeriodandDuty(u8IdxLoc, &strPwmCh);

               /* !Comment : Reset counter to zero */
               HPWM_au8PwmInCount[u8IdxLoc] = LBTY_u8MIN_VALUE;
            }
#else
            /* !Comment : call private function to calculate period and duty */
            vidCalculateInPeriodandDuty(u8IdxLoc, &strPwmCh);
#endif
         }
         else
         {
            /* !Comment : call private function to calculate period and duty */
            vidCalculateInPeriodandDuty(u8IdxLoc, &strPwmCh);

#if HPWM_MIN_RUNNABLES_COUNT > 1U
            /* !Comment : Reset counter to zero */
            HPWM_au8PwmInCount[u8IdxLoc] = LBTY_u8MIN_VALUE;
#endif
         }
       }
       /* !Comment :else (Defect State) */
       else
       {
           /* !Comment : set period with defect period value */
           HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_us = HPWM_u16DEFECT_PER_VAL;

           /* !Comment : set period with defect period value */
           HPWM_astreInPwmUnfiltered[u8IdxLoc].u16Period_ms = HPWM_u16DEFECT_PER_VAL;

           /* !Comment : set duty cycle with defect duty cycle value */
           HPWM_astreInPwmUnfiltered[u8IdxLoc].u16DutyCycle = HPWM_u16DEFECT_DUTY_VAL;

#if HPWM_MIN_RUNNABLES_COUNT > 1U
         /* !Comment : Reset counter to zero */
         HPWM_au8PwmInCount[u8IdxLoc] = LBTY_u8MIN_VALUE;
#endif
       }

#if HPWM_MIN_RUNNABLES_COUNT > 1U
      /* !Comment : check if counter equals zero */
      if(HPWM_au8PwmInCount[u8IdxLoc] == LBTY_u8MIN_VALUE)
      {
#endif

          /* !Comment : Update filtered value of period */
          vidUpdateInFilteredPeriod(u8IdxLoc);

          /* !Comment : Check if Duty Cycle needed to be updated */
          if(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8IdxLoc]).u8ChMode == HPWM_u8IN_CH_MODE_DUTY_CYCLE)
          {
             /* !Comment : Update filtered value of Duty */
             vidUpdateInDutyCycle(u8IdxLoc);
          }
          else
          {
              /* !Comment : Do Nothing */
          }
#if HPWM_MIN_RUNNABLES_COUNT > 1U
      }
      else
      {
         /* !Comment : Do Nothing */
      }
#endif
     }

#if HPWM_ALIVENESS_SUPERVISSION == HPWM_u8CP_ENABLED
     /* !Comment : report check point reached */
     u8ErrStatusLoc = (u8)SFIC_enuHpwmCP();

#if (HPWM_u32DET_REPORTING == HPWM_u32DET_USED)
     /* !Comment : check on returned status error */
     if( (u8)LBTY_OK != u8ErrStatusLoc)
     {
        /*Report an Error*/
     }
     else
     {
        /*Do Nothing */
     }
#endif
#endif

}
#endif /* BSW_PWM_IN */

/******************************************************************************/
/* !Description : This function return the HPWM software version information  */
/* !Input       : pVersionInfo -> Pointer to return the version information   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_003-V01                                                            */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetVersionInfo(LBTY_tstrVersionInfoType *pVersionInfo)
{
   /* Buffer contains the software module version                                */
   LBTY_tstrVersionInfoType strVersionLoc = {HPWM_u16VendorID, HPWM_u16ModuleID, HPWM_u8SwMajorVersion,
                                                                     HPWM_u8SwMinorVersion, HPWM_u8SwPatchVersion};

  LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK; /* Return error status */

  /* Check the pointer allocation */
  if(LBTY_NULL != pVersionInfo)
  {
    pVersionInfo->u16VendorID      = strVersionLoc.u16VendorID;
    pVersionInfo->u16ModuleID      = strVersionLoc.u16ModuleID;
    pVersionInfo->u8SwMajorVersion = strVersionLoc.u8SwMajorVersion;
    pVersionInfo->u8SwMinorVersion = strVersionLoc.u8SwMinorVersion;
    pVersionInfo->u8SwPatchVersion = strVersionLoc.u8SwPatchVersion;

  /* Everything is ok return OK */
    enuErrStatusLoc = LBTY_OK;
  }
  else
  {
    /* Notify null pointer error */
    enuErrStatusLoc = LBTY_NULL_POINTER;
  }

  /* Return Error status */
  return(enuErrStatusLoc);
}

#ifdef BSW_PWM_OUT
#if HPWM_REFRESH_DUTY_ENABLE == HPWM_REFRESH_ENABLED
/******************************************************************************/
/* !Description : refresh output PWM value                                    */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_010-V02                                     */
/******************************************************************************/
void HPWM_vidRefreshOutputDutyRunnable(void)
{

   /* !Comment : Local duty variable */
   u8 u8IdxLoc = LBTY_u8MIN_VALUE;

   /* !Comment : loop for all channels */
   for (u8IdxLoc = LBTY_u8MIN_VALUE; u8IdxLoc < HPWM_pstrOutSwVariant->HPWM_ku8OutChNbrPerVariant; u8IdxLoc++)
   {
      /* !Comment : Check if Duty cycle refresh is enabled for current channel? */
      if((HPWM_pstrOutSwVariant->HPWM_pstrOutChRefreshConfig)[u8IdxLoc].enuRefreshEnable == LBTY_TRUE)
      {
         /* !Comment : Enter Critical Section */
         SFIC_vidEnterCriticalZone();

         /* !Comment : Set the duty cycle of the current channel to the saved value */
         MFIC_enuPwmSetDutyCycle(((HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8IdxLoc]).u8ChannelNbr,
            HPWM_au16OutPwmDutyVal[u8IdxLoc]);

         /* !Comment : Exit Critical Section */
         SFIC_vidLeaveCriticalZone();
      }
      else
      {
         /* !Comment : Do Nothing */
      }
   }
}
#endif

/******************************************************************************/
/* !Description : Set duty cycle for output PWM channel                       */
/* !Input       : u8ChannelCpy    -> Channel index                            */
/*                u16DutyCycleCpy -> Duty cycle value to set                  */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_004-V02                                     */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuSetOutDutyCycle (u8 u8ChannelCpy, u16 u16DutyCycleCpy)
{
   /* !Comment : Local error status */
   LBTY_tenuErrorStatus enuRetResult = LBTY_OK;

   /* !Comment : Local duty variable */
   u16 u16OutDutyLoc = LBTY_u16MIN_VALUE;

   /* !Comment : Check if channel number is valid */
   if (u8ChannelCpy < (HPWM_pstrOutSwVariant->HPWM_ku8OutChNbrPerVariant))
   {
      /* !Comment : Check id duty cycle value is valid */
      if(u16DutyCycleCpy <= HPWM_u16MAXIMMUM_DUTY_CYCLE)
      {
         /* !Comment : Calculate the duty cycle  */
         u16OutDutyLoc = u16HpwmCalculateDuty(u8ChannelCpy, u16DutyCycleCpy);

         /* !Comment : Call Set duty cycle with requested duty */
         enuRetResult = MFIC_enuPwmSetDutyCycle(((
            HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).u8ChannelNbr, u16OutDutyLoc);

         /* !Comment : Check if return status is OK? */
         if(enuRetResult == LBTY_OK)
         {
            /* !Comment : Save the output duty cycle in Out buffer  */
            HPWM_au16OutPwmDutyVal[u8ChannelCpy] = u16OutDutyLoc;
         }
         else
         {
            /* !Comment : Couldn't set the output duty  */
         }
      }
      /* !Comment : Invalid Duty Cycle Value */
      else
      {
         /* !Comment : Report error */
         enuRetResult = LBTY_NOK;
      }
   }
   /* !Comment : Invalid Channel Number */
   else
   {
      /* !Comment : Report error */
      enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
   }

   /* !Comment : Return error status */
   return enuRetResult;
}

/******************************************************************************/
/* !Description : Set duty and period for output PWM channel                  */
/* !Input       : u8ChannelCpy    -> Channel index                            */
/*                u32PeriodCpy    -> Period value to set                      */
/*                u16DutyCpy      -> Duty to be set                           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :   Covers_SWC_HPWM_005-V02                                                          */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuSetOutPeriodAndDuty (u8 u8ChannelCpy, u16 u16PeriodCpy, u16 u16DutyCpy)
{
   /* !Comment : Local error status */
  LBTY_tenuErrorStatus enuRetResult = LBTY_OK;
  /* !Comment : local period variable */
  u32 u32PwmPeriodTicksLoc = (u32)0;
  /* !Comment : Local holder of calculated duty cycle */
  u16 u16OutDutyLoc = LBTY_u16MIN_VALUE;

  /* !Comment : Check if the required channel index is correct */
  if (u8ChannelCpy < (HPWM_pstrOutSwVariant->HPWM_ku8OutChNbrPerVariant))
  {
     /* !Comment : Calculate the period in ticks */
     /* !Comment : Ticks = (Clock * PeriodCoy) / Clock Prescaler */
     u32PwmPeriodTicksLoc = (u32)(((u32)u16PeriodCpy * (u32)(((
                                   HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).u16ChannelClockMHz)  ) / (
                                      ((HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).u16ChannelPrecaler));

     /* !Comment : Check if Period Ticks within HW limits */
     if( (u32PwmPeriodTicksLoc > (((HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).u32MaxTicks) ) ||
                                                                       (u16DutyCpy > HPWM_u16MAXIMMUM_DUTY_CYCLE) )
     {
        /* !Comment : Period too big, return NOK */
        enuRetResult = LBTY_NOK;
     }
     else
     {
        /* !Comment : Calculate the duty cycle  */
        u16OutDutyLoc = u16HpwmCalculateDuty(u8ChannelCpy, u16DutyCpy);
        /* !Comment : Call DPWM to set required period */
        enuRetResult = MFIC_enuPwmSetPeriodAndDuty(((
                                         HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).u8ChannelNbr,
                                                                                 u32PwmPeriodTicksLoc, u16OutDutyLoc);
        /* !Comment : If return is OK  */
        if(enuRetResult == LBTY_OK)
         {
           /* !Comment : set duty cycle value  */
            HPWM_au16OutPwmDutyVal[u8ChannelCpy] = u16OutDutyLoc;
         }
         else
         {
            /* !Comment : Couldn't set the output duty  */
         }
      }
   }
  /* !Comment : channel index is invalid */
  else
  {
     /* !Comment : report error */
     enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
  }

  /* !Comment : Return error status */
  return (enuRetResult);
}


/******************************************************************************/
/* !Description : Calculate Duty Cycle                                        */
/* !Input       : u8ChannelCpy -> channel number                              */
/*                u16DutyCycleCpy -> Duty Cycle value                         */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
u16 u16HpwmCalculateDuty (u8 u8ChannelCpy, u16 u16DutyCycleCpy)
{
   /* !Comment : Local value to hold calculated Duty cycle */
   u16 u16LocDutyValue = LBTY_u16MIN_VALUE;

   /* !Comment : local temp variable */
   u32 u32tempVal = (u32)0;

   /* Variable to hold the return of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_OK;

   /* !Comment : Calculate the duty cycle  */
   /* !Comment : duty = ICU_duty * 0xFFFF / 0x2710 */
   enuErrorStatusLoc = LMATH_enuMulU16ByU16ToU32(&u32tempVal, u16DutyCycleCpy, u16MAX_ICU_DUTY);

   /* !Comment : check on returned status error */
   if(LBTY_OK != enuErrorStatusLoc)
   {
      /* report an error */
   }
   else
   {
      /* do nothing */
   }

   enuErrorStatusLoc = LMATH_enuDivU32ByU16SatU16Max(&u16LocDutyValue, u32tempVal,
                                       HPWM_u16MAXIMMUM_DUTY_CYCLE, LMATH_ROUND_NEAREST, HPWM_u16MAXIMMUM_DUTY_CYCLE);
   if(LBTY_OK != enuErrorStatusLoc)
   {
      /* report an error */
   }
   else
   {
      /* do nothing */
   }

   /* !Comment : Channel is Active Low */
   if(((HPWM_pstrOutSwVariant->HPWM_pstrChConfig)[u8ChannelCpy]).enuActiveLevel == HPWM_u8ACTIVE_LOW)
   {
      /* !Comment : Calculate the inverse of the duty Cycle */
      u16LocDutyValue = u16MAX_ICU_DUTY - u16LocDutyValue;
   }
   /* !Comment : Channel is Active High */
   else
   {
      /* !Comment : Do nothing */
   }

   /* !Comment : return calculated duty cycle value */
   return u16LocDutyValue;
}

#endif /* BSW_PWM_OUT */

#ifdef BSW_PWM_IN
/******************************************************************************/
/* !Description : Get duty cycle for input PWM channel                        */
/* !Input       : u8ChannelCpy -> Channel index                               */
/*                pu16DutyCpy  -> Pointer to return duty cycle value          */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_006-V02                                                            */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetInDutyCycle (u8 u8ChannelCpy, u16* pu16DutyCpy)
{
  /* Variable to hold the error status return */
  LBTY_tenuErrorStatus enuRetResult = LBTY_OK;

  /* !Comment : Check if the pointer passed is correct */
  if(LBTY_NULL != pu16DutyCpy)
  {
     /* !Comment : Check if the required channel index is correct */
     if (u8ChannelCpy < (HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant))
     {
        /* !Comment : return unfiltered duty cycle from buffer */
       *pu16DutyCpy = HPWM_astreInPwmUnfiltered[u8ChannelCpy].u16DutyCycle;
     }
     /* !Comment : Wrong index, return not OK */
     else
     {
        /* !Comment : return error status */
        enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
     }
  }
  else
  {
     /* !Comment : report error */
     enuRetResult = LBTY_NULL_POINTER;
  }

  /* !Comment : return error status */
  return (enuRetResult);
}

/******************************************************************************/
/* !Description : Get period for input PWM channel                            */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu32PeriodCpy   -> Pointer to return period value           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :   Covers_SWC_HPWM_007-V02                                                          */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetInPeriod(u8 u8ChannelCpy, u32* pu32PeriodCpy)
{
  /* Variable to hold the error status return */
  LBTY_tenuErrorStatus enuRetResult = LBTY_OK;

  /* !Comment : Check if the pointer passed is correct */
  if(LBTY_NULL != pu32PeriodCpy)
  {
     /* !Comment : Check if the required channel index is correct */
     if (u8ChannelCpy < (HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant))
     {
        /* !Comment : Check if the period unit is in microseconds? */
         if(HPWM_astreInPwmUnfiltered[u8ChannelCpy].enuPeriodUnit == HPWM_us)
         {
               /* !Comment : return unfiltered period from buffer */
               *pu32PeriodCpy = HPWM_astreInPwmUnfiltered[u8ChannelCpy].u16Period_us;
         }
         else
         {
            /* !Comment : return unfiltered period from buffer after multiplying conversion value */
            *pu32PeriodCpy = ((u32MS_TO_US)*((u32)HPWM_astreInPwmUnfiltered[u8ChannelCpy].u16Period_ms));
         }
      }
      /* !Comment :  Wrong index, return not OK */
      else
      {
        /* !Comment : report error */
        enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
      }
  }
  else
  {
     /* !Comment : report error */
     enuRetResult = LBTY_NULL_POINTER;
  }

   /* !Comment : return error status  */
   return (enuRetResult);
}

/******************************************************************************/
/* !Description : Get filtered duty cycle for input PWM channel               */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu16DutyCpy   -> Pointer to return duty cycle value         */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HPWM_008-V02                                                            */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetFilteredInDuty(u8 u8ChannelCpy, u16* pu16DutyCpy)
{
  /* Variable to hold the error status return */
  LBTY_tenuErrorStatus enuRetResult = LBTY_OK;

  /* !Comment : Check if the pointer passed is correct */
  if(LBTY_NULL != pu16DutyCpy)
  {
     /* !Comment : Check if the required channel index is correct */
     if (u8ChannelCpy < (HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant))
     {
        /* !Comment : return filtered duty from buffer */
       *pu16DutyCpy = HPWM_astreInPwmDutyFiltred[u8ChannelCpy].u16FilteredData;
     }
     /* !Comment : Wrong index, return not OK */
     else
     {
        /* !Comment : report error */
        enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
     }
  }
  else
  {
     /* !Comment : report error */
     enuRetResult = LBTY_NULL_POINTER;
  }

  /* !Comment : return error status */
  return (enuRetResult);
}

/******************************************************************************/
/* !Description : Get filtered period for input PWM channel                   */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu16PeriodCpy   -> Pointer to return period value           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :  Covers_SWC_HPWM_009-V02                                                           */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetFilteredInPeriod(u8 u8ChannelCpy, u32* pu32PeriodCpy)
{
  /* Variable to hold the error status return */
  LBTY_tenuErrorStatus enuRetResult = LBTY_OK;

  /* Variable to hold the filtration result for period type */
  u16 u16FiltTypeLoc = LBTY_u16MIN_VALUE;

  /* !Comment : Check if the pointer passed is correct */
  if(LBTY_NULL != pu32PeriodCpy)
  {
      /* !Comment : Check if the required channel index is correct */
      if (u8ChannelCpy < (HPWM_pstrInSwVariant->HPWM_ku8InChNbrPerVariant))
      {
         /* !Comment :  Get filtered type */
         u16FiltTypeLoc = HPWM_astreInPwmTypeFiltred[u8ChannelCpy].u16FilteredData;

         /* !Comment :  If filtration type returned is microseconds */
         if(u16FiltTypeLoc == (u16)HPWM_us)
         {
               /* !Comment : return filtered period from buffer */
               *pu32PeriodCpy = HPWM_astreInPwmPeriodFiltred_us[u8ChannelCpy].u16FilteredData;
         }
         else
         {
            /* !Comment : return filtered period from buffer after multiplying conversion value */
            *pu32PeriodCpy = ((u32MS_TO_US)*((u32)HPWM_astreInPwmPeriodFiltred_ms[u8ChannelCpy].u16FilteredData));
         }
      }
     /* !Comment : Wrong index, return not OK */
     else
     {
        /* !Comment : report error */
        enuRetResult = LBTY_INDEX_OUT_OF_RANGE;
     }
  }
  else
  {
     /* !Comment : report error */
     enuRetResult = LBTY_NULL_POINTER;
  }

  /* !Comment : return error status */
  return (enuRetResult);
}

/******************************************************************************/
/* !Description : Update Input Duty cycle                                     */
/* !Input       : u8IdxCpy -> input channel index                             */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidUpdateInDutyCycle(u8 u8IdxCpy)
{
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_OK;

   /* !Comment :  check the type of the filtration */
   switch(((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxCpy]).u8DutyCycleFilterType)
   {
      /* !Comment :  Majority filter, round the value then apply the filter */
      case HPWM_u8MajorityFilter:
         /* !Comment :  Apply rounding */
         HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle = (u16)u32Round((u32)HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle,
                                                         &((HPWM_pstrInSwVariant->HPWM_pstrInPwmRoundDuty)[u8IdxCpy]));
         /* !Comment :  Apply Majority filtration */
         enuErrorStatusLoc = LFIL_enuMajorityFilter( &HPWM_astreInPwmDutyFiltred[u8IdxCpy],
                                                     HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle,
                                                     (HPWM_pstrInSwVariant->HPWM_pu8MajorityCapDuty)[u8IdxCpy]);

         /* !Comment : check on returned status error */
         if(LBTY_OK != enuErrorStatusLoc)
         {
            /* report an Error */
         }
         else
         {
            /* do nothing */
         }
         break;

      /* !Comment :  Consecutive filter, round the value then apply the filter */
      case HPWM_u8ConsecutiveFilter:
        /* !Comment :  Apply rounding */
         HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle = (u16)u32Round((u32)HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle,
                                                         &((HPWM_pstrInSwVariant->HPWM_pstrInPwmRoundDuty)[u8IdxCpy]));
         /* !Comment :  Apply consecutive filtration */
         enuErrorStatusLoc = LFIL_enuConsecutiveVal( &HPWM_astreInPwmDutyFiltred[u8IdxCpy],
                                                     HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle,
                                                     (HPWM_pstrInSwVariant->HPWM_pu8ConsecutiveCapDuty)[u8IdxCpy]);
         /* !Comment : check on returned status error */
         if(LBTY_OK != enuErrorStatusLoc)
         {
            /* report an Error */
         }
         else
         {
            /* do nothing */
         }
         break;

      /* !Comment :  Mean filter */
      case HPWM_u8MeanSamplesFilter:
        (void) LFIL_enuMeanSamples( &HPWM_astreInPwmDutyFiltred[u8IdxCpy],
                                                              HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle );
         break;

      /* !Comment :  No filtration required, set the filtered value equals to non filtered value */
      case HPWM_u8NoFilter:
         HPWM_astreInPwmDutyFiltred[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle;
         break;

      /* !Comment :  Filter type is not correct, report error and set the filtered value as unfiltered*/
      default:
         HPWM_astreInPwmDutyFiltred[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16DutyCycle;
         break;
   }
}

/******************************************************************************/
/* !Description : Update Input filtered frequency                             */
/* !Input       : u8IdxCpy -> input channel index                             */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidUpdateInFilteredPeriod(u8 u8IdxCpy)
{
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_OK;

   /* !Comment :  check the type of the filtration */
   switch(((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxCpy]).u8FrequencyFilterType)
   {
      /* !Comment :  Majority filter, round the value then apply the filter */
      case HPWM_u8MajorityFilter:

         /* !Comment :  Apply Majority filtration on period type to see which type was called more than half the time */
         (void)LFIL_enuMajorityFilter( &HPWM_astreInPwmTypeFiltred[u8IdxCpy],
                                   (u16)HPWM_astreInPwmUnfiltered[u8IdxCpy].enuPeriodUnit,
                                   (HPWM_pstrInSwVariant->HPWM_pu8MajorityCapPeriod)[u8IdxCpy]);

         /* !Comment :  Apply Majority filtration */
         (void)LFIL_enuMajorityFilter( &HPWM_astreInPwmPeriodFiltred_ms[u8IdxCpy],
            HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_ms,
            (HPWM_pstrInSwVariant->HPWM_pu8MajorityCapPeriod)[u8IdxCpy]);


         /* !Comment :  Apply Majority filtration */
         (void)LFIL_enuMajorityFilter( &HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy],
            HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_us,
            (HPWM_pstrInSwVariant->HPWM_pu8MajorityCapPeriod)[u8IdxCpy]);

         break;

      /* !Comment :  Consecutive filter, round the value then apply the filter */
      case HPWM_u8ConsecutiveFilter:

         /* !Comment :  Apply Majority filtration on period type to see which type was called more than half the time */
         (void)LFIL_enuConsecutiveVal( &HPWM_astreInPwmTypeFiltred[u8IdxCpy],
                                   (u16)HPWM_astreInPwmUnfiltered[u8IdxCpy].enuPeriodUnit,
                                   (HPWM_pstrInSwVariant->HPWM_pu8ConsecutiveCapPeriod)[u8IdxCpy]);

         /* !Comment :  Apply consecutive filtration */
         (void)LFIL_enuConsecutiveVal( &HPWM_astreInPwmPeriodFiltred_ms[u8IdxCpy],
            HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_ms,
            (HPWM_pstrInSwVariant->HPWM_pu8ConsecutiveCapPeriod)[u8IdxCpy]);

         /* !Comment :  Apply consecutive filtration */
         (void)LFIL_enuConsecutiveVal( &HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy],
            HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_us,
            (HPWM_pstrInSwVariant->HPWM_pu8ConsecutiveCapPeriod)[u8IdxCpy]);

         break;

      /* !Comment :  Mean filter */
      case HPWM_u8MeanSamplesFilter:
         /* !Comment :  Apply consecutive filtration on period type to check if the same type was called over all the samples */
         enuErrorStatusLoc = LFIL_enuConsecutiveVal( &HPWM_astreInPwmTypeFiltred[u8IdxCpy],
                                   (u16)HPWM_astreInPwmUnfiltered[u8IdxCpy].enuPeriodUnit,
                                      ((HPWM_pstrInSwVariant->HPWM_pstrInPwmFilter)[u8IdxCpy]).u8NumOfSamples);

         /* !Comment :  Apply Mean filtration for period in milliseconds */
         (void) LFIL_enuMeanSamples(&HPWM_astreInPwmPeriodFiltred_ms[u8IdxCpy], HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_ms);

         /* !Comment : check on returned status error */
         if(LBTY_OK != enuErrorStatusLoc)
         {
            HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy].u16FilteredData = HPWM_u16DEFECT_PER_VAL;
            HPWM_astreInPwmTypeFiltred[u8IdxCpy].u16FilteredData = (u16)HPWM_ms;
         }
         else
         {
            /* !Comment :  Apply Mean filtration for period in microseconds */
            (void) LFIL_enuMeanSamples(&HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy], HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_us);
         }
         break;

         /* !Comment :  No filtration required, set the filtered value equals to non filtered value */
      case HPWM_u8NoFilter:
         /* !Comment :  Return period type without filtration */
         HPWM_astreInPwmTypeFiltred[u8IdxCpy].u16FilteredData = (u16)HPWM_astreInPwmUnfiltered[u8IdxCpy].enuPeriodUnit;
         /* !Comment :  Return period in microseconds without filtration */
         HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_us;
         /* !Comment :  Return period in milliseconds without filtration */
         HPWM_astreInPwmPeriodFiltred_ms[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_ms;
         break;

         /* !Comment :  Filter type is not correct, report error and set the filtered value as unfiltered*/
      default:
         /* !Comment :  Return period type without filtration */
         HPWM_astreInPwmTypeFiltred[u8IdxCpy].u16FilteredData = (u16)HPWM_astreInPwmUnfiltered[u8IdxCpy].enuPeriodUnit;
         /* !Comment :  Return period in microseconds as is */
         HPWM_astreInPwmPeriodFiltred_us[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_us;
         /* !Comment :  Return period in milliseconds as is */
         HPWM_astreInPwmPeriodFiltred_ms[u8IdxCpy].u16FilteredData = HPWM_astreInPwmUnfiltered[u8IdxCpy].u16Period_ms;
         break;
   }
}

/******************************************************************************/
/* !Description : Get filtered frequency for input PWM channel                */
/* !Input       : u32OldValueCpy  -> Value to round                           */
/*                HPWM_tstrRoundingConfig -> Pointer to rounding configuration*/
/* !Output      : u32 -> value after rounding                                 */
/* !Scope       : Private                                                     */
/******************************************************************************/
u32 u32Round(u32 u32OldValueCpy, const HPWM_tstrRoundingConfig* strRoundConfigCpy)
{
   /* !Comment : Local result variable */
   u32 u32ResultLoc = u32OldValueCpy;
   /* !Comment : Local Modulus variable */
   u16 u16ModulValueLoc = 0;
   /* !Comment : Local Divider Variable */
   u32 u32DivValueLoc = 0;
   /* !Comment : Local Multiplier variable */
   u32 u32MultValueLoc = 0;

   /* !Comment : Check if rounding factor configured is greater than 1 */
   if ( (strRoundConfigCpy -> u8RoundingFactor) > (u8)1 )
   {
      /* !Comment : Calculate the division reminder  */
      u16ModulValueLoc = (u16) (u32OldValueCpy % (strRoundConfigCpy -> u8RoundingFactor));

      /* !Comment : check if the variable is already rounded */
      if (u16ModulValueLoc != (u16)0)
      {
         /* !Comment : divide value by rounding factor */
         u32DivValueLoc = u32OldValueCpy / (strRoundConfigCpy -> u8RoundingFactor);

         /* !Comment : multiply divided value by rounding factor */
         u32MultValueLoc = u32DivValueLoc * (strRoundConfigCpy -> u8RoundingFactor);

         /* !Comment : switch on the rounding factor */
         switch (strRoundConfigCpy -> u8RoundingType)
         {
            /* !Comment : Case rounding up */
            case HPWM_u8RoundingUp:
               /* !Comment : result is the multiplier + rounding factor */
               u32ResultLoc = u32MultValueLoc + (strRoundConfigCpy -> u8RoundingFactor);
               break;
            /* !Comment : case rounding down */
            case HPWM_u8RoundingDown:
               u32ResultLoc = u32MultValueLoc;
               break;
            /* !Comment : Case Rounding to Nearest */
            case HPWM_u8RoundingNearest:
                  /* !Comment : if the value is in the to half */
                  if((u16ModulValueLoc) >  (u16)(strRoundConfigCpy -> u8RoundingFactor / (u8)2))
                  {
                     /* !Comment : result is multiplier + rounding factor */
                     u32ResultLoc = u32MultValueLoc + (strRoundConfigCpy -> u8RoundingFactor);
                  }
                  /* !Comment : If the value is in the bottom half */
                  else
                  {
                     /* !Comment : result is the multiplier value */
                     u32ResultLoc = u32MultValueLoc;
                  }
                  break;
            default:
               /* Wrong rounding technique, Report error */
               break;
         }
      }
      /* !Comment : Value is already rounded */
      else
      {
         /* No Rounding needed */
      }
   }
   /* !Comment : Wrong rounding factor */
   else
   {
      /* Do nothing */
   }

   /* !Comment : return rounded value */
   return u32ResultLoc;
}

/******************************************************************************/
/* !Description : calculate Period and Duty Cyle for Input PWM channels       */
/* !Input       : u8ChannelIdx: ICU channel index                             */
/*                ptstrPwmCh: pointer to struct holding duty cycle parameters */
/*                            (Active Time, Period Time)                      */
/* !Output      : void                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidCalculateInPeriodandDuty (u8 u8ChannelIdx , const MFIC_tstrDutyCycleValues * ptstrPwmCh)
{
   /* !Comment : Local Error status  */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_NOK;
   /* !Comment : Local Pin Value  */
   u8 u8PinValue= (u8)0;

   /* !Comment : Check if input pwm channel is in active state ? */
   if (HPWM_au8PwmInChStatus[u8ChannelIdx] == MFIC_ICU_CH_ACTIVE_STATE)
   {
      /** !Comment :  Temporary Result Holder for ICU calculation of period and Duty  **/
        u32 u32RsltHldr = 0;

        /* !Comment : Calculate Period = (PeriodTicks * Clock Prescaler Value) / CH clock in MHz */
        (void) LMATH_enuMulU32ByU16ToU32( &u32RsltHldr,/* !Comment :  (PeriodTicks * 10000000) */
           ptstrPwmCh->MFIC_u32IcuPeriodTime,
           ((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8ChannelIdx]).u16ChClockPrescaler
        ); /* !Comment :  ToDo -> assess the need to check on the return of LMATH  */

        (void) LMATH_enuDivU32ByU16SatU32Max ( &u32RsltHldr, /* !Comment :  u32RsltHldr/CH clock  */
           u32RsltHldr,
           ((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8ChannelIdx]).u16ChClockMHz ,
           LMATH_ROUND_NEAREST,
           (u32)HPWM_u16DEFECT_PER_VAL
        ); /* !Comment :  ToDo -> assess the need to check on the return of LMATH  */

        /* !Comment :  Apply rounding */
        u32RsltHldr = u32Round(u32RsltHldr, &((HPWM_pstrInSwVariant->HPWM_pstrInPwmRoundPeriod)[u8ChannelIdx]));

        /*Set the measuring unit*/
       if(u32RsltHldr>=(u32)LBTY_u16MAX_VALUE )
       {
          /* !Comment : Set period type as ms */
          HPWM_astreInPwmUnfiltered[u8ChannelIdx].enuPeriodUnit = HPWM_ms;

          /* !Comment : Save period in us as Max  */
          HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_us  = LBTY_u16MAX_VALUE;
       }
       else
       {
          /* !Comment : Set period type as us */
          HPWM_astreInPwmUnfiltered[u8ChannelIdx].enuPeriodUnit = HPWM_us;

          /* !Comment : Save period in us as is  */
          HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_us  = (u16) u32RsltHldr;
       }

       /* !Comment : Save period in ms after conversion  */
       HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_ms  = (u16) (u32RsltHldr/u32MS_TO_US);

       /* !Comment : check if Channel mode is configured as duty cycle */
      if(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8ChannelIdx]).u8ChMode == HPWM_u8IN_CH_MODE_DUTY_CYCLE)
      {

         /* !Comment : Calculate DutyCycle = (Active Ticks / PeriodTicks) */
         /*  HPWM_astreInPwmUnfiltered[u8IdxLoc].u16DutyCycle = (u16)((strPwmCh.MFIC_u32IcuActiveTime *
          * HPWM_u16MAXIMMUM_DUTY_CYCLE) / strPwmCh.MFIC_u32IcuPeriodTime);*/
         (void ) LMATH_enuMulU32ByU16ToU32( &u32RsltHldr,/* !Comment : Active Ticks */
            ptstrPwmCh->MFIC_u32IcuActiveTime,
            HPWM_u16MAXIMMUM_DUTY_CYCLE
         );/* !Comment :  ToDo -> assess the need to check on the return of LMATH  */
         (void) LMATH_enuDivU32ByU16SatU32Max ( &u32RsltHldr, /* !Comment :  (Active Ticks / PeriodTicks)  */
            u32RsltHldr,
            (u16)ptstrPwmCh->MFIC_u32IcuPeriodTime,
            LMATH_ROUND_NEAREST,
            (u32)HPWM_u16DEFECT_DUTY_VAL
         );/* !Comment :  ToDo -> assess the need to check on the return of LMATH  */

         /* !Comment : Set DutyCycle with result value */
         HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16DutyCycle = (u16)u32RsltHldr;
      }
      else
      {
         /* !Comment : Do nothing  */
      }
   }
   /* !Comment : else check if input pwm channel is in idle state ? */
   else if (HPWM_au8PwmInChStatus[u8ChannelIdx] == MFIC_ICU_CH_IDLE_STATE)
   {
      /* !Comment : set period with Maximum period value */
      HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_us = u16MAX_IN_PERIOD;
      /* !Comment : set period with Maximum period value */
      HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_ms = u16MAX_IN_PERIOD;

      /* !Comment : Read IO pin and determine the duty cycle value */
      enuErrStatusLoc = MFIC_stdGetIoPinValue(((HPWM_pstrInSwVariant->HWPM_pstrInPwmChConfig)[u8ChannelIdx]).u8IOPin,
                                                                                                          &u8PinValue);

      /* !Comment : Check if return code is OK */
      if(enuErrStatusLoc == LBTY_OK)
      {
         /* !Comment : Check if pin is LOW */
         if(u8PinValue == MFIC_u8IO_PIN_LOW)
         {
            /* !Comment : Set duty cycle to Zero 0% */
            HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16DutyCycle = 0x0000;
         }
         /* !Comment : Pin is High */
         else
         {
            /* !Comment : set duty cycle to 100% */
            HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16DutyCycle = HPWM_u16MAXIMMUM_DUTY_CYCLE;
         }
      }
      else
      {
         /* !Comment : To Be Handled */
      }
   }
   else
   {
      /* !Comment : set period with defect period value */
      HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_us = HPWM_u16DEFECT_PER_VAL;

      /* !Comment : set period with defect period value */
      HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16Period_ms = HPWM_u16DEFECT_PER_VAL;
      /* !Comment : set duty cycle with defect duty cycle value */
      HPWM_astreInPwmUnfiltered[u8ChannelIdx].u16DutyCycle = HPWM_u16DEFECT_DUTY_VAL;
   }
}

#endif /* BSW_PWM_IN */
#endif   /* BSW_PWM */
/*************************** E N D (HPWM_prg.c) ******************************/



