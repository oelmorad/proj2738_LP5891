/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HDIO                                                    */
/* !Description     : Digital input Manager                                   */
/*                                                                            */
/* !Module          : HDIO_prg.c                                              */
/* !Revision        : 1.9                                                     */
/* !Date            : 25 Jan 2021                                             */
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
/* Mohamed gharib -- 26/8/2018 -- cdd requirements coverage                   */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  --  14/ 3 /2019 -- Fixed "Release_14-03-2019" artifacts        */
/*                         Updated Software version/Updated AUTOSAR headers   */
/* Soha Wagdy  -- 10/12/2019   -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Soha Wagdy  --  8 Sep 2020  -- [artf1042820] initialize Local Variables    */
/* Soha Wagdy  -- 23 Nov 2020  -- Updates for the following ACRs:             */
/*                                  [artf1067933 artf267567 artf794236 ]      */
/* Soha Wagdy  -- 17 Dec 2020  -- Closing review points for the               */
/*                         following ACRs:[artf1067933 artf267567 artf794236] */
/* Soha Wagdy  -- 25 Jan 2021  -- [artf1193313] Fix Compiler Warning          */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 28 NOV 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 28 NOV 2016 */
/*                                                                            */
/******************************************************************************/


#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HDIO

/******************************************************************************/
/*                          Header Files included                             */
/******************************************************************************/

#include "LBTY_int.h"
#include "LCTY_int.h"
#include "LFIL_int.h"
#include "LDEM_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HDIO.h"
#include "HFIC_IoHwAb.h"
#endif

#include "MFIC_HDIO_cfg.h"
#include "SFIC_HDIO_cfg.h"

#include "HDIO_int.h"
#include "HDIO_priv.h"

/************************** Private data declaration **************************/

#ifdef BSW_HDIO_INPUT
/******************************************************************************/
/* Buffer contains the unfiltered value of input digital pins                 */
/******************************************************************************/
static u8 HDIO_au8InputUnfilteredBuffer[HDIO_u8IN_MAX_NB];

/******************************************************************************/
/* Buffer contains the filtered value of input digital pins                   */
/******************************************************************************/
static LFIL_tstrFilterData HDIO_astrInputFilteredBuffer[HDIO_u8IN_MAX_NB];

/******************************************************************************/
/* Number of the input signals for the active variant                         */
/******************************************************************************/
static u8 HDIO_u8InpSigNB;

/******************************************************************************/
/* Number of the input signals for the active variant                         */
/******************************************************************************/
static u8 HDIO_u8InpDefectNB;

/******************************************************************************/
/* !Description : Buffer contains voltage source defects                      */
/******************************************************************************/
static LDEM_tstrDefect HDIO_astrDefects [HDIO_u8DEFECT_MAX_NB];

/** \brief \DESIGNER_START state variant Component input Cfg \DESIGNER_END
 *   \details \DESIGNER_START Type HDIO_tstrInputCompConfig / Range NA / Resolution 1 / Unit NA \DESIGNER_END*/
static HDIO_tstrInputCompConfig HDIO_strVarInputCfg;

#endif

#ifdef BSW_HDIO_OUTPUT
/******************************************************************************/
/* Number of the output signals for the active variant                        */
/******************************************************************************/
static u8 HDIO_u8OutSigNB;

/******************************************************************************/
/* Buffer contains the value of output digital pins                           */
/******************************************************************************/
static u8 HDIO_au8OutputBuffer[HDIO_u8OUT_MAX_NB];

/******************************************************************************/
/* Buffer contains the value of output digital pins                           */
/******************************************************************************/
#if HDIO_OUT_PLAUSIBILITY_CHECK == HDIO_ENABLED
static LBTY_tenuBoolean HDIO_u8OutputFaultFlag = LBTY_FALSE;

/** \brief \DESIGNER_START state variant Component output Cfg \DESIGNER_END
 *   \details \DESIGNER_START Type HDIO_tstrOutputCompConfig / Range NA / Resolution 1 / Unit NA \DESIGNER_END*/
static HDIO_tstrOutputCompConfig HDIO_strVarOutputCfg;

#endif
#endif

/******************************************************************************/
/* Software active variant                                                    */
/******************************************************************************/
static u8 HDIO_u8SwVariant;

/******************************************************************************/
/********************************* Zone Services ******************************/
/******************************************************************************/


/******************************************************************************/
/* !Description : This function shall Initialize the HDIO Parameters          */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_001-V03                                 */
/******************************************************************************/
void HDIO_vidInit(void)
{
   /* Variable to hold the loop index */
   u8 u8LoopIndexLoc = 0;
   /******************************************* Check the active varinat ****************************/
   /* Get SW active Variant */
#if HDIO_u8VARIANT_NB > 1U
   HDIO_u8SwVariant = SFIC_u8SvarGetActiveVariant();


   /* if the variant is not correct use the default variant and report error */
   if( HDIO_u8SwVariant < HDIO_u8VARIANT_NB )
   {
      /* Variant is correct, do nothing */
   }

   else
   {
      /* Use default variant */
      HDIO_u8SwVariant = HDIO_u8DEFAULT_VARIANT;

      /* Report error */
   }
#else
   HDIO_u8SwVariant = 0;
#endif


#ifdef BSW_HDIO_INPUT
   /*update HDIO_strVarInputCfg to contain variant cfgs */
   HDIO_strVarInputCfg = HDIO_astrInputCompConfigp[HDIO_u8SwVariant];
   /* Get the input signals number for the active variant  */
   HDIO_u8InpSigNB = HDIO_strVarInputCfg.HDIO_u8InputNB;

   /* Get the input defects number for the active variant  */
   HDIO_u8InpDefectNB = HDIO_strVarInputCfg.HDIO_u8DefectsNB;
#endif

#ifdef BSW_HDIO_OUTPUT
   /*update HDIO_strVarOutputCfg to contain variant cfgs */
   HDIO_strVarOutputCfg = HDIO_astrOutputCompConfigp[HDIO_u8SwVariant];
   /* Get the output signals number for the active variant  */
   HDIO_u8OutSigNB = HDIO_strVarOutputCfg.HDIO_u8OutputNB;
#endif
#ifdef BSW_HDIO_INPUT
   /* For all inputs, read the instantaneous value and initialize the filter buffer */
   for(u8LoopIndexLoc = 0; u8LoopIndexLoc < HDIO_u8InpSigNB; u8LoopIndexLoc++)
   {
      vidHdioGetInputPin(u8LoopIndexLoc);
   }
#endif

#ifdef BSW_HDIO_OUTPUT
   /* For all outputs, read the value and initialize the buffer */
   for(u8LoopIndexLoc = 0; u8LoopIndexLoc < HDIO_u8OutSigNB; u8LoopIndexLoc++)
   {
      vidHdioGetOutputPin(u8LoopIndexLoc);
   }
#endif

}

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Read DIO pins and apply the filtration mechanism          */
/*                - Update Input defects with unfiltered/filtered values      */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_002-V04                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
void HDIO_vidRunnableUpdateInput(void)
{

   /* Variable to hold the loop index */
   u8 u8LoopIndexLoc = 0;



   /* Variable to hold the index of the loop */
   u8 u8IdxLoc=0;
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif

   /* For each Input, read and call filtering function */
   for(u8LoopIndexLoc = 0; u8LoopIndexLoc < HDIO_u8InpSigNB; u8LoopIndexLoc++)
   {
      vidHdioFilterInputPin (u8LoopIndexLoc);
   }

   /********************************** Update defect values **************************************/
   for(u8IdxLoc=0 ; u8IdxLoc < HDIO_u8InpDefectNB ; u8IdxLoc++ )
   {
      /**: Call vidHdioUpdInputDefect ;*/
      vidHdioUpdInputDefect (u8IdxLoc);
   }

#if HDIO_IN_ALIVENESS_SUPERVISSION == HDIO_ENABLED

#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   enuErrorStatusLoc = SFIC_enuHdioInputCP();
   /* check on Error return*/
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,HDIO_vidRunnableUpdateInput_SID ,SFIC_u8DET_HDIO_INPUT_CP_ERROR );
   }

   else
   {
      /* Do Nothing */
   }
#else
   /* report reaching check point*/
   (void)SFIC_enuHdioInputCP();
#endif
#endif

}
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Refresh the output pins                                   */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_003-V03                                 */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
void HDIO_vidRunnableUpdateOutput(void)
{
   /* Variable to hold the loop index */
   u8 u8LoopIndexLoc;


#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif

   /* For all outputs  */
   for(u8LoopIndexLoc = 0; u8LoopIndexLoc < HDIO_u8OutSigNB; u8LoopIndexLoc++)
   {
      vidHdioUpdateOutput(u8LoopIndexLoc);
   }

#if HDIO_OUT_ALIVENESS_SUPERVISSION == HDIO_ENABLED
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   enuErrorStatusLoc = SFIC_enuHdioOutputCP();
   /* check on Error return*/
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,HDIO_vidRunnableUpdateInput_SID ,SFIC_u8DET_HDIO_OUTPUT_CP_ERROR);
   }

   else
   {
      /* Do Nothing */
   }
#else
   /* report reaching check point*/
   (void)SFIC_enuHdioOutputCP();
#endif
#endif

}
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Return Fault notification to user SWC for                 */
/*      plausibility checks to Output signals                                 */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_013-V01                                                       */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
#if HDIO_OUT_PLAUSIBILITY_CHECK == HDIO_ENABLED
void HDIO_vidRunnableReadOutput(void)
{
   /* Variable to hold the loop index */
   u8 u8LoopIndexLoc = 0;

   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc = 0;

   /* Variable to hold the Read state */
   u8 u8ReadStateLoc = 0;

   /* Reset the output fault flag */
   HDIO_u8OutputFaultFlag = LBTY_FALSE;

   /* For each Input, read and call filtering function */
   for(u8LoopIndexLoc = 0; u8LoopIndexLoc < HDIO_u8OutSigNB; u8LoopIndexLoc++)
   {
      /* Enter Critical Zone */
      SFIC_vidEnterCriticalZone();

      /* Get One shot value of the digital Output pin */
      (void)MFIC_stdGetIoPinValue((HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig)[u8LoopIndexLoc].u8DioPinId
         ,&u8ReadStateLoc);

      /* Get the physical state from the logical state */
      u8DigitalStateLoc = u8GET_PHYSICAL_STATE(u8LoopIndexLoc,
         HDIO_au8OutputBuffer[u8LoopIndexLoc],
         (HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig));

      /* Exit Critical Zone */
      SFIC_vidLeaveCriticalZone();

      /* check if the Read value is the same as the Digital state */
      if(u8DigitalStateLoc != u8ReadStateLoc)
      {
         /* Raise Flag for this Pin */
         HDIO_u8OutputFaultFlag = LBTY_TRUE;
      }
      else
      {
         /* Do Nothing */
      }
   }
}
#endif
#endif

/******************************************************************************/
/* !Description : This function return the HDIO software version information  */
/* !Input       : pstrVersionInfo -> Pointer to return the version information*/
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_004-V02                                 */
/******************************************************************************/
LBTY_tenuErrorStatus HDIO_enuGetVersionInfo(LBTY_tstrVersionInfoType *pstrVersionInfo)
{

   /******************************************************************************/
   /* Buffer contains the software module version                                */
   /******************************************************************************/
   LBTY_tstrVersionInfoType LOC_strVersion  = {HDIO_u16VendorID, HDIO_u16ModuleID, HDIO_u8SwMajorVersion,
      HDIO_u8SwMinorVersion, HDIO_u8SwPatchVersion};

   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK; /* Return error status */

   /* Check the pointer allocation */
   if(LBTY_NULL != pstrVersionInfo)
   {
      pstrVersionInfo->u16VendorID      = LOC_strVersion.u16VendorID;
      pstrVersionInfo->u16ModuleID      = LOC_strVersion.u16ModuleID;
      pstrVersionInfo->u8SwMajorVersion = LOC_strVersion.u8SwMajorVersion;
      pstrVersionInfo->u8SwMinorVersion = LOC_strVersion.u8SwMinorVersion;
      pstrVersionInfo->u8SwPatchVersion = LOC_strVersion.u8SwPatchVersion;

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

/******************************************************************************/
/* !Description : This function shall get the unfiltered one shot state for   */
/*                input digital pin                                           */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the unfiltered state   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_006-V03                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputOneShot(u8 u8InputIdCpy, u8 *pu8SigStateCpy)
{
   /* Return error status */
   LBTY_tenuErrorStatus enuErrStatusLoc= LBTY_OK;

   /* Logical state */
   u8 u8DigitalStateLoc = 0;

   /* Check if the ID is in the bounds */
   if(u8InputIdCpy < HDIO_u8InpSigNB)
   {
      if( pu8SigStateCpy != LBTY_NULL)
      {
         /* Get One shoot value of the digital input pin */
         (void) MFIC_stdGetIoPinValue(
            (HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig)[u8InputIdCpy].u8DioPinId
            ,&u8DigitalStateLoc);

         /* Get the logical state on or off */
         HDIO_au8InputUnfilteredBuffer[u8InputIdCpy] = u8GET_LOGICAL_STATE(u8InputIdCpy,
            u8DigitalStateLoc,
            (HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig));

         *pu8SigStateCpy = HDIO_au8InputUnfilteredBuffer[u8InputIdCpy];
      }

      else
      {
         /* Notify a NULL pointer error */
         enuErrStatusLoc = LBTY_NULL_POINTER;
      }
   }

   else
   {
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }

   /* Return Error status */
   return(enuErrStatusLoc);
}
#endif

/******************************************************************************/
/* !Description : This function shall get the unfiltered state for input      */
/*                digital pin                                                 */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the unfiltered state   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_005-V03                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputUnfiltered(u8 u8InputIdCpy, u8 *pu8SigStateCpy)
{
   /* Return error status */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;
   

   /* Check if the ID is in the bounds */
   if(u8InputIdCpy < HDIO_u8InpSigNB)
   {
      if( pu8SigStateCpy != LBTY_NULL)
      {
         *pu8SigStateCpy = HDIO_au8InputUnfilteredBuffer[u8InputIdCpy];
      }

      else
      {
         /* Notify a NULL pointer error */
         enuErrStatusLoc = LBTY_NULL_POINTER;
      }
   }

   else
   {
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }

   /* Return Error status */
   return(enuErrStatusLoc);
}
#endif

/******************************************************************************/
/* !Description : This function shall get the filtered state for input        */
/*                digital pin                                                 */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the filtered state     */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_007-V03                                 */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputfiltered(u8 u8InputIdCpy, u8 *pu8SigStateCpy)
{
   /* Return error status */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;


   /* Check if the ID is in the bounds */
   if(u8InputIdCpy < HDIO_u8InpSigNB)
   {
      if( pu8SigStateCpy != LBTY_NULL)
      {
         *pu8SigStateCpy = (u8)(HDIO_astrInputFilteredBuffer[u8InputIdCpy].u16FilteredData);
      }

      else
      {
         /* Notify a NULL pointer error */
         enuErrStatusLoc = LBTY_NULL_POINTER;
      }
   }

   else
   {
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }

   /* Return Error status */
   return(enuErrStatusLoc);
}


/******************************************************************************/
/* !Description : Get HDIO Pin defect status                                  */
/* !Input       : u8IdCpy -> Index of defect                                  */
/*                penuDefect -> Pointer to return the status in it            */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_010-V02                                 */
/******************************************************************************/
LBTY_tenuErrorStatus HDIO_enuGetDefectState(u8 u8IdCpy, LDEM_tenuDefectState *penuDefect)
{
   /* Variable to hold the return status */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_OK;

   /* Variable to hold defect state temporarily */
   LDEM_tenuDefectState enuDefectLoc = LDEM_enuDEFECT_ABSENT;

   /*!Comment : make sure that the passed pointer is not NULL */
   if( penuDefect != LBTY_NULL)
   {
      /*!Comment : make sure that the index is in the valid range */
      if(u8IdCpy < HDIO_u8InpDefectNB)
      {
         enuErrorStatusLoc = LDEM_enuGetValidState(&HDIO_astrDefects[u8IdCpy],&enuDefectLoc);
         if (enuErrorStatusLoc == LBTY_OK)
         {
            *penuDefect = enuDefectLoc;
         }
         else
         {
            /* do nothing. error is reported */
         }
      }
      else
      {
         enuErrorStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
      }
   }
   else
   {
      /* Notify a NULL pointer error */
      enuErrorStatusLoc = LBTY_NULL_POINTER;
   }

   return enuErrorStatusLoc;

}

/******************************************************************************/
/* !Description : Freeze/Unfreeze defect                                      */
/* !Input       : u8IdCpy  -> Index of the defect                             */
/*                enuState -> Required freezing state                         */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_011-V02                                 */
/******************************************************************************/
LBTY_tenuErrorStatus HDIO_enuSetFreezeDfctState(u8 u8IdCpy, LDEM_tenuFreezeState enuState)
{
   LBTY_tenuErrorStatus enuStatus = LBTY_OK;

   /*!Comment : make sure that the index is in the valid range */
   if( u8IdCpy < HDIO_u8InpDefectNB )
   {
      enuStatus = LDEM_enuSetFreezingState(&HDIO_astrDefects[u8IdCpy],enuState);
   }

   /*!Comment: Invalid Index, report error  */
   else
   {
      enuStatus=LBTY_INDEX_OUT_OF_RANGE;
   }

   return(enuStatus);
}

/******************************************************************************/
/* !Description : Re-initialize defect according to passed ID                 */
/* !Input       : u8IdCpy  -> Index of the defect                             */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_012-V02                                 */
/******************************************************************************/
LBTY_tenuErrorStatus HDIO_enuResetDefect(u8 u8IdCpy)
{
   /* Local Variable for Error Status Return and set it with OK */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /* if(Check if the Defect is within range) then (true) */
   if( u8IdCpy < HDIO_u8InpDefectNB )
   {
      /* Call  LDEM_enuInitDefect to reset defect with the passed defect ID */
      enuErrStatusLoc = LDEM_enuInitDefect(&HDIO_astrDefects[u8IdCpy]);
   }
   else /* else (False) */
   {
      /** Report error Index out of range */
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }
   /* endif */

   /* Return Error Status */
   return enuErrStatusLoc;
}

#endif

/******************************************************************************/
/* !Description : This function shall set the digital state for output pin    */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                u8SigStateCpy-> Required digital state                      */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_008-V02                                 */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
LBTY_tenuErrorStatus HDIO_enuSetOutputState(u8 u8OutputIdCpy, u8 u8SigStateCpy)
{
   /* Return error status */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc = 0;

   /* Check if the ID is in the bounds */
   if( (u8OutputIdCpy < HDIO_u8OutSigNB) && (u8SigStateCpy < HDIO_UNDEFINED) )
   {
      /* Update the output buffer */
      HDIO_au8OutputBuffer[u8OutputIdCpy] = u8SigStateCpy;

      /* Get the physical state from the logical state */
      u8DigitalStateLoc = u8GET_PHYSICAL_STATE(u8OutputIdCpy,u8SigStateCpy,
         (HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig));

      /* Check that the pin level in a known signal, else return a write error */
      if(u8DigitalStateLoc == MFIC_u8IO_PIN_HIGH)
      {
         (void)MFIC_stdSetIoPinValue((HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig)[u8OutputIdCpy]
                                                                                         .u8DioPinId);
      }
      else
      {
         (void) MFIC_stdRstIoPinValue((HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig)[u8OutputIdCpy]
                                                                                          .u8DioPinId);
      }

   }

   else
   {
      /* Out of index */
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }


   /* Return Error status */
   return(enuErrStatusLoc);
} 
#endif

/******************************************************************************/
/* !Description : This function shall get the digital state for output pin    */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy-> pointer to the digital state               */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_009-V03                                 */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
LBTY_tenuErrorStatus HDIO_enuGetOutputState(u8 u8OutputIdCpy, u8* pu8SigStateCpy)
{
   /* Return error status */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;


   /* Check if the ID is in the bounds */
   if( u8OutputIdCpy < HDIO_u8OutSigNB )
   {
      if( pu8SigStateCpy != LBTY_NULL)
      {
         *pu8SigStateCpy= HDIO_au8OutputBuffer[u8OutputIdCpy];
      }

      else
      {
         /* Notify a NULL pointer error */
         enuErrStatusLoc = LBTY_NULL_POINTER;
      }
   }

   else
   {
      enuErrStatusLoc = LBTY_INDEX_OUT_OF_RANGE;
   }

   /* Return Error status */
   return(enuErrStatusLoc);
}
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Return Fault Flag for Output signals check                */
/* !Input       : void                                                        */
/* !Output      : LBTY_tenuBoolean , Range: LBTY_TRUE - LBTY_FALSE                          */
/* !Scope       : Public                                                      */
/* !Trace_To    : Covers_SWC_HDIO_CDD_014-V01                                                            */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
#if HDIO_OUT_PLAUSIBILITY_CHECK == HDIO_ENABLED
LBTY_tenuBoolean HDIO_enuGetOutputFault(void)
{
   /* Return Fault Flag */
   return(HDIO_u8OutputFaultFlag);
}
#endif
#endif


#ifdef BSW_HDIO_INPUT
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Get Input Pin                                              */
/* !Input       : u8Idx ->  Channel Index                                                        */
/* !Output      : void                          */
/* !Scope       : private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioGetInputPin(u8 u8Idx)
{
   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc;
   /* Variable to hold Index of the loop */
   u8 u8IdxLoc ;
   /* Variable to hold DIO pin */
   u8 u8DioPinLoc;
   /* Variable to hold number of samples*/
   u8 u8NumOfSamplesLoc;
   /* Variable to hold initial nominal value */
   u16 u16InitNominalValuesLoc;
   /* Variable to hold defects conifg  */
   const LDEM_tstrDefectConfig* kpstrDefectConfigLoc;
   /* Variable to hold digital input config */
   const HDIO_tstrDioSig* pstrDigitalInputConfigLoc;
   /* Variable to hold the initialization mechanism of a pin */
   u8 u8InitMechanism = 0;
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* store dio pin in local variable */
  u8DioPinLoc = (HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig)[u8Idx].u8DioPinId;
  /* store number of samples in local variable */
  u8NumOfSamplesLoc =(HDIO_strVarInputCfg.HDIO_ptrInSigFltrMechanism)[u8Idx].u8NumOfSamples ;
  /* store initial nominal value in local variable */
  u16InitNominalValuesLoc =(u16)(HDIO_strVarInputCfg.HDIO_ptrInSigFltrMechanism)[u8Idx].u8InitNominalValues;
  /* store defects conifg  in local variable */
  kpstrDefectConfigLoc = HDIO_strVarInputCfg.HDIO_pstrDefectConfig;
  /* store digital input config in local variable */
  pstrDigitalInputConfigLoc = HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig ;
   /* Get One shoot value of the digital input pin */
   enuErrorStatusLoc = MFIC_stdGetIoPinValue(u8DioPinLoc,&u8DigitalStateLoc);
   /* check on error status returned */
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID, vidHdioGetInputPin_SID,SFIC_u8DET_DDIO_GETPIN_ERROR);
   }

   else
   {
      /* Do Nothing */
   }

#else
   /* Get One shoot value of the digital input pin */
   (void)MFIC_stdGetIoPinValue(
      (HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig)[u8Idx].u8DioPinId
      ,&u8DigitalStateLoc);
#endif

   /* Get the logical state on or off */
   HDIO_au8InputUnfilteredBuffer[u8Idx] = u8GET_LOGICAL_STATE(u8Idx, u8DigitalStateLoc,pstrDigitalInputConfigLoc);

   /* Get the initialization mechanism set for this pin */
   u8InitMechanism =
      (HDIO_strVarInputCfg.HDIO_ptrInSigFltrMechanism)[u8Idx].u8InitializationMechanism;

#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* check if the initialization mechanism set for this pin is from unfiltered buffer */
   if( HDIO_u8FROM_UNFILT_BUFR == u8InitMechanism )
   {
      /* Initialize the filteration array from unfiltered value */
      enuErrorStatusLoc = LFIL_enuInitFilSamples(&HDIO_astrInputFilteredBuffer[u8Idx],
         (u16)HDIO_au8InputUnfilteredBuffer[u8Idx],u8NumOfSamplesLoc);
   }
   else
   {
      /* Initialize the filtration array from nominal value*/
      enuErrorStatusLoc = LFIL_enuInitFilSamples(&HDIO_astrInputFilteredBuffer[u8Idx],u16InitNominalValuesLoc,
         u8NumOfSamplesLoc);
   }

   /* check on error status returned */
   if(LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioGetInputPin_SID,SFIC_u8DET_LFIL_ERROR);

   }
   else
   {
      /* Do Nothing */
   }
#else
   /* check if the initialization mechanism set for this pin is from unfiltered buffer */
   if( HDIO_u8FROM_UNFILT_BUFR == u8InitMechanism )
   {
      /* Initialize the filteration array from unfiltered value */
      (void)LFIL_enuInitFilSamples(&HDIO_astrInputFilteredBuffer[u8Idx],
         (u16)HDIO_au8InputUnfilteredBuffer[u8Idx],u8NumOfSamplesLoc);
   }
   else
   {
      /* Initialize the filtration array from nominal value*/
      (void)LFIL_enuInitFilSamples(&HDIO_astrInputFilteredBuffer[u8Idx],u8InitNominalValuesLoc,
         u8NumOfSamplesLoc);
   }
#endif


   /* Initialize Input defects as configured */
   for( u8IdxLoc = 0 ; u8IdxLoc < HDIO_u8InpDefectNB ; u8IdxLoc++ )
   {
      HDIO_astrDefects[u8IdxLoc].pstrConfig = &(kpstrDefectConfigLoc[u8IdxLoc]);
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
      enuErrorStatusLoc = LDEM_enuInitDefect(&HDIO_astrDefects[u8IdxLoc]);

      /* check on error status returned */
      if( LBTY_OK != enuErrorStatusLoc )
      {
         /* Report an Error */
         SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioGetInputPin_SID,SFIC_u8DET_LDEM_ERROR);
      }
      else
      {
         /* Do Nothing */
      }
#else
      (void)LDEM_enuInitDefect(&HDIO_astrDefects[u8IdxLoc]);
#endif
   }
}
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - update input defects                */
/* !Input       : u8IdxLoc ->  defect Index                                                          */
/* !Output      : void                          */
/* !Scope       : Private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioUpdInputDefect (u8 u8IdxLoc)
{
   /* Variable to hold the pin index */
   u8 u8PinIndexLoc = 0;
   /* Variable to hold defect pin */
   u8PinIndexLoc = (HDIO_strVarInputCfg.HDIO_pu8DefectToPinLink)[u8IdxLoc];
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif
   if (u8PinIndexLoc < HDIO_u8InpSigNB)
   {
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
      if( (HDIO_strVarInputCfg.HDIO_ptrDefectType)[u8IdxLoc] == HDIO_u8UNFILT_VAL)
      {
         /* Update the defect with the unfiltered read value */
         enuErrorStatusLoc = LDEM_enuUpdateDefect(
            &HDIO_astrDefects[u8IdxLoc],(u16)HDIO_au8InputUnfilteredBuffer[u8PinIndexLoc]);
      }
      else if( (HDIO_strVarInputCfg.HDIO_ptrDefectType)[u8IdxLoc] == HDIO_u8FILT_VAL)
      {
         /* Update the defect with the filtered value */
         enuErrorStatusLoc = LDEM_enuUpdateDefect(
            &HDIO_astrDefects[u8IdxLoc],HDIO_astrInputFilteredBuffer[u8PinIndexLoc].u16FilteredData);
      }
      else
      {
         SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID, vidHdioUpdInputDefect_SID,SFIC_u8DET_LDEM_ERROR);
      }
      /* check on error status returned */
      if( LBTY_OK != enuErrorStatusLoc )
      {
         /* Report an Error */
         SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID, vidHdioUpdInputDefect_SID,SFIC_u8DET_HDIO_CFG_ERROR);
      }
      else
      {
         /* Do Nothing */
      }
#else
      if( (HDIO_strVarInputCfg.HDIO_ptrDefectType)[u8IdxLoc] == HDIO_u8UNFILT_VAL)
      {
         /* Update the defect with the unfiltered read value */
         (void)LDEM_enuUpdateDefect(
            &HDIO_astrDefects[u8IdxLoc],(u16)HDIO_au8InputUnfilteredBuffer[u8PinIndexLoc]);
      }
      else if( (HDIO_strVarInputCfg.HDIO_ptrDefectType)[u8IdxLoc] == HDIO_u8FILT_VAL)
      {
         /* Update the defect with the filtered value */
         (void)LDEM_enuUpdateDefect(
            &HDIO_astrDefects[u8IdxLoc],HDIO_astrInputFilteredBuffer[u8PinIndexLoc].u16FilteredData);
      }
#endif
   }
   /* incorrect Pin index */
   else
   {
      /* Report Error */
   }
}
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - update filter input pin                */
/* !Input       : u8IdxLoc ->   Channel Index                                                            */
/* !Output      : void                          */
/* !Scope       : Private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioFilterInputPin (u8 u8Idx)
{
   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc = 0;
   u8 u8DioPinIdLoc;
   const HDIO_tstrDioSig* pstrDigitalInputConfigLoc;
   u8DioPinIdLoc = HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig[u8Idx].u8DioPinId;
   pstrDigitalInputConfigLoc = HDIO_strVarInputCfg.HDIO_pstrDigitalInputConfig;
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)

   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
   /* Get One shoot value of the digital input pin */
   enuErrorStatusLoc = MFIC_stdGetIoPinValue(u8DioPinIdLoc,&u8DigitalStateLoc);
   /* check on error status returned */
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioFilterInputPin_SID,SFIC_u8DET_DDIO_GETPIN_ERROR);
   }

   else
   {
      /* Do Nothing */
   }
#else
   /* Get One shoot value of the digital input pin */
   (void) MFIC_stdGetIoPinValue(u8DioPinIdLoc,&u8DigitalStateLoc);
#endif
   /* Get the logical state on or off */
   HDIO_au8InputUnfilteredBuffer[u8Idx] = u8GET_LOGICAL_STATE(u8Idx,u8DigitalStateLoc,pstrDigitalInputConfigLoc);
   vidHdioFiltertionMechanism (u8Idx);
}
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - update filteration Mechanism               */
/* !Input       : u8IdxLoc ->   Channel Index                                                            */
/* !Output      : void                          */
/* !Scope       : Private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioFiltertionMechanism (u8 u8IdxCpy)
{
   /* Variable to hold filtration mechanism */
   u8 u8FilterationMechanismLoc;
   /* Variable to hold Majority cap  */
   const u8* pu8MajorityCapLoc;
   /* Variable to hold Consecutive Cap  */
   const u8* pu8ConsecutiveCapLoc;
   /*Store filtration mechanism in local variable*/
   u8FilterationMechanismLoc =(HDIO_strVarInputCfg.HDIO_ptrInSigFltrMechanism)[u8IdxCpy].u8FilterationMechanism;
   /*Store Majority cap in local variable*/
   pu8MajorityCapLoc = HDIO_strVarInputCfg.HDIO_pu8MajorityCap;
   /*Store Consecutive Cap in local variable*/
   pu8ConsecutiveCapLoc = (HDIO_strVarInputCfg.HDIO_pu8ConsecutiveCap);

#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)

   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif
   /* check the type of the filtration */
   switch(u8FilterationMechanismLoc)
   {
      /* Majority filter */
      case HDIO_u8MAJORITY_FILTER:
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
         enuErrorStatusLoc = LFIL_enuMajorityFilter( &HDIO_astrInputFilteredBuffer[u8IdxCpy],
            (u16)HDIO_au8InputUnfilteredBuffer[u8IdxCpy],pu8MajorityCapLoc[u8IdxCpy]);
         /* check on error status returned */
         if( LBTY_OK != enuErrorStatusLoc )
         {
            /* Report an Error */
            SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioFiltertionMechanism_SID,SFIC_u8DET_LFIL_ERROR);
         }

         else
         {
            /* Do Nothing */
         }
#else
         (void)LFIL_enuMajorityFilter( &HDIO_astrInputFilteredBuffer[u8IdxCpy],
            (u16)HDIO_au8InputUnfilteredBuffer[u8IdxCpy],
            pu8MajorityCapLoc[u8IdxCpy]);
#endif
         break;

         /* Consecutive filter */
      case HDIO_u8CONSECUTIVE_FILTER:
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
         enuErrorStatusLoc = LFIL_enuConsecutiveVal(&HDIO_astrInputFilteredBuffer[u8IdxCpy],
            (u16)HDIO_au8InputUnfilteredBuffer[u8IdxCpy], pu8ConsecutiveCapLoc[u8IdxCpy]);
         /* check on error status returned */
         if( LBTY_OK != enuErrorStatusLoc )
         {
            /* Report an Error */
            SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioFiltertionMechanism_SID,SFIC_u8DET_LFIL_ERROR);
         }

         else
         {
            /* Do Nothing */
         }
#else
         (void)LFIL_enuConsecutiveVal(&HDIO_astrInputFilteredBuffer[u8IdxCpy],
            (u16)HDIO_au8InputUnfilteredBuffer[u8IdxCpy],pu8ConsecutiveCapLoc[u8IdxCpy]);
#endif
         break;


         /* No filteration required, set the filtered value equals to non filtered value */
      case HDIO_u8NO_FILTER:
         HDIO_astrInputFilteredBuffer[u8IdxCpy].u16FilteredData  = HDIO_au8InputUnfilteredBuffer[u8IdxCpy];
      break;


      /* Filter type is not correct, report error and set the filtered value as unfiltered*/
      default:
         HDIO_astrInputFilteredBuffer[u8IdxCpy].u16FilteredData  = HDIO_au8InputUnfilteredBuffer[u8IdxCpy];
      break;
   }/* !Comment :  ToDo -> assess the need to check on the return of LFIL  */
}
#endif
#ifdef BSW_HDIO_OUTPUT
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Get output pin value                */
/* !Input       : u8IdxLoc ->   Channel Index                                                            */
/* !Output      : void                          */
/* !Scope       : Private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioGetOutputPin(u8 u8Idx)
{
   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc = 0;


#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
   /* Get One shoot value of output pin */
   enuErrorStatusLoc = MFIC_stdGetIoPinValue((HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig)[u8Idx].u8DioPinId
      ,&u8DigitalStateLoc);
   /* check on error status returned */
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,vidHdioGetOutputPin_SID,SFIC_u8DET_DDIO_GETPIN_ERROR);
   }

   else
   {
      /* Do Nothing */
   }
#else
   /* Get One shoot value of output pin */
   (void)MFIC_stdGetIoPinValue((HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig)[u8Idx].u8DioPinId
      ,&u8DigitalStateLoc);
#endif
   /* Get the logical state on or off */
   HDIO_au8OutputBuffer[u8Idx] = u8GET_LOGICAL_STATE(u8Idx,
      u8DigitalStateLoc,
      (HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig));

}
/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - update filter input pin                */
/* !Input       : u8IdxLoc ->   Channel Index                                                            */
/* !Output      : void                          */
/* !Scope       : Private                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void vidHdioUpdateOutput(u8 u8IdxCpy)
{

   /* Variable to hold the digital state */
   u8 u8DigitalStateLoc ;
   /* Variable to hold the Dio output pin */
   u8 u8DioOutputPin;
   /* Variable to hold the Dio output buffer */
   u8 u8DioOutputBuffer;
   /* Variable to hold the digital output configuration */
   const HDIO_tstrDioSig* pstrDigitalOutputConfig ;
#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)
   /* Variable to hold the return status of any function */
   LBTY_tenuErrorStatus enuErrorStatusLoc = LBTY_NOK;
#endif
   /* Variable to hold the digital state */
   u8DioOutputBuffer= HDIO_au8OutputBuffer[u8IdxCpy];
   /* Variable to hold the digital state */
   pstrDigitalOutputConfig =(HDIO_strVarOutputCfg.HDIO_pstrDigitalOutputConfig);
   /* Variable to hold the digital state */
   u8DioOutputPin = (pstrDigitalOutputConfig)[u8IdxCpy].u8DioPinId;
   SFIC_vidEnterCriticalZone();
   /* Get the physical state from the logical state */
   u8DigitalStateLoc = u8GET_PHYSICAL_STATE(u8IdxCpy,u8DioOutputBuffer,pstrDigitalOutputConfig);

#if (HDIO_u32DET_REPORTING == HDIO_u32DET_USED)

   /* Check if the pin level is High or Low */
   if(u8DigitalStateLoc == MFIC_u8IO_PIN_HIGH)
   {
      enuErrorStatusLoc = MFIC_stdSetIoPinValue(u8DioOutputPin);
   }
   else
   {
      enuErrorStatusLoc = MFIC_stdRstIoPinValue(u8DioOutputPin);
   }

   /* check on error status returned */
   if( LBTY_OK != enuErrorStatusLoc )
   {
      /* Report an Error */
      SFIC_vidDetReportError(HDIO_u16ModuleID,(u8)HDIO_u16VendorID,HDIO_vidRunnableUpdateOutput_SID ,SFIC_u8DET_DDIO_RST_ERROR);
   }

   else
   {
      /* Do Nothing */
   }
#else
   /* Check if the pin level is High or Low */
   if(u8DigitalStateLoc == MFIC_u8IO_PIN_HIGH)
   {
      (void)  MFIC_stdSetIoPinValue(u8DioOutputPin);
   }
   else
   {
      (void) MFIC_stdRstIoPinValue(u8DioOutputPin);
   }
#endif
   SFIC_vidLeaveCriticalZone();
}
#endif

#endif
/*************************** E N D (HDIO_prg.c) ******************************/
