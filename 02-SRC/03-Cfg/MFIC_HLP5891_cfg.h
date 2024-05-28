/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file MFIC_HLP5891_cfg.h
 *  Component: \HLP5891
 *  \brief     \DESIGNER_START This config file is used as rubber layer for MCAL layer \DESIGNER_END
 *  \details   \DESIGNER_START   \DESIGNER_END
 *   \Scope: Public
 *  \n\n
 *  Coding language : C
 *    \copydoc _mfichcfg
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
/** \page _mfichcfg MFIC_HLP5891_cfg.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | MFIC_HLP5891_cfg.h               | 1.0                 | Proposed            | Initial creation         
 *     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
#ifndef MFIC_HLP5891_CFG_H_
#define MFIC_HLP5891_CFG_H_


/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "MFIC.h"

/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */



/*__________________________ DIO Abstraction Section ________________________*/
/*___________________________________________________________________________*/
/*__________________________ DIO Output Pin Section _________________________*/

#ifndef BSW_HDIO

/** \brief \DESIGNER_START  DDIO On Value used for Set high value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_u8DIO_DIGITAL_ON           ((u8)1)
/** \brief \DESIGNER_START  DDIO OFF Value used for Set Low value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_u8DIO_DIGITAL_OFF          ((u8)0)


/** \brief \DESIGNER_START  SPI Pin used for HLP5891    \DESIGNER_END */
#define HLP5891_DRV1_CCSI_PIN            ((u8)DIO_CHANNEL_2_3)

/* ***************************** MFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  HSPM_enuSpiJobRqst function from HPWM components   \DESIGNER_END*/
#define  HLP5891_enuDIOSetOutState          MFIC_stdWritePinValue

/* ************************** End MFIC Interfaces *****************************/

#endif

/*___________________________________________________________________________*/
/*______________________End of DIO Abstraction Section ______________________*/



/* ************************************************************************** */



/*___________________________________________________________________________*/
/*_____________________START SPI Abstraction Section ________________________*/
/*___________________________________________________________________________*/
#ifndef BSW_HSPM

/** \brief \DESIGNER_START  SPI Pin used for HLP5891    \DESIGNER_END */
#define HLP5891_DRV1_SPI_SLOT             ((u8)MFIC_u32SPI_CHANNEL0)

/* ***************************** MFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  initialize SPI slave  \DESIGNER_END*/
// #define  HLP5891_enuSpiInit          initPeripherals

/** \brief \DESIGNER_START Macro used  for calling  HSPM_enuSpiJobRqst function from HPWM components   \DESIGNER_END*/
#define  HLP5891_enuSpiWrReq          MFIC_enuSpiWrReq

/* ************************** End MFIC Interfaces *****************************/
#endif



/*___________________________________________________________________________*/
/*_______________________END SPI Abstraction Section ________________________*/
/*___________________________________________________________________________*/



/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */




#endif /* 03_SRC_SWC_HLP5891_02_SRC_MFIC_HLP5891_CFG_H_ */
