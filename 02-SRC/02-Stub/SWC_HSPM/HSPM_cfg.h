/******************************************************************************/
/* !Layer           : Hardware abstraction layer (HAL)                        */
/*                                                                            */
/* !Component       : HSPM_int.h                                              */
/* !Description     : SPI Manager                                             */
/* !Module          : HSPM                                                    */
/* !Revision        : 1.0                                                     */
/* !Date            : 14/06/2015                                              */
/* !Description     : SPI Manager (Provides service for SPI users and
 *                      abstracts SPI Driver)
 *                    Compatible with VLS_STD_DSPI and AUTOSAR                */
/*                                                                            */
/*                    %PCMS_HEADER_SUBSTITUTION_START%
   !File            : %PM%
   !ID Description  : %PD% %PCMS_HEADER_SUBSTITUTION_END%
                                                                              */
/* !Scope           : Program                                                 */
/*                                                                            */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : STD                                                     */
/* !Target          : STD							                          */
/*                                                                            */
/* !COPYRIGHT 2016 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/*                 Mahmed3  22/3/2017   Fix bugs in Integration with RH850 AS */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mohamed MAGDY                    !Date : 14/06/2015     */
/* !Coded by        : Mohamed MAGDY                    !Date : 14/06/2015     */
/*                                                                            */
/******************************************************************************/
/*  %PCMS_HEADER_SUBSTITUTION_START%
    %PL% %PCMS_HEADER_SUBSTITUTION_END%
 ******************************************************************************/



/******************************************************************************/
/**************************** PUBLIC CONFIGURATION ****************************/
/******************************************************************************/
#ifndef HSPM_CFG_INT_H
#ifdef  HSPM_INT_H
#define HSPM_CFG_INT_H

#include "BSW_cfg.h"

/******************************************************************************/
/*!Comment : Configurable parameter specifics the No of tires in case of
 *            Send is Failed. Used for Retry Mechanism                        */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#define u8HSPM_JOB_MAX_SEND_TRIES     (3U)


/******************************************************************************/
/*!Comment : Configurable parameter of Jobs queue size
 *            Represents the max number of jobs can be requested in the
 *            same time
 *
 * MAX     : 254                                                              */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#define u8HSPM_JOB_QUEUE_SIZE         (20U)


/******************************************************************************/
/*!Comment  :  Configurable parameter of Number of Channels
 *               Represents the number of system channels.
 *               Channel here specify a SPI slave.
 *
 *              Represents Sequence_ID in case of AUTOSAR MCAL
 *
 *                                                                            */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#define u8HSPM_CHANNELS_MAX_NO         (8U)

/*****************************************************************************/
/* !Description : Define Aliveness supervision for runnables Check           */
/* For ex: Enable/Disable HSPM_ALIVENESS_SUPERVISSION for HSPM runnable      */
/*****************************************************************************/
#define HSPM_ALIVENESS_SUPERVISSION      (HSPM_CP_ENABLED)

#endif /* HSPM_INT_H */
#endif /* HSPM_CFG_INT_H */


/******************************************************************************/
/**************************** PRIVATE CONFIGURATION ***************************/
/******************************************************************************/
#ifndef HSPM_CFG_PRIV_H
#ifdef  HSPM_PRIV_H
#define HSPM_CFG_PRIV_H

/******************************************************************************/
/*************************** !Comment : HSPM Defects **************************/
/******************************************************************************/

/*************** !Comment : Defects Configuration Decelerations ***************/
extern LDEM_tstrDefectConfig astrHspmTxTimOutDfctCfg;

extern LDEM_tstrDefectConfig astrHspmDrvReqRjctDfctCfg;


/******************************************************************************/
/*!Description:                                                               */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_STD                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidAutosarMcalInit(void);


/******************************************************************************/
/*!Description:                                                               */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_STD                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidVlsMcalInit(void);


#endif /* HSPM_PRIV_H */
#endif /* HSPM_CFG_PRIV_H */
/***************************** E N D (HSPM_cfg.h) *****************************/
