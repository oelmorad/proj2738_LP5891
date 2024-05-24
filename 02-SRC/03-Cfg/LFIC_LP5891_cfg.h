/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LFIC_LP5891_cfg.h
 *  Component: \LP5891
 *  \brief     \DESIGNER_START This config file is used as rubber layer for libraries  \DESIGNER_END
 *  \details   \DESIGNER_START   \DESIGNER_END
 *   \Scope: Public
 *  \n\n
 *  Coding language : C
 *    \copydoc _lfichcfg
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
/** \page _lfichcfg MFIC_LP5891_cfg.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | MFIC_LP5891_cfg.h               | 1.0          | Proposed            | Initial creation         
 *     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
#ifndef LFIC_LP5891_CFG_H_
#define LFIC_LP5891_CFG_H_

/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LDEM_int.h"
#include "LMATH_int.h"


/********************************** Called APIs from LDEM components  *********************/
/** \brief \DESIGNER_START Mapping to defect initialization service \DESIGNER_END */
#define LP5891_enuLdemInitDefect                           LDEM_enuInitDefect
/** \brief \DESIGNER_START Mapping to defect update service \DESIGNER_END */
#define LP5891_enuLdemUpdateDefect                         LDEM_enuUpdateDefect
/** \brief \DESIGNER_START Mapping to defect valid state getter service \DESIGNER_END */
#define LP5891_enuLdemGetValidState                        LDEM_enuGetValidState
/** \brief \DESIGNER_START Mapping to defect freeze state setter service \DESIGNER_END */
#define LP5891_enuLdemSetFreezingState                     LDEM_enuSetFreezingState
/** \brief \DESIGNER_START Mapping to 2D defect detection service \DESIGNER_END */
#define LP5891_enuLdemDefectDetection2D                    LDEM_enuDefectDetection2D

/** \brief \DESIGNER_START Mapping to 2D defect configuration type service \DESIGNER_END */
#define LP5891_tstrldemDetectionConfig2D                   LDEM_tstrDetectionConfig2D
/** \brief \DESIGNER_START Mapping to 1D defect configuration type service \DESIGNER_END */
# define LP5891_tstrldemDetectionConfig1D                   LDEM_tstrDetectionConfig1D

/** \brief \DESIGNER_START Mapping to defect configuration type service \DESIGNER_END */
#define LP5891_tstrLdemDefectConfig                        LDEM_tstrDefectConfig

/** \brief \DESIGNER_START Macro used  for calling  LDEM_tstrDefect  struct    \DESIGNER_END*/
#define LP5891_tstrLdemDefect                              LDEM_tstrDefect

/** \brief \DESIGNER_START Macro used  for calling  LDEM_tenuDefectState  enum    \DESIGNER_END*/
#define LP5891_tenuLdemDefectState                         LDEM_tenuDefectState

/** \brief \DESIGNER_START Macro used  for calling  LDEM_tenuFreezeState  state    \DESIGNER_END*/
#define LP5891_tenuLdemFreezeState                         LDEM_tenuFreezeState

/** \brief \DESIGNER_START Macro used  for calling  LDEM_enuRUNNING  state    \DESIGNER_END*/
#define LP5891_enuLdemRUNNING                              LDEM_enuRUNNING

/** \brief \DESIGNER_START Macro used  for calling  LDEM_enuFREEZED  state    \DESIGNER_END*/
#define LP5891_enuldemFREEZED                              LDEM_enuFREEZED

/** \brief \DESIGNER_START Macro used  for calling  LDEM_tenuDetectionStatus  enum    \DESIGNER_END*/
#define LP5891_tenuLdemDetectionStatus                     LDEM_tenuDetectionStatus

/** \brief \DESIGNER_START Macro used  for calling  LDEM_enuDetectionStatus_UNKNOWN  state    \DESIGNER_END*/
#define LP5891_enuLdemDetectionStatus_UNKNOWN              LDEM_enuDetectionStatus_UNKNOWN

/** \brief \DESIGNER_START Macro used  for calling  LDEM_enuDetectionStatus_RAW_DETECTED  state    \DESIGNER_END*/
#define LP5891_enuLdemStatus_DETECTED         LDEM_enuDetectionStatus_RAW_DETECTED

/** \brief \DESIGNER_START Macro used  for calling  LDEM_enuDetectionStatus_RAW_NOTDETECTED  state    \DESIGNER_END*/
#define LP5891_enuLdemStatus_NOTDETECTED      LDEM_enuDetectionStatus_RAW_NOTDETECTED
/* ************************** End LDEM Interfaces *****************************/




/********************************** Called APIs from LMATH components  *********************/









#endif /* 03_SRC_SWC_LP5891_02_SRC_LFIC_LP5891_CFG_H_ */
