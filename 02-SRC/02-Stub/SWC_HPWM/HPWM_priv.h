/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HPWM                                                    */
/* !Description     : Pulse width modulation driver                           */
/*                                                                            */
/* !Module          : HPWM_priv.h                                             */
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
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Ahmed Abdelmageed                                                          */
/*                 26/ 2 / 2019   added private function                      */
/*                                vidCalculateInPeriodandDuty to reduce STMIF */
/*                                of the function HPWM_vidRunnable[artf327887]*/
/*                 28/ 2 / 2019   changed private function 'vidUpdateInPeriod'*/
/*                                name to be 'vidUpdateInFilteredPeriod'      */
/* Ahmed Abdelmageed                                                          */
/*                 08/ 4 / 2019   added conditional macros to protect against */
/*                                unused variable compiler warnings           */
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Ahmed Ramadan-- 8 Nov 2020  -- Min frequency detection ACR [artf1104778 ]  */
/* Soha Wagdy  --  17 Dec 2020  -- Close cross review points [artf1138952]    */
/* Soha Wagdy  --  27 Dec 2020 -- Fixing APR [artf1162990] for Mean Filter    */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 24 OCT 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 24 OCT 2016 */
/*                                                                            */
/******************************************************************************/

#ifndef HPWM_PRIV_H
#define HPWM_PRIV_H


/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/

/* !Description : Measuring unit for Period. (Microseconds / Milliseconds) */
typedef enum
{
   HPWM_us =0,
   HPWM_ms
}HPWM_tenuPeriodMeasUnit;

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/
/******************************************************************************/
/*   Definitions for the software module version                              */
/******************************************************************************/
#define HPWM_u16VendorID               ((u16)59)
#define HPWM_u16ModuleID               ((u16)12)
#define HPWM_u8SwMajorVersion          ((u8)0x01)
#define HPWM_u8SwMinorVersion          ((u8)0x09)
#define HPWM_u8SwPatchVersion          ((u8)0x00)

/******************************************************************************/
/*   configuration to Enable/Disable Check Point in runnable                  */
/******************************************************************************/
#define HPWM_u8CP_ENABLED           (0xFFU)
#define HPWM_u8CP_DISABLED          (0x00U)

/******************************************************************************/
/*   configuration for Filtration mechanisms for PWM IN channels              */
/******************************************************************************/
#define HPWM_u8MeanSamplesFilter   ((u8)0x00)
#define HPWM_u8MajorityFilter      ((u8)0x1F)
#define HPWM_u8ConsecutiveFilter   ((u8)0xE3)
#define HPWM_u8NoFilter            ((u8)0xFC)

/******************************************************************************/
/* Configuration for Rounding Mechanism for PWM IN channels                   */
/******************************************************************************/
#define HPWM_u8RoundingUp          ((u8)0x00)
#define HPWM_u8RoundingDown        ((u8)0x1F)
#define HPWM_u8RoundingNearest     ((u8)0xE3)
#define HPWM_u8NoRounding          ((u8)0xFC)

/******************************************************************************/
/* Configuration for the Channel mode                                         */
/******************************************************************************/
/* !Comment : Configuration for Duty and period channel */
#define HPWM_u8IN_CH_MODE_DUTY_CYCLE   ((u8)0x00)
/* !Comment : C */
#define HPWM_u8IN_CH_MODE_PERIOD_TIME  ((u8)0xFF)

/******************************************************************************/
/* Configuration for Used/Unused channel                                      */
/******************************************************************************/
#define HPWM_u8CH_USED        ((u8)0x00)
#define HPWM_u8CH_NOT_USED    ((u8)0xFF)

/*****************************************************************************/
/* !Comment  : PWM output channel Activity Level                             */
/*****************************************************************************/
#define HPWM_u8ACTIVE_HIGH    ((u8)0xFF)
#define HPWM_u8ACTIVE_LOW     ((u8)0x00)

/*****************************************************************************/
/* !Comment  : SDET usage in runnable                                        */
/*****************************************************************************/
#define HPWM_u32DET_USED      (0x00U)
#define HPWM_u32DET_NOT_USED  (0x01U)

/*****************************************************************************/
/* !Comment  : Maximum Period Output                                         */
/*****************************************************************************/
#define u16MAX_PWM_PERIOD              ((u16)0xFFFFU)

/*****************************************************************************/
/* !Comment  : Maximum duty cycle of ICU                                     */
/*****************************************************************************/
#define u16MAX_ICU_DUTY               ( (u16)0x8000U)

/*****************************************************************************/
/* !Comment  : Maximum Period                                                */
/*****************************************************************************/
#define u16MAX_IN_PERIOD                  ((u16)0xFFFFU)

/*****************************************************************************/
/* !Comment  : Milliseconds to Microseconds Conversion Value                 */
/*****************************************************************************/
#define u32MS_TO_US                       ((u32)1000)

/******************************************************************************/
/* !Comment  : Configuration for Enable/Disable Duty Cycle Refresh            */
/******************************************************************************/
#define HPWM_u32REFRESH_ENABLED        0xAAU
#define HPWM_u32REFRESH_DISABLED       0x55U

/*****************************************************************************/
/********************************* zone constant *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone struct/union *************************/
/*****************************************************************************/

/******************************************************************************/
/*  Structure for PWM IN channels to hold input PWM channels values           */
/******************************************************************************/
typedef struct
{
    u16 u16DutyCycle;    /* Duty cycle for input channels */
    u16 u16Period_us;    /* Period in Microseconds for input channels */
    u16 u16Period_ms;    /* Period in Milliseconds for input channels */
    HPWM_tenuPeriodMeasUnit enuPeriodUnit; /* Period unit Milliseconds/Microseconds */
}HPWM_tstrInPwmCh;

/******************************************************************************/
/*   Structure for PWM IN channel Filtration mechanisms                      */
/******************************************************************************/
typedef struct
{
      u8 u8DutyCycleFilterType;
      u8 u8FrequencyFilterType;
      u8 u8NumOfSamples;
}HPWM_tstrPwmInFilterConfig;

/******************************************************************************/
/*  Structure for Rounding Mechanism                                          */
/******************************************************************************/
typedef struct
{
      u8 u8RoundingFactor;
      u8 u8RoundingType;
}HPWM_tstrRoundingConfig;

/******************************************************************************/
/*  Structure for PWM IN Channel                                              */
/******************************************************************************/
typedef struct{
      u8 u8ChNbr;
      u8 u8IOPin;
      u8 u8ChMode;
      u16 u16ChClockMHz;
      u16 u16ChClockPrescaler;
}HPWM_tstrPwmInChConfig;


/******************************************************************************/
/*   Multiple variants configuration structure for Input Channels             */
/******************************************************************************/
typedef struct{
    const u8 HPWM_ku8InChNbrPerVariant;
    const HPWM_tstrPwmInChConfig* HWPM_pstrInPwmChConfig;
    const HPWM_tstrPwmInFilterConfig* HPWM_pstrInPwmFilter;
    const u8* HPWM_pu8MajorityCapDuty;
    const u8* HPWM_pu8MajorityCapPeriod;
    const u8* HPWM_pu8ConsecutiveCapDuty;
    const u8* HPWM_pu8ConsecutiveCapPeriod;
    const HPWM_tstrRoundingConfig* HPWM_pstrInPwmRoundDuty;
    const HPWM_tstrRoundingConfig* HPWM_pstrInPwmRoundPeriod;
}HPWM_tstrInCompConfig;


/******************************************************************************/
/*   Configuration structure of PWM out Channel                               */
/******************************************************************************/
typedef struct{
  u16 u16ChannelClockMHz;
  u16 u16ChannelPrecaler;
  u8 u8ChannelNbr;
  u8 enuActiveLevel;
  u32 u32MaxTicks;
}HPWM_tstrOutChConfig;

/******************************************************************************/
/*   Runnable Configuration structure for Output Channels                     */
/******************************************************************************/
typedef struct{
      u16              u16InitialDutyCycle;       /* Initial duty that 's output on this signal  */
      LBTY_tenuBoolean enuRefreshEnable;         /* True for enable refresh on this signal, false : disable refresh on this signal*/
}HPWM_tstrOutChRefreshConfig;

/******************************************************************************/
/*   Multiple variants configuration structure for Output Channels            */
/******************************************************************************/
typedef struct{
    const u8 HPWM_ku8OutChNbrPerVariant; /* Number of Output Channels */
    const HPWM_tstrOutChConfig* HPWM_pstrChConfig; /* Configuration structure of PWM out Channel */
    const HPWM_tstrOutChRefreshConfig* HPWM_pstrOutChRefreshConfig; /* Runnable Configuration structure for Output Channels */
}HPWM_tstrOutCompConfig;

/*****************************************************************************/
/********************************* zone variable *****************************/
/*****************************************************************************/


/*****************************************************************************/
/********************************* zone function *****************************/
/*****************************************************************************/

#ifdef BSW_PWM_OUT
/******************************************************************************/
/* !Description : Calculate Duty Cycle                                        */
/* !Input       : u8ChannelCpy -> channel number                              */
/*                u16DutyCycleCpy -> Duty Cycle value                         */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
u16 u16HpwmCalculateDuty (u8 u8ChannelCpy, u16 u16DutyCycleCpy);
#endif /* BSW_PWM_OUT */

#ifdef BSW_PWM_IN

/******************************************************************************/
/* !Description : Update Input Duty cycle                                     */
/* !Input       : u8IdxCpy -> input channel index                             */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidUpdateInDutyCycle(u8 u8IdxCpy);

/******************************************************************************/
/* !Description : Update Input filtered frequency                             */
/* !Input       : u8IdxCpy -> input channel index                             */
/* !Output      : None                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidUpdateInFilteredPeriod(u8 u8IdxCpy);

/******************************************************************************/
/* !Description : Get filtered frequency for input PWM channel                */
/* !Input       : u32OldValueCpy  -> Value to round                           */
/*                HPWM_tstrRoundingConfig -> Pointer to rounding configuration*/
/* !Output      : u32 -> value after rounding                                 */
/* !Scope       : Private                                                     */
/******************************************************************************/
u32 u32Round(u32 u32OldValueCpy, const HPWM_tstrRoundingConfig* strRoundConfigCpy);

/******************************************************************************/
/* !Description : calculate Period and Duty Cyle for Input PWM channels       */
/* !Input       : u8ChannelIdx: ICU channel index                             */
/*                ptstrPwmCh: pointer to struct holding duty cycle parameters */
/*                            (Active Time, Period Time)                      */
/* !Output      : void                                                        */
/* !Scope       : Private                                                     */
/******************************************************************************/
void vidCalculateInPeriodandDuty (u8 u8ChannelIdx , const MFIC_tstrDutyCycleValues * ptstrPwmCh);
#endif /* BSW_PWM_IN */

#endif /* HPWM_PRIV_H */

/************************* E N D (HPWM_priv.h) *******************************/
