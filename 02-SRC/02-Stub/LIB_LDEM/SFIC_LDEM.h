/******************************************************************************************************************/
/* !Layer           : Service Layer                                                                               */
/*                                                                                                                */
/* !Component       : LDEM                                                                                        */
/* !Description     : Module for register check                                                                   */
/*                                                                                                                */
/* !Module          : SFIC_LDEM.h                                                                                 */
/* !Date            : 27/04/2021                                                                                  */
/* !Description     : Service layer file interface                                                                */
/* !Scope           : SFIC                                                                                        */
/*                                                                                                                */
/* !Vendor          : Valeo                                                                                       */
/*                                                                                                                */
/* !Coding language : C                                                                                           */
/* !Project         : NXP S32 STD MCAL                                                                            */
/* !Target          : NXP S32K1xx                                                                                 */
/*                                                                                                                */
/* !COPYRIGHT 2013 VALEO LIGHTING SYSTEM                                                                          */
/*  all rights reserved                                                                                           */
/*                                                                                                                */
/******************************************************************************************************************/
/* MODIFICATION LOG :                                                                                             */
/******************************************************************************************************************/
/*                                                                                                                */
/* !Designed by     : Youstina SORIAL                   !Date : 09/03/2021          	      	   		         */
/* !Coded by        : Youstina SORIAL                   !Date : 09/03/2021                                        */
/*                                                                                                                */
/******************************************************************************************************************/

/* ************************************************************************************************************** */
/* ************************************** FILE DEFINITION SECTION *********************************************** */
/* ************************************************************************************************************** */
/** \file SFIC_LDEM.h
*  Component: \swc_name
*  \brief     \DESIGNER_START LDEM's SFIC file\DESIGNER_END
*  \details   \DESIGNER_START This file must include all what is needed to interface with the service layer \DESIGNER_END
*  \n\n
*  Scope: Public
*  \n\n
*  Coding language : C
*
*/

#ifndef SFIC_LDEM_H_
#define SFIC_LDEM_H_

/* ************************************************************************************************************** */
/* ******************************************** MACRO/DEFINE SECTION ******************************************** */
/* ************************************************************************************************************** */


/*!Comment:Det Interface included to handle LDEM API Errors*/
#if( LDEM_u8DET_ENABLE == LDEM_u8DET_USED)
#include "SDET_int.h"

/*!Comment: Standard Error Identifiers */

/** \brief \DESIGNER_START Uninitialized Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8UNINIT] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETUNINIT              SDET_u8UNINIT
/** \brief \DESIGNER_START Already initialized Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8ALREADY_INITIALIZED] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETALREADY_INIT        SDET_u8ALREADY_INITIALIZED
/** \brief \DESIGNER_START Null pointer Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8PARAM_POINTER] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETPARAM_POINTER       SDET_u8PARAM_POINTER
/** \brief \DESIGNER_START Out of range Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8PARAM_INDEX] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETPARAM_INDEX         SDET_u8PARAM_INDEX
/** \brief \DESIGNER_START State default Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8STATE_DEFAULT] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETSTATE_DEFAULT       SDET_u8STATE_DEFAULT
/** \brief \DESIGNER_START NOK Det-error identifier from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8NOK] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETNOK                 SDET_u8NOK

/** \brief \DESIGNER_START Custom1 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM1] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM1             SDET_u8CUSTOM1
/** \brief \DESIGNER_START Custom2 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM2] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM2             SDET_u8CUSTOM2
/** \brief \DESIGNER_START Custom3 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM3] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM3             SDET_u8CUSTOM3
/** \brief \DESIGNER_START Custom4 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM4] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM4             SDET_u8CUSTOM4
/** \brief \DESIGNER_START Custom5 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM5] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM5             SDET_u8CUSTOM5
/** \brief \DESIGNER_START Custom6 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM6] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM6             SDET_u8CUSTOM6
/** \brief \DESIGNER_START Custom7 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM7] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM7             SDET_u8CUSTOM7
/** \brief \DESIGNER_START Custom8 Det-error identifier for future usage from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type u8 / Range [SDET_u8CUSTOM8] / Resolution 1 \DESIGNER_END
 */
#define SFIC_u8DETCUSTOM8             SDET_u8CUSTOM8

/** \brief \DESIGNER_START Det Report Error function name from SWC_SDET at service layer \DESIGNER_END
 *  \details \DESIGNER_START Type NA / Range NA / Resolution NA / Macro expansion value: SDET_vidReportError(ModuleID, PltfID, ApiId, ErrorId) \DESIGNER_END
 */
#define SFIC_vidDetReportError(ModuleID, PltfID, ApiId, ErrorId)\
		    SDET_vidReportError(ModuleID, PltfID, ApiId, ErrorId)



#else

#define SFIC_u8DETUNINIT
#define SFIC_u8DETALREADY_INIT
#define SFIC_u8DETPARAM_POINTER
#define SFIC_u8DETPARAM_INDEX
#define SFIC_u8DETSTATE_DEFAULT
#define SFIC_u8DETNOK

#define SFIC_u8INVALID_CHANNEL
#define SFIC_u8DETCUSTOM2
#define SFIC_u8DETCUSTOM3
#define SFIC_u8DETCUSTOM4
#define SFIC_u8DETCUSTOM5
#define SFIC_u8DETCUSTOM6
#define SFIC_u8DETCUSTOM7
#define SFIC_u8DETCUSTOM8

#define SFIC_vidDetReportError(ModuleID,PltfID,ApiId,ErrorId);

#endif

#endif /* SFIC_LDEM_H_ */
/************************** E N D (SFIC_LDEM.h) *******************************/
