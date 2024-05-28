/* ************************************************************************** */
/* *************** COMPONENT DESIGN DEFINITION SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file HLP5891_int.h
*  Component: HLP5891
*  \brief     \DESIGNER_START Brief description of the file \DESIGNER_END
*  \details   \DESIGNER_START Much more details can be added \DESIGNER_END
*  \n\n
*  Scope: Public
*  \n\n
*  Coding language : C
*    \copydoc _inth
*  \copydoc COPYRIGHT
*/
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _inth HLP5891_int.h History
*     | File             | Version      | Status              | Description |
*     | :-------------:  | :----------: | :-----------------: | :----------
*     |  Refer to SCM tool history log for older versions details and comments ||||
*     | HLP5891_int.h       | V1.0         | Proposed            | Initial creation
*     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */
#ifndef HLP5891_INT_H
#define HLP5891_INT_H
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "HLP5891_cfg.h"
/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
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

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */
extern void HLP5891_vidInit(void);


extern void HLP5891_vidRunMgmt(void);                /** Mode Managemnet Runnable  */



extern LBTY_tenuErrorStatus HLP5891_vidAnimateImage(u8 Driver, const u8 * const pu8image, u32 u32ImagepixelNo) ;
extern LBTY_tenuErrorStatus HLP5891_vidStopAnimation(u8 Driver) ;






#endif /* HLP5891_INT_H */
/* *********************** E N D (HLP5891_int.h) *************************** */
/* **************** TEMPLATE HISTORY - DO NOT MODIFY ************************ */
/**
* \page COPYRIGHT COPYRIGHT
* <b>..............................................................................\n
*    COPYRIGHT 2018 VALEO VISIBILITY SYSTEM   \n
*    all rights reserved\n
* ..............................................................................</b>
* \page Templatehisto Template history
*    <b>Template history:</b>
*    Version | Status   | Author          | Date       | Description
*    :-----: | :------: | :-------------- | :--------- | :----------
*    0.1     | Proposed | R.SALSON        | 19/12/2018 | Template creation \n Proposed version for TR-COMP and ASPICE
*    0.2     | Released | R.SALSON        | 18/01/2019 | Fix svn keywords substitution issue \n Update chapter numbering 6.5 to 6.4 - Protection mechanisms \n [STD SWC Template (including Doxygen Tags) Review](https://docs.google.com/spreadsheets/d/1aG6PZGLnlz_qyYptmWbM_hKHKZSOfPKYcp1RaWdZOPQ/edit?ts=5c386467#gid=1515697222)
*    0.3     | Released | R.SALSON        | 01/04/2019 | Fix artf438622 : Add Sections for "Design constraints" and "Integration constraints" in CDD template \n Add Rationals for contraints
*    1.0     | Released | R.SALSON        | 26/09/2019 | Fix artf569256 : [Doxygen Template] Add Section for Design Choices \n Fix artf569255 : [Doxygen Template] Missing Global Sequence Diagram for the component
*
*/
