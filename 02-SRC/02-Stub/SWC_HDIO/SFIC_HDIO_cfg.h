#ifndef SFIC_HDIO_CFG_H_
#define SFIC_HDIO_CFG_H_

#include "SWDM_int.h"
#include "SINTP_int.h"

#define SFIC_vidEnterCriticalZone SINTP_vidEnterCritical
#define SFIC_vidLeaveCriticalZone SINTP_vidExitCritical
#define SFIC_enuHdioInputCP()                 SWDM_enuCheckpointReached( SWDM_ID_HDIO_Input       )
#define SFIC_enuHdioOutputCP()                SWDM_enuCheckpointReached( SWDM_ID_HDIO_Output      )

/***************************** SVAR Interfaces ******************************/
#ifdef BSW_SVAR
#include "SVAR_int.h"
/** \brief \DESIGNER_START Mapping to get active variant service \DESIGNER_END */
#define SFIC_u8SvarGetActiveVariant    SVAR_u8GetActiveVariant
#endif /* BSW_SVAR */

/* ***************************** SDET Interfaces ******************************/
#include "SDET_int.h"

#if(HDIO_u32DET_REPORTING == HVLT_u32DET_USED)

#define SFIC_u8DET_HDIO_INPUT_CP_ERROR   (u8)SDET_u8CUSTOM1
#define SFIC_u8DET_DDIO_RST_ERROR          (u8)SDET_u8CUSTOM2
#define SFIC_u8DET_HDIO_OUTPUT_CP_ERROR              (u8)SDET_u8CUSTOM3
#define SFIC_u8DET_DDIO_GETPIN_ERROR             (u8)SDET_u8CUSTOM4
#define SFIC_u8DET_LFIL_ERROR            (u8)SDET_u8CUSTOM5
#define SFIC_u8DET_LDEM_ERROR             (u8)SDET_u8CUSTOM6
#define SFIC_u8DET_HDIO_CFG_ERROR             (u8)SDET_u8CUSTOM7
#define SFIC_u8DET_CUSTOM8             (u8)SDET_u8CUSTOM8

#define SFIC_vidDetReportError(ModuleID,PltfID,ApiId,ErrorId)\
          SDET_vidReportError(ModuleID,PltfID,ApiId,ErrorId)
#endif
/******************** End of interfaces definition ******/
#endif /* SFIC_HDIO_CFG_H_ */
