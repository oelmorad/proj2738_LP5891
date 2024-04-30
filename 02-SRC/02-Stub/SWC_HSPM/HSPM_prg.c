/******************************************************************************/
/* !Layer           : Hardware abstraction layer (HAL)                        */
/*                                                                            */
/* !Component       : HSPM_prg.c                                              */
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
/*    Author   --     Date    --          Modification                        */
/* Ahmed Abdelmageed                                                          */
/*                  06/11/2018            Added job start user notification   */
/*                                        callback                            */
/* Soha Wagdy  --  13/ 1 /2019 --         Update code after applying MISRA    */
/*             --              --         issues remarks                      */
/* Ahmed Abdelmageed                                                          */
/*                  03/03/2019           -removed explicit cast for the       */
/*                                        callback argument passed to         */
/*                                        'MFIC_enuDspiWriteBuff' [artf267709]*/
/*                                       -removed dead code inside the        */
/*                                        functions 'HSPM_vidMgrJobEndNotf'   */
/*                                        'vidStateBusy' [artf380189]         */
/* Soha Wagdy  --   14/3/2019  --         Update AUTOSAR headers inclusion    */
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                 */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Soha Wagdy  --  21/09/2020  -- initialize Local variable                    */
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
/****************************** Layer definition ******************************/
/******************************************************************************/

#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HSPM
/************************** Header Files Inclusion ****************************/
#include "LBTY_int.h"
#include "LCTY_int.h"
#include "LDEM_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HSPM.h"
#include "HFIC_IoHwAb.h"
#endif

#include "MFIC.h"
#include "SFIC.h"

/*!Comment: HSPM include files                                                */
#include "HSPM_int.h"
#include "HSPM_priv.h"

/******************************************************************************/
/************************** Private Data Definitions **************************/
/******************************************************************************/

/******************************************************************************/
/*!Comment  : HSPM Manager Data                                               */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
static tstrHspmManagerData strHspmManagerLog;

/******************************************************************************/
/*!Comment  : HSPM Job Queue Array                                            */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
static tstrHspmJobQueue astrHspmJobQueue[u8HSPM_JOB_QUEUE_SIZE];

/******************************************************************************/
/*!Comment  : HSPM Transmission Time-Out Defect                               */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
static LDEM_tstrDefect astrHspmTxTimOutDfct;

/******************************************************************************/
/*!Comment  : HSPM SPI Driver Request Rejection Defect                        */
/*!Trace_To : Covers_                                                         */
/******************************************************************************/
static LDEM_tstrDefect astrHspmDrvReqRjctDfct;

/******************************************************************************/
/******************************* Public Services ******************************/
/******************************************************************************/

/******************************************************************************/
/*!Description: API for Initializing the HSPM module                          */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_SWC_HSPM_CDD_001-V01                                   */
/*                                                                            */
/******************************************************************************/
void HSPM_vidInit(void) {

	/*!Comment : Initialize Manager Log Data                                    */
	strHspmManagerLog.u8JobQueueCtr = 0;
	strHspmManagerLog.u8JobQueueIndx = 0;
	strHspmManagerLog.u8TxRetryCtr = 0;

	/*!Comment : Initialize Manager Status                                      */
	strHspmManagerLog.enuStatus = LBTY_IDLE;

	/************************** !Comment : Init Defects *************************/
	/*!Comment : Init Transmission Time-Out Defect                              */
	astrHspmTxTimOutDfct.pstrConfig = &astrHspmTxTimOutDfctCfg;
	(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);


	/*!Comment : SPI Driver Request Rejection Defect                            */
	astrHspmDrvReqRjctDfct.pstrConfig = &astrHspmDrvReqRjctDfctCfg;
   (void)LDEM_enuInitDefect(&astrHspmDrvReqRjctDfct);

	/*!Comment : Initialize MCAL SPI                                            */
#ifdef AUTOSAR_USED
	/*!Comment : AUTOSAR Init                                                   */
	HSPM_vidAutosarMcalInit();
#else
	/*!Comment : u8VLS_STD_MCAL Init                                            */
	HSPM_vidVlsMcalInit();
#endif

}

/******************************************************************************/
/*!Description:                                                               */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_SWC_HSPM_CDD_003-V01                                                    */
/*                                                                            */
/******************************************************************************/
LBTY_tenuErrorStatus HSPM_enuSpiJobRqst(u8 u8ChannelIdCpy, 
										u16* pu16UsrTxBuffCpy,
										u16* pu16UsrRecvBuffCpy,
										u8 u8JobLengthCpy,
									   tpfvidHspmUsrJobCallBck pfUsrJobStartNotfCpy,
										tpfvidHspmUsrJobCallBck pfUsrJobEndNotfCpy,
										u16 u16UsrSgntrCpy) 
{
   LBTY_tenuErrorStatus enuReturnLoc = LBTY_OK; /* Error return status */
	u8 u8JobCtrLoc = (u8)0;					   /* job counter index */

	/*!Comment : CHeck for Valid Job and Empty Slot                             */
	/*pfUsrJobStartNotfCpy is not checked because it is optional                */
	/*if pfUsrJobStartNotfCpy is NULL it will not be called at job start        */
	if ((strHspmManagerLog.u8JobQueueCtr < ((u8) u8HSPM_JOB_QUEUE_SIZE))
			/*!Comment : Check for Valid Channel                                        */
			&& (u8ChannelIdCpy < ((u8) u8HSPM_CHANNELS_MAX_NO))
			/*!Comment : Check for Valid Address                                        */
			&& (pu16UsrTxBuffCpy != (LBTY_NULL))
			/*!Comment : Check for Valid Address                                        */
			&& (pu16UsrRecvBuffCpy != (LBTY_NULL))
			/*!Comment : Check for Valid Job Length                                     */
			&& (u8JobLengthCpy > ((u8) 0))
         /*!Comment : Check for Valid Address                                        */
         && (pfUsrJobEndNotfCpy != (LBTY_NULL))) {

		
		/* Start critical section */
	   HSPM_ENTER_CRITICAL_SEC();

		/*!Comment : Load Next Empty Slot Index                                 */
		u8JobCtrLoc = strHspmManagerLog.u8JobQueueCtr;

		/*!Comment : Increment Job Queue Counter to point to next Empty Slot    */
		strHspmManagerLog.u8JobQueueCtr = u8JobCtrLoc + (u8)1;

		/*!Comment : Store Job Info                                             */
		astrHspmJobQueue[u8JobCtrLoc].u8ChannelId     = u8ChannelIdCpy;
		astrHspmJobQueue[u8JobCtrLoc].pu16UsrTxBuff   = pu16UsrTxBuffCpy;
		astrHspmJobQueue[u8JobCtrLoc].pu16UsrRecvBuff = pu16UsrRecvBuffCpy;
		astrHspmJobQueue[u8JobCtrLoc].u8JobLength     = u8JobLengthCpy;
      astrHspmJobQueue[u8JobCtrLoc].pfUsrJobStartNotf = pfUsrJobStartNotfCpy;
		astrHspmJobQueue[u8JobCtrLoc].pfUsrJobEndNotf = pfUsrJobEndNotfCpy;
		astrHspmJobQueue[u8JobCtrLoc].u16UsrSgntr     = u16UsrSgntrCpy;

      HSPM_LEAVE_CRITICAL_SEC();
      /* End of critical section */
		
		/*!Comment : JOB Accepted                                               */
		enuReturnLoc = LBTY_OK;
	}
	else
	{
		/*!Comment : JOB Not Accepted                                           */
		enuReturnLoc = LBTY_NOK;
	}

	return (enuReturnLoc);
}

/******************************************************************************/
/*!Description: HSPM Manager Runnable                                         */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_SWC_HSPM_CDD_002-V01                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidRunMgr(void) {

#if HSPM_ALIVENESS_SUPERVISSION == HSPM_CP_ENABLED
   LBTY_tenuErrorStatus enuCPStatusLoc = LBTY_OK;
#endif

	switch (strHspmManagerLog.enuStatus) {

	/*!Comment : Idle State Handling                                          */
	case LBTY_IDLE:
		vidStateIdle();
		break;

		/*!Comment : Busy state Handling                                          */
	case LBTY_BUSY:
		vidStateBusy();
		break;

	default:
		break;
	}

#if HSPM_ALIVENESS_SUPERVISSION == HSPM_CP_ENABLED
   enuCPStatusLoc = SFIC_vidHspmCP();

   if(LBTY_OK!=enuCPStatusLoc)
   {
      /*Report an Error*/
   }
   else
   {
      /*Do Nothing */
   }
#endif

}

/******************************************************************************/
/*!Description: HSPM Call Back Notification                                   */
/*              Interaction is done with SPI Driver (MAL)
 *              This service is used to acknowledge the SPI Manager from SPI
 *              Driver that the transmission Job is finished with Job status
 *              passed                                                        */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_SWC_HSPM_CDD_004-V01                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidMgrJobEndNotf(

#ifdef AUTOSAR_USED
   void
#else
   /* !Comment : Job Status from Invoker                                     */
   LBTY_tenuErrorStatus enuJobStatusCpy
#endif

) {

#ifdef AUTOSAR_USED
	Spi_JobResultType enuJobStatusAutsrLoc;
#endif

	/*!Comment : Local Job Status                                               */
	LBTY_tenuErrorStatus enuJobStatusLoc ;
	/*!Comment : Local Job Index                                                */
	u8 u8JobIndxLoc =(u8)0;

	/*!Comment : Get Last Job Status                                            */
#ifdef AUTOSAR_USED
	/*!Comment : AUTOSAR MCAL                                                   */

	/*!Comment : AUTOSAR Get Job Result                                         */
	enuJobStatusAutsrLoc = Spi_GetJobResult(
			astrHspmJobQueue[strHspmManagerLog.u8JobQueueIndx].u8ChannelId);

	/*!Comment : Transform AUTOSAR Status to VLS Status                         */
	if(enuJobStatusAutsrLoc == SPI_JOB_OK )
	{
		enuJobStatusLoc = LBTY_OK;
	}
	else
	{
		enuJobStatusLoc = LBTY_NOK;
	}

#else
	/* !Comment : VLS_STD_MCAL                                                  */
	enuJobStatusLoc = enuJobStatusCpy;
#endif

	if (enuJobStatusLoc == LBTY_OK) {
		/*!Comment : Call Back User with SUCCESS status                         */
		u8JobIndxLoc = strHspmManagerLog.u8JobQueueIndx;
		astrHspmJobQueue[u8JobIndxLoc].pfUsrJobEndNotf(
				astrHspmJobQueue[u8JobIndxLoc].u16UsrSgntr, LBTY_OK);

		/*!Comment : Init Transmission Time-Out Defect                          */
		(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

		/*!Comment : Re-Init Retires Counter                                    */
		strHspmManagerLog.u8TxRetryCtr = 0;

		/*!Comment : Schedule Next Job                                      */
		strHspmManagerLog.u8JobQueueIndx++;
		vidJobScheduler();

	}
	/*!Comment : MCAL Reported a Not-OK Status                                  */
	else {
		/*!Comment : Check for Transmission Tries Counter Threshold             */
		if (strHspmManagerLog.u8TxRetryCtr < u8HSPM_JOB_MAX_SEND_TRIES) {
			/*!Comment : Init Transmission Time-Out Defect                      */
		  (void) LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

			/*!Comment : Increment Retires Counter                              */
			strHspmManagerLog.u8TxRetryCtr++;

			/*!Comment : Schedule The Same Job                                  */
			vidJobScheduler();
		}
		/*!Comment : Tries Counter THRESHOLD Reached                            */
		else {
			/*!Comment : Call Back User with FAILED status                      */
			u8JobIndxLoc = strHspmManagerLog.u8JobQueueIndx;
			astrHspmJobQueue[u8JobIndxLoc].pfUsrJobEndNotf(
					astrHspmJobQueue[u8JobIndxLoc].u16UsrSgntr, LBTY_NOK);

			/*!Comment : Init Transmission Time-Out Defect                      */
			(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

			/*!Comment : Re-Init Retires Counter                                */
			strHspmManagerLog.u8TxRetryCtr = 0;

			/*!Comment : Schedule Next Job                                  */
			strHspmManagerLog.u8JobQueueIndx++;
			vidJobScheduler();
		}

	}

}

/******************************************************************************/
/****************************** Private Services ******************************/
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
static void vidJobScheduler(void) {

	u8 u8JobIndxLoc = (u8)0;
	LBTY_tenuErrorStatus enuDrvReqStatLoc;

#ifdef AUTOSAR_USED
	Std_ReturnType enuDrvRqstStatAutsrLoc;
#endif

	u8JobIndxLoc = strHspmManagerLog.u8JobQueueIndx;

	/*!Comment : Check if current Queue Index has Job Assigned                  */
	if (u8JobIndxLoc < strHspmManagerLog.u8JobQueueCtr) {

	   /*if Job start call back is NULL (optional) do not call it*/
	   if (LBTY_NULL != astrHspmJobQueue[u8JobIndxLoc].pfUsrJobStartNotf)
	   {
         astrHspmJobQueue[u8JobIndxLoc].pfUsrJobStartNotf(
               astrHspmJobQueue[u8JobIndxLoc].u16UsrSgntr, LBTY_OK);
	   }
	   else
	   {
	      /* do nothing */
	   }

#ifdef AUTOSAR_USED
		/*!Comment : AUTOSAR Job Request                                        */

		/* !Comment : Setup External Buffer (EB)                                */
		enuDrvRqstStatAutsrLoc =
				Spi_SetupEB(astrHspmJobQueue[u8JobIndxLoc].u8ChannelId,
						astrHspmJobQueue[u8JobIndxLoc].pu16UsrTxBuff,
						astrHspmJobQueue[u8JobIndxLoc].pu16UsrRecvBuff,
						astrHspmJobQueue[u8JobIndxLoc].u8JobLength);

		/*!Comment : Transform AUTOSAR Status to VLS Status                     */
		if(enuDrvRqstStatAutsrLoc == E_OK )
		{
			enuDrvReqStatLoc = LBTY_OK;
			/* !Comment : Request ASync Transmission                            */
			Spi_AsyncTransmit(astrHspmJobQueue[u8JobIndxLoc].u8ChannelId);
		}
		else
		{
			enuDrvReqStatLoc = LBTY_NOK;
		}

#else

		enuDrvReqStatLoc =
				MFIC_enuDspiWriteBuff(astrHspmJobQueue[u8JobIndxLoc].u8ChannelId,
						astrHspmJobQueue[u8JobIndxLoc].pu16UsrTxBuff,
						astrHspmJobQueue[u8JobIndxLoc].pu16UsrRecvBuff,
						astrHspmJobQueue[u8JobIndxLoc].u8JobLength,
						&(HSPM_vidMgrJobEndNotf));
#endif

		/*!Comment : Update SPI Driver Request Rejection Defect                 */
		(void)LDEM_enuUpdateDefect(&astrHspmDrvReqRjctDfct,(u16) enuDrvReqStatLoc);

	}
	/*!Comment : No More Jobs Assigned, Transit to IDLE Mode                    */
	else {
		/*!Comment : Clear Job Queue                                            */
		vidClrJobQueue();
	}

}

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
static void vidStateIdle(void) {

	/*!Comment : Check for Requested Jobs                                       */
	if (strHspmManagerLog.u8JobQueueCtr > (u8)0) {
		/*!Comment : Set HSPM Status to Busy                                    */
		strHspmManagerLog.enuStatus = LBTY_BUSY;

		/*!Comment : Schedule First Job in the Queue                            */
		vidJobScheduler();
	}

}

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
static void vidStateBusy(void) {

	/*!Comment : Local Job Index                                                */
	u8 u8JobIndxLoc = (u8)0;
	LBTY_tenuErrorStatus enuErrorLoc;
	LDEM_tenuDefectState enuDfctStatLoc;
	LDEM_tenuDefectState enuValidDfctStateLoc;

	enuDfctStatLoc = LDEM_enuDEFECT_ABSENT;

	/*!Comment : Update Transmission Time-Out Defect                            */
	(void)LDEM_enuUpdateDefect(&astrHspmTxTimOutDfct,(u16) LBTY_TRUE);

	/*!Comment : Check Transmission Time-Out Defect                             */
	enuErrorLoc = LDEM_enuGetValidState(&astrHspmTxTimOutDfct, &enuValidDfctStateLoc);
	if ((enuValidDfctStateLoc == LDEM_enuDEFECT_PRESENT ) || (enuErrorLoc != LBTY_OK)) {
		/*!Comment : Init Transmission Time-Out Defect                          */
		(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);
		enuDfctStatLoc = LDEM_enuDEFECT_PRESENT;
	}

	/*!Comment : SPI Driver Request Rejection Defect                            */
	enuErrorLoc = LDEM_enuGetValidState(&astrHspmDrvReqRjctDfct, &enuValidDfctStateLoc);
	if ((enuValidDfctStateLoc == LDEM_enuDEFECT_PRESENT) || (enuErrorLoc != LBTY_OK)) {
		/*!Comment : SPI Driver Request Rejection Defect                        */
		(void)LDEM_enuInitDefect(&astrHspmDrvReqRjctDfct);
		enuDfctStatLoc = LDEM_enuDEFECT_PRESENT;
	}

	/*!Comment : Check Defects                                                  */
	if (enuDfctStatLoc == LDEM_enuDEFECT_PRESENT) {

		/*!Comment : Check for Transmission Tries Counter Threshold             */
		if (strHspmManagerLog.u8TxRetryCtr < ((u8) u8HSPM_JOB_MAX_SEND_TRIES)) {
			/*!Comment : Init Transmission Time-Out Defect                      */
			(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

			/*!Comment : Increment Retires Counter                              */
			strHspmManagerLog.u8TxRetryCtr++;

			/*!Comment : Schedule The Same Job                                  */
			vidJobScheduler();
		}
		/*!Comment : Tries Counter THRESHOLD Reached                            */
		else {
			/*!Comment : Call Back User with FAILED status                      */
			u8JobIndxLoc = strHspmManagerLog.u8JobQueueIndx;
			astrHspmJobQueue[u8JobIndxLoc].pfUsrJobEndNotf(
					astrHspmJobQueue[u8JobIndxLoc].u16UsrSgntr, LBTY_NOK);

			/*!Comment : Init Transmission Time-Out Defect                      */
		(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

			/*!Comment : Re-Init Retires Counter                                */
			strHspmManagerLog.u8TxRetryCtr = 0;

			/*!Comment : Schedule Next Job                                  */
			strHspmManagerLog.u8JobQueueIndx++;
			vidJobScheduler();

		}
	}
	/*!Comment : Jobs are Processing Normally, Monitor Time-Out Defect          */
	else {

	}
}

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

static void vidClrJobQueue(void) {

	HSPM_ENTER_CRITICAL_SEC();

	strHspmManagerLog.enuStatus = LBTY_IDLE;
	strHspmManagerLog.u8TxRetryCtr = 0;
	strHspmManagerLog.u8JobQueueCtr = 0;
	strHspmManagerLog.u8JobQueueIndx = 0;

	/*!Comment : Init Transmission Time-Out Defect                              */
	(void)LDEM_enuInitDefect(&astrHspmTxTimOutDfct);

	/*!Comment : SPI Driver Request Rejection Defect                            */
	(void)LDEM_enuInitDefect(&astrHspmDrvReqRjctDfct);

	HSPM_LEAVE_CRITICAL_SEC();

}


#endif /* BSW_HSPM */
/***************************** E N D (HSPM_prg.c) *****************************/
