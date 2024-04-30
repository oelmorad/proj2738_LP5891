/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HDIO                                                    */
/* !Description     : Digital input Manager                                   */
/*                                                                            */
/* !Module          : HDIO_cfg.h                                              */
/* !Revision        : 1.5                                                     */
/* !Date            : 23 Nov 2020                                             */
/*                                                                            */
/*                                                                            */
/* !Scope           : Program                                                 */
/*                                                                            */
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
/*    Author   --     Date     --          Modification                       */
/* Ahmed Assaf -- 28  NOV 2016 -- Initial Creation                            */
/* Nuha bahaa  -- 7  Mar  2018  move pin config from private to public section*/
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  -- 10/12/2019   -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Soha Wagdy  -- 11 Nov 2020  -- Fix Configurations to RAM [artf1067933]     */
/* Soha Wagdy  -- 23 Nov 2020  -- Updates for the following ACRs:             */
/*                                  [artf1067933 artf267567 artf794236 ]      */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 28 NOV 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 28 NOV 2016 */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                              Public Configurations                         */
/******************************************************************************/
#ifndef HDIO_CFG_H_INT
#ifdef  HDIO_INT_H
#define HDIO_CFG_H_INT


/*****************************************************************************/
/* !Description : Define Aliveness supervision for runnables Check           */
/* For ex: Enable/Disable HDIO_IN_ALIVENESS_SUPERVISSION for Input runnable  */
/*         Enable/Disable HDIO_OUT_ALIVENESS_SUPERVISSION for Outpu runnable */
/*****************************************************************************/
#define HDIO_IN_ALIVENESS_SUPERVISSION      (HDIO_ENABLED)
#define HDIO_OUT_ALIVENESS_SUPERVISSION     (HDIO_ENABLED)

/*****************************************************************************/
/* !Description : Define Plausibility check for Output Pins                  */
/* For ex: Enable/Disable HDIO_OUT_PLAUSIBILITY_CHECK for Output   runnable  */
/*****************************************************************************/
#define HDIO_OUT_PLAUSIBILITY_CHECK         (HDIO_ENABLED)

/************************ Variant One Configurations **************************/
/******************************************************************************/
/* !Comment : Number of digital input signals                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT

#define HDIO_u8IN_PIN0_VAR1            ((u8)0)
#define HDIO_u8IN_PIN1_VAR1            (HDIO_u8IN_PIN0_VAR1+(u8)1)
#define HDIO_u8IN_PIN2_VAR1            (HDIO_u8IN_PIN1_VAR1+(u8)1)
#define HDIO_u8IN_PIN3_VAR1            (HDIO_u8IN_PIN2_VAR1+(u8)1)
#define HDIO_u8IN_NB_SIG_VAR1          (HDIO_u8IN_PIN3_VAR1+(u8)1)

/******************************************************************************/
/* !Description : Define Index for each PIN defect starting with 0            */
/******************************************************************************/
#define HDIO_u8DEFECT_PIN0_VAR1    ((u8)0)
#define HDIO_u8DEFECT_PIN1_VAR1    (HDIO_u8DEFECT_PIN0_VAR1 + ((u8)1))
#define HDIO_u8DEFECT_PIN2_VAR1    (HDIO_u8DEFECT_PIN1_VAR1 + ((u8)1))
#define HDIO_u8DEFECT_PIN3_VAR1    (HDIO_u8DEFECT_PIN2_VAR1 + ((u8)1))
#define HDIO_u8DEFECTNB_VAR1       (HDIO_u8DEFECT_PIN3_VAR1 + ((u8)1))  /* Number of defects  */

#endif

/******************************************************************************/
/* !Comment : Number of digital output signals                                */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT

#define HDIO_u8OUT_PIN0_VAR1           ((u8)0)
#define HDIO_u8OUT_PIN1_VAR1           (HDIO_u8OUT_PIN0_VAR1+ (u8)1)
#define HDIO_u8OUT_PIN2_VAR1           (HDIO_u8OUT_PIN1_VAR1+ (u8)1)
#define HDIO_u8OUT_PIN3_VAR1           (HDIO_u8OUT_PIN2_VAR1+ (u8)1)
#define HDIO_u8OUT_NB_SIG_VAR1         (HDIO_u8OUT_PIN3_VAR1+ (u8)1)

#endif

/******************************************************************************/

/************************ Variant TWO Configurations **************************/
/******************************************************************************/
/* !Comment : Number of digital input signals                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT

#define HDIO_u8IN_PIN0_VAR2            ((u8)0)
#define HDIO_u8IN_PIN1_VAR2            (HDIO_u8IN_PIN0_VAR2+(u8)1)
#define HDIO_u8IN_NB_SIG_VAR2          (HDIO_u8IN_PIN1_VAR2+(u8)1)

/******************************************************************************/
/* !Description : Define Index for each PIN defect starting with 0            */
/******************************************************************************/
#define HDIO_u8DEFECT_PIN0_VAR2    ((u8)0)
#define HDIO_u8DEFECT_PIN1_VAR2    (HDIO_u8DEFECT_PIN0_VAR2 + ((u8)1))
#define HDIO_u8DEFECTNB_VAR2       (HDIO_u8DEFECT_PIN1_VAR2 + ((u8)1))  /* Number of defects  */

#endif

/******************************************************************************/
/* !Comment : Number of digital output signals                                */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT

#define HDIO_u8OUT_PIN0_VAR2           ((u8)0)
#define HDIO_u8OUT_PIN1_VAR2           (HDIO_u8OUT_PIN0_VAR2+ (u8)1)
#define HDIO_u8OUT_NB_SIG_VAR2        ( HDIO_u8OUT_PIN1_VAR2+(u8)1)

#endif

/************************ Variant TWO Configurations **************************/

#endif
#endif
/******************************************************************************/
/*                       End of Public Configurations                         */
/******************************************************************************/



/******************************************************************************/
/*                              Private Configurations                        */
/******************************************************************************/
#ifndef HDIO_CFG_H_PRIV
#ifdef  HDIO_PRIV_H
#define HDIO_CFG_H_PRIV

/******************************************************************************/
/**************************** General Configurations **************************/
/******************************************************************************/
/* !Comment : Number of SW Variants                                           */
/* !Note    : Use suffix U not casting because preprocessor condition is used */
/******************************************************************************/
#define HDIO_u8VARIANT_NB         2U

/******************************************************************************/
/* !Comment : Default variant to be used in case of error                     */
/******************************************************************************/
#define HDIO_u8DEFAULT_VARIANT    ((u8)0)

#ifdef BSW_HDIO_INPUT
/******************************************************************************/
/* !Comment : Maximum number of input signals between all variants            */
/******************************************************************************/
#define HDIO_u8IN_MAX_NB          HDIO_u8IN_NB_SIG_VAR1

/******************************************************************************/
/* !Description : Max number of Defects for input pins between all variants   */
/******************************************************************************/
#define HDIO_u8DEFECT_MAX_NB      HDIO_u8DEFECTNB_VAR1

#endif

#ifdef BSW_HDIO_OUTPUT
/******************************************************************************/
/* !Comment : Maximum number of output signals between all variants           */
/******************************************************************************/
#define HDIO_u8OUT_MAX_NB         HDIO_u8OUT_NB_SIG_VAR1

#endif
/**************************** General Configurations **************************/

/******************************************************************************/
/* !Comment : Memory placement configuration  [ROM_CONFIG or RAM_CONFIG]      */
/******************************************************************************/
#define CONFIG_MEM_PLACEMENT  ROM_CONFIG

/******************************************************************************/
/* !Comment : Enable/disable DET Reporting                                    */
/******************************************************************************/
#define HDIO_u32DET_REPORTING     HDIO_u32DET_USED

#endif
#endif
/******************************************************************************/
/*                       End of Private Configurations                        */
/******************************************************************************/


/***************************** E N D (HDIO_cfg.h)  ***************************/
