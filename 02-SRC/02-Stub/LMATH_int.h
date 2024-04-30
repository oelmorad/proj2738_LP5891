/* ************************************************************************** */
/* *************** COMPONENT DESIGN DEFINITION SECTION ********************** */
/* ************************************************************************** */
/** \mainpage LIB_LMATH Components Design Document
 * \tableofcontents
 * \section intro 1 - Introduction
 *   \par 1.1 - Document Scope
 *     This document is the Components Design Document for LIB_LMATH component developped on STD  project.
 *     \copydoc _cfgprj
 *   \par 1.2 - Reference Documents
 *     \# |  Core/Standard Document reference            | Version   | Status      | Description                                                                                                                                                        |
 *     -- | :-------------------------------------------:|:---------:|:-----------:|:------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
 *     1  | Doxygen Guidelines                           | V1.1      | Released    |(https://docs.google.com/document/d/11H9bLdIPRVhDOuVjXYYh4VZyxFfaH96t96EHnnS1vZc/edit#heading=h.hidgczfnngw)                                                        |
 *     \copydoc _cfgdoc
 *   \par 1.3 - Component Description
 *     Description for the component role and behaviors: \n
 *	  Library of MATHematical functions
 *
 *
 *
 * \section context 2 - Software Context
 *   \DESIGNER_START Define software context diagram \DESIGNER_END
 *
 *   @startuml
 *   skinparam componentStyle uml2
 *
 *     [Component User]
 *     [LMATH]
 *
 *     [Component User]     ....> LMATH_enuAddU16toS16SatS32Max   : <<use>>
 *     [Component User]     ...>  LMATH_enuAddSatU8Max            : <<use>>
 *     [Component User]     ..>   LMATH_enuSubSatU8Min            : <<use>>
 *     [Component User]     ..>   LMATH_enuAddS16toS16Sat16Max    : <<use>>
 *     [Component User]     ..>   LMATH_enuSubS16toS16Sat16Max    : <<use>>
 *     [Component User]     ...>  LMATH_enuSubAbsU8               : <<use>>
 *     [Component User]     ..>   LMATH_enuLimitU8ToRangeU8       : <<use>>
 *     [Component User]     ...>  LMATH_enuAddSatU16Max           : <<use>>
 *     [Component User]     ..>   LMATH_enuSubSatU16Min           : <<use>>
 *     [Component User]     ...>  LMATH_enuSubAbsU16              : <<use>>
 *     [Component User]     ..>   LMATH_u16InterpolLinearSearch   : <<use>>
 *     [Component User]     ..>   LMATH_s16InterpolLinearSearch   : <<use>>
 *     [Component User]     ...>  LMATH_enuYInterpolSatU16MinMax  : <<use>>
 *     [Component User]     ....> LMATH_enuYInterpolSatS16MinMax  : <<use>>
 *
 *     LMATH_enuAddU16toS16SatS32Max   ...> [LMATH]
 *      LMATH_enuAddSatU8Max           ..>  [LMATH]
 *     LMATH_enuSubSatU8Min            ..>  [LMATH]
 *      LMATH_enuAddS16toS16Sat16Max   ..>  [LMATH]
 *     LMATH_enuSubS16toS16Sat16Max    ...> [LMATH]
 *      LMATH_enuSubAbsU8              ..>  [LMATH]
 *     LMATH_enuLimitU8ToRangeU8       ...> [LMATH]
 *      LMATH_enuAddSatU16Max          ..>  [LMATH]
 *     LMATH_enuSubSatU16Min           ...> [LMATH]
 *      LMATH_enuSubAbsU16             ..>  [LMATH]
 *     LMATH_u16InterpolLinearSearch   ...> [LMATH]
 *     LMATH_s16InterpolLinearSearch   ..>  [LMATH]
 *     LMATH_enuYInterpolSatU16MinMax  ...> [LMATH]
 *     LMATH_enuYInterpolSatS16MinMax  ..>  [LMATH]
 *
 *     [LMATH]     ..> LMATH_enuLimitU16ToRangeU16    : <<use>>
 *     [LMATH]     ...>LMATH_enuMulU8ByU8ToU16        : <<use>>
 *     [LMATH]     ..> LMATH_enuDivU16ByU8SatU8Max    : <<use>>
 *     [LMATH]     ...>LMATH_enuMulU16ByU16ToU32      : <<use>>
 *     [LMATH]     ..> LMATH_enuDivU32ByU16SatU16Max  : <<use>>
 *     [LMATH]     ...>LMATH_enuDivU32ByU32SatU32Max  : <<use>>
 *     [LMATH]     ..> LMATH_enuMulU32ByU16ToU32      : <<use>>
 *     [LMATH]     ...>LMATH_enuAddSatU32Max          : <<use>>
 *     [LMATH]     ..> LMATH_enuParityU8              : <<use>>
 *     [LMATH]     ...>LMATH_enuParityU16             : <<use>>
 *     [LMATH]     ..> LMATH_enuLimitU32ToRangeU16    : <<use>>
 *     [LMATH]     ...>LMATH_enuLimitU32ToRangeU8     : <<use>>
 *     [LMATH]     ..> LMATH_enuLimitToRangeS32       : <<use>>
 *     [LMATH]     ...>LMATH_enuLimitToRangeS16       : <<use>>
 *     [LMATH]     ..> LMATH_enuDivU32ByU16SatU32Max  : <<use>>
 *     [LMATH]     ...>LMATH_enuDivU16ByU8SatU16Max   : <<use>>
 *     [LMATH]     ..> LMATH_enuAddSatS32Max          : <<use>>
 *     [LMATH]     ...>LMATH_s32GetAbs                : <<use>>
 *     [LMATH]     ..> LMATH_enuGetVersionInfo        : <<use>>
 *
 *   @enduml
 *
 * \section usecase 3 - Component Use Cases
 *
 *   LMATH Component Use Case 1: Initialization diagram
 *   @startuml
 *   skinparam componentStyle uml2
 *
 *     :LMATH: as User
 *     (LMATH services) as SRV
 *     LMATH --> (Initialize the driver) : << LMATH_enuInit() >>
 *   @enduml
 *
 *    LMATH Component Use Case 2: Nominal diagram
 *   @startuml
 *   skinparam componentStyle uml2
 *
 *     :Component User: as User
 *     (LMATH services) as SRV
 *   User --> LMATH                    									: <<use>>
 *   LMATH ---------> (Addition signed to unsigned)         							: <<LMATH_enuAddU16toS16SatS32Max()>>
 *	 LMATH --------> (Addition of two u8 terms)         								: <<LMATH_enuAddSatU8Max()>>
 *	 LMATH ---------> (subtraction of two u8 terms)           							: <<LMATH_enuSubSatU8Min()>>
 *   LMATH --------> (addition of two s16 terms)         								: <<LMATH_enuAddS16toS16Sat16Max()>>
 *	 LMATH ---------> (subtraction of two s16 terms)         							: <<LMATH_enuSubS16toS16Sat16Max()>>
 *	 LMATH --------> (the absolute subtraction of two u8 terms)           			: <<LMATH_enuSubAbsU8()>>
 *   LMATH ---------> (Limit an u8 value to a range)         							: <<LMATH_enuLimitU8ToRangeU8()>>
 *	 LMATH --------> (addition of two u16 terms)         								: <<LMATH_enuAddSatU16Max()>>
 *   LMATH ---------> (subtraction of two u16)         								: <<LMATH_enuSubSatU16Min()>>
 *	 LMATH --------> (absolute subtraction of two u16)         						: <<LMATH_enuSubAbsU16()>>
 *	 LMATH ---------> (Limit an u16 value to a range)           						: <<LMATH_enuLimitU16ToRangeU16()>>
 *   LMATH --------> (the multiplication of two u8 terms)         					: <<LMATH_enuMulU8ByU8ToU16()>>
 *	 LMATH ---------> (division of an u16 numerator by an u8 denominator)         		: <<LMATH_enuDivU16ByU8SatU8Max()>>
 *	 LMATH --------> (multiplication of two u16 terms)           						: <<LMATH_enuMulU16ByU16ToU32()>>
 *   LMATH ---------> (the division of an u32 numerator  by an u16 denominator)        : <<LMATH_enuDivU32ByU16SatU16Max()>>
 *	 LMATH --------> ( the division of an u32 numerator,by an u32 denominator)        : <<LMATH_enuDivU32ByU32SatU32Max()>>
 *   LMATH ---------> (the multiplication of u32 by u16)         						: <<LMATH_enuMulU32ByU16ToU32()>>
 *	 LMATH --------> (addition of two u32 terms)         								: <<LMATH_enuAddSatU32Max()>>
 *	 LMATH ---------> (Get the parity of u8 value)           							: <<LMATH_enuParityU8()>>
 *   LMATH --------> (Get the parity of u16 value)         							: <<LMATH_enuParityU16()>>
 *	 LMATH ---------> (the linear interpolation value of u16)         					: <<LMATH_u16InterpolLinearSearch()>>
 *	 LMATH --------> (the linear interpolation value odf s16)           				: <<LMATH_s16InterpolLinearSearch()>>
 *   LMATH ---------> (Calculate the interpolation value of sat u16)         			: <<LMATH_enuYInterpolSatU16MinMax()>>
 *	 LMATH --------> (Calculate the interpolation value sat s16)         				: <<LMATH_enuYInterpolSatS16MinMax()>>
 *   LMATH ---------> (Limit an u16 value to a u16 range)         			    		: <<LMATH_enuLimitU32ToRangeU16()>>
 *	 LMATH --------> (Limit an u32 value to a U8 range)         						: <<LMATH_enuLimitU32ToRangeU8()>>
 *	 LMATH ---------> (Limit an s32 value to a range)           						: <<LMATH_enuLimitToRangeS32()>>
 *   LMATH --------> (Limit an s16 value to a range)         							: <<LMATH_enuLimitToRangeS16()>>
 *	 LMATH ---------> (the division of an u32 numerator by u16 denominator)    		: <<LMATH_enuDivU32ByU16SatU32Max()>>
 *	 LMATH --------> (the division of an u16 numerator by u8 denominator)     		: <<LMATH_enuDivU16ByU8SatU16Max()>>
 *   LMATH ---------> (addition of two s32 terms Saturate)         					: <<LMATH_enuAddSatS32Max()>>
 *	 LMATH --------> (get the absolute value for s32)         						: <<LMATH_s32GetAbs()>>
 *	 LMATH ---------> (Get version info)      											: <<LMATH_enuGetVersionInfo()>>
 *   @enduml
 *
 * \section DConstraints 4 - Design Constraints
<<<<<<< .mine
 *   \par Req_SWC_LMATH_CDD_034-V01:
 *       \DESIGNER_START\DESIGNER_END
||||||| .r284
 *   \par Req_STD_LMATH_CDD_034-V01:
 *       \DESIGNER_START Req_STD_LMATH_CDD_034-V01\DESIGNER_END
=======
 *   \par Diagnosis Constraints:
 *       \DESIGNER_START DIAG_001 \DESIGNER_END
>>>>>>> .r298
 *   \n\b Description:\n
 *        each public interface should return error status weather an error exists or not \DESIGNER_END
 *
 *
 * \section sequence 5 - Resources Management
 *   \par 5.1 - Hardware resources
 *      Hardware resources list here: µC hardware uses RL78 instance
 *   \par 5.2 - Resources consumption objectives
 *     Estimation of RAM / ROM consumption:
 *       - Estimation of RAM consumption:  8 bytes
 *       - Estimation of ROM consumption:  4444 bytes
 *
 * \section IConstraints 6 - Integration Constraints
 *
 *   \par Req_STD_LMATH_CDD_034-V01-:
 *       \DESIGNER_START Req_STD_LMATH_CDD_034-V01 \DESIGNER_END
 *   \n\b Description:\n
 *        Returned error status from each public service should be checked before reading the result \DESIGNER_END
 *
 *	\section Management 7 - Sequence Management
 *   @startuml
 *   title LMATH Sequence Management diagram
 *      activate ENV
 *      ENV          -> LMATH        : <<LMATH_enuAddU16toS16SatS32Max()>>     
 *      ENV          -> LMATH        : <<LMATH_enuAddSatU8Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuSubSatU8Min()>>
 *      ENV          -> LMATH        : <<LMATH_enuAddS16toS16Sat16Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuSubS16toS16Sat16Max()>>    
 *      ENV          -> LMATH        : <<LMATH_enuSubAbsU8()>>
 *      ENV          -> LMATH        : <<LMATH_enuLimitU8ToRangeU8()>>      
 *      ENV          -> LMATH        : <<LMATH_enuAddSatU16Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuSubSatU16Min()>>     
 *      ENV          -> LMATH        : <<LMATH_enuSubAbsU16()>>
 *      ENV          -> LMATH        : <<LMATH_enuLimitU16ToRangeU16()>>
 *      ENV          -> LMATH        : <<LMATH_enuMulU8ByU8ToU16()>>
 *      ENV          -> LMATH        : <<LMATH_enuDivU16ByU8SatU8Max()>>    
 *      ENV          -> LMATH        : <<LMATH_enuMulU16ByU16ToU32()>>
 *      ENV          -> LMATH        : <<LMATH_enuDivU32ByU16SatU16Max()>>      
 *      ENV          -> LMATH        : <<LMATH_enuDivU32ByU32SatU32Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuMulU32ByU16ToU32()>>     
 *      ENV          -> LMATH        : <<LMATH_enuAddSatU32Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuParityU8()>>
 *      ENV          -> LMATH        : <<LMATH_enuParityU16()>>
 *      ENV          -> LMATH        : <<LMATH_u16InterpolLinearSearch()>>    
 *      ENV          -> LMATH        : <<LMATH_s16InterpolLinearSearch()>>
 *      ENV          -> LMATH        : <<LMATH_enuYInterpolSatU16MinMax()>      
 *      ENV          -> LMATH        : <<LMATH_enuYInterpolSatS16MinMax()>
 *      ENV          -> LMATH        : <<LMATH_enuLimitU32ToRangeU16()>>     
 *      ENV          -> LMATH        : <<LMATH_enuLimitU32ToRangeU8()>>
 *      ENV          -> LMATH        : <<LMATH_enuLimitToRangeS32()>>
 *      ENV          -> LMATH        : <<LMATH_enuLimitToRangeS16()>>
 *      ENV          -> LMATH        : <<LMATH_enuDivU32ByU16SatU32Max()>>    
 *      ENV          -> LMATH        : <<LMATH_enuDivU16ByU8SatU16Max()>>
 *      ENV          -> LMATH        : <<LMATH_enuAddSatS32Max()>>      
 *      ENV          -> LMATH        : <<LMATH_s32GetAbs()>>
 *      ENV          -> LMATH        : LMATH_enuGetVersionInfo()
 *		deactivate ENV
 *   @enduml
 *
 *
 * \section history 7 - Document Information
 *   \par 7).1 - Core/Standard part information
 *     Current Core/Standard Version   | Current Core/Standard Status
 *     :-----------------------------: | :---------------------------:
 *     \ v1.1                          | \ released
 *
 *     \copydoc _inth
 *     \copydoc _privh
 *     \copydoc _prgc
 *     \copydoc _cfginf
 *     \copydoc _cfgh
 *     \copydoc _cfgc
 * 	   \copydoc COPYRIGHT
 *     \copydoc Templatehisto
 */
/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LMATH_int.h
 *  Component          LIB_LMATH
 *  \brief             Library of MATHematical functions (LMATH) driver
 *  \details           Library of MATHematical functions (LMATH) driver
 *                     Module          : LMATH_int.h
 *			              Date            : 02 Apr 2014
 *			              Project         : STD
 *                     Target          : STD
 *                     Vendor          : Valeo
 *  \n\n
 *  Scope            : Component
 *  \n\n
 *  Coding language  : C
 *  \copydoc _inth
 *  \copydoc           COPYRIGHT
 */
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _privh LMATH_int.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						Initial ceration 																					||||
 *     | LMATH_int.h      | V1.0        | Proposed            | \verbatim $Rev::1            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::02-04-2014 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Gauthier Lagaisse   	$: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 		Updated code after applying review remarks of tag 59.22-01.00.00-08.00  																					||||
 *     | LMATH_int.h      | V1.0        | Proposed            | \verbatim $Rev::2            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::22-05-2018 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Ahmed abdelmegeed   	$: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 		 Update code after applying MISRA issues remarks 																					||||
 *     | LMATH_int.h      | V1.1        | Proposed            | \verbatim $Rev::            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::13-01-2019 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy   	$: Author of last commit    \endverbatim |
 */
  /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 				  migration to Doxygen																					||||
 *     | LMATH_int.h      | V1.2        | Proposed            | \verbatim $Rev::1            		$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::14-04-2020 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Dina Shinaishin   	$: Author of last commit    \endverbatim |
 */
  /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |               Close review points                                                             ||||
 *     | LMATH_int.h      | V1.2        | released            | \verbatim $Rev::    284             $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::   05-05-2020     #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy      $: Author of last commit    \endverbatim |
 */

/* ***************************************************************************************** */
/* ************************* HEADER PROTECTION ********************************************* */
/* ***************************************************************************************** */
#ifndef LMATH_INT_H
#define LMATH_INT_H

/******************************************************************************/
/******************************************************************************/
/**** AREA: HEADER INCLUDED FILES *********************************************/
/******************************************************************************/
/******************************************************************************/


/******************************************************************************/
/******************************************************************************/
/**** AREA: DEFINES ***********************************************************/
/******************************************************************************/
/******************************************************************************/




/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/**
 * \brief \DESIGNER_START Defines 2D coordinates on u16 values \DESIGNER_END
*/
struct strLmathU16Coord2D
{
      /* !Comment : x coordinate (abscissa)                                       */
      /* !Range   : [0..65535]                                                    */
      u16 u16X;

      /* !Comment : y coordinate (ordinate)                                       */
      /* !Range   : [0..65535]                                                    */
      u16 u16Y;
};

 /**
  * \brief \DESIGNER_START Defines 2D coordinates on s16 values \DESIGNER_END
 */
struct strLmathS16Coord2D
{
      /* !Comment : x coordinate (abscissa)                                       */
      /* !Range   : [-32768..+32767]                                              */
      s16 s16X;

      /* !Comment : y coordinate (ordinate)                                       */
      /* !Range   : [-32768..+32767]                                              */
      s16 s16Y;
};

/**
 *  \brief \DESIGNER_START Enumerates Rounding methods (used into divisions) \DESIGNER_END
*/
enum enuLmathRounding
{
   LMATH_ROUND_DOWN      = (u8)0x00,     /* Round Down                         */
   LMATH_ROUND_NEAREST   = (u8)0x80,     /* Round to Nearest                   */
   LMATH_ROUND_UP        = (u8)0xFF      /* Round Up                           */
};

/**
 *  \brief \DESIGNER_START Enumerates Parities \DESIGNER_END
*/
enum enuLmathParity
{
   LMATH_PARITY_EVEN     = (u8)0x00,     /* Parity Even                        */
   LMATH_PARITY_ODD      = (u8)0x01      /* Parity Odd                         */
};



/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/
/*****************************************************************************/

/**
 * \brief \DESIGNER_START this type defines Rounding methods (used into divisions)  \DESIGNER_END
*/
typedef enum enuLmathRounding LMATH_tenuRounding;

/**
 * \brief \DESIGNER_START This type defines Parities  \DESIGNER_END
*/
typedef enum enuLmathParity LMATH_tenuParity;

/**
 * \brief \DESIGNER_START This type defines 2D coordinates on u16 values   \DESIGNER_END
*/
typedef struct strLmathU16Coord2D LMATH_tstrU16Coord2D;


/**
 * \brief \DESIGNER_START This type defines 2D coordinates on s16 values  \DESIGNER_END
*/
typedef struct strLmathS16Coord2D LMATH_tstrS16Coord2D;

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone constant *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone struct/union *************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone variable *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone function *****************************/
/*****************************************************************************/


/* ***************************************************************************************** */
/**  \brief      Addition signed to unsigned
 *   \details    This service shall do the following actions :
 *               - Calculate the addition of U16 to S16
 *               - Set the result into *u32ResultCpy
 *
 *   \param[in]  *s32ResultCpy -> pointer to return the result, Range[-2147483647...2147483647]
 *                s32TermLeftCpy -> the left term of the addition operation,
 *                                  Range[-2147483647...2147483647]
 *                s32TermRightCpy-> the right term of the addition operation,
 *                                  Range[-2147483647...2147483647]
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_001-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ***************************************************************************************** */
extern LBTY_tenuErrorStatus LMATH_enuAddU16toS16SatS32Max(s32 *s32ResultCpy, u16 u16TermLeftCpy, s16 s16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      Addition of two u8
 *   \details    This service shall do the following actions :
 *               - Calculate the addition of two u8 terms
 *               - Saturate the result to u8MAX value (255)
 *               - Set the result into *u8ResultCpy
 *
 *   \param[in]  *u8ResultCpy -> pointer to return the result, Range[0...255]
 *                u8TermLeftCpy -> the left term of the addition operation, Range[0..255]
 *                u8TermRightCpy-> the right term of the addition operation,Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_002-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuAddSatU8Max(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two u8
 *   \details    This service shall do the following actions :
 *               - Calculate the subtraction of two u8 terms
 *               - Saturate the result to u8MIN value (0)
 *                - Set the result into *u8ResultCpy
 *
 *   \param[in]  *u8ResultCpy -> pointer to return the result, Range[0...255]
 *                u8TermLeftCpy -> the left term of the addition operation, Range[0..255]
 *                u8TermRightCpy-> the right term of the addition operation,Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_003-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuSubSatU8Min(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      addition of two s16
 *   \details    This service shall do the following actions :
 *               - Calculate the addition of s16 to S16
 *               - Set the result into *u16ResultCpy
 *
 *   \param[in]  *u8ResultCpy -> pointer to return the result, Range[0...255]
 *                s16TermLeftCpy -> the left term of the addition operation,Range[-32768...32767
 *                s16TermRightCpy-> the right term of the addition operation,Range[-32768...32767]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_004-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddS16toS16Sat16Max(s16 *s16ResultCpy, s16 s16TermLeftCpy, s16 s16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two s16
 *   \details    This service shall do the following actions :
 *               - Calculate the subtraction  of s16 to S16
 *               - Set the result into *u16ResultCpy
 *
 *   \param[in]  *u8ResultCpy -> pointer to return the result, Range[0...255]
 *                s16TermLeftCpy -> the left term of the addition operation,Range[-32768...32767
 *                s16TermRightCpy-> the right term of the addition operation,Range[-32768...32767]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_005-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubS16toS16Sat16Max(s16 *s16ResultCpy, s16 s16TermLeftCpy, s16 s16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two u8
 *   \details    This service shall do the following actions :
 *               - Calculate the absolute subtraction of two u8 terms
 *               - Set the result into *u8ResultCpy
 *
 *   \param[in]  *u8ResultCpy -> pointer to return the result, Range[0...255]
 *                u8TermLeftCpy -> the left term of the subtract operation, Range[0..255]
 *                u8TermRightCpy-> the right term of the subtract operation,Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_006-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuSubAbsU8(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two u8
 *   \details    This service shall do the following actions :
 *               - Limit an u8 value to a range ==> [Min..Max]
 *               - Set the result into *u8ResultCpy
 *
 *   \param[in]   *u8ResultCpy-> pointer to return the result, Range[0...255]
 *                u8ValueCpy  -> Value to be limited, Range[0..255]
 *                u8MinCpy    -> Minimum value of range, Range[0..u8Max]
 *                 u8MaxCpy    -> Maximum value of range, Range[u8Min..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_007-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuLimitU8ToRangeU8(u8 *u8ResultCpy,u8 u8ValueCpy, u8 u8MinCpy, u8 u8MaxCpy);

/* ***************************************************************************************** */
/**  \brief      addition of two u16 terms
 *   \details    This service shall do the following actions :
 *                - Calculate the addition of two u16 terms
 *                - Saturate the result to u16MAX value (65535)
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy -> pointer to return the result, Range[0...65535]
 *                u16TermLeftCpy -> the left term of the addition operation, Range[0..65535]
 *                u16TermRightCpy-> the right term of the addition operation,Range[0..65535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_008-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuAddSatU16Max(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two u16
 *   \details    This service shall do the following actions :
 *                - Calculate the subtraction of two u16 terms
 *                - Saturate the result to u16MIN value (0)
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy -> pointer to return the result, Range[0...56535]
 *                u16TermLeftCpy -> the left term of the addition operation, Range[0..65535]
 *                u16TermRightCpy-> the right term of the addition operation,Range[0..65535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_009-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuSubSatU16Min(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      absolute subtraction of two u16
 *   \details    This service shall do the following actions :
 *               - Calculate the absolute subtraction of two u16 terms
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy -> pointer to return the result, Range[0...65535]
 *                u16TermLeftCpy -> the left term of the addition operation, Range[0..65535]
 *                u16TermRightCpy-> the right term of the addition operation,Range[0..65535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_010-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuSubAbsU16(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      Limit an u16 value to a range
 *   \details    This service shall do the following actions :
 *                - Limit an u16 value to a range ==> [Min..Max]
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy-> pointer to return the result, Range[0...56535]
 *                u16ValueCpy  -> Value to be limited, Range[0..56535]
 *                u16MinCpy    -> Minimum value of range, Range[0..u16Max]
 *                u16MaxCpy    -> Maximum value of range, Range[u16Min..56535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_011-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuLimitU16ToRangeU16(u16 *u16ResultCpy, u16 u16ValueCpy, u16 u16MinCpy,
   u16 u16MaxCpy);

/* ***************************************************************************************** */
/**  \brief      the multiplication of two u8 terms
 *   \details    This service shall do the following actions :
 *                - Calculate the multiplication of two u8 terms
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy-> pointer to return the result, Range[0...56535]
 *                u8TermLeftCpy  -> left term of operation, Range[0..255]
 *                u8TermRightCpy -> right term of operation, Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_012-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuMulU8ByU8ToU16(u16 *u16ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      division of an u16 numerator by an u8 denominator
 *   \details    This service shall do the following actions :
 *                - Calculate the division of an u16 numerator by an u8 denominator
 *                - Round off, down or up the result,according to requested method
 *                - Saturate the result to u8MAX value (255)
 *                - Set the result into *u8ResultCpy
 *
 *   \param[in]   *u8ResultCpy   -> pointer to return the result, Range[0..255]
 *                u16NumCpy      -> Numerator , Range[0..65535]
 *                u8DenomCpy     -> Denominator, Range[1..255]
 *                enuRoundingCpy -> Rounding method to use
 *                u8DefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_013-V01
 *
 *   \par Coverage: Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuDivU16ByU8SatU8Max(u8* u8ResultCpy, u16 u16NumCpy, u8 u8DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u8 u8DefaultValCpy);

/* ***************************************************************************************** */
/**  \brief      multiplication of two u16 terms
 *   \details    This service shall do the following actions :
 *                - Calculate the multiplication of two u16 terms
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u32ResultCpy  -> pointer to return the result, Range[0..4294967295]
 *                u16TermLeftCpy  -> left term of operation, Range[0..255]
 *                u16TermRightCpy -> right term of operation, Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_014-V01
 *
 *   \par Coverage: Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuMulU16ByU16ToU32(u32 *u32ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      the division of an u32 numerator  by an u16 denominator
 *   \details    This service shall do the following actions :
 *                 - Calculate the division of an u32 numerator
 *                   by an u16 denominator
 *                 - Round off, down or up the result,
 *                   according to requested method
 *                 - Saturate the result to u16MAX value (56535)
 *                 - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy   -> pointer to return the result, Range[0..65535]
 *                u32NumCpy      -> Numerator , [0..4294967295]
 *                u16DenomCpy     -> Denominator, Range[0..65535]
 *                enuRoundingCpy -> Rounding method to use
 *                u16DefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_015-V01
 *
 *   \par Coverage: Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuDivU32ByU16SatU16Max(u16* u16ResultCpy, u32 u32NumCpy, u16 u16DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u16 u16DefaultValCpy);

/* ***************************************************************************************** */
/**  \brief       the division of an u32 numerator,by an u32 denominator
 *   \details    This service shall do the following actions :
 *                  - Calculate the division of an u32 numerator,by an u32 denominator
 *                 - Round off, down or up the result, according to requested method
 *
 *                 - Set the result into *u32ResultCpy  y
 *
 *   \param[in]   *u32ResultCpy   -> pointer to return the result, Range[0..4294967295]
 *                u32NumCpy      -> Numerator , [0..4294967295]
 *                u32DenomCpy     -> Denominator, Range[0..4294967295]
 *                enuRoundingCpy -> Rounding method to use
 *                u32DefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_016-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuDivU32ByU32SatU32Max(u32* u32ResultCpy, u32 u32NumCpy, u32 u32DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u32 u32DefaultValCpy);

/* ***************************************************************************************** */
/**  \brief      addition of two u16 terms
 *   \details    This service shall do the following actions :
 *                  - Calculate the multiplication of u32 by u16
 *                - Set the result into *u32ResultCpy
 *
 *   \param[in]   *u32ResultCpy  -> pointer to return the result, Range[0..4294967295]
 *                u32TermLeftCpy  -> left term of operation, Range[0..4294967295]
 *                u16TermRightCpy -> right term of operation, Range[0..56535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_017-V01

 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuMulU32ByU16ToU32(u32 *u32ResultCpy, u32 u32TermLeftCpy, u16 u16TermRightCpy);


/* ***************************************************************************************** */
/**  \brief      addition of two u16 terms
 *   \details    This service shall do the following actions :
 *                  - Calculate the addition of two u32 terms
 *                - Saturate the result to u32MAX value (4294967295)
 *                - Set the result into *u32ResultCpy
 *
 *   \param[in]   *u32ResultCpy -> pointer to return the result, Range[0...4294967295]
 *                u32TermLeftCpy -> the left term of the addition operation, Range[0..4294967295]
 *                u32TermRightCpy-> the right term of the addition operation,Range[0..4294967295]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_018-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuAddSatU32Max(u32 *u32ResultCpy, u32 u32TermLeftCpy, u32 u32TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      Get the parity of u8 value
 *   \details    This service shall do the following actions :
 *                  - Get the parity of u8 value
 *                  - Set the result into *penuResultCpy
 *
 *   \param[in]   *penuResultCpy -> pointer to return the result, Parity of input value
 *                u8ValCpy       -> Value to test parity, Range[0..255]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_019-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuParityU8(LMATH_tenuParity *penuResultCpy, u8 u8ValCpy);

/* ***************************************************************************************** */
/**  \brief      parity  of two u16 terms
 *   \details    This service shall do the following actions :
 *                  - Get the parity of u16 value
 *                  - Set the result into *penuResultCpy
 *
 *   \param[in]   *penuResultCpy -> pointer to return the result, Parity of input value
 *                u8ValCpy       -> Value to test parity, Range[0..65535]
 *
 *   \return     LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_020-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuParityU16(LMATH_tenuParity *penuResultCpy,u16 u16ValCpy);

/* ***************************************************************************************** */
/**  \brief      calculation of the linear interpolation value
 *   \details    This service shall do the following actions :
 *                  - Returns the calculation of the linear interpolation value
 *                  (Y coordinate) from a list of u16 {Xk;Yk} coordinates.
 *                  ==> {Y,X} = f( {X1;X1} , ... , {Xn;Yn} )
 *                  <=> Y = f( {X1;X1} , ... , {Xn;Yn} , X )
 *                - Assume {Xk;Yk} coordinates represents
 *                  a mathematical function(x) (ordered by Xk: Xk-1 < Xk)
 *                - Extrapolate the result
 *                  ==> if X<X1, calculate Y using {X1;X1},{X2;X2}
 *                  ==> if Xn<X, calculate Y using {Xn-1;Xn-1},{Xn;Xn}
 *                - Round off, down or up the result,
 *                  according to requested method
 *                - Saturate the result if calculation is out of u16 bounds
 *
 *   \param[in]   u16XCpyy                      -> X coordinate used to interpolate Y ones,Range:[0..65535]
 *                kastrTabU16Coord2DCpy[]       -> Table of u16 coordinates {X1;X1} , ... , {Xn;Yn}
 *                u8TabSizeCpy                  ->Size (number of elements) of table of coordinates,Range:[1..255]
 *                enuRoundingCpy                ->
 *
 *   \return   u16YResultLoc ->Y Result variable ==> Y interpolated coordinate,Range:[0..65535]
 *   \par Requirement ID:Req_SWC_LMATH_CDD_021-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern u16 LMATH_u16InterpolLinearSearch(
   /* !Comment : X coordinate used to interpolate Y ones                       */
   /* !Range   : [0..65535]                                                    */
   u16 u16XCpy,
   /* !Comment : Table of u16 coordinates {X1;X1} , ... , {Xn;Yn}              */
   /*            {Xk;Yk} coordinates shall represents                          */
   /*            a mathematical function(x) (ordered by Xk: Xk-1 < Xk)         */
   /* !Range   : N/A                                                           */
   const LMATH_tstrU16Coord2D kastrTabU16Coord2DCpy[],
   /* !Comment : Size (number of elements) of table of coordinates             */
   /* !Range   : [1..255]                                                      */
   u8  u8TabSizeCpy,
   /* !Comment : Rounding method to use                                        */
   /* !Range   : N/A                                                           */
   LMATH_tenuRounding enuRoundingCpy
);


/* ***************************************************************************************** */
/**  \brief      calculation of the linear interpolation value
 *   \details    This service shall do the following actions :
 *                  - Returns the calculation of the linear interpolation value
 *                  (Y coordinate) from a list of s16 {Xk;Yk} coordinates.
 *                  ==> {Y,X} = f( {X1;X1} , ... , {Xn;Yn} )
 *                  <=> Y = f( {X1;X1} , ... , {Xn;Yn} , X )
 *                - Assume {Xk;Yk} coordinates represents
 *                  a mathematical function(x) (ordered by Xk: Xk-1 < Xk)
 *                - Extrapolate the result
 *                  ==> if X<X1, calculate Y using {X1;X1},{X2;X2}
 *                  ==> if Xn<X, calculate Y using {Xn-1;Xn-1},{Xn;Xn}
 *                - Round off, down or up the result,
 *                  according to requested method
 *                - Saturate the result if calculation is out of s16 bounds
 *
 *   \param[in]   u16XCpyy                      -> X coordinate used to interpolate Y ones,Range:[-32768..+32767]
 *                kastrTabU16Coord2DCpy[]       -> Table of s16 coordinates {X1;X1} , ... , {Xn;Yn}
 *                u8TabSizeCpy                  ->Size (number of elements) of table of coordinates,Range:[1..255]
 *                enuRoundingCpy                ->Rounding method to use
 *
 *   \return   u16YResultLoc ->Y Result variable ==> Y interpolated coordinate,Range:[-32768..+32767]
 *   \par Requirement ID:Req_SWC_LMATH_CDD_022-V01
 *
 *   \par Coverage:Covers
 *
 *
 */
/* ******************************************************************************************/
extern s16 LMATH_s16InterpolLinearSearch(
   /* !Comment : X coordinate used to interpolate Y ones                       */
   /* !Range   : [-32768..+32767]                                              */
   s16 s16XCpy,
   /* !Comment : Table of s16 coordinates {X1;X1} , ... , {Xn;Yn}              */
   /*            {Xk;Yk} coordinates shall represents                          */
   /*            a mathematical function(x) (ordered by Xk: Xk-1 < Xk)         */
   /* !Range   : N/A                                                           */
   const LMATH_tstrS16Coord2D kastrTabS16Coord2DCpy[],
   /* !Comment : Size (number of elements) of table of coordinates             */
   /* !Range   : [1..255]                                                      */
   u8  u8TabSizeCpy,
   /* !Comment : Rounding method to use                                        */
   /* !Range   : N/A                                                           */
   LMATH_tenuRounding enuRoundingCpy
);

/* ***************************************************************************************** */
/**  \brief       Calculate the interpolation value (Y coordinate)
 *   \details    This service shall do the following actions :
 *                  - Calculate the interpolation value (Y coordinate)
 *                  from an u16 linear function
 *                  ==> {Y,X} = f( {x1;y1} , {x2;y2} )
 *                  <=> Y = f( {x1;y1} , {x2;y2}, X )
 *                - Manage the interpolation with a positive or negative slope
 *                - Set the interpolation result to y1 value in case of x1=x2
 *                - Extrapolate the result if X < x1 or x2 < X
 *                - Round off, down or up the result,
 *                  according to requested method
 *                - Saturate the result if calculation is out of u16 bounds
 *                - Set the result into u16YResultVar
 *
 *   \param[in]   u16YResultCpy
 *                u16XCpy
 *                u16X1Cpy
 *                u16Y1Cpy
 *                u16X2Cpy
 *                u16Y2Cpy
 *                enuRoundingCpy
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_023-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuYInterpolSatU16MinMax(u16 *u16YResultCpy, u16 u16XCpy, u16 u16X1Cpy,
   u16 u16Y1Cpy, u16 u16X2Cpy, u16 u16Y2Cpy,LMATH_tenuRounding enuRoundingCpy );

/* ***************************************************************************************** */
/**  \brief      Calculate the interpolation value
 *   \details    This service shall do the following actions :
 *                   Calculate the interpolation value (Y coordinate)
 *                  from an s16 linear function
 *                  ==> {Y,X} = f( {x1;y1} , {x2;y2} )
 *                  <=> Y = f( {x1;y1} , {x2;y2}, X )
 *                - Manage the interpolation with a positive or negative slope
 *                - Set the interpolation result to y1 value in case of x1=x2
 *                - Extrapolate the result if X < x1 or x2 < X
 *                - Round off, down or up the result,
 *                  according to requested method
 *                - Saturate the result if calculation is out of s16 bounds
 *                - Set the result into s16YResultVar
 *
 *   \param[in]   u16YResultCpy
 *                u16XCpy
 *                u16X1Cpy
 *                u16Y1Cpy
 *                s16X2Cpy
 *                u16Y2Cpy
 *                enuRoundingCpy
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_024-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
extern LBTY_tenuErrorStatus LMATH_enuYInterpolSatS16MinMax(s16 *s16YResultCpy, s16 s16XCpy, s16 s16X1Cpy,
   s16 s16Y1Cpy, s16 s16X2Cpy, s16 s16Y2Cpy,LMATH_tenuRounding enuRoundingCpy );

/* ***************************************************************************************** */
/**  \brief      Limit an u16 value to a u16 range
 *   \details    This service shall do the following actions :
 *                - Limit an u16 value to a u16 range ==> [Min..Max]
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]    *u16ResultCpy-> pointer to return the result, Range[0...56535]
 *                u32ValueCpy  -> Value to be limited, Range[0..4294967295]
 *                u16MinCpy    -> Minimum value of range, Range[0..u16Max]
 *                u16MaxCpy    -> Maximum value of range, Range[u16Min..56535]
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_025-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU32ToRangeU16(u16 *u16ResultCpy, u32 u32ValueCpy, u16 u16MinCpy, u16 u16MaxCpy);

/* ***************************************************************************************** */
/**  \brief      Limit an u32 value to a U8 range
 *   \details    This service shall do the following actions :
 *                - Limit an u32 value to a U8 range ==> [Min..Max]
 *                - Set the result into *u8ResultCpy
 *
 *   \param[in]   *u8ResultCpy-> pointer to return the result, Range[0...255]
 *                u32ValueCpy  -> Value to be limited, Range[0..42949
 *                u8MinCpy    -> Minimum value of range, Range[0..u8Max]
 *                u8MaxCpy    -> Maximum value of range, Range[u8Min..255]
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_026-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU32ToRangeU8(u8 *u8ResultCpy,u32 u32ValueCpy, u8 u8MinCpy, u8 u8MaxCpy);

/* ***************************************************************************************** */
/**  \brief      Limit an s32 value to a range
 *   \details    This service shall do the following actions :
 *                - Limit an s32 value to a range ==> [Min..Max]
 *                - Set the result into *s326ResultCpy
 *
 *   \param[in]   *s326ResultCpy-> pointer to return the result,Range[-2147483647..2147483647]
 *                s32ValueCpy  -> Value to be limited,         Range[-2147483647..2147483647]
 *                s32MinCpy    -> Minimum value of range, Range[2147483647..u16Max]
 *                u32MaxCpy    -> Maximum value of range, Range[u16Min..2147483647]
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_027-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitToRangeS32(s32 *s32ResultCpy, s32 s32ValueCpy, s32 s32MinCpy, s32 u32MaxCpy);

/* ***************************************************************************************** */
/**  \brief      Limit an s32 value to a range
 *   \details    This service shall do the following actions :
 *                - Limit an s32 value to a range ==> [Min..Max]
 *                - Set the result into *s16ResultCpy
 *
 *   \param[in]   *s16ResultCpy-> pointer to return the result,Range[-23767..23767]
 *                s32ValueCpy  -> Value to be limited, Range[-2147483647..2147483647]
 *                s16MinCpy    -> Minimum value of range, Range[-23767..u16Max]
 *                s16MaxCpy    -> Maximum value of range, Range[u16Min..23767]
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_028-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitToRangeS16(s16 *s16ResultCpy, s32 s32ValueCpy, s16 s16MinCpy, s16 s16MaxCpy);

/* ***************************************************************************************** */
/**  \brief      Calculate the division of an u32 numerator
 *   \details    This service shall do the following actions :
 *                 - Calculate the division of an u32 numerator by an u16 denominator
 *                   by an u16 denominator
 *                 - Round off, down or up the result,
 *                   according to requested method
 *                 - Set the result into *u32ResultCpy
 *
 *   \param[in]   *u32ResultCpy   -> pointer to return the result, Range[0..4294967295]
 *                u32NumCpy      -> Numerator , [0..4294967295]
 *                u16DenomCpy     -> Denominator, Range[0..65535]
 *                enuRoundingCpy -> Rounding method to use
 *                u32DefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_029-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU32ByU16SatU32Max(u32* u32ResultCpy, u32 u32NumCpy, u16 u16DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u32 u32DefaultValCpy);

/* ***************************************************************************************** */
/**  \brief      the division of an u16 numerator by u8 denominator
 *   \details    This service shall do the following actions :
 *               - Calculate the division of an u16 numerator
 *                   by an u8 denominator
 *                 - Round off, down or up the result,
 *                   according to requested method
 *                 - Set the result into *u16ResultCpy
 *
 *   \param[in]   *u16ResultCpy   -> pointer to return the result, Range[0..56535]
 *                u16NumCpy      -> Numerator , Range[0..65535]
 *                u8DenomCpy     -> Denominator, Range[1..255]
 *                enuRoundingCpy -> Rounding method to use
 *                u16DefaultValCpy-> Default value to return in case of Denominator Null error
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_030-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU16ByU8SatU16Max(u16* u16ResultCpy, u16 u16NumCpy, u8 u8DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u16 u16DefaultValCpy);

/* ***************************************************************************************** */
/**  \brief      addition of two s32 terms
 *   \details    This service shall do the following actions :
 *                - Calculate the addition of two s32 terms
 *                - Saturate the result to s32MAX value (4294967295)
 *                - Set the result into *u32ResultCpy
 *
 *   \param[in]    *s32ResultCpy -> pointer to return the result, Range[-2147483647...2147483647]
 *                s32TermLeftCpy -> the left term of the addition operation,
 *                                  Range[-2147483647...2147483647]
 *                s32TermRightCpy-> the right term of the addition operation,
 *                                  Range[-2147483647...2147483647]
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_031-V01
 *
 *   \par Coverage:Covers_
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddSatS32Max(s32 *s32ResultCpy, s32 s32TermLeftCpy, s32 s32TermRightCpy);

/******************************************************************************************/
/**
 *   \brief    LFIL Get Version Info
 *   \details  This function shall provide the ability to Get Version Info
 *
 *   \param[out]    pVersionInfo   / LBTY_tstrVersionInfoType*
 *
 *   \return  Return Status of the function \n
 *            Returned Value List:
 *            Return Status Values
 *            Return Value:
 *             - LBTY_OK: execution success
 *             - LBTY_NOK: initialization wasn't called
 *             - LBTY_NULL_POINTER: null pointer parameter detected
 *
 *   \par Requirement ID:Req_SWC_LMATH_CDD_032-V01
 *
 *   \par Coverage::Covers_
 *
 *
 */
/*******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuGetVersionInfo(LBTY_tstrVersionInfoType *pVersionInfo);


/******************************************************************************************/
/**
 *   \brief     get the absolute value for signed 32 value
 *   \details  This service shall do the following actions :
 *               - get the absolute value for signed 32 value
 *
 *   \param[out]    s32valCpy -> the signed value
 *
 *   \return  s32 positive value
 *
 *   \par Requirement ID:Req_SWC_LMATH_CDD_033-V01
 *
 *   \par Coverage:
 *
 *
 */
/*******************************************************************************************/
s32 LMATH_s32GetAbs(s32 s32valCpy);

#endif /* LMATH_INT_H */
/**** E N D (LMATH_int.h) *****************************************************/

