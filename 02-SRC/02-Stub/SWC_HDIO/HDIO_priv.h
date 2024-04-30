/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HDIO                                                    */
/* !Description     : Digital input Manager                                   */
/*                                                                            */
/* !Module          : HDIO_priv.h                                             */
/* !Revision        : 1.5                                                     */
/* !Date            : 17 Dec 2020                                             */
/*                                                                            */
/*                                                                            */
/* !Scope           : Program                                                 */
/*                                                                            */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : STD                                                     */
/* !Target          : STD                                                     */
/*                                                                            */
/* !COPYRIGHT 2016 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/*    Author   --     Date     --          Modification                       */
/* Ahmed Assaf -- 28  NOV 2016 -- Initial Creation                            */
/* Ahmed Assaf  -- 9  MAR 2017    Public and private configurations           */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  -- 10/12/2019   -- Fix Mandatory KL issues                     */
/* Soha Wagdy  --  02/06/2020  -- Add safety runnable calls                   */
/* Soha Wagdy  -- 23 Nov 2020  -- Updates for the following ACRs:             */
/*                                  [artf1067933 artf267567 artf794236 ]      */
/* Soha Wagdy  -- 17 Dec 2020  -- Closing review points for the               */
/*                         following ACRs:[artf1067933 artf267567 artf794236] */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 28 NOV 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 28 NOV 2016 */
/*                                                                            */
/******************************************************************************/

#ifndef HDIO_PRIV_H
#define HDIO_PRIV_H


#include "HDIO_cfg.h"
/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/******************************************************************************/
/*   Definitions for the software module version                              */
/******************************************************************************/
#define HDIO_u16VendorID         ((u16)0x59)
#define HDIO_u16ModuleID         ((u16)0x18)
#define HDIO_u8SwMajorVersion    ((u8)0x03)
#define HDIO_u8SwMinorVersion    ((u8)0x05)
#define HDIO_u8SwPatchVersion    ((u8)0x00)

/**********************************************************************************************************************/
/* !Description : DET reporting APIs ID definition                                                                    */
/**********************************************************************************************************************/
#define HDIO_vidRunnableUpdateInput_SID                           ((u8)0x00)
#define HDIO_vidRunnableUpdateOutput_SID                          ((u8)0x01)
#define vidHdioGetInputPin_SID                                    ((u8)0x02)
#define vidHdioUpdInputDefect_SID                                 ((u8)0x03)
#define vidHdioFilterInputPin_SID                                 ((u8)0x04)
#define vidHdioGetOutputPin_SID                                   ((u8)0x05)
#define vidHdioFiltertionMechanism_SID                            ((u8)0x06)
/******************************************************************************/
/* !Comment : Digital activation state                                        */
/******************************************************************************/
#define HDIO_u8ACTIVE_HIGH       ((u8)0x01)
#define HDIO_u8ACTIVE_LOW        ((u8)0x00)

/******************************************************************************/
/* !Comment : Initialization Filteration mechanism types                      */
/******************************************************************************/
#define HDIO_u8FROM_UNFILT_BUFR  ((u8)0xFF)
#define HDIO_u8FROM_NOMINAL_VAL  ((u8)0x00)

/******************************************************************************/
/* !Comment : Initialization Filteration Nominal Values                       */
/******************************************************************************/
#define HDIO_u8OFF               ((u8)0x00)
#define HDIO_u8ON                ((u8)0x01)

/******************************************************************************/
/* !Comment : Defect Update Types                                             */
/******************************************************************************/
#define HDIO_u8UNFILT_VAL        ((u8)0x00)
#define HDIO_u8FILT_VAL          ((u8)0xFF)

/******************************************************************************/
/* !Comment : Filteration mechanism types                                     */
/******************************************************************************/
#define HDIO_u8MAJORITY_FILTER      ((u8)0x00)
#define HDIO_u8CONSECUTIVE_FILTER   ((u8)0x1F)
#define HDIO_u8NO_FILTER            ((u8)0xE3)

/******************************************************************************/
/* !Description : Enable/Disable defenitions                                  */
/******************************************************************************/
#define HDIO_ENABLED       (0xFFU)
#define HDIO_DISABLED      (0x00U)

/*****************************************************************************/
/* !Comment  : SDET usage in runnable                                        */
/*****************************************************************************/
#define HDIO_u32DET_USED      (0x00U)
#define HDIO_u32DET_NOT_USED  (0xFFU)

/******************************************************************************/
/* !Comment : Memory placement configurations  [ROM_CONFIG or RAM_CONFIG]     */
/******************************************************************************/
#define ROM_CONFIG            (0x00U)
#define RAM_CONFIG            (0xFFU)

/******************************************************************************/
/* !Comment : Memory placement based on configuration: ROM_CONFIG / RAM_CONFIG*/
/******************************************************************************/
#if CONFIG_MEM_PLACEMENT == ROM_CONFIG
#define HDIO_CONST const
#else
#define HDIO_CONST
#endif

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/


/******************************************************************************/
/*                        -----------------------------                       */
/*                        | Active | Actual | Logical |                       */
/*                        | -------|--------|---------|                       */
/*                        |    0   |   0    |    1    |                       */
/*                        | -------|--------|---------|                       */
/*                        |    0   |   1    |    0    |                       */
/*                        | -------|--------|---------|                       */
/*                        |    1   |   0    |    0    |                       */
/*                        | -------|--------|---------|                       */
/*                        |    1   |   1    |    1    |                       */
/*                        -----------------------------                       */
/******************************************************************************/
#define u8GET_LOGICAL_STATE(u8IdxCpy, u8ActualStateCpy,pstrConfigCpy)                  \
                        (((u8ActualStateCpy) == ( pstrConfigCpy)[(u8IdxCpy)].u8ActiveState) ? HDIO_ON : HDIO_OFF)


/******************************************************************************/
/*                       --------------------------------                     */
/*                       | Active | Logical | Physical  |                     */
/*                       | -------|---------|---------- |                     */
/*                       |    0   |   0     |    1      |                     */
/*                       | -------|---------|---------- |                     */
/*                       |    0   |   1     |    0      |                     */
/*                       | -------|---------|---------- |                     */
/*                       |    1   |   0     |    0      |                     */
/*                       | -------|---------|---------- |                     */
/*                       |    1   |   1     |    1      |                     */
/*                       --------------------------------                     */
/******************************************************************************/
#define u8GET_PHYSICAL_STATE(u8IdxCpy, u8ActualStateCpy,pstrConfigCpy)                  \
         (((u8ActualStateCpy) ==  (pstrConfigCpy)[(u8IdxCpy)].u8ActiveState) ? MFIC_u8IO_PIN_HIGH : MFIC_u8IO_PIN_LOW)


/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/

/******************************************************************************/
/* !Comment : Filteration configuration                                       */
/******************************************************************************/
typedef struct
{
      u8 u8InitializationMechanism;
      u8 u8InitNominalValues;
      u8 u8FilterationMechanism;
      u8 u8NumOfSamples;
}HDIO_tstrDIOFilterConfig;

/******************************************************************************/
/* !Comment : Digital input/output pin configuration                          */
/******************************************************************************/
typedef struct 
{
   u8 u8DioPinId;
   u8 u8ActiveState;
}HDIO_tstrDioSig;


/******************************************************************************/
/* !Comment : Input Component Configurations                           */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
typedef struct
{
   u8 HDIO_u8InputNB;
   u8 HDIO_u8DefectsNB;
   const HDIO_tstrDioSig* HDIO_pstrDigitalInputConfig;
   const HDIO_tstrDIOFilterConfig* HDIO_ptrInSigFltrMechanism;
   const u8* HDIO_pu8MajorityCap;
   const u8* HDIO_pu8ConsecutiveCap;
   const LDEM_tstrDefectConfig* HDIO_pstrDefectConfig;
   const u8* HDIO_pu8DefectToPinLink;
   const u8* HDIO_ptrDefectType;

}HDIO_tstrInputCompConfig;
#endif

/******************************************************************************/
/* !Comment : Output Component Configurations                                 */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
typedef struct
{
   u8 HDIO_u8OutputNB;
   const HDIO_tstrDioSig* HDIO_pstrDigitalOutputConfig;

}HDIO_tstrOutputCompConfig;
#endif

/******************************************************************************/
/********************************** zone constant *****************************/
/******************************************************************************/

/******************************************************************************/
/* Input Component configurations                                             */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
extern HDIO_tstrInputCompConfig HDIO_astrInputCompConfigp[HDIO_u8VARIANT_NB];
#endif

/******************************************************************************/
/* Output Component Configurations                                            */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
extern HDIO_tstrOutputCompConfig HDIO_astrOutputCompConfigp[HDIO_u8VARIANT_NB];
#endif


#ifdef BSW_HDIO_INPUT
extern void vidHdioGetInputPin(u8 u8Idx);
extern void vidHdioUpdInputDefect (u8 u8Idx);
extern void vidHdioFilterInputPin (u8 u8Idx);
extern void vidHdioFiltertionMechanism (u8 u8IdxCpy);
#endif

#ifdef BSW_HDIO_OUTPUT
extern void vidHdioGetOutputPin(u8 u8Idx);
extern void vidHdioUpdateOutput(u8 u8IdxCpy);
#endif


#endif /*HDIO_PRIV_H */
/*************************** E N D (HDIO_priv.c) ******************************/

