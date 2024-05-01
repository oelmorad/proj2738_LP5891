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
*     | LP5891_cfg.h       | 1.0          | Proposed            | \verbatim $Rev::             $: Revision of last commit \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Date::           #$: Date of last commit     \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Author::          $: Author of last commit   \endverbatim |
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
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8MAXNo_COMPONENT   1U

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8MAX_DEVICES 1U

/** \brief \DESIGNER_START Number of buck components \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8MAX_PIXELS 1U

/** \brief \DESIGNER_START Max Number of frames   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0x55] / Resolution NA / Unit NA \DESIGNER_END*/
#define LP5891_U16IMAGE_MAX     ((u16)1)

/* ************************************************************************** */



/** \brief \DESIGNER_START Initial configuration  \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u8SYSCFG1_INIT_VALUE         ((u8)0x90)
#define LP5891_u8SYSCFG2_INIT_VALUE         ((u8)0x00)
#define LP5891_u8CMWTAP_INIT_VALUE          ((u8)0x08)
#define LP5891_u8PWMDIV_INIT_VALUE          ((u8)0x06)
#define LP5891_u8TWLMT_INIT_VALUE           ((u8)0x9A)
#define LP5891_u8CH1TON_INIT_VALUE          ((u8)0x07)
#define LP5891_u8CH2TON_INIT_VALUE          ((u8)0x07)




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
