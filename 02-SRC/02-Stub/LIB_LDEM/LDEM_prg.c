/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LDEM_prg.c
 *  Component: \swc_name
 *  \brief     \DESIGNER_START Library of defect management (LDEM) \DESIGNER_END
 *  \details   \DESIGNER_START Diagnostic Event Manager library responsible for processing and storing diagnostic events (errors) \DESIGNER_END
 *  \n\n
 *  Scope: Private
 *  \n\n
 *  Coding language : C
 *    \copydoc _prgc
 *  \copydoc COPYRIGHT
 */


/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                        Initial Creation                                                                                      ||||
 *     | LDEM_prg.c       | V1.0         |Proposed             | \verbatim $Rev::  11               $: Revision of last commit \endverbatim  |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 11/10/2016       #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Ahmed Assaf    $: Author of last commit   \endverbatim  |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                updating covered requirement in code ||||
 *     | LDEM_prg.c       | V1.0         |Proposed             | \verbatim $Rev::  11           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 27/8/2018    #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: mgharib   $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     | Update code aftr applying MISRA issues remarks ||||
 *     | LDEM_prg.c       | V1.1         |Proposed             | \verbatim $Rev::  11           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 13/1/2019    #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Soha wagdy   $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                        migration to Doxygen ||||
 *     | LDEM_prg.c       | V1.1         |Proposed             | \verbatim $Rev::  11                   $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 13/04/2020           #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Dina Shinaishin    $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                   Add new Unfreeze action to LDEM        ||||
 *     | LDEM_prg.c       | V1.2         |Proposed             | \verbatim $Rev::  226                 $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 28/04/2020          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Dina Shinaishin     $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                   Update new Unfreeze action to LDEM        ||||
 *     | LDEM_prg.c       | V1.3         |Proposed             | \verbatim $Rev::  226                 $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 13/05/2020          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Ahmed Assaf     $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                   Initialize local variables      ||||
 *     | LDEM_prg.c       | V1.4         |Proposed             | \verbatim $Rev::  243                $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::27/09/2020          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Dina Shinaishin     $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |                   Update private function vidUpdateDfctCounter arifact no (artf833717 )       ||||
 *     | LDEM_prg.c       | V1.5         |Proposed             | \verbatim $Rev::  245                $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::11/10/2020          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Dina Shinaishin     $: Author of last commit   \endverbatim |
 */

/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     | Update the module with 2APIs LDEM_enuDefectDetection1D and LDEM_enuDefectDetection2D and update the CDD.        ||||
 *     | LDEM_prg.c       | V1.6         |Proposed             | \verbatim $Rev::    248              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::   19/05/2021      #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Youstina SORIAL  $: Author of last commit   \endverbatim |
 */

/** \page _prgc LDEM_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     | Fixing Klocwork mandatory issues.        ||||
 *     | LDEM_prg.c       |\CoreVersion | \CoreVersion_Status  | \verbatim $Rev::    249              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::   23/05/2021      #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Youstina SORIAL  $: Author of last commit   \endverbatim |
 */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "LBTY_int.h"
#include "LDEM_int.h"
#include "LDEM_cfg.h"
#include "LDEM_priv.h"


#include "SFIC_LDEM.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************* PUBLIC FUNCTION SECTION ************************ */
/* ************************************************************************** */
#if (PLTF_DEFECTMNG ==  PLTF_DEFECT_LDEM )
/**
 *   \brief \DESIGNER_START LDEM initialization function \DESIGNER_END
 *   \details \DESIGNER_START This function initializes the defect parameters to its initial state. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]   pstrDefect \DESIGNER_START Pointer to the defect structure to be initialized / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return status value \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK          : Execution success.
 *               - LBTY_NULL_POINTER: Null output parameter detected.
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_001-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START  Covers_STD_SRS_VIM_001-V01
 *                      \n Covers_STD_SRS_VIM_002-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM initialization main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuInitDefect()
 *      activate LDEM
 *      LDEM -> LDEM : vidResetDefect()
 *      LDEM --> ENV : Return status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuInitDefect(LDEM_tstrDefect *pstrDefect)
{
   /**
    * LDEM Init Defect activity diagram
    * @startuml
    * title LDEM Init Defect activity diagram
    * start */

   /*Comment: Initialize return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;

   /**
    *if(Check if the pointer is not pointing to NULL) then (true)
    */
   if (LBTY_NULL != pstrDefect)
   {
      /**:Initialize the defect validated state value;*/
      pstrDefect->strValue.enuValidState = pstrDefect->pstrConfig->enuIntialState;

      /**:Initialize the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = pstrDefect->pstrConfig->enuIntialState;

      /**:Initialize the Defect Parameters;*/
      vidResetDefect(pstrDefect);
   }
   /**else(false)*/
   else
   {
      /**:Report Error, Pointer to NULL;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}



/**
 *   \brief \DESIGNER_START LDEM Update defects \DESIGNER_END
 *   \details \DESIGNER_START This function is used to detect the defect and update its state. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]   pstrDefect   \DESIGNER_START Pointer to Defect to be validated          / Type LDEM_tstrDefect* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]       u16ReadValue \DESIGNER_START Read Value to be used for defect detection / Type u16              / Range [0x00..0xFFFF] / Resolution 1  / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Description of the returned value \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK           : Execution success.
 *               - LBTY_NOK          : Execution end with error.
 *               - LBTY_NULL_POINTER : Null output parameter detected.
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_002-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_003-V01
 *                     \n Covers_STD_SRS_VIM_004-V01
 *                     \n Covers_STD_SRS_VIM_005-V01
 *                     \n Covers_STD_SRS_VIM_006-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM Update defects main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuUpdateDefect()
 *      activate LDEM
 *      LDEM -> LDEM : enuUpadteInstState()
 *      LDEM -> LDEM : vidUpdateDfctCounter()
 *      LDEM -> LDEM : vidUpdateDefectState()
 *      LDEM --> ENV : return status
 *      deactivate LDEM
 *   @enduml
 */

extern LBTY_tenuErrorStatus LDEM_enuUpdateDefect(LDEM_tstrDefect *pstrDefect, u16 u16ReadValue)
{
   /**
    * LDEM Update Defect activity diagram
    * @startuml
    * title LDEM Update Defect activity diagram
    * start */

   /*Comment: Initialize return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;

   /** if(Check if the pointer is not pointing to NULL) then (true) */
   if ( LBTY_NULL != pstrDefect )
   {
      /** if(Check if the defect is not frozen) then (true) */
      if ( LDEM_enuFREEZED != pstrDefect->strValue.enuFreezeState )
      {
         /**:Get the after update instant state;*/
         enuOperationStatusLoc = enuUpadteInstState(pstrDefect,u16ReadValue);

         /** if(Check if the error status = LBTY_OK) then (true) */
         if(enuOperationStatusLoc == LBTY_OK)
         {
            /**:Update defect counter;*/
            vidUpdateDfctCounter(pstrDefect);

            /**:Update defect validated status;*/
            vidUpdateDefectState(pstrDefect);
         }
         else /**else (false)*/
         {
            /**:Instant status not updated correctly, Do nothing and keep the return NOK;*/
         }
         /**endif*/
      }
      else /**else(false)*/
      {
         /**:Do nothing, Defect is in freeze state ;*/
      }
      /**endif*/
   }
   else /**else (false)*/
   {
      /**:Report Error, NULL pointer received;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}


/**
 *   \brief \DESIGNER_START LDEM Get Version Information \DESIGNER_END
 *   \details \DESIGNER_START This function return the LDEM software version information. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in,out]   pstrVersionInfo \DESIGNER_START Pointer to version structure / Type LBTY_tstrVersionInfoType* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK          : Execution success.
 *               - LBTY_NULL_POINTER: Null output parameter detected.
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_003-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_009-V01 \DESIGNER_END
 *
 *   @startuml
 *   title Get Version Information main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuGetVersionInfo
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */

LBTY_tenuErrorStatus LDEM_enuGetVersionInfo(LBTY_tstrVersionInfoType *pstrVersionInfo)
{
   /*Comment: Buffer contains the software module version                                */
   LBTY_tstrVersionInfoType LOC_strVersion = {(u16)0x59, (u16)0x20, (u8)0x03,(u8)0x00, (u8)0x00};

   /*Comment: Initialize return error status to NOK */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_NOK;

   /**
    *   Get Version Info activity diagram
    * @startuml
    * title Get Version Info activity diagram
    * start
    * if(Check if the passed pointer is NULL) then (valid) */
   if(LBTY_NULL != pstrVersionInfo)
   {

      /**: copy the version info; */
      /* Comment: Set return variable Vendor ID with current module version                                    */
      pstrVersionInfo->u16VendorID      = LOC_strVersion.u16VendorID;
      /**: copy the Module info; */
      /* Comment: Set return variable Module ID with current module version                                    */
      pstrVersionInfo->u16ModuleID      = LOC_strVersion.u16ModuleID;
      /**: copy the Major info; */
      /* Comment: Set return SW Major version with current module version                                      */
      pstrVersionInfo->u8SwMajorVersion = LOC_strVersion.u8SwMajorVersion;
      /**: copy the Minor info; */
      /* Comment: Set return SW minor version with current module version                                      */
      pstrVersionInfo->u8SwMinorVersion = LOC_strVersion.u8SwMinorVersion;
      /**: copy the patch info; */
      /* Comment: Set return SW patch version with current module version                                      */
      pstrVersionInfo->u8SwPatchVersion = LOC_strVersion.u8SwPatchVersion;

      /**:Set return status to LBTY_OK;*/
      enuErrStatusLoc = LBTY_OK;
   }
   /**else (false)*/
   else
   {
      /**:Notify null pointer error;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return Error status;*/
   return(enuErrStatusLoc);
   /**stop*/
   /**@enduml*/
}


/**
 *   \brief \DESIGNER_START LDEM freezing state \DESIGNER_END
 *   \details \DESIGNER_START This function has the ability to Freeze/Unfreeze defect \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out] pstrDefect \DESIGNER_START Pointer to the defect structure to be validated                  / Type LDEM_tstrDefect*     / Range [NA]                               / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]     enuState   \DESIGNER_START Variable to tell if the state of the defect is running or frozen / Type LDEM_tenuFreezeState / Range [LDEM_enuRUNNING, LDEM_enuFREEZED] / Resolution 1  / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK          : Execution success
 *               - LBTY_NOK         : Execution end with error
 *               - LBTY_NULL_POINTER: Null output parameter detected
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_004-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_010-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuSetFreezingState main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuSetFreezingState
 *      activate LDEM
 *      LDEM -> LDEM : vidResetDefect()
 *      LDEM --> ENV : return operation status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuSetFreezingState(LDEM_tstrDefect *pstrDefect, LDEM_tenuFreezeState enuState )
{
   /*Comment: Initialize return error status to ok */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;

   /**
    *  LDEM Set Freezing State activity diagram
    * @startuml
    * title LDEM Set Freezing State activity diagram
    * start */

   /**
    *if(Check if  the pointer is not pointing to NULL) then (true)
    */
   if ( LBTY_NULL != pstrDefect )
   {
      /**
       *if(Check if the Request for unfreeze defect) then (true)
       */
      if ((LDEM_enuRUNNING == enuState) && (LDEM_enuFREEZED == pstrDefect->strValue.enuFreezeState))
      {

         /**
          *if(Check if the required state is to unfreeze the the defect, check the unfreeze action) then (true)
          */
         switch( pstrDefect->pstrConfig->enuUnfreezeAction )
         {
            /**
             *if(Check if the freeze action = LDEM_enuCounter_Reset)  then (true)
             */
            case LDEM_enuCounter_Only_Reset:
               /**:get the error status from the reset defect;*/
               vidResetDefect(pstrDefect);
               break;
               /**
                *elseif(the freeze action = LDEM_enuTotal_Reset) then (true)
                */
            case LDEM_enuTotal_Reset:
               /**: Initialize the defect validated state value;*/
               pstrDefect->strValue.enuValidState = pstrDefect->pstrConfig->enuIntialState;

               /**: Initialize the defect instantaneous state value;*/
               pstrDefect->strValue.enuInsState = pstrDefect->pstrConfig->enuIntialState;

               /**: Get the error status from the reset defect;*/
               vidResetDefect(pstrDefect);
               break;

            case LDEM_enuCounter_Continue:
               /**: Do Nothing, counter should not be changed;*/
               break;
               /**else (false)*/
            default:
               /**: Set error status to be NOK;*/
               enuOperationStatusLoc = LBTY_NOK;
               break;
               /**endif*/
         }
         /**endif*/

         /**:Set the freeze state to be Running;*/
         pstrDefect->strValue.enuFreezeState = LDEM_enuRUNNING;
      }

      /**
       *elseif(Check if the state is freeze) then (true)
       */
      else if (LDEM_enuFREEZED == enuState)
      {
         /**:Set the state to be freezed;*/
         pstrDefect->strValue.enuFreezeState = LDEM_enuFREEZED;
      }
      /**else(false)*/
      else
      {
         /**:Return error status to be NOK;*/
         enuOperationStatusLoc = LBTY_NOK;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:Report Error, NULL pointer received;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}

/**
 *   \brief \DESIGNER_START LDEM instantaneous state \DESIGNER_END
 *   \details \DESIGNER_START This function gets the defect instantaneous state. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]     kpstrDefect \DESIGNER_START Pointer to the defect structure to be validated / Type const LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out] penuState  \DESIGNER_START Pointer to defect status                         / Type LDEM_tenuDefectState*  / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return of the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK           : Execution success
 *               - LBTY_NULL_POINTER : Null output parameter detected
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_005-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_003-V01 \n
 *                        Covers_STD_SRS_VIM_006-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuGetInsState main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuGetInsState()
 *      activate LDEM
 *      LDEM --> ENV : Return operation status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuGetInsState(const LDEM_tstrDefect *kpstrDefect, LDEM_tenuDefectState * penuState)
{
   /*Comment: Initialize return error status to OK */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;
   /**
    *  LDEM Get instantaneous State activity diagram
    * @startuml
    * title LDEM Get instantaneous State  activity diagram
    * start */

   /**
    *if(Check if the pointer is not pointing to NULL) then (true)
    */
   if ( LBTY_NULL != kpstrDefect )
   {
      /**:Update the state with the updated instantaneous state;*/
      *penuState = kpstrDefect->strValue.enuInsState;
   }
   /**else(false)*/
   else
   {
      /**:Report Null pointer as error status;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**Stop*/
   /**@enduml*/
}


/**
 *   \brief \DESIGNER_START LDEM valid state \DESIGNER_END
 *   \details \DESIGNER_START This function gets the defect Validated state. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]     pstrDefect \DESIGNER_START Pointer to the defect structure to be validated / Type LDEM_tstrDefect*      / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out] penuState  \DESIGNER_START Pointer to defect status                        / Type LDEM_tenuDefectState* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return of the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK           : Execution success
 *               - LBTY_NULL_POINTER : Null output parameter detected
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_006-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_008-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuGetValidState main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuGetValidState()
 *      activate LDEM
 *      LDEM --> ENV : return operation status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuGetValidState  (const LDEM_tstrDefect *kpstrDefect, LDEM_tenuDefectState *penuState)
{
   /*Comment: Initialize return error status to OK */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;
   /**
    *  LDEM Get Valid State activity diagram
    * @startuml
    * title LDEM Get Valid State  activity diagram
    * start */

   /**
    *if(Check if the pointer is not pointing to NULL) then (true)
    */
   if ( LBTY_NULL != kpstrDefect )
   {
      /**:Update the value with the valid state value;*/
      *penuState = kpstrDefect->strValue.enuValidState;
   }
   /**else(false)*/
   else
   {
      /**:Report Null pointer error;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}


/**
 *   \brief \DESIGNER_START LDEM counter attributes \DESIGNER_END
 *   \details \DESIGNER_START This function initializes the defect counter attributes. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]     u16IncCpy        \DESIGNER_START Variable that holds the increment value         / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in]     u16DecCpy        \DESIGNER_START Variable that holds the decrement value         / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in]     u16InitVal       \DESIGNER_START Variable that holds the counter initial value   / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in]     u16CtrTh         \DESIGNER_START Variable that holds the counter threshold value / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in,out] pstrDefectConfig \DESIGNER_START Pointer to defect configuration                 / Type LDEM_tstrDefectConfig* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return of the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK           : Execution success
 *               - LBTY_NULL_POINTER : Null output parameter detected
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_007-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_002-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuSetCntrParams main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuSetCntrParams()
 *      activate LDEM
 *      LDEM --> ENV : return operation status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuSetCntrParams(LDEM_tstrDefectConfig *pstrDefectConfig,
   u16 u16IncCpy,
   u16 u16DecCpy,
   u16 u16InitVal,
   u16 u16CtrTh)
{
   /*Comment:  return error status   */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;
   
   /**
    *  LDEM Set Counter Parameters activity diagram
    * @startuml
    * title LDEM Set Counter Parameters  activity diagram
    * start */
   
   /**
    *if(Check if the pointer is not pointing to NULL) then (true)
    */
   if ( LBTY_NULL != pstrDefectConfig )
   {
      /**:Update then increment value'*/
      pstrDefectConfig->u16Increment = u16IncCpy;
      /**:update the decrement value;*/
      pstrDefectConfig->u16Decrement = u16DecCpy;
      /**:update the initial counter value;*/
      pstrDefectConfig->u16CounterInitialValue = u16InitVal;
      /**:Update the counter threshold;*/
      pstrDefectConfig->u16CounterThreshold = u16CtrTh;
      
      /**:Return Error status ot be OK;*/
      enuOperationStatusLoc = LBTY_OK;
   }
   /**else (false) */
   else
   {
      /**:Report Error, Pointer to NULL;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   
   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}

/**
 *   \brief \DESIGNER_START LDEM reading defect values \DESIGNER_END
 *   \details \DESIGNER_START This function initializes the defect reading value thresholds. \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]     u16LowThCpy      \DESIGNER_START Variable that holds the Low threshold value  / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in]     u16HighThCpy     \DESIGNER_START Variable that holds the high threshold value / Type u16                    / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *   \param[in,out] pstrDefectConfig \DESIGNER_START Pointer to defect configuration              / Type LDEM_tstrDefectConfig* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return of the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK           : Execution success
 *               - LBTY_NULL_POINTER : Null output parameter detected
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_008-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_STD_SRS_VIM_001-V01 \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuSetDfctValTh main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuSetDfctValTh()
 *      activate LDEM
 *      LDEM --> ENV : return operation status
 *      deactivate LDEM
 *   @enduml
 */
extern LBTY_tenuErrorStatus LDEM_enuSetDfctValTh(LDEM_tstrDefectConfig *pstrDefectConfig,
   u16 u16LowThCpy,
   u16 u16HighThCpy)
{
   
   /*Comment:  return error status   */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;

   /**
    *  LDEM Set Defect value thresholds activity diagram
    * @startuml
    * title LDEM Set Defect value thresholds activity diagram
    * start */
   
   /**
    *if(Check if the pointer is not pointing to null) then (true)
    */
   if (LBTY_NULL != pstrDefectConfig)
   {
      /**:update the low threshold value;*/
      pstrDefectConfig->u16ThresholdLow = u16LowThCpy;
      /**:update the high threshold value;*/
      pstrDefectConfig->u16ThresholdHigh = u16HighThCpy;
      
      /**:Return LBTY_OK as error status;*/
      enuOperationStatusLoc = LBTY_OK;
   }
   /**else(false)*/
   else
   {
      /**:Report Error, Pointer to NULL;*/
      enuOperationStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   
   /**:Return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}


#endif

#if (PLTF_DEFECTMNG == PLTF_DEFECT_HANDLER )
/**
 *   \brief \DESIGNER_START Defect detection for 1 defect API \DESIGNER_END
 *   \details \DESIGNER_START This function compares the monitored one defect value against configured threshold.  \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]   pstrDetectionConfig \DESIGNER_START Pointer to detection configuration structure                    / Type LDEM_tstrDetectionConfig1D * / Range [NA]               / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]   s32ReadValue        \DESIGNER_START Monitored data value to be evaluated against detection type     / Type u32                          / Range [0x00..0xFFFFFFFF] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[out]  penuDetectionStatus \DESIGNER_START Pointer to the defect detection status  (Detected, Not Detected)/ Type penuDetectionStatus*         / Range [NA]               / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Error status value \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START
 *               - LBTY_OK: Execution success
 *               - LBTY_NOK: Execution Failed
 *               - LBTY_NULL_POINTER: NULL output parameter detected
 *
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_010-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_DEFECT_HANDLER_GDD_LDEM_001-V01  \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuDefectDetection1D main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuDefectDetection1D
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
LBTY_tenuErrorStatus LDEM_enuDefectDetection1D(LDEM_tstrDetectionConfig1D *pstrDetectionConfig , s32 s32ReadValue, LDEM_tenuDetectionStatus *penuDetectionStatus)
{
   /* !Comment: Create local variable to have the operation status                  */
   LBTY_tenuErrorStatus enuOperationStatus = LBTY_OK;
   /* !Comment: Create local variable to have the Threshold value                   */
   s32 s32ThreValue = LBTY_s32MIN_VALUE;
   /* !Comment: Create local variable to have the operator type                     */
   LDEM_tenuDetectOperator enuDetectionOperator = LDEM_enuOP_EQUALS;
   /* !Comment: Create local variable to have the threshold 1 detection value       */
   LBTY_tenuBoolean  enuThr1DetectionValue = LBTY_TRUE;

   /**
    * @startuml
    * title LDEM_enuDefectDetection1D activity diagram
    * start*/
   
   /** if (check if the input pointer are not NULL) then (YES)*/
   if ((LBTY_NULL != pstrDetectionConfig) && (LBTY_NULL != penuDetectionStatus)
      && (LBTY_NULL != pstrDetectionConfig->kps32Threshold))
   {
      /**: Get the value of the threshold ;*/
      s32ThreValue = (*pstrDetectionConfig->kps32Threshold);
      /**: Get the Type of the operator ;*/
      enuDetectionOperator = (pstrDetectionConfig->kenuOp);

      /**: Get the defect status of threshold \n by calling enuGetDefectStatus ;*/
      enuOperationStatus = enuGetDefectStatus(s32ThreValue,
         enuDetectionOperator, s32ReadValue, &enuThr1DetectionValue);

      /** if (Check if the enuGetDefectStatus return LBTY_OK) then (Yes) */
      if(LBTY_OK == enuOperationStatus)
      {
         /** if (Check if the detection value is LBTY_TRUE) then (YES) */
         if (LBTY_TRUE == enuThr1DetectionValue)
         {
            /** #DarkSalmon: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_DETECTED ; */
            *penuDetectionStatus = LDEM_enuDetectionStatus_RAW_DETECTED;
         }
         else /** else (Detection value is LBTY_FALSE)*/
         {
            /** #ForestGreen: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_NOTDETECTED ; */
            *penuDetectionStatus = LDEM_enuDetectionStatus_RAW_NOTDETECTED;

         }
         /** endif */

      }
      else/* else(enuGetDefectStatus did not return OK)*/
      {
         /**: Set the error status to LBTY_NOK ;*/
         enuOperationStatus = LBTY_NOK;
         /**: [DIAG_001]: Report DET with index parameter LDEM_u8SDET_UNKNOWN_DET_TYPE \n in LDEM_u8DEFECT_DETECT_1D_SID API ;*/
         SFIC_vidDetReportError( LDEM_u16MODULE_ID, LDEM_u8PLTF_ID ,LDEM_u8DEFECT_DETECT_1D_SID,LDEM_u8SDET_UNKNOWN_DET_TYPE);


      }
      /** endif */
   }
   else/* else(Null pointer exists)*/
   {
      /**: [DIAG_001]: Report DET with null pointer parameter SFIC_u8DETPARAM_POINTER \n in LDEM_u8DEFECT_DETECT_1D_SID API;*/
      SFIC_vidDetReportError( LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
         ,LDEM_u8DEFECT_DETECT_1D_SID,SFIC_u8DETPARAM_POINTER);

      /**: Set the error status to LBTY_NULL_POINTER ;*/
      enuOperationStatus = LBTY_NULL_POINTER;
   }
   /** endif */
   
   /**: Return the error status  ;*/
   return enuOperationStatus;
   
   /** stop*/
   /** @enduml*/
}



/**
 *   \brief \DESIGNER_START Defect detection for 2 defects API \DESIGNER_END
 *   \details \DESIGNER_START This function compares the monitored two defects values against configured thresholds.  \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]   pstrDetectionConfig \DESIGNER_START Pointer to detection configuration structure                              / Type LDEM_tstrDetectionConfig2D * / Range [NA]               / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]   s32ReadValue        \DESIGNER_START Monitored data value to be evaluated against detection type               / Type u32                          / Range [0x00..0xFFFFFFFF] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[out]  penuDetectionStatus \DESIGNER_START Pointer to the defect detection status  (Detected, Not Detected & unknown)/ Type penuDetectionStatus*         / Range [NA]               / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Error status value \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START
 *               - LBTY_OK: Execution success
 *               - LBTY_NOK: Wrong configuration.
 *               - LBTY_NULL_POINTER: NULL output parameter detected \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START Req_SWC_LDEM_CDD_011-V01 \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START Covers_DEFECT_HANDLER_GDD_LDEM_002-V01  \DESIGNER_END
 *
 *   @startuml
 *   title LDEM_enuDefectDetection2D main sequence
 *      boundary ENV
 *      ENV -> LDEM : LDEM_enuDefectDetection2D
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
LBTY_tenuErrorStatus LDEM_enuDefectDetection2D(LDEM_tstrDetectionConfig2D *pstrDetectionConfig , s32 s32ReadValue, LDEM_tenuDetectionStatus *penuDetectionStatus)
{
   /* !Comment: Create local variable to have the operation status                       */
   LBTY_tenuErrorStatus enuOperationStatus = LBTY_OK;
   /* !Comment: Create local variable to have the operation status                       */
   LBTY_tenuErrorStatus enuOperationStatus1 = LBTY_OK;
   /* !Comment: Create local variable to have the operation status                       */
   LBTY_tenuErrorStatus enuOperationStatus2 = LBTY_OK;
   /* !Comment: Create local variable to have the first Threshold value                  */
   s32 s32ThreValue1 = LBTY_s32MIN_VALUE;
   /* !Comment: Create local variable to have the second Threshold value                 */
   s32 s32ThreValue2 = LBTY_s32MIN_VALUE;
   /* !Comment: Create local variable to have the operator types to the first threshold  */
   LDEM_tenuDetectOperator enuDetectionOperator1 = LDEM_enuOP_EQUALS;
   /* !Comment: Create local variable to have the operator types to the second threshold */
   LDEM_tenuDetectOperator enuDetectionOperator2 = LDEM_enuOP_EQUALS;
   /* !Comment: Create local variable to have the detection types                        */
   LDEM_tenuDetectionType enuDetectionType2D = LDEM_enuDetectionType_2D;
   /* !Comment: Create local variable to have the result                                 */
   LBTY_tenuBoolean  enuThr1DetectionValue = LBTY_TRUE;
   /* !Comment: Create local variable to have the detection types                        */
   LBTY_tenuBoolean  enuThr2DetectionValue = LBTY_TRUE;
   
   /**
    * @startuml
    * title LDEM_enuDefectDetection2D activity diagram
    * start
    */
   
   /** if (check if the input pointer are not NULL) then (OK)*/
   if ((LBTY_NULL != pstrDetectionConfig)
      && (LBTY_NULL != penuDetectionStatus)
      && (LBTY_NULL != pstrDetectionConfig->kps32Threshold1)
      && (LBTY_NULL != pstrDetectionConfig->kps32Threshold2))
   {
      /* !Comment: Get the type of the detection */
      enuDetectionType2D = (pstrDetectionConfig->kenuDetectionType2D);
      /* !Comment: Get the value of the first threshold */
      s32ThreValue1 = *(pstrDetectionConfig->kps32Threshold1);
      /* !Comment: Get the value of the second threshold */
      s32ThreValue2 = *(pstrDetectionConfig->kps32Threshold2);
      /* !Comment: Get the Type of the operator for the first threshold */
      enuDetectionOperator1 = (pstrDetectionConfig->kenuOp1);
      /* !Comment: Get the Type of the operator for the second threshold */
      enuDetectionOperator2 = (pstrDetectionConfig->kenuOp2);

      /**: Get the defect status of threshold 1 by calling enuGetDefectStatus ;*/
      enuOperationStatus1 = enuGetDefectStatus(s32ThreValue1,
         enuDetectionOperator1, s32ReadValue, &enuThr1DetectionValue);
      /**: Get the defect status of threshold 2 by calling enuGetDefectStatus ;*/
      enuOperationStatus2 = enuGetDefectStatus(s32ThreValue2,
         enuDetectionOperator2, s32ReadValue, &enuThr2DetectionValue);

      /** if (Check if the return of enuGetDefectStatus is LBTY_OK) then (Yes) */
      if ((LBTY_OK == enuOperationStatus1) && (LBTY_OK == enuOperationStatus2))
      {
         /**:Call enuGetDetectionStatus;*/
         enuOperationStatus = enuGetDetectionStatus (penuDetectionStatus,enuDetectionType2D,enuThr1DetectionValue,enuThr2DetectionValue);
      }
      else /** else (operator is not within range) */
      {
         /**: Set the return status to LBTY_NOK; */
         enuOperationStatus = LBTY_NOK;
         /**: [DIAG_001]: Report DET with LDEM_u8SDET_UNKNOWN_DET_TYPE parameter ;*/
         SFIC_vidDetReportError(LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
            , LDEM_u8DEFECT_DETECT_2D_SID, LDEM_u8SDET_UNKNOWN_DET_TYPE);

         /** endif */
      }
   }
   else/** else(Null pointer exists)*/
   {
      /**: Report DET with null pointer parameter SFIC_u8DETPARAM_POINTER \n in LDEM_u8DEFECT_DETECT_2D_SID API;*/
      SFIC_vidDetReportError( LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
         ,LDEM_u8DEFECT_DETECT_2D_SID,SFIC_u8DETPARAM_POINTER);

      /**: Set the error status to LBTY_NULL_POINTER ;*/
      enuOperationStatus = LBTY_NULL_POINTER;
   }
   /** endif */

   /**: Return the error status  ;*/
   return enuOperationStatus;

   /** stop*/
   /** @enduml*/

}
#endif

/* ************************************************************************** */
/* ************************* PRIVATE FUNCTION SECTION *********************** */
/* ************************************************************************** */

#if (PLTF_DEFECTMNG ==  PLTF_DEFECT_LDEM )
/**
 *   \brief \DESIGNER_START LDEM Reset Defect Parameters \DESIGNER_END
 *   \details \DESIGNER_START This function resets the defect parameters \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be Reset / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidResetDefect main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidResetDefect
 *   @enduml
 */
static void vidResetDefect(LDEM_tstrDefect *pstrDefect)
{
   
   /**
    *  Reset Defect activity diagram
    * @startuml
    * title Reset Defect activity diagram
    * start */
   
   /**
    *if(check if the correct Threshold to compare) then (true)
    */
   if (LDEM_enuDEFECT_ABSENT != pstrDefect->strValue.enuValidState)
   {
      /**:update the counter value to be = the configurable threshold value;*/
      pstrDefect->strValue.u16Counter = pstrDefect->pstrConfig->u16CounterThreshold;
   }
   /**else(false)*/
   else
   {
      /**:Set the value counter to be equal;*/
      pstrDefect->strValue.u16Counter = LBTY_u16MIN_VALUE;
   }
   /**endif*/
   
   /**:Check the correct threshold according to the counter value;*/
   vidUpdateDefectState(pstrDefect);

   /**
    *if(check if the  initial value is not more than the threshold) then (true)
    */
   if ( pstrDefect->pstrConfig->u16CounterInitialValue > pstrDefect->pstrConfig->u16CounterThreshold)
   {
      /**:Set the value to Threshold;*/
      pstrDefect->strValue.u16Counter = pstrDefect->pstrConfig->u16CounterThreshold;
   }
   /**else(false)*/
   else
   {
      /**:Initialize the counter value with the initial value;*/
      pstrDefect->strValue.u16Counter     = pstrDefect->pstrConfig->u16CounterInitialValue;
   }
   /**endif*/


   /**:Initialize the freezing state value;*/
   pstrDefect->strValue.enuFreezeState = pstrDefect->pstrConfig->enuFreezeInitialValue;

   /**stop*/
   /**@enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM More than operator \DESIGNER_END
 *   \details \DESIGNER_START That Function shall check if the read value is greater than threshold and the update the defct \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be updated / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  u16ReadValueLoc \DESIGNER_START Read value/ Type u16 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidMoreThanOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidMoreThanOperator
 *   @enduml
 */
static void vidMoreThanOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc)
{
   /**
    * @startuml
    * title vidMoreThanOperator activity diagram
    * start
    */
   /**
    *if(Check if the read value > threshold value ) then (true)
    */
   if ( u16ReadValueLoc > pstrDefect->strValue.u16Threshold )
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_PRESENT;
   }
   /**else(false)*/
   else
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_ABSENT;
   }
   /**endif*/
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM More than or equal operator \DESIGNER_END
 *   \details \DESIGNER_START That Function shall check if the read value is greater than or equal threshold and the update the defct \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be updated / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  u16ReadValueLoc \DESIGNER_START Read value/ Type u16 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidMoreThanOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidMoreThanOrEqualOperator
 *   @enduml
 */
static void vidMoreThanOrEqualOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc)
{
   /**
    * @startuml
    * title vidMoreThanOrEqualOperator activity diagram
    * start
    */
   /**
    *if(Check if the read value is greater than or equal the threshold value) then (true)
    */
   if ( u16ReadValueLoc >= pstrDefect->strValue.u16Threshold )
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_PRESENT;
   }
   /**else(false)*/
   else
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_ABSENT;
   }
   /**endif*/
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM less than operator \DESIGNER_END
 *   \details \DESIGNER_START That Function shall check if the read value is less than threshold and the update the defct \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be updated / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  u16ReadValueLoc \DESIGNER_START Read value/ Type u16 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidLessThanOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidLessThanOperator
 *   @enduml
 */
static void vidLessThanOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc)
{
   /**
    * @startuml
    * title vidLessThanOperator activity diagram
    * start
    */
   /**
    *if(Check if the read value is less than the threshold value) then (true)
    */
   if ( u16ReadValueLoc < pstrDefect->strValue.u16Threshold )
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_PRESENT;
   }
   /**else(false)*/
   else
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_ABSENT;
   }
   /**endif*/
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM less than or equal operator \DESIGNER_END
 *   \details \DESIGNER_START That Function shall check if the read value is less than or equal threshold and the update the defct \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be updated / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  u16ReadValueLoc \DESIGNER_START Read value/ Type u16 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidLessThanOrEqualOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidLessThanOrEqualOperator
 *   @enduml
 */
static void vidLessThanOrEqualOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc)
{
   /**
    * @startuml
    * title vidLessThanOrEqualOperator activity diagram
    * start
    */
   /**
    *if(Check if the read value is less than or equal the threshold value) then (true)
    */
   if ( u16ReadValueLoc <= pstrDefect->strValue.u16Threshold )
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_PRESENT;
   }
   /**else(false)*/
   else
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_ABSENT;
   }
   /**endif*/
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM  equal operator \DESIGNER_END
 *   \details \DESIGNER_START That Function shall check if the read value is equal threshold and the update the defect \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect \DESIGNER_START Pointer to Defect to be updated / Type LDEM_tstrDefect* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  u16ReadValueLoc \DESIGNER_START Read value/ Type u16 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidEqOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidEqOperator
 *   @enduml
 */
static void vidEqOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc)
{
   /**
    * @startuml
    * title vidEqOperator activity diagram
    * start
    */
   /**
    *if(Check if the read value is equal the threshold value) then (true)
    */
   if ( u16ReadValueLoc == pstrDefect->strValue.u16Threshold )
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_PRESENT;
   }
   /**else(false)*/
   else
   {
      /**:update the defect instantaneous state value;*/
      pstrDefect->strValue.enuInsState = LDEM_enuDEFECT_ABSENT;
   }
   /**endif*/
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START LDEM update instant status \DESIGNER_END
 *   \details \DESIGNER_START This function updates the instant status of the defect \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect  \DESIGNER_START Pointer to Defect to be validated    / Type LDEM_tstrDefect* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]      u16ReadValue \DESIGNER_START Variable that holds the read value  / Type u16              / Range [0x00..0xFFFE] / Resolution 1  / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START Return the operation status \n \DESIGNER_END
 *           Returned Value List:
 *               - LBTY_OK          : Execution success
 *               - LBTY_NOK         : Execution end with error
 *
 *   @startuml
 *   title enuUpadteInstState main sequence
 *      boundary ENV
 *      ENV -> LDEM : enuUpadteInstState
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
static LBTY_tenuErrorStatus enuUpadteInstState(LDEM_tstrDefect *pstrDefect, u16 u16ReadValue)
{
   /*Comment: Initialize return error status to OK */
   LBTY_tenuErrorStatus enuOperationStatusLoc = LBTY_OK;
   
   /**
    *  LDEM Update instant State activity diagram
    * @startuml
    * title LDEM Update instant State activity diagram
    * start */
   
   /**
    *if(Check if the instantaneous state of the defect based on its compare operator) then (true)
    */
   switch(pstrDefect->pstrConfig->enuOperator)
   {
      /**
       *if(Check if the enuOperator = LDEM_enuMoreThan) then (true)
       */
      case LDEM_enuMoreThan:
         /**:Call vidMoreThanOperator;*/
         vidMoreThanOperator(pstrDefect,u16ReadValue);
         break;

         /**
          *elseif(Check if the enuOperator = LDEM_enuMoreThOrEq) then (true)
          */
      case LDEM_enuMoreThOrEq:
         /**:Call vidMoreThanOrEqualOperator;*/
         vidMoreThanOrEqualOperator(pstrDefect,u16ReadValue);
         break;
         /**
          * elseif(Check if the enuOperator = LDEM_enuLessThan) then (true)
          */
      case LDEM_enuLessThan:
         /**:Call vidLessThanOperator;*/
         vidLessThanOperator(pstrDefect,u16ReadValue);
         break;

         /**
          *elseif(Check if the enuOperator = LDEM_enuLessThOrEq) then (true)
          */
      case LDEM_enuLessThOrEq:
         /**:Call vidLessThanOrEqualOperator;*/
         vidLessThanOrEqualOperator(pstrDefect,u16ReadValue);
         break;
         
         /**
          *elseif(check if the enuOperator = LDEM_enuEqualsTo) then (true)
          */
      case LDEM_enuEqualsTo:
         /**:Call vidEqualOperator;*/
         vidEqOperator(pstrDefect,u16ReadValue);
         break;
         /**else(false)*/
      default:
         /**:Return LBTY_NOK as error status;*/
         enuOperationStatusLoc = LBTY_NOK;
         break;
         /**endif*/
   }
   /**endif*/
   /**:return error status;*/
   return enuOperationStatusLoc;
   /**stop*/
   /**@enduml*/
}


/**
 *   \brief \DESIGNER_START LDEM update defect counter \DESIGNER_END
 *   \details \DESIGNER_START This function updates the defect counter based on the instant state \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect  \DESIGNER_START Pointer to Defect to be validated    / Type LDEM_tstrDefect* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \DESIGNER_END
 *
 *   @startuml
 *   title vidUpdateDfctCounter main sequence
 *      boundary ENV
 *      ENV -> LDEM : vidUpdateDfctCounter
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
static void vidUpdateDfctCounter(LDEM_tstrDefect *pstrDefect)
{
   /**
    *  LDEM Update defect counter activity diagram
    * @startuml
    * title LDEM Update instant State activity diagram
    * start */

   /**
    *if(Check if the instant value = DEFECT PRESENT) then (true)
    */
   if ( pstrDefect->strValue.enuInsState == LDEM_enuDEFECT_PRESENT )
   {


      /**
       * if(cehck if the counter is not exceeding the threshold ) then (true)
       */
      if( pstrDefect->strValue.u16Counter > (pstrDefect->pstrConfig->u16CounterThreshold - pstrDefect->pstrConfig->u16Increment)  )
      {
         /**:saturate the counter at the threshold;*/
         pstrDefect->strValue.u16Counter = pstrDefect->pstrConfig->u16CounterThreshold;
      }
      /**else(false)*/
      else
      {
         /**:Increment counter;*/
         pstrDefect->strValue.u16Counter += pstrDefect->pstrConfig->u16Increment;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**
       *if(Check if the value of counter is greater than the decrement counter ) then (true)
       */
      if( pstrDefect->strValue.u16Counter > pstrDefect->pstrConfig->u16Decrement )
      {
         /**:Decrement the counter only if the value of the counter is more that the decrement value;*/
         pstrDefect->strValue.u16Counter -= pstrDefect->pstrConfig->u16Decrement;
      }
      /**else(false)*/
      else
      {
         /**:Counter is already less than the decrement value, set the value to 0;*/
         pstrDefect->strValue.u16Counter = LBTY_u16MIN_VALUE;
      }
      /**endif*/
   }
   /**endif*/
   
   /**stop*/
   /**@enduml*/
}

/**
 *   \brief \DESIGNER_START LDEM update validated state \DESIGNER_END
 *   \details \DESIGNER_START This function updates the validated state \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  pstrDefect  \DESIGNER_START Pointer to Defect to be validated    / Type LDEM_tstrDefect* / Range [NA]           / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \DESIGNER_END
 *
 *   @startuml
 *   title vidUpdateDefectState main sequence
 *      boundary ENV
 *      ENV -> LDEM : vidUpdateDefectState
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
static void vidUpdateDefectState(LDEM_tstrDefect *pstrDefect)
{
   /*Comment: initialize operator to be = the configured value */
   LDEM_tenuOperator enuOperatorLoc = pstrDefect->pstrConfig->enuOperator;
   
   /**
    *  LDEM Update defect State activity diagram
    * @startuml
    * title LDEM Update defect State activity diagram
    * start */
   
   /**
    *if(Check if the  counter reaches counter threshold, update detection state) then (true)
    */
   if ( pstrDefect->strValue.u16Counter >= pstrDefect->pstrConfig->u16CounterThreshold)
   {
      /**:update the valid state to be = the present defect;*/
      pstrDefect->strValue.enuValidState = LDEM_enuDEFECT_PRESENT;
      
      /**
       *if(Check if the operator is = LDEM_enuMoreThan or operator is = LDEM_enuMoreThOrEq) then (true)
       */
      if (  (enuOperatorLoc == LDEM_enuMoreThan) || (enuOperatorLoc == LDEM_enuMoreThOrEq))
      {
         /**:update the threshold value to be equal the configurable threshold low value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdLow;
      }
      /**
       *elseif(check if the operator is = LDEM_enuLessThan or the operator value = LDEM_enuLessThOrEq) then (true)
       */
      else if ((enuOperatorLoc == LDEM_enuLessThan) || (enuOperatorLoc == LDEM_enuLessThOrEq))
      {
         /**::update the threshold value to be equal the configurable threshold high value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdHigh;
      }
      /**else(false)*/
      else
      {
         /**::update the threshold value to be equal the configurable threshold high value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdHigh;
      }
      /**endif*/
   }
   /**
    *elseif(check if the value of counter is less than or euqal 0) then (true)
    */
   else if ( pstrDefect->strValue.u16Counter <= (u16)0 )
   {
      /**
       *if(Check if the defect is reversible) then (true)
       */
      if (pstrDefect->pstrConfig->enuReverseState != LDEM_enuIRREVERSIBLE)
      {
         /**:set the value of valid state to be = Absent defect;*/
         pstrDefect->strValue.enuValidState = LDEM_enuDEFECT_ABSENT;
      }
      /**else(false)*/
      else
      {
         /**:Defect is irreversible, Do Nothing;*/
      }
      /**endif*/
      
      /**
       *if(check if the operator = LDEM_enuMoreThan or operator = LDEM_enuMoreThOrEq) then (true)
       */
      if ( (enuOperatorLoc == LDEM_enuMoreThan) || (enuOperatorLoc == LDEM_enuMoreThOrEq))
      {
         /**::update the threshold value to be equal the configurable threshold high value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdHigh;
      }
      /**
       *elseif(check if the operator = LDEM_enuLessThan or operator = LDEM_enuLessThOrEq) then (true)
       */
      else if (   (enuOperatorLoc == LDEM_enuLessThan) ||(enuOperatorLoc == LDEM_enuLessThOrEq))
      {
         /**::update the threshold value to be equal the configurable threshold Low value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdLow;
      }
      /**else(false)*/
      else
      {
         /**::update the threshold value to be equal the configurable threshold high value;*/
         pstrDefect->strValue.u16Threshold = pstrDefect->pstrConfig->u16ThresholdHigh;
      }
      /**endif*/
   }
   /**else(False)*/
   else
   {
      /**:Counter in hysteresis, don't update the state;*/
   }
   /**endif*/
   /**stop*/
   /**@enduml*/
}

#endif /*(PLTF_DEFECTMNG ==  PLTF_DEFECT_LDEM )*/

#if(PLTF_DEFECTMNG == PLTF_DEFECT_HANDLER )
/**
 *   \brief \DESIGNER_START Get defect status \DESIGNER_END
 *   \details \DESIGNER_START Compares the monitored value against configured threshold according to its operator type \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in] s32ThresholdVal \DESIGNER_START Threshold value where the input value will be compared against / Type s32                      / Range [-2147483648..2147483647] / Resolution 1 / Unit NA \DESIGNER_END
 *   \param[in] s32ReadValue    \DESIGNER_START Monitored data value to be evaluated against                   / Type s32                      / Range [-2147483648..2147483647] / Resolution 1 / Unit NA \DESIGNER_END
 *   \param[in] enuOperatorType \DESIGNER_START The detection operator type                                    / Type LDEM_tenuDetectOperator  / Range [LDEM_enuOP_EQUALS, LDEM_enuOP_DIFF, LDEM_enuOP_GREATER_THAN, LDEM_enuOP_LOWER_THAN, LDEM_enuOP_GREATER_OR_EQ, LDEM_enuOP_LOWER_OR_EQ] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START LBTY_tenuBoolean: Defect status if exists or not \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START
 *               - LBTY_OK : Successful operation
 *               - LBTY_INDEX_OUT_OF_RANGE: Operator out of the defined range \DESIGNER_END
 *
 *   @startuml
 *   title enuGetDefectStatus main sequence
 *      boundary ENV
 *      ENV -> LDEM : enuGetDefectStatus
 *      activate LDEM
 *      LDEM --> ENV : return
 *      deactivate LDEM
 *   @enduml
 */
static LBTY_tenuErrorStatus enuGetDefectStatus( s32 s32ThresholdVal, LDEM_tenuDetectOperator enuOperatorType, s32 s32ReadValue, LBTY_tenuBoolean *enuDefectExist )
{
   /* !Comment: Create a local variable to have the value if the defect exists or not  */
   LBTY_tenuErrorStatus enuOperationStatus =  LBTY_OK;

   /**
    * @startuml
    * title enuGetDefectStatus activity diagram
    * start
    */

   switch (enuOperatorType)
   {
      /** if (Check if the Operator type is LDEM_enuOP_EQUALS) then (OK)*/
      case LDEM_enuOP_EQUALS:
         /**:Call vidEqualOperator ;*/
         vidEqualOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);
         break;

         /** else if (Check if the Operator type is LDEM_enuOP_DIFF) then (OK) */
      case LDEM_enuOP_DIFF:
         /**:Call vidDiffOperator ;*/
         vidDiffOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);
         break;

         /** else if (Check if the Operator type is LDEM_enuOP_GREATER_THAN) then (OK) */
      case LDEM_enuOP_GREATER_THAN:
         /**:Call vidGreaterThanOperator ;*/
         vidGreaterThanOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);

         break;

         /** else if (Check if the Operator type \n is LDEM_enuOP_LOWER_THAN) then (OK) */
      case LDEM_enuOP_LOWER_THAN:
         /**:Call vidLowerThanOperator ;*/
         vidLowerThanOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);
         break;

         /** else if (Check if the Operator type is \n LDEM_enuOP_GREATER_OR_EQ) then (OK) */
      case LDEM_enuOP_GREATER_OR_EQ:
         /**:Call vidGreaterThanOrEqualOperator ;*/
         vidGreaterThanOrEqualOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);
         break;

         /** else if (Check if the Operator type is LDEM_enuOP_LOWER_OR_EQ) then (OK) */
      case LDEM_enuOP_LOWER_OR_EQ:
         /**:Call vidLowerThanOrEqualOperator ;*/
         vidLowerThanOrEqualOperator (s32ThresholdVal,s32ReadValue,enuDefectExist);
         break;

         /** else (Type is out of the defined range) */
      default :

         /**: Set operation status to LBTY_INDEX_OUT_OF_RANGE ;*/
         enuOperationStatus = LBTY_INDEX_OUT_OF_RANGE;

         /**: Report DET with index  parameter SFIC_u8DETPARAM_INDEX in LDEM_u8GET_DEFECT_STATUS API;*/
         SFIC_vidDetReportError( LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
            ,LDEM_u8GET_DEFECT_STATUS,SFIC_u8DETPARAM_INDEX);
         break;
         /** endif */
   }
   /**: Return the operation status ;*/
   return enuOperationStatus ;

   /** stop*/
   /** @enduml*/
}

/**
 *   \brief \DESIGNER_START Get detection status \DESIGNER_END
 *   \details \DESIGNER_START This function get detection status \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  penuDetectionStatusLoc \DESIGNER_START Pointer to Detction status / Type LDEM_tenuDetectionStatus* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuDetectionType2DLoc \DESIGNER_START 2D detection type/ Type LDEM_tenuDetectionType / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr1DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr2DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START LBTY_tenuErrorStatus \n \DESIGNER_END
 *
 *   @startuml
 *   title enuGetDetectionStatus main sequence
 *      boundary ENV
 *      LDEM -> LDEM : enuGetDetectionStatus
 *   @enduml
 */
static LBTY_tenuErrorStatus enuGetDetectionStatus (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LDEM_tenuDetectionType enuDetectionType2DLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc)
{
   /* !Comment: Create local variable to have the operation status                       */
   LBTY_tenuErrorStatus enuOperationStatus = LBTY_OK;
   /**
    * @startuml
    * title enuGetDetectionStatus activity diagram
    * start
    */
   switch (enuDetectionType2DLoc)
   {
      /**  if (Check if the type of the 2D Defect Detection \n is LDEM_enuDetectionType_2D) then (YES) */
      case LDEM_enuDetectionType_2D:
         /**:Call vidGetDetectionType2D;*/
         vidGetDetectionStatus2D (penuDetectionStatusLoc,enuThr1DetectionValueLoc,enuThr2DetectionValueLoc);
         break;

         /** else if (Check if the type of the 2D Defect Detection \n is LDEM_enuDetectionType_2DHyst) then (YES) */
      case LDEM_enuDetectionType_2DHyst:
         /**:Call vidGetDetectionType2DHyst;*/
         vidGetDetectionStatus2DHyst (penuDetectionStatusLoc,enuThr1DetectionValueLoc,enuThr2DetectionValueLoc);
         break;

         /** else if (Check if the type of the 2D Defect Detection is LDEM_enuDetectionType_2DInRange) then (YES) */
      case LDEM_enuDetectionType_2DInRange:
         /**:Call vidGetDetectionType2DInRange;*/
         vidGetDetectionStatus2DInRange (penuDetectionStatusLoc,enuThr1DetectionValueLoc,enuThr2DetectionValueLoc);
         break;

         /** else if (Check if the type of the 2D Defect Detection \n is LDEM_enuDetectionType_2DOutRange) then (YES) */
      case LDEM_enuDetectionType_2DOutRange:
         /**:Call vidGetDetectionType2DOutRange;*/
         vidGetDetectionStatus2DOutRange (penuDetectionStatusLoc,enuThr1DetectionValueLoc,enuThr2DetectionValueLoc);
         break;

         /** else if (Check if the type of the 2D Defect Detection \n is LDEM_enuDetectionType_1D) then (NO) */
      case LDEM_enuDetectionType_1D:
         /**: Set the return status to LBTY_NOK; */
         enuOperationStatus = LBTY_NOK;

         /**: [DIAG_001]: Report DET with SFIC_u8DETNOK parameter ;*/
         SFIC_vidDetReportError(LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
            , LDEM_u8DEFECT_DETECT_2D_SID, SFIC_u8DETNOK);

         break;

         /** else if (check if the type of the 2D Defect Detection \n is LDEM_enuDetectionType_NotSTD) then (NO) */
      case LDEM_enuDetectionType_NotSTD:
         /**: Set the return status to LBTY_NOK; */
         enuOperationStatus = LBTY_NOK;
         /**: [DIAG_001]: Report DET with LDEM_u8SDET_NOT_STANDRT_DET_TYPE parameter ;*/
         SFIC_vidDetReportError(LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
            , LDEM_u8DEFECT_DETECT_2D_SID,
            LDEM_u8SDET_NOT_STANDRT_DET_TYPE);

         break;

         /** else (Unknown detection type) */
      default:
         /**: Set the return status to LBTY_NOK; */
         enuOperationStatus = LBTY_NOK;
         /**: [DIAG_001]: Report DET with LDEM_u8SDET_UNKNOWN_DET_TYPE parameter ;*/
         SFIC_vidDetReportError(LDEM_u16MODULE_ID, LDEM_u8PLTF_ID
            , LDEM_u8DEFECT_DETECT_2D_SID, LDEM_u8SDET_UNKNOWN_DET_TYPE);

         /** endif */
         break;
   }
   /**: Return the error status  ;*/
   return enuOperationStatus;
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START get 2d detection status \DESIGNER_END
 *   \details \DESIGNER_START This function Shall get 2d detection status \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  penuDetectionStatusLoc \DESIGNER_START Pointer to Detction status / Type LDEM_tenuDetectionStatus* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr1DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr2DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START LBTY_tenuErrorStatus \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGetDetectionStatus2D main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGetDetectionStatus2D
 *   @enduml
 */
static void vidGetDetectionStatus2D (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc)
{
   /**
    * @startuml
    * title vidGetDetectionStatus2D activity diagram
    * start
    */


   /** if (check if there No defect is detected by threshold 1 \n and No defect is detected by threshold 2 ) then (YES) */
   if ((LBTY_FALSE == enuThr1DetectionValueLoc)
      && (LBTY_FALSE == enuThr2DetectionValueLoc))
   {
      /** #OldLace: Set the pointer to the detection status to \n  LDEM_enuDetectionStatus_UNKNOWN ; */
      *penuDetectionStatusLoc = LDEM_enuDetectionStatus_UNKNOWN;

   }
   /** else if (check if there is No defect detected by threshold 1 \n and defect is detected by threshold 2 ) then (YES) */
   else if ((LBTY_FALSE == enuThr1DetectionValueLoc)
      && (LBTY_TRUE == enuThr2DetectionValueLoc))
   {
      /** #ForestGreen: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_NOTDETECTED ; */
      *penuDetectionStatusLoc =
         LDEM_enuDetectionStatus_RAW_NOTDETECTED;
   }
   /** else if (check if there is defect detected by threshold 1 \n and  NO defect is detected by threshold 2 ) then (YES) */
   else if ((LBTY_TRUE == enuThr1DetectionValueLoc)
      && (LBTY_FALSE == enuThr2DetectionValueLoc))
   {
      /** #DarkSalmon: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_DETECTED ; */
      *penuDetectionStatusLoc = LDEM_enuDetectionStatus_RAW_DETECTED;

   }
   else /** else (There is defect detected by threshold 1 \n and defect is detected by threshold 2)*/
   {
      /** #DodgerBlue: Don't Set the pointer to the detection status; */
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START get 2d Hyst detection status \DESIGNER_END
 *   \details \DESIGNER_START This function Shall get 2d Hyst detection status \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  penuDetectionStatusLoc \DESIGNER_START Pointer to Detection status / Type LDEM_tenuDetectionStatus* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr1DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr2DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGetDetectionStatus2DHyst main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGetDetectionStatus2DHyst
 *   @enduml
 */
static void vidGetDetectionStatus2DHyst (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc)
{
   /**
    * @startuml
    * title vidGetDetectionStatus2DHyst activity diagram
    * start
    */

   /** if (check if there No defect is detected by threshold 1 \n and No defect is detected by threshold 2 ) then (YES) */
   if ((LBTY_FALSE == enuThr1DetectionValueLoc)
      && (LBTY_FALSE == enuThr2DetectionValueLoc))
   {
      /** #DodgerBlue: Don't Set the pointer to the detection status; */
   }
   /** else if (check if there No defect is detected by threshold 1 \n and defect is detected by threshold 2 ) then (YES) */
   else if ((LBTY_FALSE == enuThr1DetectionValueLoc)
      && (LBTY_TRUE == enuThr2DetectionValueLoc))
   {
      /** #ForestGreen: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_NOTDETECTED ; */
      *penuDetectionStatusLoc =
         LDEM_enuDetectionStatus_RAW_NOTDETECTED;
   }
   /** else if (check if there defect is detected by threshold 1 \n and NO defect is detected by threshold 2 ) then (YES) */
   else if ((LBTY_TRUE == enuThr1DetectionValueLoc)
      && (LBTY_FALSE == enuThr2DetectionValueLoc))
   {
      /** #DarkSalmon: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_DETECTED ; */
      *penuDetectionStatusLoc = LDEM_enuDetectionStatus_RAW_DETECTED;

   }
   else /** else (There is defect detected by threshold 1 \n and defect is detected by threshold 2)*/
   {
      /** #DodgerBlue: Don't Set the pointer to the detection status; */
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START get 2d In range detection status \DESIGNER_END
 *   \details \DESIGNER_START This function Shall get 2d in range detection status \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  penuDetectionStatusLoc \DESIGNER_START Pointer to Detection status / Type LDEM_tenuDetectionStatus* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr1DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr2DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGetDetectionStatus2DInRange main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGetDetectionStatus2DInRange
 *   @enduml
 */
static void vidGetDetectionStatus2DInRange (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc)
{
   /**
    * @startuml
    * title vidGetDetectionStatus2DInRange activity diagram
    * start
    */

   /** if (Check if There is defect detected by threshold 1 \n and defect is detected by threshold 2)*/
   if ((LBTY_TRUE == enuThr1DetectionValueLoc)
      && (LBTY_TRUE == enuThr2DetectionValueLoc))
   {

      /** #DarkSalmon: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_DETECTED ; */
      *penuDetectionStatusLoc = LDEM_enuDetectionStatus_RAW_DETECTED;
   }
   else /** else (all other defect possibilities ) */
   {
      /** #ForestGreen: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_NOTDETECTED ; */
      *penuDetectionStatusLoc =
         LDEM_enuDetectionStatus_RAW_NOTDETECTED;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START get 2d out range detection status \DESIGNER_END
 *   \details \DESIGNER_START This function Shall get 2d out range detection status \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in,out]  penuDetectionStatusLoc \DESIGNER_START Pointer to Detction status / Type LDEM_tenuDetectionStatus* / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr1DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  enuThr2DetectionValueLoc \DESIGNER_START Threshold detection value/ Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGetDetectionStatus2DOutRange main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGetDetectionStatus2DOutRange
 *   @enduml
 */
static void vidGetDetectionStatus2DOutRange (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc)
{
   /**
    * @startuml
    * title vidGetDetectionStatus2DOutRange activity diagram
    * start
    */

   /** if (Check if There is NO defect detected by threshold 1 \n and NO defect is detected by threshold 2)*/
   if ((LBTY_FALSE == enuThr1DetectionValueLoc)
      && (LBTY_FALSE == enuThr2DetectionValueLoc))
   {
      /** #ForestGreen: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_NOTDETECTED ; */
      *penuDetectionStatusLoc =
         LDEM_enuDetectionStatus_RAW_NOTDETECTED;
   }
   else /** else (all other defect possibilities ) */
   {
      /** #DarkSalmon: Set the pointer to the detection status \n to LDEM_enuDetectionStatus_RAW_DETECTED ; */
      *penuDetectionStatusLoc = LDEM_enuDetectionStatus_RAW_DETECTED;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Equal operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value equal read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidEqualOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidEqualOperator
 *   @enduml
 */
static void vidEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title vidEqualOperator activity diagram
    * start
    */

   /** if (Check if the input value is \n EQUAL to the Threshold value) then (OK) */
   if (s32ThresholdValLoc == s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is not equal to the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;

   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Different operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value different read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidDiffOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidDiffOperator
 *   @enduml
 */
static void vidDiffOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title vidDiffOperator activity diagram
    * start
    */
   /** if (Check if the input value is NOT_EQUAL to the Threshold value) then (OK) */
   if (s32ThresholdValLoc != s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is equal to the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Greater than  operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value greater than read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGreaterThanOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGreaterThanOperator
 *   @enduml
 */
static void vidGreaterThanOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title LDEM_enuDefectDetection2D activity diagram
    * start
    */
   /** if (Check if the input value is GREATER than the Threshold value) then (OK) */
   if (s32ThresholdValLoc < s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is not GREATER than the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Lower than  operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value Lower than read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidLowerThanOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidLowerThanOperator
 *   @enduml
 */
static void vidLowerThanOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title LDEM_enuDefectDetection2D activity diagram
    * start
    */

   /** if (Check if the input value is LOWER than the Threshold value) then (OK) */
   if (s32ThresholdValLoc > s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is not LOWER than the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Greater than or equal operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value Greater than or equal  read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGreaterThanOrEqualOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGreaterThanOrEqualOperator
 *   @enduml
 */
static void vidGreaterThanOrEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title LDEM_enuDefectDetection2D activity diagram
    * start
    */

   /** if (Check if the input value is GREATER than OR EQUAL the Threshold value) then (OK) */
   if (s32ThresholdValLoc <= s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is not GREATER than OR EQUAL to the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;

   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
/**
 *   \brief \DESIGNER_START Lower than or equal operator \DESIGNER_END
 *   \details \DESIGNER_START This function Shall Check if the threshold value Lower than or equal  read value operator \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Private \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante \DESIGNER_END
 *
 *   \param[in]  s32ThresholdValLoc \DESIGNER_START Threshold value  status / Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in]  s32ReadValueLoc \DESIGNER_START Read value/ Type s32 / Range [-2,147,483,648 .. 2,147,483,647] / Resolution NA / Unit NA \DESIGNER_END
 *   \param[in,out]  enuDefectExistLoc \DESIGNER_START Existence defect / Type LBTY_tenuBoolean / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   @startuml
 *   title vidGreaterThanOrEqualOperator main sequence
 *      boundary ENV
 *      LDEM -> LDEM : vidGreaterThanOrEqualOperator
 *   @enduml
 */
static void vidLowerThanOrEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc)
{
   /**
    * @startuml
    * title LDEM_enuDefectDetection2D activity diagram
    * start
    */
   /** if (Check if the input value is LOWER than OR EQUAL the Threshold value) then (OK) */
   if (s32ThresholdValLoc >= s32ReadValueLoc )
   {
      /** #DarkSalmon: Defect exists, set return value to LBTY_TRUE  ;*/
      *enuDefectExistLoc = LBTY_TRUE;
   }
   else /** else (The input value is not LOWER than OR EQUAL the threshold) */
   {
      /** #ForestGreen: Defect does NOT exists, set return value to LBTY_FALSE ;*/
      *enuDefectExistLoc =  LBTY_FALSE;
   }
   /** endif */
   /** stop*/
   /** @enduml*/
}
#endif /* (PLTF_DEFECTMNG == PLTF_DEFECT_HANDLER )*/
