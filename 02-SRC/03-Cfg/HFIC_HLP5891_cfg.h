/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file HFIC_HLP5891_cfg.h
 *  Component: \HLP5891
 *  \brief     \DESIGNER_START This config file is used as rubber layer for HAL layer \DESIGNER_END
 *  \details   \DESIGNER_START   \DESIGNER_END
 *   \Scope: Public
 *  \n\n
 *  Coding language : C
 *    \copydoc _hfichcfg
 *  \copydoc
 *
 *  \DESIGNER_START
 *
 *  COPYRIGHT
 *
 *   Copyright (C) 2013 VALEO LIGHTING SYSTEM
 *
 *    \DESIGNER_END
 */
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _hfichcfg HFIC_HLP5891_cfg.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | HFIC_HLP5891_cfg.h               | 1.0          | Proposed            | Initial creation         
 *     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
#ifndef HFIC_HLP5891_CFG_H_
#define HFIC_HLP5891_CFG_H_

/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "BSW_cfg.h"

/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */


/*__________________________ HDIO Abstraction Section ________________________*/
/*___________________________________________________________________________*/
/*__________________________ HDIO Output Pin Section _________________________*/

#ifdef BSW_HDIO

#include "HDIO_int.h"

/** \brief \DESIGNER_START  HDIO On Value used for Set high value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_u8DIO_DIGITAL_ON           ((u8)1)
/** \brief \DESIGNER_START  HDIO OFF Value used for Set Low value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_u8DIO_DIGITAL_OFF          ((u8)0)


/** \brief \DESIGNER_START  HDIO Pin used for HLP5891    \DESIGNER_END */
#define HLP5891_DRV1_DIO_CS             ((u8)0)

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  SetOutDigitalState function from HDIO components   \DESIGNER_END*/
#define  HLP5891_enuDIOSetOutState          HDIO_enuSetOutputState

/* ************************** End HFIC Interfaces *****************************/
#endif

/*___________________________________________________________________________*/
/*______________________End of HDIO Abstraction Section ______________________*/



/* ************************************************************************** */




/*___________________________________________________________________________*/
/*_____________________START HPWM Abstraction Section ________________________*/
/*___________________________________________________________________________*/

#ifdef BSW_HPWM

#include "HPWM_int.h"

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  HPWM_enuSetOutDutyCycle function from HPWM components   \DESIGNER_END*/
#define  HLP5891_enuPWMSetOutDUTY          HPWM_enuSetOutDutyCycle

/* ************************** End HFIC Interfaces *****************************/
#endif


/*___________________________________________________________________________*/
/*_______________________END HPWM Abstraction Section ________________________*/
/*___________________________________________________________________________*/

/* ************************************************************************** */




/*___________________________________________________________________________*/
/*_____________________START HSPM Abstraction Section ________________________*/
/*___________________________________________________________________________*/


#ifdef BSW_HSPM

#include "HSPM_int.h"


/** \brief \DESIGNER_START  HDIO Pin used for HLP5891    \DESIGNER_END */
#define HLP5891_DRV1_SPI_SLOT             ((u8)0)

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  HSPM_enuSpiJobRqst function from HPWM components   \DESIGNER_END*/
#define  HLP5891_enuSpiWrReq          HSPM_enuSpiJobRqst

/* ************************** End HFIC Interfaces *****************************/
#endif



/*___________________________________________________________________________*/
/*_______________________END HSPM Abstraction Section ________________________*/
/*___________________________________________________________________________*/

/* ************************************************************************** */




/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */




#endif /* 03_SRC_SWC_HLP5891_02_SRC_HFIC_HLP5891_CFG_H_ */
