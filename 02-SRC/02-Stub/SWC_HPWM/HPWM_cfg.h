/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HPWM                                                    */
/* !Description     : Pulse width modulation driver                           */
/*                                                                            */
/* !Module          : HPWM_cfg.h                                              */
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
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Ahmed Ramadan-- 8 Nov 2020  -- Min frequency detection ACR [artf1104778 ]  */
/* Soha Wagdy  --  8 Dec 2020  -- Close cross review points [artf1138952]     */
/* Soha Wagdy  --  27 Dec 2020 -- Fixing APR [artf1162990] for Mean Filter    */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 24 OCT 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 24 OCT 2016 */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                              Public Configurations                         */
/******************************************************************************/
#ifndef HPWM_CFG_H_INT
#ifdef HPWM_INT_H
#define HPWM_CFG_H_INT


/*****************************************************************************/
/* !Description : Define Aliveness supervision for runnables Check           */
/* For ex: Enable/Disable HPWM_ALIVENESS_SUPERVISSION for HPWM runnable      */
/*****************************************************************************/
#define HPWM_ALIVENESS_SUPERVISSION      (HPWM_u8CP_ENABLED)

/******************************Variant 1 Configurations************************/

/******************************************************************************/
/* !Description : Define Index for each PWM Input Channel start with 0        */
/* For ex: #define HPWM_u8SRC1    ( (u8) 0 )                                  */
/*         #define HPWM_u8SRC2    (HPWM_u8SRC1 + ((u8)1)                      */
/*         #define HPWM_u8SRC3    (HPWM_u8SRC2 + ((u8)1)                      */
/*         #define HPWM_u8NB      (HPWM_u8SRC3 + ((u8)1)                      */
/******************************************************************************/
#define HPWM_u8IN_CH1         (0U)                   /* Channel 1  */
#define HPWM_u8IN_CH2         (HPWM_u8IN_CH1 + 1U)    /* Channel 2  */
#define HPWM_u8IN_NB_Var1     (HPWM_u8IN_CH2 + 1U)  /* Number of Channels */

/******************************************************************************/
/* !Description : Define Index for each PWM Output Channel start with 0       */
/* For ex: #define HPWM_u8IN_SRC1    ( (u8) 0 )                               */
/*         #define HPWM_u8IN_SRC2    (HPWM_u8SRC1 + ((u8)1)                   */
/*         #define HPWM_u8IN_SRC3    (HPWM_u8SRC2 + ((u8)1)                   */
/*         #define HPWM_u8IN_NB      (HPWM_u8SRC3 + ((u8)1)                   */
/******************************************************************************/
#define HPWM_u8OUT_CH1         (0U)                  /* Channel 1  */
#define HPWM_u8OUT_CH2         (HPWM_u8OUT_CH1 + 1U) /* Channel 2  */
#define HPWM_u8OUT_NB_Var1     (HPWM_u8OUT_CH2 + 1U) /* Number of Channels */

#endif   /* HPWM_INT_H     */
#endif   /* HPWM_CFG_H_INT */


#ifndef HPWM_CFG_H_PRIV
#ifdef HPWM_PRIV_H
#define HPWM_CFG_H_PRIV

/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/******************************************************************************/
/* Description: Number of variants used                                       */
/* !Note    : Use suffix U not casting because preprocessor condition is used */
/******************************************************************************/
#define HPWM_u8VARIANT_NB            1U

/******************************************************************************/
/* Description: Default variant to be used in case of error                   */
/* !Note    : Use suffix U not casting because preprocessor condition is used */
/******************************************************************************/
#define HPWM_u8DEFAULT_VARIANT       0U

/******************************************************************************/
/* Description: Maximum number of input channels across all variants          */
/* !Note    : Use suffix U not casting because preprocessor condition is used */
/******************************************************************************/
#define HPWM_u8IN_NB       HPWM_u8IN_NB_Var1

/******************************************************************************/
/* Description: Maximum number of output channels across all variants         */
/* !Note    : Use suffix U not casting because preprocessor condition is used */
/******************************************************************************/
#define HPWM_u8OUT_NB       HPWM_u8OUT_NB_Var1

/* !Comment : Maximum number of filtration samples */
#define HPWM_u8MAX_FILT_SAMPLES         (u8)8

/* !Comment : Minimum number of Runnable calls after which input channel are considered to be idle */
#define HPWM_MIN_RUNNABLES_COUNT          3U

/* !Comment : Enable the refreshing of the duty cycle*/
#define HPWM_REFRESH_DUTY_ENABLE  HPWM_REFRESH_ENABLED

/* !Comment : Enable/disable DET Reporting           */
#define HPWM_u32DET_REPORTING     HPWM_u32DET_USED
/*****************************************************************************/
/*****************************************************************************/
/********************************* zone constant *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone struct/union *************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone variable *****************************/
/*****************************************************************************/

#ifdef BSW_PWM_IN

/******************************************************************************/
/*  Software variants configuration array for Input Channels                  */
/******************************************************************************/
extern HPWM_tstrInCompConfig HPWM_astrInVariantConfig[HPWM_u8VARIANT_NB];

#endif   /* BSW_PWM_IN */


#ifdef BSW_PWM_OUT
/******************************************************************************/
/*  Software variants configuration array for Output Channels                 */
/******************************************************************************/
extern HPWM_tstrOutCompConfig HPWM_astrOutVariantConfig[HPWM_u8VARIANT_NB];

#endif   /* BSW_PWM_OUT */
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone function *****************************/
/*****************************************************************************/


#endif     /* HPWM_CFG_H_PRIV   */
#endif     /* HPWM_INT_H        */


/***************************** E N D (HPWM_cfg.h)  ***************************/
