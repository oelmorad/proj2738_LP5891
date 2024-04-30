/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LDEM_priv.h
 *  Component: \swc_name
 *  \brief     \DESIGNER_START Library of defect management (LDEM) . \DESIGNER_END
 *  \details   \DESIGNER_START including private ( definitions, macros and functions prototypes ). \DESIGNER_END
 *  \n\n
 *  Scope: Private
 *  \n\n
 *  Coding language : C
 *    \copydoc _privh
 *  \copydoc COPYRIGHT
 */

/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _privh LDEM_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						Initial Creation						   																      ||||
 *     | LDEM_priv.h      | V1.1        | Proposed            | \verbatim $Rev::            			$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::1-10-2016 				#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Ahmed Assaf   		$: Author of last commit    \endverbatim |
 */
/** \page _privh LDEM_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |				update code after applying review remarks of tag 59.20-01.00.00-04.01								  		          ||||
 *     | LDEM_priv.h      | V1.2        | Proposed            | \verbatim $Rev::            			$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::19-06-2018 			#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author::Ahmed abdelmageed   	$: Author of last commit    \endverbatim |
 */
/** \page _privh LDEM_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						Update code after applying MISRA issues remarks                              						          ||||
 *     | LDEM_priv.h      | V1.3        | Proposed            | \verbatim $Rev::            			$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::1-10-2016 				#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha wagdy   		$: Author of last commit    \endverbatim |
 */
/** \page _privh LDEM_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						migration to Doxygen						                                                                  ||||
 *     | LDEM_priv.h      | V1.4        | Proposed            | \verbatim $Rev::            		    $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::13-04-2020 			#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Dina shinaishin   	$: Author of last commit    \endverbatim |
 */
/** \page _prgc LDEM_priv.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     | Update the module with 2APIs LDEM_enuDefectDetection1D and LDEM_enuDefectDetection2D and update the CDD.        ||||
 *     | LDEM_priv.h      |\CoreVersion | \CoreVersion_Status  | \verbatim $Rev::    247              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::   27/04/2021      #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Youstina SORIAL  $: Author of last commit   \endverbatim |
 */
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */

#ifndef LDEM_PRIV_H
#define LDEM_PRIV_H

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/**@{*/
/** @name DET report
 */

/** \brief \DESIGNER_START Macro to enable the DET  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit [NA] \DESIGNER_END */
#define LDEM_u8DET_USED                        0x55

/** \brief \DESIGNER_START Macro to disable the DET  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0xAA] / Resolution NA / Unit [NA] \DESIGNER_END */
#define LDEM_u8DET_NOT_USED                    0xAA
/**@}*/


/**@{*/
/** @name LDEM SWC version information
 */
/** \brief \DESIGNER_START Vendor ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u16 / Range [59] / Resolution [NA] / Unit [NA] \DESIGNER_END */
#define LDEM_u16VENDOR_ID                 ((u16)59)

/** \brief \DESIGNER_START Module ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u16 / Range [20] / Resolution [NA] / Unit [NA] \DESIGNER_END */
#define LDEM_u16MODULE_ID                 ((u16)20)

/** \brief \DESIGNER_START SW Major ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0..255] / Resolution [NA] / Unit [NA] \DESIGNER_END */
#define LDEM_u8SW_MAJOR_VERSION           ((u8)3)

/** \brief \DESIGNER_START SW Minor ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0..255] / Resolution [NA] / Unit [NA] \DESIGNER_END */
#define LDEM_u8SW_MINOR_VERSION           ((u8)0)

/** \brief \DESIGNER_START Patch ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0..255] / Resolution [NA] / Unit [NA] \DESIGNER_END */
#define LDEM_u8SW_PATCH_VERSION           ((u8)0)

/** \brief \DESIGNER_START SWC module vendor identifier \DESIGNER_END
 *  \details \DESIGNER_START u8 / Range [LDEM_u16VENDOR_ID] / Resolution NA / Unit NA \DESIGNER_END */
#define LDEM_u8PLTF_ID                (u8)LDEM_u16VENDOR_ID

/**@}*/

/*************************************************************************************************************/
/**@{*/
/** @name LDEM SWC LDEM APIs IDs
 */
/** \brief \DESIGNER_START LDEM_u8DEFECT_DETECT_1D_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8DEFECT_DETECT_1D_SID              ((u8)0)

/** \brief \DESIGNER_START LDEM_u8DEFECT_DETECT_2D_SID ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [1] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8DEFECT_DETECT_2D_SID              (LDEM_u8DEFECT_DETECT_1D_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8GET_DEFECT_STATUS ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [2] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8GET_DEFECT_STATUS                 (LDEM_u8DEFECT_DETECT_2D_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8INIT_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [3] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8INIT_SID                          (LDEM_u8GET_DEFECT_STATUS + (u8)1)

/** \brief \DESIGNER_START LDEM_u8UPDATE_DEFECT_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [4] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8UPDATE_DEFECT_SID                 (LDEM_u8INIT_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8GET_VER_INFO_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [5] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8GET_VER_INFO_SID                  (LDEM_u8UPDATE_DEFECT_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8SET_FREEZ_STATE_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [6] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8SET_FREEZ_STATE_SID               (LDEM_u8GET_VER_INFO_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8GET_INST_STATE_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [7] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8GET_INST_STATE_SID                (LDEM_u8SET_FREEZ_STATE_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8GET_VALID_STATE_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [8] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8GET_VALID_STATE_SID                (LDEM_u8GET_INST_STATE_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8SET_CNT_PARAM_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [9] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8SET_CNT_PARAM_SID                  (LDEM_u8GET_VALID_STATE_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8SET_DEF_VAL_SID function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [10] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8SET_DEF_VAL_SID                    (LDEM_u8SET_CNT_PARAM_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8UPDATE_INST_STATE function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [11] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8UPDATE_INST_STATE                  (LDEM_u8SET_DEF_VAL_SID + (u8)1)

/** \brief \DESIGNER_START LDEM_u8UPDATE_DEF_CNT function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [12] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8UPDATE_DEF_CNT                     (LDEM_u8UPDATE_INST_STATE + (u8)1)

/** \brief \DESIGNER_START LDEM_u8UPDATE_INST_CNT function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [13] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8UPDATE_INST_CNT                    (LDEM_u8UPDATE_DEF_CNT + (u8)1)

/** \brief \DESIGNER_START LDEM_u8RESET_DEFECT function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [14] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8RESET_DEFECT                       (LDEM_u8UPDATE_INST_CNT + (u8)1)
/** \brief \DESIGNER_START LDEM_u8GET_DETECTION_TYPE function ID  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [15] / Resolution 1 / Unit [NA] \DESIGNER_END */
#define LDEM_u8GET_DETECTION_TYPE                 (LDEM_u8RESET_DEFECT + (u8)1)
/**@}*/


/*************************************************************************************************************/
/**@{*/
/** @name Custom DET defects
 */

/** \brief \DESIGNER_START DET not standard detection type  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [SFIC_u8DETCUSTOM1] / Resolution NA / Unit [NA] \DESIGNER_END */
#define LDEM_u8SDET_NOT_STANDRT_DET_TYPE      (SFIC_u8DETCUSTOM1)

/** \brief \DESIGNER_START DET Unknown detection type  \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [SFIC_u8DETCUSTOM2] / Resolution NA / Unit [NA] \DESIGNER_END */
#define LDEM_u8SDET_UNKNOWN_DET_TYPE          (SFIC_u8DETCUSTOM2)

/**@}*/


/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
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
#if(PLTF_DEFECTMNG ==  PLTF_DEFECT_LDEM )

static LBTY_tenuErrorStatus enuUpadteInstState(LDEM_tstrDefect *pstrDefect, u16 u16ReadValue);

static void vidUpdateDfctCounter(LDEM_tstrDefect *pstrDefect);

static void vidUpdateDefectState(LDEM_tstrDefect *pstrDefect);

static void vidResetDefect(LDEM_tstrDefect *pstrDefect);

static void vidMoreThanOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc);

static void vidMoreThanOrEqualOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc);

static void vidLessThanOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc);

static void vidLessThanOrEqualOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc);

static void vidEqOperator(LDEM_tstrDefect *pstrDefect,u16 u16ReadValueLoc);
#endif

#if (PLTF_DEFECTMNG == PLTF_DEFECT_HANDLER )

static LBTY_tenuErrorStatus enuGetDefectStatus( s32 s32ThresholdVal, LDEM_tenuDetectOperator enuOperatorType, s32 s32ReadValue, LBTY_tenuBoolean *enuDefectExist);

static LBTY_tenuErrorStatus enuGetDetectionStatus (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LDEM_tenuDetectionType enuDetectionType2DLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc);

static void vidGetDetectionStatus2D (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc);

static void vidGetDetectionStatus2DHyst (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc);

static void vidGetDetectionStatus2DInRange (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc);

static void vidGetDetectionStatus2DOutRange (LDEM_tenuDetectionStatus *penuDetectionStatusLoc,LBTY_tenuBoolean  enuThr1DetectionValueLoc,LBTY_tenuBoolean  enuThr2DetectionValueLoc);

static void vidEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);

static void vidDiffOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);

static void vidGreaterThanOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);

static void vidLowerThanOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);

static void vidGreaterThanOrEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);

static void vidLowerThanOrEqualOperator (s32 s32ThresholdValLoc,s32 s32ReadValueLoc,LBTY_tenuBoolean *enuDefectExistLoc);
#endif /* (PLTF_DEFECTMNG == PLTF_DEFECT_HANDLER )*/
#endif
