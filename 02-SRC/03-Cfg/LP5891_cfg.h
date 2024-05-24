/* ************************************************************************** */
/* *************** CONFIGURATION DESIGN DEFINITION SECTION ****************** */
/* ************************************************************************** */
/** \page _cfgprj Configuration Description
*     \n SWC_LP5891 component is configured for STD project. */
/** \page _cfgdoc Configuration Document Reference
*   \# | Configuration Document reference
*   -- | --------------------------------
*   1  | \DESIGNER_START  \DESIGNER_END
*/
/** \page _cfginf Configuration Part Information
*   \par 11.2 - Configuration part information
*     Current Configuration Version   | Current Configuration Status
*     :-----------------------------: | :---------------------------:
*     1.0                             | Proposed
*/
/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LP5891_cfg.h
*  Component: \swc_name
*  \brief     \DESIGNER_START Abstraction layer between APP. and LED Matrix Driver \DESIGNER_END
*  \n\n
*  Scope: Public
*  \n\n
*  Coding language : C
*    \copydoc _cfgh
*  \copydoc COPYRIGHT
*/
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _cfgh LP5891_cfg.h History
*     | File             | Version      | Status              | Description |
*     | :-------------:  | :----------: | :-----------------: | :----------
*     |  Refer to SCM tool history log for older versions details and comments ||||
 *     |  LP5891_cfg.h                   | 1.0                 | Proposed            | Initial creation         
 *     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */
#ifndef LP5891_CFG_H
#define LP5891_CFG_H
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */


/* ************************************************************************** */
/* **************************** FEATURES SECTION **************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START   Feature oN/Off  \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-0Xff] / Resolution NA / Unit :NA \DESIGNER_END*/
#define LP5891_FEATURE_ON           (0x55U)
#define LP5891_FEATURE_OFF          (0x5AU)

/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FEATURE_OFF,LP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_BLOCK_TRANSFER            (0x55U)
#define LP5891_HALFIMAGE_TRANSFER            (0x5AU)
#define LP5891_FULLIMAGE_TRANSFER            (0x5FU)


/**********************************************************************************************************************/
/*!Description: Image Keys protection Functionality Enable/Disable                                                             */
/*!Range: [LP5891_FEATURE_ON - LP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Keys protection Functionality to check the image validity   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FEATURE_OFF,LP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_IMAGEKEY_FEATURE        LP5891_FEATURE_OFF


/**********************************************************************************************************************/
/*!Description: GrayScale Functionality Enable/Disable                                                             */
/*!Range: [LP5891_FEATURE_ON - LP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START GrayScale Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FEATURE_OFF,LP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_GREYSCALE_FEATURE      LP5891_FEATURE_ON


/**********************************************************************************************************************/
/*!Description: RGB Functionality Enable/Disable                                                             */
/*!Range: [LP5891_FEATURE_ON - LP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START RGB Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FEATURE_OFF,LP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_RGB_FEATURE            LP5891_FEATURE_ON


/**********************************************************************************************************************/
/*!Description: Image Queuing Functionality Enable/Disable                                                             */
/*!Range: [LP5891_FEATURE_ON - LP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FEATURE_OFF,LP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_IMAGEQUEUE_FEATURE            LP5891_FEATURE_OFF


/**********************************************************************************************************************/
/*!Description: Image Queuing Functionality Enable/Disable                                                             */
/*!Range: [LP5891_FEATURE_ON - LP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [LP5891_FULLIMAGE_TRANSFER,LP5891_HALFIMAGE_TRANSFER,LP5891_BLOCK_TRANSFER] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define LP5891_IMAGE_TRANSFER            LP5891_HALFIMAGE_TRANSFER


/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8MAXNo_COMPONENT   1U

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8MAX_DEVICES 12U

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u32BLOCKPerRun_No 12U

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u32PIXELPerRUN 661U

/** \brief \DESIGNER_START Max Number of frames   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit NA \DESIGNER_END*/
#define LP5891_U16IMAGE_MAX     1U

/** \brief \DESIGNER_START Max Number of frames   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit NA \DESIGNER_END*/
#define LP5891_U16TXRXBUFFER_MAX     65000U


/** \brief \DESIGNER_START Number of INIT_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8INIT_FRAMES_NO 77U


/** \brief \DESIGNER_START Number of RESET_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8RESET_FRAMES_NO 7U

/** \brief \DESIGNER_START Number of VSYNC_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8VSYNC_FRAMES_NO 6U
#define LP5891_u8VSYNC_FRAMES_TRIALS 3U

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


#endif /* LP5891_CFG_H */
/* *********************** E N D (LP5891_cfg.h) *************************** */
