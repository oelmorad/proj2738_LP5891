/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LMATH_prg.c
 *  Component       LIB_LMATH
 *  \brief          Library of MATHematical functions(LMATH) Driver
 *
 *  \details        Library of MATHematical functions(LMATH) Driver
 *                  Module          : LMATH_prg.c
 *                  Date            : 02 Apr 2014
 *                  Project         : STD
 *                  Target          : STD
 *                  Vendor          : Valeo
 *  \n\n
 *  Scope           : Public
 *  \n\n
 *  Coding language : C
 * \copydoc _prgc
 * \copydoc           COPYRIGHT
 *
 */
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |                   Initial ceration                                                              ||||
 *     | LMATH_prg.c      | V1.0        | Proposed            | \verbatim $Rev::1               $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::08-04-2014     #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Gauthier Lagaisse    $: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |                update covered requirements                                                               ||||
 *     | LMATH_prg.c      | V1.0        | Proposed            | \verbatim $Rev::2               $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::27-08-2018     #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Mohamed gharib    $: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |        Update code after applying MISRA issues remarks                                                               ||||
 *     | LMATH_prg.c      | V1.1        | Proposed            | \verbatim $Rev::             $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::13-01-2019     #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy     $: Author of last commit    \endverbatim |
 */
  /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |               migration to Doxygen                                                              ||||
 *     | LMATH_prg.c      | V1.2        | Proposed            | \verbatim $Rev::1                  $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::14-04-2020     #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Dina Shinaishin      $: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |               Close Review Points                                                              ||||
 *     | LMATH_prg.c      | V1.2        | Released            | \verbatim $Rev::    285            $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::   05-05-2020    #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Soha Wagdy     $: Author of last commit    \endverbatim |
 */
 /** \page _privh LMATH_prg.c History
 *     | File             | Version     | Status              | Description |
 *     | :-------------:  | :---------: | :-----------------: | :----------
 *     |              Initialize local variables                                                               ||||
 *     | LMATH_prg.c      | V1.3        | Released            | \verbatim $Rev::    290           $: Revision of last commit  \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Date::   27/09/2020    #$: Date of last commit     \endverbatim |
 *     | ^                | ^           | ^                   | \verbatim $Author:: Dina Shinaishin    $: Author of last commit    \endverbatim |
 */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "LMATH_int.h"
#include "LMATH_priv.h"

/******************************************************************************/
/******************************************************************************/
/**** AREA: Variables *********************************************************/
/******************************************************************************/
/******************************************************************************/


/******************************************************************************/
/******************************************************************************/
/**** AREA: PUBLIC FUNCTION DEFINITIONS ***************************************/
/******************************************************************************/
/******************************************************************************/


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

 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddSatU8Max(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy)
{
   /**
    *  LMATH Add Sat U8 Max activity diagram
    * @startuml
    * title Add Sat U8 Max activity diagram
    * start */


   /*Comment:Buffer 16 bits for calculation,Range   : [0..65535] */
   u16 u16ResultVarBuffLoc = (u16)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK                                      */
   LBTY_tenuErrorStatus enuErrStatusLoc  = LBTY_OK;

   /**
    *if(Check if the created u8ResultCpy exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {

      /**:Stock the (LeftTerm + RightTerm) calculation on a 16 bits buffer;*/
      u16ResultVarBuffLoc = (u16)u8TermLeftCpy + (u16)u8TermRightCpy;

      /**
       *if(Check if the max value is greater than the result) then (true)
       */
      if( (u16)LBTY_u8MAX_VALUE > u16ResultVarBuffLoc )
      {
         /**: Calculation result did NOT overflow u8MAX value (255)
           Set result variable to calculation result;*/
         *u8ResultCpy = (u8)u16ResultVarBuffLoc;
      }
      /**else (false)*/
      else
      {
         /**:Calculation result overflow u8MAX value (255)
            Set result variable to u8MAX value;*/
         *u8ResultCpy = LBTY_u8MAX_VALUE;
      }
      /**endif*/
   }
   /**else (false) */
   else
   {
      /**:Return LBTY_NULL_POINTER as error Status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;

   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddSatU16Max(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Add Sat U16 Max activity diagram
    * @startuml
    * title LMATH Add Sat U16 Max activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the (max value - left term) greater than right term ) then (true)
       */
      if( (LBTY_u16MAX_VALUE - (u16TermLeftCpy)) > (u16TermRightCpy) )
      {
         /**:Calculation will NOT overflow u16MAX value (65535)
             Set result variable to calculation result;*/
         *u16ResultCpy = (u16)( u16TermLeftCpy + u16TermRightCpy );
      }
      /**else (false)*/
      else
      {
         /**:Calculation will overflow u16MAX value (65535)
             Set result variable to u16MAX value;*/
         *u16ResultCpy = LBTY_u16MAX_VALUE;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Retrun LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error Status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}
/* ***************************************************************************************** */
/**  \brief      addition of two u32 terms
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddSatU32Max(u32 *u32ResultCpy, u32 u32TermLeftCpy, u32 u32TermRightCpy)
{
   /**
    *  LMATH Add Sat U32Max activity diagram
    * @startuml
    * title LMATH Add Sat U32Max activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u32ResultCpy created exists) then (true)
    */
   if(u32ResultCpy != LBTY_NULL)
   {
      /**
       *if(check if (max value - left term) greater than right term) then (true)
       */
      if( (LBTY_u32MAX_VALUE - (u32TermLeftCpy)) > (u32TermRightCpy) )
      {
         /**: Calculation will NOT overflow u32MAX value (4294967295)
             Set result variable to calculation result  ;*/
         *u32ResultCpy = (u32)( u32TermLeftCpy + u32TermRightCpy );
      }
      /**else(false)*/
      else
      {
         /**: Calculation will overflow u32MAX value (4294967295)
             Set result variable to u32MAX value  ;*/
         *u32ResultCpy = LBTY_u32MAX_VALUE;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddSatS32Max(s32 *s32ResultCpy, s32 s32TermLeftCpy, s32 s32TermRightCpy)
{
   /**
    *  LMATH Add Sat S32Max activity diagram
    * @startuml
    * title LMATH Add Sat S32Max  activity diagram
    * start */

   /*Comment:Set Local temp variable to save result */
   s32 s32TempAddLoc = (s32)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s32ResultCpy created exists) then (true)
    */
   if(s32ResultCpy != LBTY_NULL)
   {
      /**:Set the result in TempAdd to be = (  (s32TermLeftCpy/2) + (s32TermRightCpy/2) );*/
      s32TempAddLoc = (s32TermLeftCpy/2) + (s32TermRightCpy/2);
      /**
       *if(Check if the tempAdd is greater than pr equal zero) then (true)
       */
      if (s32TempAddLoc >= 0)
      {
         /**
          *if (Check if the tempAdd less than the (LBTY_s32MAX_VALUE/2)) then (true)
          */
         if (s32TempAddLoc < (LBTY_s32MAX_VALUE/2))
         {
            /**:Set the result to be = (s32TermLeftCpy + s32TermRightCpy);*/
            *s32ResultCpy = s32TermLeftCpy + s32TermRightCpy;
         }
         /**else (false)*/
         else
         {
            /**:set the result to be = max value;*/
            *s32ResultCpy = LBTY_s32MAX_VALUE;
         }
         /**endif*/
      }
      /**else(false)*/
      else
      {
         /**
          *if(Check if the tempadd is greater than (LBTY_s32MIN_VALUE/2) ) then (true)
          */
         if (s32TempAddLoc > (LBTY_s32MIN_VALUE/2))
         {
            /**:Set result to be = (s32TermLeftCpy + s32TermRightCpy);*/
            *s32ResultCpy = s32TermLeftCpy + s32TermRightCpy;
         }
         /**else (false)*/
         else
         {
            /**:Set result to be = min value;*/
            *s32ResultCpy = LBTY_s32MIN_VALUE;
         }
         /**endif*/
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Retrun LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ***************************************************************************************** */
LBTY_tenuErrorStatus LMATH_enuAddU16toS16SatS32Max(s32 *s32ResultCpy, u16 u16TermLeftCpy, s16 s16TermRightCpy)
{
   /**
    *  LMATH Add U16 to S16 Sat S32Max activity diagram
    * @startuml
    * title LMATH Add U16 to S16 Sat S32Max activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK                                      */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the created s32ResultCpy exists) then (true)*/
   if(s32ResultCpy != LBTY_NULL)
   {
      /**:Add Left term and the right term and save them in s32ResultCpy;*/
      *s32ResultCpy = (s32)u16TermLeftCpy + (s32)s16TermRightCpy;
   }
   /**else (false)*/
   else
   {
      /**: Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:return error Status;*/
   return enuErrStatusLoc;

   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuAddS16toS16Sat16Max(s16 *s16ResultCpy, s16 s16TermLeftCpy, s16 s16TermRightCpy)
{
   /**
    *  LMATH Add S16 to S16 Sat 16Max activity diagram
    * @startuml
    * title LMATH Add S16 to S16 Sat 16Max activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuReturnStateLoc = LBTY_OK ;

   /*Comment: two local temp variable */
   s16 s16Temp1Loc = (s16)0;
   s16 s16Temp2Loc = (s16)0 ;
   /**
    *if(Check if the s16ResultCpy created exists) then (true)
    */
   if (s16ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if the left and the right term is greater than or equal 0) then (true)
       */

      if (s16TermLeftCpy >=0 && s16TermRightCpy >= 0)
      {
         /**
          *if(Check if the mas value - left term is greater than right term) then (true)
          */
         if( ( LBTY_s16MAX_VALUE - s16TermLeftCpy ) > s16TermRightCpy )
         {
            /**:Add two s16 and set the result in s16ResultCpy;*/
            *s16ResultCpy = s16TermLeftCpy + s16TermRightCpy ;
         }
         /**else (false)*/
         else
         {
            /**:Set Result by the max value;*/
            *s16ResultCpy = LBTY_s16MAX_VALUE ;
         }
         /**endif*/
      }

      /**
       * elseif( Check if the left and the right term less than 0)  then (vaild) */
      else if ((s16TermLeftCpy < 0 )&& (s16TermRightCpy < 0))
      {
         /**:Set the temp1 variable to be =  left term * -1;*/
         s16Temp1Loc = s16TermLeftCpy *-1 ;
         /**:Set the temp2 variable to be = Right term * -1;*/
         s16Temp2Loc = s16TermRightCpy *-1 ;

         /**
          *if(Check if the (max value - temp1+1) is less than temp2) then (true)
          */
         if ((LBTY_s16MAX_VALUE - s16Temp1Loc + 1 ) > s16Temp2Loc )
         {
            /**:set the result to be = left term + right term;*/
            *s16ResultCpy = s16TermLeftCpy + s16TermRightCpy ;
         }
         /**else (false)*/
         else
         {
            /**:Set the result by the min value;*/
            *s16ResultCpy = LBTY_s16MIN_VALUE ;
         }
         /**endif*/
      }
      /**else (false)*/
      else
      {
         /**:set the result to be = left term + right term;*/
         *s16ResultCpy = s16TermLeftCpy + s16TermRightCpy ;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:return LBTY_NULL_POINTER as error status;*/
      enuReturnStateLoc =  LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error Status;*/
   return enuReturnStateLoc ;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubS16toS16Sat16Max(s16 *s16ResultCpy, s16 s16TermLeftCpy, s16 s16TermRightCpy)
{
   /**
    *  LMATH Sub S16 to S16 Sat 16Max activity diagram
    * @startuml
    * title LMATH Sub S16 to S16 Sat 16Max activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuReturnStateLoc = LBTY_OK ;
   /*Comment: local temp variable */
   s16 s16Temp1Loc = (s16)0 ;

   /**
    *if(Check if the s16ResultCpy created exists) then (true)
    */
   if (s16ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if the left and right right are greater than zero) then (true)
       */
      if ((s16TermLeftCpy >=0 )&&(s16TermRightCpy >= 0 ))
      {
         /**:Set the result o be = left term - right term;*/
         *s16ResultCpy =s16TermLeftCpy - s16TermRightCpy ;
      }
      /**
       *elseif (Check if the left and right term are less than zero) then (true)
       */
      else if ((s16TermLeftCpy < 0 )&&(s16TermRightCpy <  0 ))
      {
         /**:Set the result to be = left term - right term;*/
         *s16ResultCpy =s16TermLeftCpy - s16TermRightCpy ;
      }
      /**else (False) */
      else
      {
         /**
          *if(Check if left term is greater than zero) then (true)
          */
         if (s16TermLeftCpy >= 0)
         {
            /**:Set temp1 = Right term *-1;*/
            s16Temp1Loc = s16TermRightCpy * -1  ;
            /**
             *if(Check if the (max value - left term ) is greater than temp1) then (true)
             */
            if((LBTY_s16MAX_VALUE - s16TermLeftCpy )>s16Temp1Loc)
            {
               /**:Set the result to be = left term - right term;*/
               *s16ResultCpy =s16TermLeftCpy - s16TermRightCpy ;
            }
            /**else (False)*/
            else
            {
               /**:Set the result to be = Max value;*/
               *s16ResultCpy = LBTY_s16MAX_VALUE ;
            }
            /**endif*/
         }
         /**else(false)*/
         else
         {
            /**:set the temp1 to be = (left term * -1);*/
            s16Temp1Loc = s16TermLeftCpy * -1  ;
            /**
             *if(Check if the (max value - temp1 ) is greater than right term ) then (true)
             */
            if((LBTY_s16MAX_VALUE - s16Temp1Loc ) > s16TermRightCpy)
            {
               /**:Set the result to be = left term - right term;*/
               *s16ResultCpy =s16TermLeftCpy - s16TermRightCpy ;
            }
            /**else(False)*/
            else
            {
               /**:Set the reult to be = Min Value;*/
               *s16ResultCpy = LBTY_s16MIN_VALUE ;
            }
            /**endif*/
         }
         /**endif*/
      }
      /**endif*/
   }
   /**else(False)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as a return status;*/
      enuReturnStateLoc = LBTY_NULL_POINTER ;
   }
   /**endif*/
   /**:Return error status;*/
   return enuReturnStateLoc ;
   /** stop */
   /** @enduml*/
}

/* ***************************************************************************************** */
/**  \brief      subtraction of two u8 terms
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubSatU8Min(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy)
{
   /**
    *  LMATH Sub Sat U8Min activity diagram
    * @startuml
    * title LMATH Sub Sat U8Min activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if (Check if the u8ResultCpy created exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if the left term greater than righ term) then (true)
       */
      if( (u8TermLeftCpy) > (u8TermRightCpy) )
      {

         /**:Calculation will NOT underflow u8MIN value (0)
             Set result variable to (LeftTerm - RightTerm) calculation;*/
         *u8ResultCpy = u8TermLeftCpy - u8TermRightCpy;
      }
      /**else (false) */
      else
      {
         /**:Calculation will underflow u8MIN value (0)
              Set result variable to u8MIN value ;*/
         *u8ResultCpy = LBTY_u8MIN_VALUE;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubSatU16Min(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Sub Sat U16Min activity diagram
    * @startuml
    * title LMATH Sub Sat U16Min activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if left term greater than right term) then (true)
       */
      if( (u16TermLeftCpy) > (u16TermRightCpy) )
      {
         /**:Calculation will NOT underflow u16MIN value (0)
             Set result variable to (LeftTerm - RightTerm) calculation;*/
         *u16ResultCpy = (u16)( (u16TermLeftCpy) - (u16TermRightCpy) );
      }
      /**else(false)*/
      else
      {
         /**:Calculation will underflow u16MIN value (0)
             Set result variable to u16MIN value;*/
         *u16ResultCpy = LBTY_u16MIN_VALUE;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;

   /** stop */
   /** @enduml*/

}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubAbsU8(u8 *u8ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy)
{
   /**
    *  LMATH Sub Abs U8 activity diagram
    * @startuml
    * title LMATH Sub Abs U8 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s16ResultCpy created exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {

      /**
       *if(Check if left term is larger than right term) then (true)
       */
      if( (u8TermLeftCpy) > (u8TermRightCpy) )
      {
         /**:Calculation will NOT underflow u8MIN value (0)
             Set result variable to (LeftTerm - RightTerm) calculation;*/
         *u8ResultCpy = u8TermLeftCpy - u8TermRightCpy;
      }
      /**else (False)*/
      else
      {
         /**:Calculation will underflow u8MIN value (0)
             Set result variable to (RightTerm - LeftTerm) calculation;*/
         *u8ResultCpy = u8TermRightCpy - u8TermLeftCpy;
      }
      /**endif*/
   }
   /**else (False)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error Status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuSubAbsU16(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Sub Abs U16 activity diagram
    * @startuml
    * title LMATH Sub Abs U16 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {

      /**
       *if (Check if left term is larger than right term) then (true)
       */
      if( (u16TermLeftCpy) > (u16TermRightCpy) )
      {
         /**: Calculation will NOT underflow u16MIN value (0)
              Set result variable to (LeftTerm - RightTerm) calculation;*/
         *u16ResultCpy = u16TermLeftCpy - u16TermRightCpy;
      }
      /**else (false)*/
      else
      {
         /**:Calculation will underflow u16MIN value (0)
             Set result variable to (RightTerm - LeftTerm) calculation;*/
         *u16ResultCpy = u16TermRightCpy - u16TermLeftCpy;
      }
      /**endif*/
   }
   /**else(False)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;

   /** stop */
   /** @enduml*/
}

/* ***************************************************************************************** */
/**  \brief      Limit an u8 value
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU8ToRangeU8(u8 *u8ResultCpy,u8 u8ValueCpy, u8 u8MinCpy, u8 u8MaxCpy)
{
   /**
    *  LMATH Limit U8 To Range U8 activity diagram
    * @startuml
    * title LMATH Limit U8 To Range U8 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s16ResultCpy created exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the value less than Min ) then (true)
       */
      if( (u8ValueCpy) < (u8MinCpy) )
      {
         /**:Value is out of Minimum range
             Set result variable to Minimum;*/
         *u8ResultCpy = u8MinCpy;
      }
      /**
       *elseif(Check if the value is less Max cpy) then (true)
       */
      else if( (u8ValueCpy) > (u8MaxCpy) )
      {
         /**:Value is out of Maximum range
             Set result variable to Maximum;*/
         *u8ResultCpy = u8MaxCpy;
      }
      /**else(false)*/
      else
      {
         /**:Value is in [Min..Max] range
             Set result variable to value;*/
         *u8ResultCpy = u8ValueCpy;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error Status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU32ToRangeU8(u8 *u8ResultCpy,u32 u32ValueCpy, u8 u8MinCpy, u8 u8MaxCpy)
{
   /**
    *  LMATH Limit U32 To Range U8 activity diagram
    * @startuml
    * title LMATH Limit U32 To Range U8 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(check if the u8ResultCpy created exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the value less than the min value) then (true)
       */
      if( (u32)u32ValueCpy < (u32)u8MinCpy)
      {
         /**: Set result variable to Minimum
              Value is out of Minimum range;*/
         *u8ResultCpy = u8MinCpy;
      }
      /**
       *elseif (Check if the value greater than the max value) then (true)
       */
      else if( (u32)u32ValueCpy > (u32)u8MaxCpy )
      {
         /**:Value is out of Maximum range
             Set result variable to Maximum ;*/
         *u8ResultCpy = u8MaxCpy;
      }
      /**else(false)*/
      else
      {
         /**:Value is in [Min..Max] range
            Set result variable to value;*/
         *u8ResultCpy = (u8)u32ValueCpy;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU16ToRangeU16(u16 *u16ResultCpy, u16 u16ValueCpy, u16 u16MinCpy, u16 u16MaxCpy)
{
   /**
    * LMATH Limit U16 To Range U16 activity diagram
    * @startuml
    * title LMATH Limit U16 To Range U16 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the value is less than the min value ) then (true)
       */
      if( (u16ValueCpy) < (u16MinCpy) )
      {
         /**:Value is out of Minimum range
             Set result variable to Minimum;*/
         *u16ResultCpy = u16MinCpy;
      }
      /**
       *elseif (Check if the value is greater than the max value) then (true)
       */
      else if( (u16ValueCpy) > (u16MaxCpy) )
      {
         /**:Value is out of Maximum range
              Set result variable to Maximum;*/
         *u16ResultCpy = u16MaxCpy;
      }
      /**else (False)*/
      else
      {
         /**:Value is in [Min..Max] range
             Set result variable to value;*/
         *u16ResultCpy = u16ValueCpy;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitU32ToRangeU16(u16 *u16ResultCpy, u32 u32ValueCpy, u16 u16MinCpy, u16 u16MaxCpy)
{
   /**
    *  LMATH Limit U32 To Range U16 activity diagram
    * @startuml
    * title LMATH Limit U32 To Range U16 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the value is less than the min value) then (true)
       */
      if( (u32)u32ValueCpy < (u32)u16MinCpy )
      {
         /**:Value is out of Minimum range
             Set result variable to Minimum;*/
         *u16ResultCpy = u16MinCpy;
      }
      /**
       *elseif(Check if the value is greater than the max value) then (true)
       */
      else if( (u32)u32ValueCpy > (u32)u16MaxCpy )
      {
         /**:Value is out of Maximum range
             Set result variable to Maximum;*/
         *u16ResultCpy = u16MaxCpy;
      }
      /**else (false)*/
      else
      {
         /**:Value is in [Min..Max] range
             Set result variable to value;*/
         *u16ResultCpy = (u16)u32ValueCpy;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return Error status;*/
   return enuErrStatusLoc;

   /**stop*/
   /**@enduml*/
}
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitToRangeS32(s32 *s32ResultCpy, s32 s32ValueCpy, s32 s32MinCpy, s32 u32MaxCpy)
{
   /**
    * LMATH Limit To Range S32 activity diagram
    * @startuml
    * title LMATH Limit To Range S32 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s32ResultCpy created exists) then (true)
    */
   if(s32ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if the value is less than the min value) then (true)
       */
      if( (s32ValueCpy) < (s32MinCpy) )
      {
         /**:Value is out of Minimum range
             Set result variable to Minimum;*/
         *s32ResultCpy = s32MinCpy;
      }
      /**
       *elseif (check if the value is greater than the max value) then (true)
       */
      else if( (s32ValueCpy) > (u32MaxCpy) )
      {
         /**:Value is out of Maximum range
              Set result variable to Maximum;*/
         *s32ResultCpy = u32MaxCpy;
      }
      /**else (false)*/
      else
      { /* !Pseudo: Value is in [Min..Max] range */
         /* !Pseudo: Set result variable to value */
         /**: Value is in [Min..Max] range
              Set result variable to value;*/
         *s32ResultCpy = s32ValueCpy;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error Status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuLimitToRangeS16(s16 *s16ResultCpy, s32 s32ValueCpy, s16 s16MinCpy, s16 s16MaxCpy)
{
   /**
    *  LMATH Limit To Range S16 activity diagram
    * @startuml
    * title LMATH Limit To Range S16 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s16ResultCpy created exists) then (true)
    */
   if(s16ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if the value is less than the min value) then (true)
       */
      if( (s32)s32ValueCpy < (s32)s16MinCpy )
      {
         /**:Value is out of Minimum range
             Set result variable to Minimum;*/
         *s16ResultCpy = s16MinCpy;
      }
      /**
       *elseif (Check if the value is greater than mac value) then (true)
       */
      else if( (s32)s32ValueCpy > (s32)s16MaxCpy )
      {
         /**:Value is out of Maximum range
             Set result variable to Maximum;*/
         *s16ResultCpy = s16MaxCpy;
      }
      /**else (false)*/
      else
      {
         /**:Value is in [Min..Max] range
             Set result variable to value;*/
         *s16ResultCpy = (s16)s32ValueCpy;
      }
      /**endif*/
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml */
}
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuMulU8ByU8ToU16(u16 *u16ResultCpy, u8 u8TermLeftCpy, u8 u8TermRightCpy)
{
   /**
    *  LMATH Mul U8 By U8 To U16 activity diagram
    * @startuml
    * title LMATH Mul U8 By U8 To U16 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created exists) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**:Set result variable to (LeftTerm * RightTerm) calculation;*/
      *u16ResultCpy = (u16)u8TermLeftCpy * (u16)u8TermRightCpy ;
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error Status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}
/* ***************************************************************************************** */
/**  \brief      Calculate the multiplication of two u16 terms
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuMulU16ByU16ToU32(u32 *u32ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Mul U16 By U16 To U32 activity diagram
    * @startuml
    * title Mul U16 By U16 To U32 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;


   /**
    *if(Check if the u32ResultCpy created exists) then (true)
    */
   if(u32ResultCpy != LBTY_NULL)
   {
      /**:Set result variable to (LeftTerm * RightTerm) calculation   ;*/
      *u32ResultCpy = (u32)u16TermLeftCpy * (u32)u16TermRightCpy;
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

/* ***************************************************************************************** */
/**  \brief      Calculate the multiplication of u32 by u16
 *   \details    This service shall do the following actions :
 *                - Calculate the multiplication of u32 by u16
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
 *
 *
 *   \par Coverage:
 *
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuMulU32ByU16ToU32(u32 *u32ResultCpy, u32 u32TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Mul U32 By U16 To U32 activity diagram
    * @startuml
    * title Mul U32 By U16 To U32 activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK  */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;
   /*Comment: set over flow variable = 0 */
   u32 u32OvrflwChck = (u32)0;

   /**
    *if(Check if the u32ResultCpy created exists) then (true)
    */
   if(u32ResultCpy != LBTY_NULL)
   {
      /**
       *if(check if the left term not equal zero) then (true)
       */
      if(u32TermLeftCpy != (u32)0)
      {
         /**:set over flow variable to be = (LBTY_u32MAX_VALUE / u32TermLeftCpy);*/
         u32OvrflwChck = LBTY_u32MAX_VALUE / u32TermLeftCpy;

         /**
          *if(Check if the over flow greater thab or equal right term value) then (true)
          */
         if(u32OvrflwChck >= u16TermRightCpy)
         {
            /**:Set result variable to (LeftTerm * RightTerm) calculation ;*/
            *u32ResultCpy = u32TermLeftCpy * (u32)u16TermRightCpy;
         }
         /**else (false)*/
         else
         {
            /**:Over flow detected set result to max U32 ;*/
            *u32ResultCpy = LBTY_u32MAX_VALUE;
         }
         /**endif*/
      }
      /**else(false)*/
      else
      {
         /**:Set the result to be = zero;*/
         *u32ResultCpy = (u32)0;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU16ByU8SatU8Max(u8* u8ResultCpy, u16 u16NumCpy, u8 u8DenomCpy, LMATH_tenuRounding enuRoundingCpy, u8 u8DefaultValCpy)
{
   /**
    *  LMATH Div U16 By U8 Sat U8Max activity diagram
    * @startuml
    * title LMATH Div U16 By U8 Sat U8Max activity diagram
    * start */

   /*Comment : Buffered Numerator for calculation, Range: [0..65535]  */
   u16 u16NumBuffLoc = (u16)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u8ResultCpy created exists) then (true)
    */
   if(u8ResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if The Denominator is NOT null) then (true)
       */
      if( (u8)0 != u8DenomCpy )
      {
         /**
          *if(check if enuRoundingCpy is true) then (true)
          */
         switch(enuRoundingCpy)
         {
            /**
             *if(check if enuRoundingCpy = LMATH_ROUND_DOWN) then (true)
             */
            case LMATH_ROUND_DOWN:
               /**:Set Buffered Numerator to Numerator value;*/
               u16NumBuffLoc = u16NumCpy;
               break;
               /**
                *elseif(enuRoundingCpy = LMATH_ROUND_NEAREST ) then (true)
                */
            case LMATH_ROUND_NEAREST:

               /**:Requested Rounding method is Round to Nearest
                   [ Numerator + ( Denominator / 2 ) ]  / Denominator
                   Calculate ( Denominator / 2 );*/
               u16NumBuffLoc = (u16)( u8DenomCpy >> (u8)1 );

               /**: Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
               enuErrStatusLoc = LMATH_enuAddSatU16Max( &u16NumBuffLoc, u16NumCpy, u16NumBuffLoc );
               break;

               /**
                *elseif(enuRoundingCpy = LMATH_ROUND_UP) then (true)
                */
            case LMATH_ROUND_UP:
               /**:Requested Rounding method is Round Up
                   [ Numerator + ( Denominator - 1 ) ]  / Denominator
                   Calculate ( Denominator - 1 );*/
               u16NumBuffLoc = (u16)( u8DenomCpy - (u8)1 );

               /**:Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
               enuErrStatusLoc = LMATH_enuAddSatU16Max( &u16NumBuffLoc, u16NumCpy, u16NumBuffLoc );
               break;

               /**else (false)*/
            default:
               /**:Set Buffered Numerator to Numerator value;*/
               u16NumBuffLoc = u16NumCpy;
               break;
               /**endif*/
         }
         /**endif*/

         /**
          *if(Check if NumBuffLoc shifted by 8 is less than Denom) then (true)
          */
         if( (u8)( u16NumBuffLoc >> (u16)8)  < u8DenomCpy )
         {
            /**:Set result variable to (NumeratorBuffer / Denominator) calc;*/
            *u8ResultCpy = (u8)( u16NumBuffLoc / u8DenomCpy );
         }
         /**else(false)*/
         else
         {
            /**:Set result variable to u8MAX value;*/
            *u8ResultCpy = LBTY_u8MAX_VALUE;
         }
         /**endif*/

      }
      /**else (False)*/
      else
      {
         /**:The Denominator is null
             Set result variable to Default value (Denominator Null error);*/
         *u8ResultCpy = u8DefaultValCpy;
         /**:Set error status to be LBTY_NOK;*/
         enuErrStatusLoc = LBTY_NOK;
      }
      /**endif*/
   }
   /**else (False)*/
   else
   {
      /**:Return error status LBTY_NULL_POINTER;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /** stop */
   /** @enduml*/
}
/* ***************************************************************************************** */
/**  \brief      the division of an u16 numerator by an u8 denominat
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU16ByU8SatU16Max(u16* u16ResultCpy, u16 u16NumCpy, u8 u8DenomCpy, LMATH_tenuRounding enuRoundingCpy, u16 u8DefaultValCpy)
{
   /**
    *  LMATH Div U16 By U8 Sa U16 Max activity diagram
    * @startuml
    * title Div U16 By U8 Sa U16 Max activity diagram
    * start */

   /*Comment:Buffered Numerator for calculation */
   u16 u16NumBuffLoc = (u16)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if (Check if the u16ResultCpy created exist) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if The Denominator is NOT null) then (true)
       */
      if( (u8)0 != u8DenomCpy )
      {

         /**
          *if(check if enuRoundingCpy) then (true)
          */
         switch(enuRoundingCpy)
         {
            /**
             *if(Check if enuRoundingCpy = LMATH_ROUND_DOWN ) then (true)
             */
            case LMATH_ROUND_DOWN:

               /**:Set Buffered Numerator to Numerator value;*/
               u16NumBuffLoc = u16NumCpy;
               break;

               /**
                *elseif(Check if enuRoundingCpy = LMATH_ROUND_NEAREST) then (true)
                */
            case LMATH_ROUND_NEAREST:
               /**: Calculate ( Denominator / 2 );*/
               u16NumBuffLoc = (u16)( u8DenomCpy >> (u8)1 );

               /**:Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
               enuErrStatusLoc = LMATH_enuAddSatU16Max( &u16NumBuffLoc, u16NumCpy, u16NumBuffLoc );
               break;
               /**
                *elseif(Check if the enuRoundingCpy = LMATH_ROUND_UP) then (true)
                */
            case LMATH_ROUND_UP:
               /**: Calculate ( Denominator - 1 );*/
               u16NumBuffLoc = (u16)( u8DenomCpy - (u8)1 );

               /**: Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
               enuErrStatusLoc = LMATH_enuAddSatU16Max( &u16NumBuffLoc, u16NumCpy, u16NumBuffLoc );
               break;

               /**else(false)*/
            default:
               /**: Set Buffered Numerator to Numerator value;*/
               u16NumBuffLoc = u16NumCpy;
               break;
               /**endif*/
         }
         /**endif*/

         /**: Set result variable to (NumeratorBuffer / Denominator) calc;*/
         *u16ResultCpy = (u16)( u16NumBuffLoc / (u8DenomCpy) );


      }
      /**else(false)*/
      else
      {
         /**: Set result variable to Default value (Denominator Null error);*/
         *u16ResultCpy = u8DefaultValCpy;
         /**:Retunr LBTY_NOK as error status;*/
         enuErrStatusLoc = LBTY_NOK;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;

   /**stop*/
   /**@enduml*/
}
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
 *   \par Requirement ID: Req_SWC_LMATH_CDD_015-V01
 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU32ByU16SatU16Max(u16* u16ResultCpy, u32 u32NumCpy, u16 u16DenomCpy, LMATH_tenuRounding enuRoundingCpy, u16 u16DefaultValCpy)
{
   /**
    *  LMATH Div U3 2By U16 Sat U16 Max activity diagram
    * @startuml
    * title LMATH Div U3 2By U16 Sat U16 Max activity diagram
    * start */

   /*Comment: Buffered Numerator for calculation */
   u32 u32NumBuffLoc = (u32)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u16ResultCpy created is exits) then (true)
    */
   if(u16ResultCpy != LBTY_NULL)
   {
      /**
       *if ( The Denominator is NOT equal null) then (true)
       */
      if( (u16)0 != u16DenomCpy )
      {
         /**
          *if(Check if enuRoundingCpy) then (true)
          */
         switch(enuRoundingCpy)
         {
            /**
             * if (check if enuRoundingCpy = LMATH_ROUND_DOWN) then (true)
             */
            case LMATH_ROUND_DOWN:
               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;
               /**
                *elseif(Check if enuRoundingCpy = LMATH_ROUND_NEAREST) then (true)
                */
            case LMATH_ROUND_NEAREST:
               /**: Calculate ( Denominator / 2 );*/
               u32NumBuffLoc = (u32)( u16DenomCpy >> (u16)1 );

               /**: Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;
               /**
                *elseif(Check if enuRoundingCpy = LMATH_ROUND_UP) then (true)
                */
            case LMATH_ROUND_UP:
               /**: Calculate ( Denominator - 1 );*/
               u32NumBuffLoc = (u32)u16DenomCpy - (u32)1;

               /**: Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;
               /**else(false)*/
            default:
               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;
               /**endif*/
         }
         /**
          *if(check if Calculation will NOT overflow u16MAX value (255)) then (true)
          */
         if( (u16)(u32NumBuffLoc >> (u32)16) < u16DenomCpy )
         {
            /**: Set result variable to (NumeratorBuffer / Denominator) calculation;*/
            *u16ResultCpy = (u16)( u32NumBuffLoc / (u16DenomCpy) );
         }
         /**else(false)*/
         else
         {
            /**: Set result variable to u16MAX value;*/
            *u16ResultCpy = LBTY_u16MAX_VALUE;
         }
         /**endif*/
      }
      /**else (false)*/
      else
      {
         /**: Set result variable to Default value (Denominator Null error);*/
         *u16ResultCpy = u16DefaultValCpy;
         /**:Return LBTY_NOK as error status;*/
         enuErrStatusLoc = LBTY_NOK;
      }
      /**endif*/
   }
   /**else(False)*/
   else
   {
      /**:Return LBTY_NULL_POINTER;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

/* ***************************************************************************************** */
/**  \brief      Calculate the division of an u32 numerator
 *   \details    This service shall do the following actions :
 *                 - Calculate the division of an u32 numerator
 *                   by an u16 denominator
 *                 - Round off, down or up the result,
 *                   according to requested method
 *                 - Set the result into *u32ResultCpy
 *
 *   \param[in]   *u32ResultCpy   -> pointer to return the result, Range[0..4294967295]
 *                u32NumCpy      -> Numerator , [0..4294967295]
 *                u16DenomCpy     -> , Range[0..65535]
 *                enuRoundingCpy -> Rounding method to use
 *                u32DefaultValCpy -> Default value to return in case of Denominator Null error
 *
 *   \return   LBTY_tenuErrorStatus \n
 *               Returned Value List:
 *                 - LBTY_OK: execution success
 *                 - LBTY_NOK: execution end with error
 *   \par Requirement ID:Req_SWC_LMATH_CDD_029-V01
 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU32ByU16SatU32Max(u32* u32ResultCpy, u32 u32NumCpy, u16 u16DenomCpy, LMATH_tenuRounding enuRoundingCpy, u32 u32DefaultValCpy)
{
   /**
    *  LMATH Div U32 By U16 Sat U32 Max activity diagram
    * @startuml
    * title Div U32 By U16 Sat U32 Max activity diagram
    * start */

   /*Comment: Buffered Numerator for calculation */
   u32 u32NumBuffLoc = (u32)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u32ResultCpy created exists) then (true)
    */
   if(u32ResultCpy != LBTY_NULL)
   {
      /**
       *if(check if the value of Denominator is NOT null ) then (true)
       */
      if( (u16)0 != u16DenomCpy)
      {
         /**
          *if (enuRoundingCpy) then (true)
          */
         switch(enuRoundingCpy)
         {
            /**
             *if (check if the enuRoundingCpy = LMATH_ROUND_DOWN) then (true)
             */
            case LMATH_ROUND_DOWN:

               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;

               /**
                *elseif (Check if the enuRoundingCpy = LMATH_ROUND_NEAREST) then (true)
                */
            case LMATH_ROUND_NEAREST:
               /**: Calculate ( Denominator / 2 );*/
               u32NumBuffLoc = (u32)( u16DenomCpy >> (u16)1 );

               /**:Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;
               /**
                *elseif (Check if the enuRoundingCpy = LMATH_ROUND_UP) then (true)
                */
            case LMATH_ROUND_UP:
               /**: Calculate ( Denominator - 1 );*/
               u32NumBuffLoc = (u32)u16DenomCpy - (u32)1;
               /**: Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;
               /**else (false)*/
            default:
               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;
               /**endif*/

         }
         /**endif*/
         /**: Set result variable to (NumeratorBuffer / Denominator) calculation;*/
         *u32ResultCpy = (u32)( u32NumBuffLoc / (u16DenomCpy) );
      }
      /**else (false)*/
      else
      {
         /**: Set result variable to Default value (Denominator Null error);*/
         *u32ResultCpy = u32DefaultValCpy;
         /**:Return LBTY_NOK as error status;*/
         enuErrStatusLoc = LBTY_NOK;
      }
      /**endif*/

   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;

   /**stop*/
   /**@enduml*/
}
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuDivU32ByU32SatU32Max(u32* u32ResultCpy, u32 u32NumCpy, u32 u32DenomCpy,
   LMATH_tenuRounding enuRoundingCpy, u32 u32DefaultValCpy)
{
   /**
    *  LMATH Div U32 By U32 Sat U32 Max activity diagram
    * @startuml
    * title LMATH Div U32 By U32 Sat U32 Max  activity diagram
    * start */

   /*Comment: Buffered Numerator for calculation */
   u32 u32NumBuffLoc = (u32)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the u32ResultCpy created exist) then (true)
    */
   if(u32ResultCpy != LBTY_NULL)
   {
      /**
       *if(Check if The Denominator is NOT null ) then (true)
       */
      if( (u32)0 != u32DenomCpy )
      {
         /**
          *if (check if enuRoundingCpy) then (ture)
          */
         switch(enuRoundingCpy)
         {
            /**
             *if (check if enuRoundingCpy = LMATH_ROUND_DOWN) then (true)
             */
            case LMATH_ROUND_DOWN:
               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;

               /**
                *elseif(Check if the enuRoundingCpy = LMATH_ROUND_NEAREST) then (true)
                */
            case LMATH_ROUND_NEAREST:
               /**: Calculate ( Denominator / 2 );*/
               u32NumBuffLoc = (u32)( u32DenomCpy >> (u32)1 );

               /**: Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;

               /**
                *elseif(Check if enuRoundingCpy = LMATH_ROUND_UP) then (true)
                */
            case LMATH_ROUND_UP:
               /**: Calculate ( Denominator - 1 );*/
               u32NumBuffLoc = (u32)( u32DenomCpy - (u32)1 );

               /**: Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
               enuErrStatusLoc = LMATH_enuAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
               break;

               /**else (false)*/
            default:
               /**: Set Buffered Numerator to Numerator value;*/
               u32NumBuffLoc = u32NumCpy;
               break;
               /**endif*/
         }
         /**endif*/
         /**: Set result variable to (NumeratorBuffer / Denominator) calculation;*/
         *u32ResultCpy = (u32)( u32NumBuffLoc / (u32DenomCpy) );

      }
      /**else(false)*/
      else
      {
         /**: Set result variable to Default value (Denominator Null error);*/
         *u32ResultCpy = u32DefaultValCpy;
         /**:Return LBTY_NOK as error status;*/
         enuErrStatusLoc = LBTY_NOK;
      }
      /**endif*/
   }
   /**else(false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuParityU8(LMATH_tenuParity *penuResultCpy, u8 u8ValCpy)
{
   /**
    *  LMATH Parity U8 activity diagram
    * @startuml
    * title LMATH Parity U8  activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the penuResultCpy created exists) then (true)
    */
   if(penuResultCpy != LBTY_NULL)
   {
      /**:Set the result with the parity value ;*/
      *penuResultCpy =  (((u8ValCpy) & (u8)0x01) == (u8)0x01) ? LMATH_PARITY_ODD : LMATH_PARITY_EVEN ;
   }
   /**else (False)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Retrun error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}
/* ***************************************************************************************** */
/**  \brief      Get the parity of u16 value
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuParityU16(LMATH_tenuParity *penuResultCpy,u16 u16ValCpy)
{
   /**
    *  LMATH Parity U16 activity diagram
    * @startuml
    * title LMATH Parity U16  activity diagram
    * start */

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the penuResultCpy created exists) then (true)
    */
   if(penuResultCpy != LBTY_NULL)
   {
      /**:Set the result with the parity value ;*/
      *penuResultCpy = (((u16ValCpy) & (u16)0x0001) == (u16)0x0001) ? LMATH_PARITY_ODD : LMATH_PARITY_EVEN ;
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/

   /**:Retrun error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/

}

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
s32 LMATH_s32GetAbs(s32 s32valCpy)
{
   /**
    *  LMATH s32 Get Abs activity diagram
    * @startuml
    * title LMATH s32 Get Abs activity diagram
    * start */

   /*Comment:Local variable to save Abx value */
   s32 s32AbsValLoc = (s32)0;
   /**
    *if (Check if the value greater than or equal Zero) then (true)
    */
   if(s32valCpy >= 0)
   {
      /**:Set the positive result of value in Abs value;*/
      s32AbsValLoc = s32valCpy;
   }
   /**else (false)*/
   else
   {
      /**:Set the negative result of value in Abs value;*/
      s32AbsValLoc = - s32valCpy;
   }
   /**endif*/

   /**:Return error status;*/
   return s32AbsValLoc;

   /** stop */
   /** @enduml*/
}
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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuYInterpolSatU16MinMax(u16 *u16YResultCpy, u16 u16XCpy, u16 u16X1Cpy, u16 u16Y1Cpy,
   u16 u16X2Cpy, u16 u16Y2Cpy,LMATH_tenuRounding enuRoundingCpy )
{
   /**
    *  LMATH Y Interpol Sat U16 Min Max activity diagram
    * @startuml
    * title LMATH  Y Interpol Sat U16 Min Max activity diagram
    * start */

   /*Comment: Y slope absolute difference value: ABS(y2 - y1)               */
   u16 u16AbsDiffSlopeYLoc = (u16)0;

   /*Comment: X slope absolute difference value: ABS(x2 - x1)               */
   u16 u16AbsDiffSlopeXLoc = (u16)0;

   /*Comment: X absolute difference value: ABS(X - x1)                      */
   u16 u16AbsDiffXLoc = (u16)0;

   /*Comment: Counter of negatives (for absolute differences)               */
   u8  u8CountNegDiffLoc = (u8)0;

   /*Comment: Calculation u16 buffered value                                */
   u16 u16CalcBuffLoc = (u16)0;

   /*Comment: Calculation u32 buffered value                                */
   u32 u32CalcBuffLoc = (u32)0;

   /*Comment: variable to set parity                                        */
   LMATH_tenuParity parityLoc = LMATH_PARITY_EVEN;


   /*Comment: return status                                                 */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /*Comment:  Initially, there is no negatives                             */
   u8CountNegDiffLoc = (u8)0;

   /**
    *if (Check if the u16YResultCpy created exist) then (true)
    */
   if(u16YResultCpy != LBTY_NULL)
   {
      /**
       *if (Check if the value of y2 is greater than the value of y1) then (true)
       */
      if( u16Y2Cpy > u16Y1Cpy )
      {
         /**:Set Y slope absolute difference value to (y2 - y1);*/
         u16AbsDiffSlopeYLoc = (u16)( (u16Y2Cpy) - (u16Y1Cpy) );
      }
      /**else(false)*/
      else
      {
         /**:Set Y slope absolute difference value to (y1 - y2);*/
         u16AbsDiffSlopeYLoc = (u16)( (u16Y1Cpy) - (u16Y2Cpy) );
         /**: There is one (more) negative value;*/
         u8CountNegDiffLoc++;
      }
      /**endif*/

      /**
       *if (check if the value of x2 is greater than the value of x1) then (true)
       */
      if( (u16X2Cpy) > (u16X1Cpy) )
      {
         /**:Set X slope absolute difference value to (x2 - x1) ;*/
         u16AbsDiffSlopeXLoc = (u16)( (u16X2Cpy) - (u16X1Cpy) );
      }
      /**else (false)*/
      else
      {
         /**:Set X slope absolute difference value to (x1 - x2);*/
         u16AbsDiffSlopeXLoc = (u16)( (u16X1Cpy) - (u16X2Cpy) );
         /**: There is one (more) negative value;*/
         u8CountNegDiffLoc++;
      }
      /**endif*/

      /**
       *if (Check if the value of X is greater than the value of X1) then (true)
       */
      if( (u16XCpy) > (u16X1Cpy) )
      {
         /**:Set X absolute difference value to (X - x1) ;*/
         u16AbsDiffXLoc = (u16)( (u16XCpy) - (u16X1Cpy) );
      }
      /**else (false)*/
      else
      {
         /**:Set X absolute difference value to (x1 - X);*/
         u16AbsDiffXLoc = (u16)( (u16X1Cpy) - (u16XCpy) );
         /**:There is one (more) negative value;*/
         u8CountNegDiffLoc++;
      }
      /**endif*/

      /**: Buff  = Abs(y2 - y1) * Abs(X - x1) = AbsDiffSlopeY * AbsDiffX;*/
      vidMulU16ByU16ToU32(
         &u32CalcBuffLoc,
         u16AbsDiffSlopeYLoc,
         u16AbsDiffXLoc
      );

      /**:Buff=(AbsDiffSlopeY * AbsDiffX)/AbsDiffSlopeX  ;*/
      vidDivU32ByU16SatU16Max(
         &u16CalcBuffLoc,
         u32CalcBuffLoc,
         u16AbsDiffSlopeXLoc,
         enuRoundingCpy,
         (u16)0
      );

      /**:Return error status of the parity ;*/
      enuErrStatusLoc = LMATH_enuParityU8(&parityLoc, u8CountNegDiffLoc);
      /**
       *if (Check if the parity = even parity) then (true)
       */
      if( parityLoc == LMATH_PARITY_EVEN )
      {
         /**: Set Y Result variable to (y1 + Buff) calculation
              (Buff should be a positive value);*/
         enuErrStatusLoc = LMATH_enuAddSatU16Max(
            u16YResultCpy,
            u16Y1Cpy,
            u16CalcBuffLoc
         );
      }
      /**else (false)*/
      else
      {
         /**: Set Y Result variable to (y1 - Buff) calculation
             (Buff should be a negative value);*/
         vidSubSatU16Min(
            u16YResultCpy,
            u16Y1Cpy,
            u16CalcBuffLoc
         );
      }
      /**endif*/

   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuYInterpolSatS16MinMax(s16 *s16YResultCpy, s16 s16XCpy, s16 s16X1Cpy, s16 s16Y1Cpy,
   s16 s16X2Cpy, s16 s16Y2Cpy,LMATH_tenuRounding enuRoundingCpy )
{
   /**
    *  LMATH Y Inter pol Sat S16 Min Max activity diagram
    * @startuml
    * title Y Interpol Sat S16 Min Max activity diagram
    * start */

   /*Comment: X coordinate used to deduce Y ones                            */
   u16 u16XLoc = (u16)0;

   /*Comment: 1st point of interpolation / X coordinate (x1)                */
   u16 u16X1Loc = (u16)0;

   /*Comment: 1st point of interpolation / Y coordinate (y1)                */
   u16 u16Y1Loc = (u16)0;

   /*Comment: 2nd point of interpolation / X coordinate (x2)                */
   u16 u16X2Loc = (u16)0;

   /*Comment: 2nd point of interpolation / Y coordinate (y2)                */
   u16 u16Y2Loc = (u16)0;

   /*Comment : Y Result variable                                             */
   u16 u16YLoc = (u16)0;

   /*Comment: Initialize the LMATH return status = LBTY_OK    */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_OK;

   /**
    *if(Check if the s16YResultCpy created exists) then (true)
    */
   if(s16YResultCpy != LBTY_NULL)
   {
      /**: Translate all input coordinates ( {x1;y1} , {x2;y2}, X );*/
      u16XLoc  = (u16)( (s16XCpy)  - LBTY_s16MIN_VALUE );
      u16X1Loc = (u16)( (s16)s16X1Cpy - LBTY_s16MIN_VALUE );
      u16Y1Loc = (u16)( (s16)s16Y1Cpy - LBTY_s16MIN_VALUE );
      u16X2Loc = (u16)( (s16)s16X2Cpy - LBTY_s16MIN_VALUE );
      u16Y2Loc = (u16)( (s16)s16Y2Cpy - LBTY_s16MIN_VALUE );
      /**: Calculate the interpolation value (Y coordinate)
          in an u16 orthonormal system;*/
      vidYInterpolSatU16MinMax(
         &u16YLoc,
         u16XLoc,
         u16X1Loc,
         u16Y1Loc,
         u16X2Loc,
         u16Y2Loc,
         enuRoundingCpy
      );

      /**: Set Y Result variable to translation of Y deduced coordinate
           from an u16 to an s16 orthonormal system;*/
      *s16YResultCpy = (s16)( (s16)u16YLoc + LBTY_s16MIN_VALUE );
   }
   /**else (false)*/
   else
   {
      /**:Return LBTY_NULL_POINTER as error status;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /**endif*/
   /**:Return error status;*/
   return enuErrStatusLoc;
   /**stop*/
   /**@enduml*/
}

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
 *                enuRoundingCpy                ->Rounding method to use
 *
 *   \return   u16YResultLoc ->Y Result variable ==> Y interpolated coordinate,Range:[0..65535]
 *   \par Requirement ID:Req_SWC_LMATH_CDD_021-V01
 *
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
u16 LMATH_u16InterpolLinearSearch(
   u16 u16XCpy,
   const LMATH_tstrU16Coord2D kastrTabU16Coord2DCpy[],
   u8  u8TabSizeCpy,
   LMATH_tenuRounding enuRoundingCpy
)
{
   /**
    *  LMATH Interpol Linear Search activity diagram
    * @startuml
    * title LMATH Interpol Linear Search   activity diagram
    * start */

   /*Comment: variable to set the result     */
   u16 u16YResultLoc = (u16)0;

   /*Comment: 1st point of interpolation / X coordinate (x1)     */
   u16 u16X1Loc = (u16)0;

   /*Comment: 1st point of interpolation / Y coordinate (y1)     */
   u16 u16Y1Loc = (u16)0;

   /*Comment: 2nd point of interpolation / X coordinate (x2)       */
   u16 u16X2Loc = (u16)0;

   /*Comment: 2nd point of interpolation / Y coordinate (y2)         */
   u16 u16Y2Loc = (u16)0;

   /*Comment: Index used to scan Table of coordinates        */
   u8  u8IndexLoc = (u8)0;

   /*Comment:  Flag which indicates that both points for interpolation found      */
   LBTY_tenuBoolean enuPointsFoundLoc;

   /**:Set the buffer for 1st point of interpolation({x1Buff;y1Buff});*/
   /**:to the 1st point within coordinates table;*/
   u16X1Loc = kastrTabU16Coord2DCpy[0].u16X;
   u16Y1Loc = kastrTabU16Coord2DCpy[0].u16Y;

   /**: Set the buffer for 2nd point of interpolation({x2Buff;y2Buff})
        to the 1st point within coordinates table;*/
   u16X2Loc = kastrTabU16Coord2DCpy[0].u16X;
   u16Y2Loc = kastrTabU16Coord2DCpy[0].u16Y;

   /**: At the beginning, both points for interpolation not found;*/
   enuPointsFoundLoc = LBTY_FALSE;

   /**: Loop over all the TabSize;*/
   /** repeat */
   for(
      u8IndexLoc = (u8)1 ;
      (u8IndexLoc < u8TabSizeCpy) && (enuPointsFoundLoc != LBTY_TRUE) ;
      u8IndexLoc++
   )
   {  /**: Scan all points within coordinates table
            (While Points to use for interpolation NOT founds);*/

      /**: Set the buffer for 1st point of interpolation ({x1Buff;y1Buff})
            to the buffer for 2nd point of interpolation ({x2Buff;y2Buff});*/
      u16X1Loc = u16X2Loc;
      u16Y1Loc = u16Y2Loc;

      /**: Set the buffer for 2nd point of interpolation ({x2Buff;y2Buff})
            to the current point within coordinates table;*/
      u16X2Loc = kastrTabU16Coord2DCpy[u8IndexLoc].u16X;
      u16Y2Loc = kastrTabU16Coord2DCpy[u8IndexLoc].u16Y;

      /**
       *if(check if the x value is greater than the x2 value) then (true)
       */
      if( u16XCpy > u16X2Loc )
      {
         /**:Do Nothing;*/
      }
      /**else (false)*/
      else
      {
         /**: set points found as LBTY_TRUE;*/
         enuPointsFoundLoc = LBTY_TRUE;
      }
      /**endif*/
      /** repeat while (index < tabsize?) is (yes)
       * ->no;
       */

   }


   /**: Set the result to interpolation value using buffered points;*/
   vidYInterpolSatU16MinMax(
      &u16YResultLoc,
      u16XCpy,
      u16X1Loc,
      u16Y1Loc,
      u16X2Loc,
      u16Y2Loc,
      enuRoundingCpy
   );
   /**: Return the result of interpolation;*/
   return u16YResultLoc;

   /**stop*/
   /**@enduml*/

}

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
 *   \par Coverage:
 *
 *
 */
/* ******************************************************************************************/
s16 LMATH_s16InterpolLinearSearch(
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
)
{
   /**
    *  LMATH s16 Interpol Linear Search activity diagram
    * @startuml
    * title LMATH s16 Interpol Linear Search  activity diagram
    * start */


   /*Comment: variable to set the result     */
   s16 s16YResultLoc = (s16)0;

   /*Comment: 1st point of interpolation / X coordinate (x1)      */
   s16 s16X1Loc = (s16)0;

   /*Comment: 1st point of interpolation / Y coordinate (y1)      */
   s16 s16Y1Loc = (s16)0;

   /*Comment: 2nd point of interpolation / X coordinate (x2)     */
   s16 s16X2Loc = (s16)0;

   /*Comment: 2nd point of interpolation / Y coordinate (y2)      */
   s16 s16Y2Loc = (s16)0;

   /*Comment: Index used to scan Table of coordinates       */
   u8  u8IndexLoc = (u8)0;

   /*Comment : Flag which indicates that both points for interpolation found */
   LBTY_tenuBoolean enuPointsFoundLoc;


   /**: Set the buffer for 1st point of interpolation ({x1Buff;y1Buff})
        to the 1st point within coordinates table;*/
   s16X1Loc = kastrTabS16Coord2DCpy[0].s16X;
   s16Y1Loc = kastrTabS16Coord2DCpy[0].s16Y;

   /**: Set the buffer for 2nd point of interpolation({x2Buff;y2Buff})
        to the 1st point within coordinates table;*/
   s16X2Loc = kastrTabS16Coord2DCpy[0].s16X;
   s16Y2Loc = kastrTabS16Coord2DCpy[0].s16Y;

   /**: At the beginning, both points for interpolation not found;*/
   enuPointsFoundLoc = LBTY_FALSE;

   /**: Loop over all the Table Size;*/
   /** repeat */
   for(
      u8IndexLoc = (u8)1 ;
      (u8IndexLoc < u8TabSizeCpy) && (enuPointsFoundLoc != LBTY_TRUE) ;
      u8IndexLoc++
   )
   {
      /**: Scan all points within coordinates table
               (While Points to use for interpolation NOT founds);*/

      /**: Set the buffer for 1st point of interpolation ({x1Buff;y1Buff})
               to the buffer for 2nd point of interpolation ({x2Buff;y2Buff});*/
      s16X1Loc = s16X2Loc;
      s16Y1Loc = s16Y2Loc;

      /**: Set the buffer for 2nd point of interpolation ({x2Buff;y2Buff})
          to the current point within coordinates table;*/
      s16X2Loc = kastrTabS16Coord2DCpy[u8IndexLoc].s16X;
      s16Y2Loc = kastrTabS16Coord2DCpy[u8IndexLoc].s16Y;

      /**
       *if (check if the value of x is greater than then value of X2) then (true)
       */
      if( s16XCpy > s16X2Loc )
      {
         /**:Do Nothing;*/
      }
      /**else (false)*/
      else
      {
        /**: set points found as LBTY_TRUE;*/
         enuPointsFoundLoc = LBTY_TRUE;
      }
      /**endif*/
      /** repeat while (index < table size?) is (yes)
       * ->no;
       */

   }


   /**: Set the result to interpolation value using buffered points;*/
   vidYInterpolSatS16MinMax(
      &s16YResultLoc,
      s16XCpy,
      s16X1Loc,
      s16Y1Loc,
      s16X2Loc,
      s16Y2Loc,
      enuRoundingCpy
   );



   /**: Return the result of interpolation;*/
   return s16YResultLoc;
   /**stop*/
   /**@enduml*/
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/******************************* AREA: PRIVATE FUNCTION DEFINITIONS **************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/


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
static void vidAddSatU32Max(u32 *u32ResultCpy, u32 u32TermLeftCpy, u32 u32TermRightCpy)
{
   /**
    *  LMATH Add Sat U32 Max activity diagram
    * @startuml
    * title LMATH Add Sat U32 Max  activity diagram
    * start */

   /**: Set result variable to be = (Left term + Right term);*/
   *u32ResultCpy = (u32)( (u32)u32TermLeftCpy + (u32)u32TermRightCpy );

   return ;

   /**stop*/
   /**@enduml*/
}

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
 *     \par Requirement ID:Req_SWC_LMATH_CDD_031-V01
 *    \par Coverage:
 */
/* ******************************************************************************************/
static void vidSubSatU16Min(u16 *u16ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Sub Sat U16 Min activity diagram
    * @startuml
    * title LMATH Sub Sat U16 Min activity diagram
    * start */
   /**
    *if (Check if the left term is greater than right term) then (true)
    */
   if( (u16TermLeftCpy) > (u16TermRightCpy) )
   {

      /**: Set result variable to (LeftTerm - RightTerm) calculation;*/
      *u16ResultCpy = (u16)( (u16TermLeftCpy) - (u16TermRightCpy) );
   }
   /**else (false)*/
   else
   {
      /**: Set result variable to u16MIN value; */
      *u16ResultCpy = LBTY_u16MIN_VALUE;
   }
   /**endif*/

   return ;
   /**stop*/
   /**@enduml*/

}

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
static void vidMulU16ByU16ToU32(u32 *u32ResultCpy, u16 u16TermLeftCpy, u16 u16TermRightCpy)
{
   /**
    *  LMATH Mul U16 By U16 To U32 activity diagram
    * @startuml
    * title LMATH Mul U16 By U16 To U32activity diagram
    * start */

   /**: Set result variable to (LeftTerm * RightTerm) calculation;*/
   *u32ResultCpy = (u32)u16TermLeftCpy * (u32)u16TermRightCpy;

   return;
   /**stop*/
   /**@enduml*/
}

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
static void vidDivU32ByU16SatU16Max(u16* u16ResultCpy, u32 u32NumCpy, u16 u16DenomCpy, LMATH_tenuRounding enuRoundingCpy, u16 u16DenomNullDefaultValCpy)
{
   /**
    *  LMATH Div U32 By U16 Sat U16 Max activity diagram
    * @startuml
    * title LMATH Div U32 By U16 Sat U16 Max activity diagram
    * start */

   /*Comment: Buffered Numerator for calculation */
   u32 u32NumBuffLoc = (u32)0;

   /**
    *if(Check if The Denominator is NOT equal null) then (true)
    */
   if( (u16)0 != u16DenomCpy )
   {
      /**
       * if(Check if enuRoundingCpy) then (true)
       */
      switch(enuRoundingCpy)
      {
         /**
          *if (Check if the enuRoundingCpy = LMATH_ROUND_DOWN) then (true)
          */
         case LMATH_ROUND_DOWN:
            /**: Set Buffered Numerator to Numerator value;*/
            u32NumBuffLoc = u32NumCpy;
            break;
            /**
             *elseif(Check if the enuRoundingCpy = LMATH_ROUND_NEAREST) then (true)
             */
         case LMATH_ROUND_NEAREST:
            /**: Calculate ( Denominator / 2 );*/
            u32NumBuffLoc = (u32)( u16DenomCpy >> (u16)1 );

            /**: Set Buffered Numerator to Numerator + ( Denominator / 2 );*/
            vidAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
            break;
            /**
             *elseif(Check if the enuRoundingCpy = LMATH_ROUND_UP) then (true)
             */
         case LMATH_ROUND_UP:
            /**: Calculate ( Denominator - 1 );*/
            u32NumBuffLoc = (u32)u16DenomCpy - (u32)1;

            /**: Set Buffered Numerator to Numerator + ( Denominator - 1 );*/
            vidAddSatU32Max( &u32NumBuffLoc, u32NumCpy, u32NumBuffLoc );
            break;
            /**else(false)*/
         default:
            /**: Set Buffered Numerator to Numerator value;*/
            u32NumBuffLoc = u32NumCpy;
            break;
            /**endif*/
      }
      /**endif*/
      /**
       *if(check if the number in the buffer shifted by 16 is greater than Denominator) then (true)
       */
      if( (u16)(u32NumBuffLoc >> (u32)16) < u16DenomCpy )
      {
         /**: Set result variable to (NumeratorBuffer / Denominator) calculation;*/
         *u16ResultCpy = (u16)( u32NumBuffLoc / u16DenomCpy );
      }
      /**else(false)*/
      else
      {
         /**: Set result variable to u16MAX value;*/
         *u16ResultCpy = LBTY_u16MAX_VALUE;
      }
      /**endif*/

   }
   /**else(false)*/
   else
   {
      /**: Set result variable to Default value (Denominator Null error);*/
      *u16ResultCpy = u16DenomNullDefaultValCpy ;
   }
   /**endif*/
   return;
   /**stop*/
   /**@enduml*/
}
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
static void vidYInterpolSatU16MinMax(u16 *u16YResultCpy, u16 u16XCpy, u16 u16X1Cpy, u16 u16Y1Cpy, u16 u16X2Cpy, u16 u16Y2Cpy,LMATH_tenuRounding enuRoundingCpy )
{
   /**
    *  LMATH Y Inter pol Sat U16 Min Max activity diagram
    * @startuml
    * title LMATH Y Inter pol Sat U16 Min Max activity diagram
    * start */

   /* Comment : Y slope absolute difference value: ABS(y2 - y1)               */
   u16 u16AbsDiffSlopeYLoc = (u16)0;

   /* Comment : X slope absolute difference value: ABS(x2 - x1)               */
   u16 u16AbsDiffSlopeXLoc = (u16)0;

   /*Comment : X absolute difference value: ABS(X - x1)                      */
   u16 u16AbsDiffXLoc = (u16)0;

   /*Comment : Counter of negatives (for absolute differences)               */
   u8  u8CountNegDiffLoc = (u8)0;

   /*Comment : Calculation u16 buffered value                                */
   u16 u16CalcBuffLoc = (u16)0;

   /*Comment : Calculation u32 buffered value                                */
   u32 u32CalcBuffLoc = (u32)0;

   /*Comment : variable to set parity                                        */
   LMATH_tenuParity parityLoc =LMATH_PARITY_EVEN  ;

   /*Comment:  Initially, there is no negatives                               */
   u8CountNegDiffLoc = (u8)0;




   /**
    *if(Check if the value of Y2 is greater than the value of Y1) then (true)
    */
   if( (u16Y2Cpy) > (u16Y1Cpy) )
   {
      /**: Set Y slope absolute difference value to (y2 - y1);*/
      u16AbsDiffSlopeYLoc = (u16)( (u16Y2Cpy) - (u16Y1Cpy) );
   }
   /**else(false)*/
   else
   {
      /**: Set Y slope absolute difference value to (y1 - y2);*/
      u16AbsDiffSlopeYLoc = (u16)( (u16Y1Cpy) - (u16Y2Cpy) );
      /**: There is one (more) negative value;*/
      u8CountNegDiffLoc++;
   }
   /**endif*/

   /**
    *if(Check if the value of X2 is greater than X1) then (true)
    */
   if( (u16X2Cpy) > (u16X1Cpy) )
   {
      /**: Set X slope absolute difference value to (x2 - x1);*/
      u16AbsDiffSlopeXLoc = (u16)( (u16X2Cpy) - (u16X1Cpy) );
   }
   /**else(false)*/
   else
   {
      /**: Set X slope absolute difference value to (x1 - x2);*/
      u16AbsDiffSlopeXLoc = (u16)( (u16X1Cpy) - (u16X2Cpy) );
      /**: There is one (more) negative value;*/
      u8CountNegDiffLoc++;
   }
   /**endif*/

   /**
    *if(Check if the value of X is greater than value of X1 ) then (true)
    */
   if( (u16XCpy) > (u16X1Cpy) )
   {
      /**: Set X absolute difference value to (X - x1);*/
      u16AbsDiffXLoc = (u16)( (u16XCpy) - (u16X1Cpy) );
   }
   /**else(false)*/
   else
   {
      /**: Set X absolute difference value to (x1 - X);*/
      u16AbsDiffXLoc = (u16)( (u16X1Cpy) - (u16XCpy) );
      /**: There is one (more) negative value;*/
      u8CountNegDiffLoc++;
   }
   /**endif*/

   /**: Buff  = Abs(y2 - y1) * Abs(X - x1) = AbsDiffSlopeY * AbsDiffX;*/
   vidMulU16ByU16ToU32( &u32CalcBuffLoc,
      u16AbsDiffSlopeYLoc,
      u16AbsDiffXLoc
   );

   /**: Buff  = (AbsDiffSlopeY * AbsDiffX)/ AbsDiffSlopeX;*/
   vidDivU32ByU16SatU16Max(
      &u16CalcBuffLoc,
      u32CalcBuffLoc,
      u16AbsDiffSlopeXLoc,
      enuRoundingCpy,
      (u16)0
   );

   /**:Get the parity value;*/
   (void) LMATH_enuParityU8(&parityLoc, u8CountNegDiffLoc);
   /**
    *if(Check if the parity is even) then (true)
    */
   if( parityLoc == LMATH_PARITY_EVEN )
   {
      /**: Set Y Result variable to (y1 + Buff) calculation
           (Buff should be a positive value);*/
      (void)  LMATH_enuAddSatU16Max(
         u16YResultCpy,
         u16Y1Cpy,
         u16CalcBuffLoc
      );
   }
   /**else(false)*/
   else
   {
      /**: Set Y Result variable to (y1 - Buff) calculation
            (Buff should be a negative value);*/
      vidSubSatU16Min(
         u16YResultCpy,
         u16Y1Cpy,
         u16CalcBuffLoc
      );
   }
   /**endif*/
   return;
   /**stop*/
   /**@enduml*/
}
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
static void vidYInterpolSatS16MinMax(s16 *s16YResultCpy, s16 s16XCpy, s16 s16X1Cpy, s16 s16Y1Cpy, s16 s16X2Cpy, s16 s16Y2Cpy,LMATH_tenuRounding enuRoundingCpy )
{
   /**
    *  LMATH Y Interpol Sat S16 Min Max activity diagram
    * @startuml
    * title LMATH Y Interpol Sat S16 Min Max activity diagram
    * start */

   /*Comment : X coordinate used to deduce Y ones                            */
   u16 u16XLoc = (u16)0;

   /*Comment : 1st point of interpolation / X coordinate (x1)                */
   u16 u16X1Loc = (u16)0;

   /*Comment : 1st point of interpolation / Y coordinate (y1)                */
   u16 u16Y1Loc = (u16)0;

   /*Comment : 2nd point of interpolation / X coordinate (x2)                */
   u16 u16X2Loc = (u16)0;

   /*Comment : 2nd point of interpolation / Y coordinate (y2)                */
   u16 u16Y2Loc = (u16)0;

   /*Comment : Y Result variable                                             */
   u16 u16YLoc = (u16)0;


   /**: Translate all input coordinates ( {x1;y1} , {x2;y2}, X );*/
   u16XLoc  = (u16)( (s16XCpy)  - LBTY_s16MIN_VALUE );
   u16X1Loc = (u16)( (s16X1Cpy) - LBTY_s16MIN_VALUE );
   u16Y1Loc = (u16)( (s16Y1Cpy) - LBTY_s16MIN_VALUE );
   u16X2Loc = (u16)( (s16X2Cpy) - LBTY_s16MIN_VALUE );
   u16Y2Loc = (u16)( (s16Y2Cpy) - LBTY_s16MIN_VALUE );

   /**: Calculate the interpolation value (Y coordinate);*/
   vidYInterpolSatU16MinMax(
      &u16YLoc,
      u16XLoc,
      u16X1Loc,
      u16Y1Loc,
      u16X2Loc,
      u16Y2Loc,
      enuRoundingCpy
   );

   /**: Set Y Result variable to translation of Y deduced coordinate;*/
   *s16YResultCpy = (s16)( (s16)u16YLoc + LBTY_s16MIN_VALUE );

   return ;
   /**stop*/
   /**@enduml*/
}

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
 *   \par Coverage:
 *
 *
 */
/*******************************************************************************************/
LBTY_tenuErrorStatus LMATH_enuGetVersionInfo(LBTY_tstrVersionInfoType *pVersionInfo)
{

   /*Comment: Buffer contains the software module version                             */
   LBTY_tstrVersionInfoType LOC_strVersion = {(u16)0x59, (u16)0x22, (u8)0x01,(u8)0x03, (u8)0x00};

   /*Comment: Initialize return error status to NOK */
   LBTY_tenuErrorStatus enuErrStatusLoc = LBTY_NOK;

   /**
    *   Get Version Info activity diagram
    * @startuml
    * title Get Version Info activity diagram
    * start
    * if(Check if the passed pointer is NULL) then (valid) */
   if(LBTY_NULL != pVersionInfo)
   {
      /**: copy the version info;*/
      /* Comment: Set return variable Vendor ID with current module version                                    */
      pVersionInfo->u16VendorID      = LOC_strVersion.u16VendorID;
      /**: copy the Module info;*/
      /* Comment: Set return variable Module ID with current module version                                    */
      pVersionInfo->u16ModuleID      = LOC_strVersion.u16ModuleID;
      /**: copy the Major info;*/
      /* Comment: Set return SW Major version with current module version                                      */
      pVersionInfo->u8SwMajorVersion = LOC_strVersion.u8SwMajorVersion;
      /**: copy the Minor info;*/
      /* Comment: Set return SW minor version with current module version                                      */
      pVersionInfo->u8SwMinorVersion = LOC_strVersion.u8SwMinorVersion;
      /**: copy the Patch info;*/
      /* Comment: Set return SW patch version with current module version                                      */
      pVersionInfo->u8SwPatchVersion = LOC_strVersion.u8SwPatchVersion;

      /**: Set return status to LBTY_OK;*/
      enuErrStatusLoc = LBTY_OK;
   }
   /**else(false)*/
   else
   {
      /**: Set return status to null pointer error;*/
      enuErrStatusLoc = LBTY_NULL_POINTER;
   }
   /** endif */
   /**: Return operation status value;*/
   return(enuErrStatusLoc);

   /** stop*/
   /** @enduml*/
}



/**** E N D (LMATH_int.h) *****************************************************/

