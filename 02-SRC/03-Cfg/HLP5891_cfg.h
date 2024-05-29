/* ************************************************************************** */
/* *************** CONFIGURATION DESIGN DEFINITION SECTION ****************** */
/* ************************************************************************** */
/** \page _cfgprj Configuration Description
*     \n SWC_HLP5891 component is configured for STD project. */
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
/** \file HLP5891_cfg.h
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
/** \page _cfgh HLP5891_cfg.h History
*     | File             | Version      | Status              | Description |
*     | :-------------:  | :----------: | :-----------------: | :----------
*     |  Refer to SCM tool history log for older versions details and comments ||||
 *     |  HLP5891_cfg.h                   | 1.0                 | Proposed            | Initial creation         
 *     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */
#ifndef HLP5891_CFG_H
#define HLP5891_CFG_H
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
#define HLP5891_FEATURE_ON           (0x55U)
#define HLP5891_FEATURE_OFF          (0x5AU)

/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FEATURE_OFF,HLP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_BLOCK_TRANSFER            (0x55U)
#define HLP5891_HALFIMAGE_TRANSFER            (0x5AU)
#define HLP5891_FULLIMAGE_TRANSFER            (0x5FU)


/**********************************************************************************************************************/
/*!Description: Image Keys protection Functionality Enable/Disable                                                             */
/*!Range: [HLP5891_FEATURE_ON - HLP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Keys protection Functionality to check the image validity   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FEATURE_OFF,HLP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_IMAGEKEY_FEATURE        HLP5891_FEATURE_OFF


/**********************************************************************************************************************/
/*!Description: GrayScale Functionality Enable/Disable                                                             */
/*!Range: [HLP5891_FEATURE_ON - HLP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START GrayScale Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FEATURE_OFF,HLP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_GREYSCALE_FEATURE      HLP5891_FEATURE_ON


/**********************************************************************************************************************/
/*!Description: RGB Functionality Enable/Disable                                                             */
/*!Range: [HLP5891_FEATURE_ON - HLP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START RGB Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FEATURE_OFF,HLP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_RGB_FEATURE            HLP5891_FEATURE_ON


/**********************************************************************************************************************/
/*!Description: Image Queuing Functionality Enable/Disable                                                             */
/*!Range: [HLP5891_FEATURE_ON - HLP5891_FEATURE_OFF]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FEATURE_OFF,HLP5891_FEATURE_ON] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_IMAGEQUEUE_FEATURE            HLP5891_FEATURE_OFF


/**********************************************************************************************************************/
/*!Description: Image Queuing Functionality Enable/Disable                                                             */
/*!Range: [HLP5891_FULLIMAGE_TRANSFER,HLP5891_HALFIMAGE_TRANSFER,HLP5891_BLOCK_TRANSFER]                                                                            */
/**********************************************************************************************************************/
/** \brief \DESIGNER_START Image Queuing Functionality   \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [HLP5891_FULLIMAGE_TRANSFER,HLP5891_HALFIMAGE_TRANSFER,HLP5891_BLOCK_TRANSFER] / Resolution 1 / Unit :NA \DESIGNER_END*/
#define HLP5891_IMAGE_TRANSFER            HLP5891_BLOCK_TRANSFER


/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8CHIP_LP1   0U
/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8MAXNo_COMPONENT   (HLP5891_u8CHIP_LP1 + 1U)

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8MAX_DEVICES 12U


#if HLP5891_IMAGE_TRANSFER == HLP5891_BLOCK_TRANSFER
/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u32PIXELPerRUN 7932U
#endif


/** \brief \DESIGNER_START Max Number of frames   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit NA \DESIGNER_END*/
#define HLP5891_U16IMAGE_MAX     1U

/** \brief \DESIGNER_START Max Number of frames   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit NA \DESIGNER_END*/
#define HLP5891_U16TXRXBUFFER_MAX     10000U


/** \brief \DESIGNER_START Number of INIT_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8INIT_FRAMES_NO 77U


/** \brief \DESIGNER_START Number of RESET_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8RESET_FRAMES_NO 7U

/** \brief \DESIGNER_START Number of VSYNC_FRAMES \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define HLP5891_u8VSYNC_FRAMES_NO 6U
#define HLP5891_u8VSYNC_FRAMES_TRIALS 3U

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


#endif /* HLP5891_CFG_H */
/* *********************** E N D (HLP5891_cfg.h) *************************** */
