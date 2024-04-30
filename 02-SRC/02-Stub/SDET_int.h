/**********************************************************************************************************************/
/* !Layer           : Service Layer                                                                                   */
/*                                                                                                                    */
/* !Component       : SDET                                                                                            */
/* !Description     : SDET stub interface file                                                                        */
/*                                                                                                                    */
/* !Module          : SDET_int.h                                                                                      */
/* !Revision        : 1.0                                                                                             */
/* !Date            : 12/20/2018                                                                                      */
/* !Description     : stub interface file                                                                             */
/* !Scope           : Interface                                                                                       */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* !Coding language : C                                                                                               */
/* !Project         : NXP S32 STD MCAL                                                                                */
/* !Target          : NXP S32K1xx                                                                                     */
/*                                                                                                                    */
/* !COPYRIGHT 2013 VALEO LIGHTING SYSTEM                                                                              */
/*  all rights reserved                                                                                               */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* MODIFICATION LOG :                                                                                                 */
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Designed by     : Nuha BAHAA                    !Date : 12/20/2018                                             */
/* !Coded by        : Nuha BAHAA                    !Date : 12/20/2018                                             */
/*                                                                                                                    */
/**********************************************************************************************************************/
#ifndef SDET_INT_H_
#define SDET_INT_H_

/*!Comment: Standard Error Identifiers                                                                                */
#define SDET_u8UNINIT                     (u8)0x00
#define SDET_u8ALREADY_INITIALIZED        (u8)0x0F
#define SDET_u8PARAM_POINTER              (u8)0x33
#define SDET_u8PARAM_INDEX                (u8)0X3C
#define SDET_u8STATE_DEFAULT              (u8)0x55
#define SDET_u8NOK                        (u8)0x5A

#define SDET_u8CUSTOM1                    (u8)0x96
#define SDET_u8CUSTOM2                    (u8)0x99
#define SDET_u8CUSTOM3                    (u8)0xA5
#define SDET_u8CUSTOM4                    (u8)0xAA
#define SDET_u8CUSTOM5                    (u8)0xC3
#define SDET_u8CUSTOM6                    (u8)0xCC
#define SDET_u8CUSTOM7                    (u8)0xF0
#define SDET_u8CUSTOM8                    (u8)0xFF



extern void SDET_vidReportError(u16 ModuleID , u8 PltfID,
                                                  u8  ApiId   , u8 ErrorId);

#endif /* DET_INT_H_ */
