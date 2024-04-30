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
/* !Target          : STD                                                     */
/*                                                                            */
/* !COPYRIGHT 2015 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/* MODIFICATION LOG :                                                         */
/*    Author   --     Date    --          Modification                        */
/* Ahmed abdelmageed                                                          */
/*                 06/11/2018     Added job start user notification callback  */
/* Soha Wagdy      13/ 1 /2019    Update code after applying MISRA            */
/*             --                 issues remarks                              */
/* Ahmed Abdelmageed                                                          */
/*                 03/03/2019     Update argument name of type                */
/*                                'tpfvidHspmMcalVlsCallBck' to match the     */
/*                                function HSPM_vidMgrJobEndNotf [artf399069] */
/* Soha Wagdy       |  10/12/2019   | Fix Mandatory KL issues                 */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mohamed MAGDY                    !Date : 14/06/2015     */
/* !Coded by        : Mohamed MAGDY                    !Date : 14/06/2015     */
/*                                                                            */
/******************************************************************************/
/*  %PCMS_HEADER_SUBSTITUTION_START%
    %PL% %PCMS_HEADER_SUBSTITUTION_END%
 ******************************************************************************/


#ifndef HSPM_INT_H
#define HSPM_INT_H

/******************************************************************************/
/************************** Header Files Inclusion ****************************/
// #include "HSPM_cfg.h"

/******************************************************************************/
/******************************** Zone Typedef ********************************/
/******************************************************************************/


/******************************************************************************/
/*!Comment  : MCAL Job End Call Back Function Type                            */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
#ifdef AUTOSAR_USED

typedef void (*tpfvidHspmMcalAutsrCallBck ) (void);

#else

typedef void (*tpfvidHspmMcalVlsCallBck ) (LBTY_tenuErrorStatus enuJobStatusCpy);

#endif

/******************************************************************************/
/*!Comment  : User Job End Call Back Function Type                            */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
typedef
    void (*tpfvidHspmUsrJobCallBck )
          (u16 u16UsrSgntrCpy , LBTY_tenuErrorStatus enuErrStat);


/******************************************************************************/
/********************************* Zone Macro *********************************/
/******************************************************************************/

/******************************************************************************/
/********************************* Zone Define ********************************/
/******************************************************************************/


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
void HSPM_vidInit(void);


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
LBTY_tenuErrorStatus
HSPM_enuSpiJobRqst(
    /* !Comment : Channel ID                                                  */
    u8 u8ChannelIdCpy             ,
    /* !Comment : User TX Buffer                                              */
    u16* pu16UsrTxBuffCpy         ,
    /* !Comment : User RX Buffer                                              */
    u16* pu16UsrRecvBuffCpy       ,
    /* !Comment : Job Length (No of Frames)                                   */
    u8 u8JobLengthCpy             ,
    /* !Comment : User Job Start Call Back Notification Function                */
    tpfvidHspmUsrJobCallBck pfUsrJobStartNotfCpy,
    /* !Comment : User Job End Call Back Notification Function                */
    tpfvidHspmUsrJobCallBck pfUsrJobEndNotfCpy,
    /* !Comment : User Call Back Signature                                    */
    u16 u16UsrSgntrCpy
);


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
void HSPM_vidRunMgr(void);


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
void HSPM_vidMgrJobEndNotf(
#ifdef AUTOSAR_USED
   void
#else
   /* !Comment : Job Status from Invoker                                     */
   LBTY_tenuErrorStatus enuJobStatusCpy
#endif
    );




#endif /* HSPM_INT_H */

/***************************** E N D (HSPM_int.h) *****************************/
