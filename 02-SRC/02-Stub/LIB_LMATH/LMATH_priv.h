/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LMATH_priv.h
 *  Component       LIB_LMATH
 *  \brief          Library of MATHematical functions (LMATH) Driver
 *                   
 *  \details        Library of MATHematical functions (LMATH) Driver
 *                  Module          : LMATH_priv.h
 *				 	Date            : 02 April 2014
 *					Project         : STD
 *                  Target          : STD
 *                  Vendor          : Valeo
 *  \n\n
 *  Scope           : Private
 *  \n\n
 *  Coding language : C
 * \copydoc _privh
 * \copydoc           COPYRIGHT
 *
 */

/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _privh LMATH_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						Initial ceration 																					||||
 *     | LMATH_priv.h      | V1.0        | Proposed            | \verbatim $Rev::1            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::02-04-2014 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Gauthier Lagaisse   	$: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 						Converted Macro-like functions to functions 																					||||
 *     | LMATH_priv.h      | V1.0        | Proposed            | \verbatim $Rev::2            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::20-04-2017 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: sahmed2   	$: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 		Updated code after review remarks of tag 59.22-01.00.00-08.00 																					||||
 *     | LMATH_priv.h      | V1.0        | Proposed            | \verbatim $Rev::            	$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::11-04-2018 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Ahmed abdelmageed   	$: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 				Update code after applying MISRA issues remarks																					||||
 *     | LMATH_priv.h      | V1.1        | Proposed            | \verbatim $Rev::1            		$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::13-01-2019 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy   	$: Author of last commit    \endverbatim |
 */
  /** \page _privh LMATH_priv.h History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     | 				  migration to Doxygen																					||||
 *     | LMATH_priv.h      | V1.2        | Proposed            | \verbatim $Rev::1            		$: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::13-01-2019 		#$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Dina Shinaishin   	$: Author of last commit    \endverbatim |
 */
/** \page _privh LMATH_priv.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |               Close Review Points                                                              ||||
 *     | LMATH_priv.c      | V1.2        | Released            | \verbatim $Rev::    285            $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::   05-05-2020    #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy     $: Author of last commit    \endverbatim |
 */
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */

#ifndef LMATH_PRIV_H
#define LMATH_PRIV_H

/* ***************************************************************************************** */
/**  \brief       the addition of two u32 terms
 *   \details    This service shall do the following actions :
 *                 - Calculate the addition of two u32 terms
 *                - Saturate the result to u32MAX value (4294967295)
 *                - Set the result into *u32ResultCpy
 *
 *   \param[in]    *u32ResultCpy -> pointer to return the result, Range[0...4294967295]
 *                u32TermLeftCpy -> the left term of the addition operation, Range[0..4294967295]
 *                u32TermRightCpy-> the right term of the addition operation,Range[0..4294967295]
 *
 *   \return     void
 *
 *
 */
/* ******************************************************************************************/
static void vidAddSatU32Max(u32 *u32ResultCpy, u32 u32TermLeftCpy, u32 u32TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      subtraction of two u16 terms
 *   \details    This service shall do the following actions :
 *                -  Calculate the subtraction of two u16 terms
 *                - Saturate the result to u16MIN value (0)
 *                - Set the result into *u16ResultCpy
 *
 *   \param[in]     *16ResultCpy -> pointer to return the result, Range[0...56535]
 *                 16TermLeftCpy -> the left term of the subtract operation, Range[0..56535]
 *                 16TermRightCpy-> the right term of the subtract operation,Range[0..56535]
 *
 *   \return     void
 *
 *    \par Coverage:Covers_STD_LMATH_CDD_031-V01
 */
/* ******************************************************************************************/
static void vidSubSatU16Min(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);


/* ***************************************************************************************** */
/**  \brief      multiplication of two u16 terms
 *   \details    This service shall do the following actions :
 *                 - Calculate the multiplication of two u16 terms
 *
 *   \param[in]    *u32ResultCpy  -> pointer to return the result, Range[0..4294967295]
 *                u16TermLeftCpy  -> left term of operation, Range[0..255]
 *                u16TermRightCpy -> right term of operation, Range[0..255]
 *
 *   \return     void
 *
 *
 */
/* ******************************************************************************************/
static void vidMulU16ByU16ToU32(u32 *u32ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy);

/* ***************************************************************************************** */
/**  \brief      the division of an u32 numerator by an u16 denominator
 *   \details    This service shall do the following actions :
 *                 - Calculate the division of an u32 numerator
 *                   by an u16 denominator
 *                 - Round off, down or up the result,
 *                   according to requested method
 *                 - Saturate the result to u16MAX value (56535)
 *                 - Set the result into *u16ResultCpyy
 *
 *   \param[in]    *u16ResultCpy   -> pointer to return the result, Range[0..65535]
 *                u32NumCpy      -> Numerator , [0..4294967295]
 *                u16DenomCpy     -> Denominator, Range[0..65535]
 *                enuRoundingCpy -> Rounding method to use
 *                u16DenomNullDefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return     void
 *
 *
 */
/* ******************************************************************************************/
static void vidDivU32ByU16SatU16Max(u16* u16ResultCpy, u32 u32NumCpy, u16 u16DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u16 u16DenomNullDefaultValCpy);


/* ***************************************************************************************** */
/**  \brief       the addition of two u32 terms
 *   \details    This service shall do the following actions :
 *                 -
 *
 *   \param[in]   *u16ResultCpy   -> pointer to return the result, Range[0..65535]
 *                u16XCpy  ->
 *                u16X1Cpy ->
 *                u16Y1Cpy ->
 *                u16X2Cpy ->
 *                u16Y2Cpy
 *                enuRoundingCpy -> Rounding method to use
 *
 *   \return     void
 *   \par Requirement ID:
 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/

static void vidYInterpolSatU16MinMax(u16 *u16YResultCpy, u16 u16XCpy, u16 u16X1Cpy, u16 u16Y1Cpy, u16 u16X2Cpy,
   u16 u16Y2Cpy,LMATH_tenuRounding enuRoundingCpy );
/* ***************************************************************************************** */
/**  \brief       the addition of two u32 terms
 *   \details    This service shall do the following actions :
 *                 -
 *
 *   \param[in]   *u16ResultCpy   -> pointer to return the result, Range[0..65535]
 *                u16XCpy  ->
 *                u16X1Cpy ->
 *                u16Y1Cpy ->
 *                u16X2Cpy ->
 *                u16Y2Cpy
 *                enuRoundingCpy -> Rounding method to use
 *
 *   \return     void
 *
 */
/* ******************************************************************************************/
static void vidYInterpolSatS16MinMax(s16 *s16YResultCpy, s16 s16XCpy, s16 s16X1Cpy, s16 s16Y1Cpy, s16 s16X2Cpy,
   s16 s16Y2Cpy,LMATH_tenuRounding enuRoundingCpy );


#endif /* LFIL_PRIV_H_ */
