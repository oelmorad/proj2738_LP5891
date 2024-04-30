/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HPWM                                                    */
/* !Description     : Pulse width modulation driver                           */
/*                                                                            */
/* !Module          : HPWM_cfg.c                                              */
/* !Revision        : 2.3                                                     */
/* !Date            : 8 Nov 2020                                              */
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
/*             --             --                                              */
/* Ahmed Abdelmageed                                                          */
/*                 25/ 2 / 2019   update the inclusion of SchM_HPWM.h to be   */
/*                                included only if BSW_HPWM_IN is defined     */
/*                                [artf267815]                                */
/* Soha Wagdy  --  14/3/2019   -- Update AUTOSAR headers inclusion            */
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                     */
/* Ahmed Ramadan-- 8 Nov 2020  -- Min frequency detection ACR [artf1104778 ]  */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 24 OCT 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 24 OCT 2016 */
/*                                                                            */
/******************************************************************************/

#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HPWM

#include "LBTY_int.h"
#include "LCTY_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HPWM.h"
#ifdef BSW_PWM_IN
#include "SchM_HPWM.h"
#endif /* BSW_PWM_IN */
#include "HFIC_IoHwAb.h"
#endif

#include "MFIC.h"

#include "HPWM_int.h"
#include "HPWM_priv.h"
#include "HPWM_cfg.h"

/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone constant *****************************/
/*****************************************************************************/

#ifdef BSW_PWM_IN

/*****************************************************************************/
/* Configuration structure for each Input channel                            */
/*****************************************************************************/
static const HPWM_tstrPwmInChConfig HWPM_strInPwmChConfig_Var1[HPWM_u8IN_NB_Var1] = {

   {MFIC_PWM_IN_A0, MFIC_u8IO_TRDIOA0, HPWM_u8IN_CH_MODE_DUTY_CYCLE,  40, 16 },
   {MFIC_PWM_IN_B0, MFIC_u8IO_TRDIOB0, HPWM_u8IN_CH_MODE_DUTY_CYCLE,  80, 16 }

};

/*****************************************************************************/
/* Configuration of the filtration mechanism for input channels              */
/*****************************************************************************/
static const HPWM_tstrPwmInFilterConfig HPWM_strInPwmFilter_Var1[HPWM_u8IN_NB_Var1]=
{
   /* Duty Cycle           -      Period             - Number of samples */
   {HPWM_u8MajorityFilter    , HPWM_u8ConsecutiveFilter ,        8          },
   {HPWM_u8MeanSamplesFilter , HPWM_u8MajorityFilter    ,        8          }
};


/******************************************************************************/
/* Configuration for DIO pin for each PWM channel                             */
/* i.e. which pin number in MFIC_u8IO_PIN is the same as PWM pin              */
/******************************************************************************/

/*****************************************************************************/
/* Majority cap parameter for duty cycle                                     */
/*****************************************************************************/
static const u8 HPWM_au8MajorityCapDuty_Var1[HPWM_u8IN_NB_Var1]=
{
   5,
   0 /* Not majority filter*/
};

/*****************************************************************************/
/* Majority cap parameter for period                                         */
/*****************************************************************************/
static const u8 HPWM_au8MajorityCapPeriod_Var1[HPWM_u8IN_NB_Var1]=
{
   0, /* Not majority filter*/
   5
};

/*****************************************************************************/
/* Consecutive cap parameter for duty cycle                                  */
/*****************************************************************************/
static const u8 HPWM_au8ConsecCapDuty_Var1[HPWM_u8IN_NB_Var1]=
{
   0, /* Not consecutive filter*/
   0 /* Not consecutive filter*/
};

/*****************************************************************************/
/* Consecutive cap parameter for Period                                   */
/*****************************************************************************/
static const u8 HPWM_au8ConsecCapPeriod_Var1[HPWM_u8IN_NB_Var1]=
{
   5,
   0 /* Not consecutive filter*/
};


/*****************************************************************************/
/* Rounding configuration for Duty                                           */
/*****************************************************************************/
static const HPWM_tstrRoundingConfig HPWM_astrInPwmRoundDuty_Var1[HPWM_u8IN_NB_Var1]=
{
   /* Rounding Factor  -  Rounding Type */
   {         5         ,  HPWM_u8RoundingUp      },
   {         4         ,  HPWM_u8RoundingDown    }

};


/*****************************************************************************/
/* Rounding configuration for input Period                                   */
/*****************************************************************************/
static const HPWM_tstrRoundingConfig HPWM_astrInPwmRoundPeriod_Var1[HPWM_u8IN_NB_Var1] =
{
   /* Rounding Factor  -  Rounding Type */
   {         5         ,  HPWM_u8RoundingUp      },
   {         4         ,  HPWM_u8RoundingDown    }
};


#endif   /* BSW_PWM_IN */

#ifdef BSW_PWM_OUT

/*****************************************************************************/
/* Configuration for each PWM output channel                                 */
/*****************************************************************************/
static const HPWM_tstrOutChConfig HPWM_astrOutPwmChConfig_VAR1[HPWM_u8OUT_NB_Var1] = {

   /* clock    prescaler          Channel Nbr            Active Level            size   */
     {  80  ,     1      , MFIC_u8PWM_OUT_CHANNEL_0  ,  HPWM_u8ACTIVE_HIGH   ,  0xFFFFU},   /* TAU00 */
     {  80  ,     1      , MFIC_u8PWM_OUT_CHANNEL_1  ,  HPWM_u8ACTIVE_LOW   ,  0xFFFFU}    /* TAU01 */

};

/*****************************************************************************/
/* Runnable Configuration for each PWM output channel                        */
/*    - Range for Initial Duty: [0x000 : 0x2710]                             */
/*    - Range for Signal Refresh: [LBTY_TRUE / LBTY_FALSE]                   */
/*****************************************************************************/
static const HPWM_tstrOutChRefreshConfig HPWM_astrOutChRefreshConfig_VAR1 [HPWM_u8OUT_NB_Var1] =
{
   /* Initial Duty Cycle    ,  Enable/Disable Refresh for this signal */
   {  0x0000                ,     LBTY_FALSE },
   {  0x0000                ,     LBTY_TRUE  },
};
#endif   /* BSW_PWM_OUT */


#ifdef BSW_PWM_IN

/******************************************************************************/
/*  Software variants configuration array for Input Channels                  */
/******************************************************************************/
HPWM_tstrInCompConfig HPWM_astrInVariantConfig[HPWM_u8VARIANT_NB] = {

   {HPWM_u8IN_NB_Var1, HWPM_strInPwmChConfig_Var1, HPWM_strInPwmFilter_Var1, HPWM_au8MajorityCapDuty_Var1, HPWM_au8MajorityCapPeriod_Var1,
      HPWM_au8ConsecCapDuty_Var1, HPWM_au8ConsecCapPeriod_Var1, HPWM_astrInPwmRoundDuty_Var1,
      HPWM_astrInPwmRoundPeriod_Var1}
};

#endif   /* BSW_PWM_IN */


#ifdef BSW_PWM_OUT

/******************************************************************************/
/*  Software variants configuration array for Output Channels                 */
/******************************************************************************/
HPWM_tstrOutCompConfig HPWM_astrOutVariantConfig[HPWM_u8VARIANT_NB] = {
   {HPWM_u8OUT_NB_Var1, HPWM_astrOutPwmChConfig_VAR1,HPWM_astrOutChRefreshConfig_VAR1}
};

#endif   /* BSW_PWM_OUT */

/*****************************************************************************/
/********************************* zone struct/union *************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone variable *****************************/
/*****************************************************************************/
#endif /* BSW_PWM */
/***************************** E N D (HPWM_cfg.c)  ***************************/
