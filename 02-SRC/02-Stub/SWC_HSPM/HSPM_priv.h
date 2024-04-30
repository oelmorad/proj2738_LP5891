/******************************************************************************/
/* !Layer           : Hardware abstraction layer (HAL)                        */
/*                                                                            */
/* !Component       : HSPM_priv.h                                              */
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
/* !Project         : STD		                                              */
/* !Target          : STD							                          */
/*                                                                            */
/* !COPYRIGHT 2015 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/*                      Ahmed abdelmageed  6/11/2018   Added job start user   */
/*                                                     notification callback  */
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


#ifndef HSPM_PRIV_H
#define HSPM_PRIV_H

/******************************************************************************/
/************************** Header Files Inclusion ****************************/
/******************************************************************************/
#include "HSPM_cfg.h"

/******************************************************************************/
/******************************** Zone Typedef ********************************/
/******************************************************************************/

/******************************************************************************/
/*!Comment  : HSPM Job Queue Type                                             */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
typedef struct
{
  /* !Comment : Channel ID                                                    */
  u8 u8ChannelId;
  /* !Comment : User TX Buffer                                                */
  u16* pu16UsrTxBuff;
  /* !Comment : User RX Buffer                                                */
  u16* pu16UsrRecvBuff;
  /* !Comment : Job Length (No of Frames)                                     */
  u8 u8JobLength;
  /* !Comment : User Job Start Call Back Notification Function                */
  tpfvidHspmUsrJobCallBck pfUsrJobStartNotf;
  /* !Comment : User Job End Call Back Notification Function                  */
  tpfvidHspmUsrJobCallBck pfUsrJobEndNotf;
  /* !Comment : User Call Back Argument (User Signature)                      */
  u16 u16UsrSgntr;

}
tstrHspmJobQueue;


/******************************************************************************/
/*!Comment  : HSPM Manager Data Type                                          */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
typedef struct
{
  /* !Comment : Number of Job in requested in the Queue                       */
  u8 u8JobQueueCtr;
  /* !Comment : Current Job Handled in the Queue                              */
  u8 u8JobQueueIndx;
  /* !Comment : Send Tries counter represents the number of tries to re-send a
   *            failed job.                                                   */
  u8 u8TxRetryCtr;
  /* !Comment : HSPM Manager Working Status                                   */
  LBTY_tenuWorkingStatus enuStatus;
}
tstrHspmManagerData;

/******************************************************************************/
/********************************* Zone Macro *********************************/
/******************************************************************************/

/******************************************************************************/
/********************************* Zone Define ********************************/
/******************************************************************************/

/******************************************************************************/
/*!Comment  : ENTER Critical Section Macro                                    */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#ifdef AUTOSAR_USED
#define HSPM_ENTER_CRITICAL_SEC()  SchM_Enter_HSPM_HSPM_CRITICAL_SEC()
#else
#define HSPM_ENTER_CRITICAL_SEC()  SFIC_vidEnterCriticalZone()
#endif /* AUTOSAR_USED */
/******************************************************************************/
/*!Comment  : LEAVE Critical Section Macro                                    */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#ifdef AUTOSAR_USED
#define HSPM_LEAVE_CRITICAL_SEC()  SchM_Exit_HSPM_HSPM_CRITICAL_SEC()
#else
#define HSPM_LEAVE_CRITICAL_SEC()  SFIC_vidLeaveCriticalZone()
#endif /* AUTOSAR_USED */

/******************************************************************************/
/* !Description : Enable/Disable Check Point                                  */
/******************************************************************************/
#define HSPM_CP_ENABLED       1U
#define HSPM_CP_DISABLED      0U

/******************************************************************************/
/******************************** Zone Constant *******************************/
/******************************************************************************/

/******************************************************************************/
/**************************** Zone Structure\Union ****************************/
/******************************************************************************/

/******************************************************************************/
/******************************** Zone Variable *******************************/
/******************************************************************************/



/******************************************************************************/
/******************************** Zone Function *******************************/
/******************************************************************************/

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
static void vidStateBusy(void);

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
static void vidStateIdle(void);

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
static void vidJobScheduler (void);

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
static void vidClrJobQueue (void);

#endif /* HSPM_PRIV_H */

/***************************** E N D (HSPM_priv.h) ****************************/
