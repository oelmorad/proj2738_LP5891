/******************************************************************************/
/* !Layer           : LIB                                                     */
/*                                                                            */
/* !Component       : LBOP_int.h                                              */
/* !Description     : Basic Byte Operation for all standard types.            */
/*                                                                            */
/* !Module          : LBOP                                                    */
/* !Revision        : 1.0                                                     */
/* !Date            : 10/03/2014                                              */
/* !Description     :                                                         */
/*                    %PCMS_HEADER_SUBSTITUTION_START%
   !File            : %PM%
   !ID description  : %PD% %PCMS_HEADER_SUBSTITUTION_END%
                                                                              */
/* !Scope           : Interface                                               */
/*                                                                            */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : CINCO                                                   */
/* !Target          : Renesas RL78/F14                                        */
/*                                                                            */
/* !COPYRIGHT 2014 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mourad SAKLY                     !Date : 10/03/2014     */
/* !Coded by        : Mourad SAKLY                     !Date : 10/03/2014     */
/*                                                                            */
/******************************************************************************/
/*  %PCMS_HEADER_SUBSTITUTION_START%
    %PL% %PCMS_HEADER_SUBSTITUTION_END%
 ******************************************************************************/

#ifndef LBOP_INT_H
#define LBOP_INT_H



#define LBOP_u8BIT0          ((u8) 0)
#define LBOP_u8BIT1          ((u8) 1)
#define LBOP_u8BIT2          ((u8) 2)
#define LBOP_u8BIT3          ((u8) 3)
#define LBOP_u8BIT4          ((u8) 4)
#define LBOP_u8BIT5          ((u8) 5)
#define LBOP_u8BIT6          ((u8) 6)
#define LBOP_u8BIT7          ((u8) 7)

#define LBOP_u8BIT8          ((u8) 8)
#define LBOP_u8BIT9          ((u8) 9)
#define LBOP_u8BIT10         ((u8)10)
#define LBOP_u8BIT11         ((u8)11)
#define LBOP_u8BIT12         ((u8)12)
#define LBOP_u8BIT13         ((u8)13)
#define LBOP_u8BIT14         ((u8)14)
#define LBOP_u8BIT15         ((u8)15)



#define LBOP_vidSetBitInByteData(u8ByteData, u8BitPosition) \
u8ByteData |= (u8)((u8)1 << u8BitPosition)

#define LBOP_vidResetBitInByteData(u8ByteData, u8BitPosition) \
u8ByteData &= (u8)(~(u8)((u8)1 << u8BitPosition))



#define LBOP_vidResetByteData(u8ByteData) \
(u8ByteData) = (u8)0x00



/************************************************************
 * Description: Gets a bit of an u8 word at the given position
 * GUID:
 * Parameters:
 *              u8 u8Word               : u8 word
 *                                        [0x00..0xFF]
 *              u8 u8Pos                : Position of the bit to get
 *                                        [0..7]
 *
 * Return type          :u8
 ************************************************************/
#define LBOP_u8GET_BIT_U8( u8Word, u8Pos )                                      \
  ((u8)( ( ((u8)(u8Word)) & ( ((u8)0x01)<<((u8)(u8Pos)) ) ) >> ((u8)(u8Pos)) ))

/************************************************************
 * Description: Gets a bit of an u16 word at the given position
 * GUID:
 * Parameters:
 *              u16 u16Word             : u16 word
 *                                        [0x00..0xFFFF]
 *              u8 u8Pos                : Position of the bit to get
 *                                        [0..15]
 *
 * Return type          :u8
 ************************************************************/
#define LBOP_u8GET_BIT_U16( u16Word, u8Pos )                                    \
  ((u8)( ( ((u16)(u16Word)) & ( ((u16)0x0001)<<((u8)(u8Pos)) ) ) >> ((u8)(u8Pos)) ))


/************************************************************
 * Description: Shift an u16 word (from the right) to the (left) given position
 * GUID:
 * Parameters:
 *              u16 u16Word             : u16 word
 *                                        [0x00..0xFFFF]
 *              u8 u8Pos                : Position of the bit to get
 *                                        [0..15]
 *
 * Return type          :u8
 ************************************************************/
#define LBOP_u16SHIFT_TO_POS( u16Word, u8Pos )                                  \
  ((u16)( ((u16)(u16Word)) << ((u8)(u8Pos)) ))

/************************************************************
 * Description: Shift an u16 word from the (left) given position (to the right)
 * GUID:
 * Parameters:
 *              u16 u16Word             : u16 word
 *                                        [0x00..0xFFFF]
 *              u8 u8Pos                : Position of the bit to get
 *                                        [0..15]
 *
 * Return type          :u8
 ************************************************************/
#define LBOP_u16SHIFT_FROM_POS( u16Word, u8Pos )                                \
  ((u16)( ((u16)(u16Word)) >> ((u8)(u8Pos)) ))




#endif /* LBOP_INT_H */

/*************************** E N D (LBOP_Int.h) ********************************/

