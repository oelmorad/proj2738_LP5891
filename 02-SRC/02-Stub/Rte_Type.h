/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_Type.h
 *           Config:  Hepta.dpa
 *      ECU-Project:  Hepta
 *
 *        Generator:  MICROSAR RTE Generator Version 4.24.0
 *                    RTE Core Version 1.24.0
 *          License:  PAI2633
 *
 *      Description:  Header file containing user defined AUTOSAR types and RTE structures
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_TYPE_H
# define RTE_TYPE_H


/* PRQA S 1039 EOF */ /* MD_Rte_1039 */

/**********************************************************************************************************************
 * Data type definitions
 *********************************************************************************************************************/
#include "Platform_Types.h"
# define Rte_TypeDef_Boolean
typedef boolean Boolean;

# define Rte_TypeDef_NvM_DstPtrType
typedef void * NvM_DstPtrType;

# define Rte_TypeDef_NvM_SrcPtrType
typedef const void * NvM_SrcPtrType;

# define Rte_TypeDef_SFIX16_S1P953125EN5
typedef sint16 SFIX16_S1P953125EN5;

# define Rte_TypeDef_SFIX16_SP001
typedef sint16 SFIX16_SP001;

# define Rte_TypeDef_SFIX16_SP01
typedef sint16 SFIX16_SP01;

# define Rte_TypeDef_SFIX16_SP1
typedef sint16 SFIX16_SP1;

# define Rte_TypeDef_SFIX8_EN4
typedef sint8 SFIX8_EN4;

# define Rte_TypeDef_SFIX8_EN5
typedef sint8 SFIX8_EN5;

# define Rte_TypeDef_SInt16
typedef sint16 SInt16;

# define Rte_TypeDef_UFIX16_EN16
typedef uint16 UFIX16_EN16;

# define Rte_TypeDef_UFIX16_SP01
typedef uint16 UFIX16_SP01;

# define Rte_TypeDef_UFIX16_SP02
typedef uint16 UFIX16_SP02;

# define Rte_TypeDef_UFIX16_SP0244140625
typedef uint16 UFIX16_SP0244140625;

# define Rte_TypeDef_UFIX16_SP1
typedef uint16 UFIX16_SP1;

# define Rte_TypeDef_UFIX8_EN4
typedef uint8 UFIX8_EN4;

# define Rte_TypeDef_UFIX8_EN5
typedef uint8 UFIX8_EN5;

# define Rte_TypeDef_UFIX8_EN8
typedef uint8 UFIX8_EN8;

# define Rte_TypeDef_UFIX8_SP005
typedef uint8 UFIX8_SP005;

# define Rte_TypeDef_UFIX8_SP01
typedef uint8 UFIX8_SP01;

# define Rte_TypeDef_UFIX8_SP02
typedef uint8 UFIX8_SP02;

# define Rte_TypeDef_UFIX8_SP1
typedef uint8 UFIX8_SP1;

# define Rte_TypeDef_UFIX8_SP390625
typedef uint8 UFIX8_SP390625;

# define Rte_TypeDef_UInt16
typedef uint16 UInt16;

# define Rte_TypeDef_UInt8
typedef uint8 UInt8;

# define Rte_TypeDef_afs_type
typedef sint32 afs_type;



# define Rte_TypeDef_CLUSTER
typedef struct
{
  SFIX16_SP1 HAngleLeft;
  SFIX16_SP1 HAngleRight;
  SFIX16_SP1 VAngleBot;
  Boolean Valitidy;
  UInt8 Brightness;
  UFIX8_SP02 RampUp;
  UFIX8_SP02 RampDown;
} CLUSTER;

# define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;

# define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;

# define Rte_TypeDef_ComM_UserHandleType
typedef uint16 ComM_UserHandleType;

# define Rte_TypeDef_Dcm_CommunicationModeType
typedef uint8 Dcm_CommunicationModeType;

# define Rte_TypeDef_Dcm_ConfirmationStatusType
typedef uint8 Dcm_ConfirmationStatusType;

# define Rte_TypeDef_Dcm_ControlDtcSettingType
typedef uint8 Dcm_ControlDtcSettingType;

# define Rte_TypeDef_Dcm_DiagnosticSessionControlType
typedef uint8 Dcm_DiagnosticSessionControlType;

# define Rte_TypeDef_Dcm_EcuResetType
typedef uint8 Dcm_EcuResetType;

# define Rte_TypeDef_Dcm_NegativeResponseCodeType
typedef uint8 Dcm_NegativeResponseCodeType;

# define Rte_TypeDef_Dcm_OpStatusType
typedef uint8 Dcm_OpStatusType;

# define Rte_TypeDef_Dcm_ProtocolType
typedef uint8 Dcm_ProtocolType;

# define Rte_TypeDef_Dcm_RequestKindType
typedef uint8 Dcm_RequestKindType;

# define Rte_TypeDef_Dcm_SecLevelType
typedef uint8 Dcm_SecLevelType;

# define Rte_TypeDef_Dcm_SesCtrlType
typedef uint8 Dcm_SesCtrlType;

# define Rte_TypeDef_Dem_DTCFormatType
typedef uint8 Dem_DTCFormatType;

# define Rte_TypeDef_Dem_DTCGroupType
typedef uint32 Dem_DTCGroupType;

# define Rte_TypeDef_Dem_DTCKindType
typedef uint8 Dem_DTCKindType;

# define Rte_TypeDef_Dem_DTCOriginType
typedef uint16 Dem_DTCOriginType;

# define Rte_TypeDef_Dem_DTCSeverityType
typedef uint8 Dem_DTCSeverityType;

# define Rte_TypeDef_Dem_DTCStatusMaskType
typedef uint8 Dem_DTCStatusMaskType;

# define Rte_TypeDef_Dem_DTRControlType
typedef uint8 Dem_DTRControlType;

# define Rte_TypeDef_Dem_DebounceResetStatusType
typedef uint8 Dem_DebounceResetStatusType;

# define Rte_TypeDef_Dem_DebouncingStateType
typedef uint8 Dem_DebouncingStateType;

# define Rte_TypeDef_Dem_EventIdType
typedef uint16 Dem_EventIdType;

# define Rte_TypeDef_Dem_EventStatusType
typedef uint8 Dem_EventStatusType;

# define Rte_TypeDef_Dem_IndicatorStatusType
typedef uint8 Dem_IndicatorStatusType;

# define Rte_TypeDef_Dem_InitMonitorReasonType
typedef uint8 Dem_InitMonitorReasonType;

# define Rte_TypeDef_Dem_IumprDenomCondIdType
typedef uint8 Dem_IumprDenomCondIdType;

# define Rte_TypeDef_Dem_IumprDenomCondStatusType
typedef uint8 Dem_IumprDenomCondStatusType;

# define Rte_TypeDef_Dem_IumprReadinessGroupType
typedef uint8 Dem_IumprReadinessGroupType;

# define Rte_TypeDef_Dem_MonitorStatusType
typedef uint8 Dem_MonitorStatusType;

# define Rte_TypeDef_Dem_OperationCycleStateType
typedef uint8 Dem_OperationCycleStateType;

# define Rte_TypeDef_Dem_RatioIdType
typedef uint16 Dem_RatioIdType;

# define Rte_TypeDef_Dem_UdsStatusByteType
typedef uint8 Dem_UdsStatusByteType;

# define Rte_TypeDef_EcuM_BootTargetType
typedef uint8 EcuM_BootTargetType;

# define Rte_TypeDef_EcuM_ModeType
typedef uint8 EcuM_ModeType;

# define Rte_TypeDef_EcuM_ShutdownCauseType
typedef uint8 EcuM_ShutdownCauseType;

# define Rte_TypeDef_EcuM_StateType
typedef uint8 EcuM_StateType;

# define Rte_TypeDef_EcuM_TimeType
typedef uint32 EcuM_TimeType;

# define Rte_TypeDef_EcuM_UserType
typedef uint8 EcuM_UserType;

# define Rte_TypeDef_FiM_FunctionIdType
typedef uint8 FiM_FunctionIdType;

# define Rte_TypeDef_LBTY_tenuBoolean
typedef uint8 LBTY_tenuBoolean;

# define Rte_TypeDef_LBTY_tenuErrorStatus
typedef uint8 LBTY_tenuErrorStatus;

# define Rte_TypeDef_LBTY_tenuWorkingStatus
typedef uint8 LBTY_tenuWorkingStatus;

# define Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;

# define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;

# define Rte_TypeDef_TimeInMicrosecondsType
typedef uint32 TimeInMicrosecondsType;

# define Rte_TypeDef_WdgM_CheckpointIdType
typedef uint16 WdgM_CheckpointIdType;

# define Rte_TypeDef_WdgM_LocalStatusType
typedef uint8 WdgM_LocalStatusType;

# define Rte_TypeDef_WdgM_SupervisedEntityIdType
typedef uint16 WdgM_SupervisedEntityIdType;

# define Rte_TypeDef_s16
typedef sint16 s16;

# define Rte_TypeDef_s32
typedef sint32 s32;

# define Rte_TypeDef_s8
typedef sint8 s8;

# define Rte_TypeDef_u16
typedef uint16 u16;

# define Rte_TypeDef_u32
typedef uint32 u32;

# define Rte_TypeDef_u8
typedef uint8 u8;

# define Rte_TypeDef_LBTY_tstrVersionInfoType
typedef struct
{
  u16 u16VendorID;
  u16 u16ModuleID;
  u8 u8SwMajorVersion;
  u8 u8SwMinorVersion;
  u8 u8SwPatchVersion;
} LBTY_tstrVersionInfoType;

# define Rte_TypeDef_LDEM_tenuDefectState
typedef u8 LDEM_tenuDefectState;

# define Rte_TypeDef_LDEM_tenuFreezeState
typedef u8 LDEM_tenuFreezeState;


# ifndef RTE_SUPPRESS_UNUSED_DATATYPES
/**********************************************************************************************************************
 * Unused Data type definitions
 *********************************************************************************************************************/

#  define Rte_TypeDef_SFIX16_EN11
typedef sint16 SFIX16_EN11;

#  define Rte_TypeDef_SFIX16_SP0001
typedef sint16 SFIX16_SP0001;

#  define Rte_TypeDef_SFIX8_SP1
typedef sint8 SFIX8_SP1;

#  define Rte_TypeDef_UFIX16_E1
typedef uint16 UFIX16_E1;

#  define Rte_TypeDef_UFIX16_EN6
typedef uint16 UFIX16_EN6;

#  define Rte_TypeDef_UFIX16_SP005
typedef uint16 UFIX16_SP005;

#  define Rte_TypeDef_UFIX32_SP001
typedef uint32 UFIX32_SP001;

#  define Rte_TypeDef_UFIX8_EN1
typedef uint8 UFIX8_EN1;

#  define Rte_TypeDef_UFIX8_EN6
typedef uint8 UFIX8_EN6;

#  define Rte_TypeDef_UInt32
typedef uint32 UInt32;

#  define Rte_TypeDef_dtRef_VOID
typedef void * dtRef_VOID;

#  define Rte_TypeDef_dtRef_const_VOID
typedef const void * dtRef_const_VOID;

#  define Rte_TypeDef_hb_type
typedef sint32 hb_type;



#  define Rte_TypeDef_DSMLvl_tenuFailureType
typedef uint8 DSMLvl_tenuFailureType;

#  define Rte_TypeDef_Dem_OperationCycleIdType
typedef uint8 Dem_OperationCycleIdType;

#  define Rte_TypeDef_HBIN_tenuBinCh
typedef uint8 HBIN_tenuBinCh;

#  define Rte_TypeDef_HBIN_tenuBinNb
typedef uint8 HBIN_tenuBinNb;

#  define Rte_TypeDef_HBIN_tenuCurLedNb
typedef uint8 HBIN_tenuCurLedNb;

#  define Rte_TypeDef_NvMBlockIdType
typedef NvM_BlockIdType NvMBlockIdType;

#  define Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;

# endif




#endif /* RTE_TYPE_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_1039:  MISRA rule: Rule1.2
     Reason:     Same macro and function names are required to meet AUTOSAR spec.
     Risk:       No functional risk. Macro will be undefined before function definition.
     Prevention: Not required.

*/
