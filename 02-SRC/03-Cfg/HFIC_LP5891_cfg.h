/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file HFIC_LP5891_cfg.h
 *  Component: \LP5891
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
/** \page _hfichcfg HFIC_LP5891_cfg.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | HFIC_LP5891_cfg.h       | \CoreVersion | \CoreVersion_Status | \verbatim $Rev:: 4469         $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 26 Sep,2023  #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Oelmorad  $: Author of last commit   \endverbatim |
 */
#ifndef HFIC_LP5891_CFG_H_
#define HFIC_LP5891_CFG_H_

/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#include "BSW_cfg.h"


#ifdef BSW_HDIO

#include "HDIO_int.h"

/** \brief \DESIGNER_START  HDIO On Value used for Set high value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_u8HDIO_DIGITAL_ON           ((u8)1)
/** \brief \DESIGNER_START  HDIO OFF Value used for Set Low value on the output pin    \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0-1] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_u8HDIO_DIGITAL_OFF          ((u8)0)


/** \brief \DESIGNER_START  HDIO Pin used for LP5891    \DESIGNER_END */
#define LP5891_DRV1_DIO_CS             ((u8)0)
/** \brief \DESIGNER_START  HDIO Pin used for LP5891    \DESIGNER_END */
#define LP5891_DRV2_DIO_CS             ((u8)1)

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  SetOutDigitalState function from HDIO components   \DESIGNER_END*/
#define  LP5891_enuHDIOSetOutDigitalState          HDIO_enuSetOutputState

/* ************************** End HFIC Interfaces *****************************/
#endif



#ifdef BSW_HPWM

#include "HPWM_int.h"

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  HPWM_enuSetOutDutyCycle function from HPWM components   \DESIGNER_END*/
#define  LP5891_enuHPWMSetOutDUTY          HPWM_enuSetOutDutyCycle

/* ************************** End HFIC Interfaces *****************************/
#endif



#ifdef BSW_HSPM

#include "HSPM_int.h"


/** \brief \DESIGNER_START  HDIO Pin used for LP5891    \DESIGNER_END */
#define LP5891_DRV1_SPI_SLOT             ((u8)0)

/** \brief \DESIGNER_START  HDIO Pin used for LP5891    \DESIGNER_END */
#define LP5891_DRV2_SPI_SLOT             ((u8)1)

/* ***************************** HFIC Interfaces ******************************/
/** \brief \DESIGNER_START Macro used  for calling  HSPM_enuSpiJobRqst function from HPWM components   \DESIGNER_END*/
#define  LP5891_enuSpiWrReq          HSPM_enuSpiJobRqst

/* ************************** End HFIC Interfaces *****************************/
#endif








/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */




#endif /* 03_SRC_SWC_LP5891_02_SRC_HFIC_LP5891_CFG_H_ */
