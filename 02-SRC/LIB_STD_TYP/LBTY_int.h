/******************************************************************************/
/* !Layer           : LIB                                                     */
/*																			  */
/* !Component       : LBTY						      						  */
/* !Description     : Base Types for all standard types.                      */
/*                                                                            */
/* !Module          : LBTY                                                    */
/* !Description     :                                                         */
/*                    %PCMS_HEADER_SUBSTITUTION_START%
   !File            : %PM%
 !ID description  : %PD% %PCMS_HEADER_SUBSTITUTION_END%
 */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : L012N1305 xBD GEN2                                      */
/* !Target          : Renesas RL78/F14                                        */
/*                                                                            */
/* !COPYRIGHT 2013 VALEO LIGHTING SYSTEM.                                     */
/* all rights reserved                                                        */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/* Ahmed Abdelmageed                                                          */
/*                 13/ 3 / 2019   - update the inclusion of Rte_IoHwAb_Type.h */
/*                                to Rte_MFIC_Type.h in case of AUTOSAR_USED  */
/*                                is defined [artf436141]                     */
/*                                - added  Complete state to                  */
/*                                LBTY_tenuWorkingStatus type [artf372174]    */
/******************************************************************************/
/* !Designed by     : Si-Ky HO        @Date : 12/12/2013                      */
/*  									                                      */
/* !Coded by        : Si-Ky HO        @Date : 12/12/2013                      */
/*  									                                      */
/******************************************************************************/
/*  %PCMS_HEADER_SUBSTITUTION_START%
 %PL% %PCMS_HEADER_SUBSTITUTION_END%
 ******************************************************************************/

#ifndef LBTY_INT_H
#define LBTY_INT_H

#ifdef AUTOSAR_USED
#include "Rte_MFIC_Type.h"
#else

/******************************************************************************/
/* !Comment  : Standard Unsigned Byte                                         */
/* !Range    : 0..255                                                         */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_001                                         */
/******************************************************************************/
typedef unsigned char u8;


/******************************************************************************/
/* !Comment  : Standard Unsigned Word                                         */
/* !Range    : 0..65535                                                       */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_002                                         */
/******************************************************************************/
typedef unsigned short int u16;

/******************************************************************************/
/* !Comment  : Standard Unsigned Long Word                                    */
/* !Range    : 0..4294967295                                                  */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_003                                         */
/******************************************************************************/
typedef unsigned long int u32;

/******************************************************************************/
/* !Comment  : Standard Signed Byte                                           */
/* !Range    : -128..127                                                      */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_004                                      */
/******************************************************************************/
typedef signed char s8;

/******************************************************************************/
/* !Comment  : Standard Signed Word                                           */
/* !Range    : -32768..32767                                                  */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_005                                         */
/******************************************************************************/
typedef signed short int s16;

/******************************************************************************/
/* !Comment  : Standard Signed Long Word                                      */
/* !Range    : -2147483648..2147483647                                        */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_006                                         */
/******************************************************************************/
typedef signed long int s32;


typedef struct
{
  u16 u16VendorID;
  u16 u16ModuleID;
  u8  u8SwMajorVersion;
  u8  u8SwMinorVersion;
  u8  u8SwPatchVersion;
}LBTY_tstrVersionInfoType;

/******************************************************************************/
/* !Comment  : Error return type                                              */
/* !Range    : BTY_u8NOK, BTY_u8OK                                            */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_014                                         */
/******************************************************************************/
typedef enum
{
  LBTY_OK = (u16)0,
  LBTY_NOK,
  LBTY_NULL_POINTER,
  LBTY_INDEX_OUT_OF_RANGE,
  LBTY_NO_MASTER_CHANNEL,
  LBTY_READ_ERROR,
  LBTY_WRITE_ERROR,
  LBTY_UNDEFINED_ERROR,
  LBTY_IN_PROGRESS        /* Error is not available, wait for availability */
} LBTY_tenuErrorStatus;


/******************************************************************************/
/* !Comment  : Boolean type                                                   */
/* !Range    : BTY_u8FALSE, BTY_u8TRUE                                        */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_015                                         */
/******************************************************************************/
typedef enum
{
  LBTY_TRUE = 0x55,
  LBTY_FALSE = 0xAA
} LBTY_tenuBoolean;

/******************************************************************************/
/* !Comment  : Current state status                                           */
/* !Range    : BTY_u8INITIALIZED, BTY_u8IDLE, BTY_u8BUSY                      */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_013                                         */
/******************************************************************************/
typedef enum
{
  LBTY_INITIALIZED = 0x00, /* Component is initialized */
  LBTY_IDLE,            /* Component is not performing action */
  LBTY_BUSY,            /* Component is running */
  LBTY_UNINITIALIZED,      /* Component is not initialized properly */
  LBTY_DEFECT,          /* Component is in defect */
  LBTY_FAILSAFE ,           /* Component is in Fail-safe operations */
  LBTY_OFF ,                /* Component in OFF state */
  LBTY_COMPLETE                 /* Component COMPLETE the operation */
} LBTY_tenuWorkingStatus;

#endif


/******************************************************************************/
/********************************* zone type_def ******************************/
/******************************************************************************/


/******************************************************************************/
/* !Comment  : Pointer to Standard Unsigned Byte                              */
/* !Range    : 0..255                                                         */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_007                                         */
/******************************************************************************/
typedef u8* pu8;

/******************************************************************************/
/* !Comment  : Pointer to Standard Unsigned Word                              */
/* !Range    : 0..65535                                                       */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_008                                         */
/******************************************************************************/

typedef u16* pu16;

/******************************************************************************/
/* !Comment  : Pointer to Standard Unsigned Long Word                         */
/* !Range    : 0..4294967295                                                  */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_009                                         */
/******************************************************************************/

typedef u32* pu32;

/******************************************************************************/
/* !Comment  : Pointer to Standard Signed Byte                                */
/* !Range    : -128..127                                                      */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_010                                         */
/******************************************************************************/

typedef s8* ps8;

/******************************************************************************/
/* !Comment  : Pointer to Standard Signed Word                                */
/* !Range    : -32768..32767                                                  */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_011                                         */
/******************************************************************************/

typedef s16* ps16;

/******************************************************************************/
/* !Comment  : Pointer to Standard Signed Long Word                           */
/* !Range    : -2147483648..2147483647                                        */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_012                                         */
/******************************************************************************/

typedef s32* ps32;


/******************************************************************************/
/* !Comment  : Type definition for byte and bit access                        */
/* !Range    : union                                                          */
/* !Unit    : None                                                            */
/*  !Trace_To: Covers_L011N1220_GDD_BTY_494-V01                               */
/******************************************************************************/
typedef union
{
  struct
  {
    u8 u8b0 :1; /* !comment : lsb (least significant bit)*/
    u8 u8b1 :1; /* !comment : BIT 1*/
    u8 u8b2 :1; /* !comment : BIT 2*/
    u8 u8b3 :1; /* !comment : BIT 3*/
    u8 u8b4 :1; /* !comment : BIT 4*/
    u8 u8b5 :1; /* !comment : BIT 5*/
    u8 u8b6 :1; /* !comment : BIT 6*/
    u8 u8b7 :1; /* !comment : msb (most significant bit)*/
  } strBit; /* !comment : for bit  access */
  u8 u8Byte; /* !comment : for byte access */
} LBTY_tuniPort;

/* !Comment  : Type definition for short, byte and bit access                 */
/*  !Trace_To: Covers_L012N0901_GDD_BTY_495-V01                               */
typedef union
{
  struct
  {
    u8 u8b0 :1; /* !comment : lsb (least significant bit)*/
    u8 u8b1 :1; /* !comment : BIT 1*/
    u8 u8b2 :1; /* !comment : BIT 2*/
    u8 u8b3 :1; /* !comment : BIT 3*/
    u8 u8b4 :1; /* !comment : BIT 4*/
    u8 u8b5 :1; /* !comment : BIT 5*/
    u8 u8b6 :1; /* !comment : BIT 6*/
    u8 u8b7 :1; /* !comment : BIT 7*/
    u8 u8b8 :1; /* !comment : BIT 8*/
    u8 u8b9 :1; /* !comment : BIT 9*/
    u8 u8b10 :1; /* !comment : BIT 10*/
    u8 u8b11 :1; /* !comment : BIT 11*/
    u8 u8b12 :1; /* !comment : BIT 12*/
    u8 u8b13 :1; /* !comment : BIT 13*/
    u8 u8b14 :1; /* !comment : BIT 14*/
    u8 u8b15 :1; /* !comment : msb (most significant bit)*/
  } strBit; /* !comment : for bit  access*/
  struct
  {
    u8 u8low; /* !comment : Least significant byte*/
    u8 u8high; /* !comment : Most significant byte*/
  } strByte; /* !comment : for byte access*/
  u16 u16Word; /* !comment : for word access*/
} LBTY_tuniPort16;



/******************************************************************************/
/********************************** zone macro ********************************/
/******************************************************************************/

/******************************************************************************/
/********************************** zone define *******************************/
/******************************************************************************/

/* !Trace_To : Covers_req_swc_bty_017                                         */
#define	LBTY_u8MIN_VALUE	((u8)0)

/* !Trace_To : Covers_req_swc_bty_018                                         */
#define LBTY_u8MAX_VALUE	((u8)255)

/* !Trace_To : Covers_req_swc_bty_019                                         */
#define LBTY_s8MIN_VALUE	((s8)-128)

/* !Trace_To : Covers_req_swc_bty_020                                         */
#define LBTY_s8MAX_VALUE	((s8)127)

/* !Trace_To : Covers_req_swc_bty_021                                         */
#define LBTY_u16MIN_VALUE	((u16)0)

/* !Trace_To : Covers_req_swc_bty_022                                         */
#define LBTY_u16MAX_VALUE	((u16)65535)

/* !Trace_To : Covers_req_swc_bty_023                                         */
#define LBTY_s16MIN_VALUE	((s16)-32768)

/* !Trace_To : Covers_req_swc_bty_024                                         */
#define LBTY_s16MAX_VALUE	((s16)32767)

/* !Trace_To : Covers_req_swc_bty_025                                         */
#define LBTY_u32MIN_VALUE	((u32)0)

/* !Trace_To : Covers_req_swc_bty_026                                         */
#define LBTY_u32MAX_VALUE ((u32)4294967295UL)

/* !Trace_To : Covers_req_swc_bty_027                                         */
#define  LBTY_s32MAX_VALUE ((s32)2147483647)

/* !Trace_To : Covers_req_swc_bty_028                                         */
#define LBTY_s32MIN_VALUE	((s32)-2147483647-1)

/******************************************************************************/
/* !Comment  : Definition of the value of Null pointer                        */
/* !Range    : 0..0                                                           */
/* !Unit     : None                                                           */
/* !Trace_To : Covers_req_swc_bty_016                                         */
/******************************************************************************/
#define LBTY_NULL               ((void*)0)

#endif /* LBTY_INT_H */

/*************************** E N D (LBTY_Int.h) ********************************/

