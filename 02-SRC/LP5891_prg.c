/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LP5891_prg.c
 *  Component: \SWC_LP5891
 *  \brief     \DESIGNER_START Abstraction layer between App. & LED Matrix Driver \DESIGNER_END
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
/** \page _prgc LP5891_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | LP5891_prg.c       | 1.0          | Proposed            | \verbatim $Rev::              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::            #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author::           $: Author of last commit   \endverbatim |
 */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "BSW_cfg.h"

#include "LFIC_LP5891_cfg.h"
#include "MFIC_LP5891_cfg.h"
#include "HFIC_LP5891_cfg.h"

#include "LP5891_priv.h"
#include "LP5891_cfg.h"
#include "LP5891_int.h"

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
static u16 au16StatTxBuffer[85];
static u16 au16StatRxBuffer[85];



/* ************************************************************************** */
/* ************************* PUBLIC FUNCTION SECTION ************************ */
/* ************************************************************************** */
/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void LP5891_vidInit(void)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */











   /** stop*/
   /** @enduml*/
}








/**
 *   \brief \DESIGNER_START Component  Runnable function \DESIGNER_END
 *   \details \DESIGNER_START Run Component State machine, Set SW Enable value, Read Chip Diag  and Update Defects \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START ASynchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START None\DESIGNER_END
 *   \param[out]      void \DESIGNER_START None \DESIGNER_END
 *   \param[in,out]   void \DESIGNER_START None \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *       \DESIGNER_START                  
 *       \DESIGNER_END
 *
 *   \DESIGNER_START  Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary ENV
 *      ENV -> LP5891 : LP5891_vidRunMgmt
 *      activate LP5891
 *      LP5891 ->  :
 *       --> LP5891 : return
 *      LP5891 --> ENV : return
 *      deactivate LP5891
 *   @enduml
 */
void LP5891_vidRunMgmt(void)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      u8 u8NbOfStatCmds = 0;

   (void) LP5891_enuHDIOSetOutDigitalState( 0,  LP5891_u8HDIO_DIGITAL_OFF);

   (void) LP5891_enuHPWMSetOutDUTY(0,0);


     (void) LP5891_enuHspmSpiWrReq(0,au16StatTxBuffer,
         au16StatRxBuffer,
         u8NbOfStatCmds,
         0,
         (tpfvidHspmUsrJobCallBck)&LP5891_vidConfJobEndNotif,
         0);

      /** stop*/
   /** @enduml*/
}






/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void LP5891_vidConfJobEndNotif(u16 u8SgntrCpy, LBTY_tenuErrorStatus enuErrStat)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */




   /** stop*/
   /** @enduml*/
}

/* ************************************************************************** */
/* ************************* PRIVATE FUNCTION SECTION *********************** */
/* ************************************************************************** */






/* *********************** E N D (LP5891_prg.c) *************************** */
