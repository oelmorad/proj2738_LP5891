/******************************************************************************/
/* !Layer           : Hardware abstraction layer (HAL)                        */
/*                                                                            */
/* !Component       : HSPM_int.h                                              */
/* !Description     : SPI Manager                                             */
/* !Module          : HSPM                                                    */
/* !Revision        : 1.0                                                     */
/* !Date            : 14/06/2015                                              */
/* !Description     : SPI Manager (Provides service for SPI users and
 *                      abstracts SPI Driver)
 *                    Compatible with VLS_STD_DSPI and AUTOSAR                */
/*                                                                            */
/*                    %PCMS_HEADER_SUBSTITUTION_START%
   !File            : %PM%
   !ID Description  : %PD% %PCMS_HEADER_SUBSTITUTION_END%
                                                                              */
/* !Scope           : Program                                                 */
/*                                                                            */
/* !Vendor          :                                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/* !Project         : STD                                                     */
/* !Target          : STD							                          */
/*                                                                            */
/* !COPYRIGHT 2016 VALEO LIGHTING SYSTEM                                      */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/*                     Mahmed3  30/5/2017   Modify HSPM to wpork with new LDEM*/
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  --   14/3/2019  --         Update AUTOSAR headers inclusion    */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mohamed MAGDY                    !Date : 14/06/2015     */
/* !Coded by        : Mohamed MAGDY                    !Date : 14/06/2015     */
/*                                                                            */
/******************************************************************************/
/*  %PCMS_HEADER_SUBSTITUTION_START%
    %PL% %PCMS_HEADER_SUBSTITUTION_END%
 ******************************************************************************/


#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HSPM

/******************************************************************************/
/************************** Header Files Inclusion ****************************/
/******************************************************************************/
/*!Comment: Basic Libraries */
#include "LBTY_int.h"
#include "LCTY_int.h"
#include "LDEM_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HSPM.h"
#include "HFIC_IoHwAb.h"
#include "Std_Types.h"
#include "Spi.h"
#endif

/*!Comment: HSPM include files */
#include "HSPM_int.h"
#include "HSPM_priv.h"
#include "HSPM_cfg.h"

/******************************************************************************/


/******************************************************************************/
/******************************** Zone Typedef ********************************/
/******************************************************************************/

/******************************************************************************/
/********************************* Zone Macro *********************************/
/******************************************************************************/

/******************************************************************************/
/********************************* Zone Define ********************************/
/******************************************************************************/

/******************************************************************************/
/******************************** Zone Constant *******************************/
/******************************************************************************/

/******************************************************************************/
/**************************** Zone Structure\Union ****************************/
/******************************************************************************/

/******************************************************************************/
/******************************** Zone Variable *******************************/
/******************************************************************************/

/******************* !Comment : Transmission Time-Out Defect ******************/
LDEM_tstrDefectConfig astrHspmTxTimOutDfctCfg =
  {

      1  ,                     /*!Comment : Increment                       */
      1  ,                     /*!Comment : Decrement                       */
      3  ,                     /*!Comment : CounterThreshold                */
      1  ,                    /*!Comment : HysteresisHigh                  */
      1  ,                         /*!Comment : HysteresisLow                   */

      LDEM_enuREVERSIBLE ,                    /*!Comment : Defect Reversible/Irreversible  */
      LDEM_enuLEFTSIDE,                       /* !Comment : Defect operator                */
      LDEM_enuCounter_Continue,               /* !Comment : Unfreeze action                */

      LDEM_enuDEFECT_ABSENT ,                /*!Comment : Defect Initial State             */
      0  ,                /*!Comment : Counter Initial Value            */
      LDEM_enuRUNNING                        /*!Comment : Freeze state                     */
  };


/******************** !Comment : SPI Driver Request Defect ********************/
LDEM_tstrDefectConfig astrHspmDrvReqRjctDfctCfg =
  {

     1  ,                     /*!Comment : Increment                       */
     1  ,                     /*!Comment : Decrement                       */
     1  ,                     /*!Comment : CounterThreshold                */
     1  ,                    /*!Comment : HysteresisHigh                  */
     1  ,                   /*!Comment : HysteresisLow                   */

     LDEM_enuREVERSIBLE ,                     /*!Comment : Defect Reversible/Irreversible  */
     LDEM_enuRIGHTSIDE,                       /* !Comment : Defect operator                */
     LDEM_enuCounter_Continue,                /* !Comment : Unfreeze action                */

     LDEM_enuDEFECT_ABSENT ,                  /*!Comment : Defect Initial State             */
     1  ,                 /*!Comment : Counter Initial Value            */
     LDEM_enuRUNNING                          /*!Comment : Freeze state                     */
  };


/******************************************************************************/
/******************************** Zone Function *******************************/
/******************************************************************************/

/******************************************************************************/
/*!Description:                                                               */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_STD                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidVlsMcalInit(void)
{

}


/******************************************************************************/
/*!Description:                                                               */
/*                                                                            */
/*!Parameters : None                                                          */
/*                                                                            */
/*!Return     : None                                                          */
/*                                                                            */
/*!Trace_To   : Covers_STD                                                    */
/*                                                                            */
/******************************************************************************/
void HSPM_vidAutosarMcalInit(void)
{
#ifdef AUTOSAR_USED
   Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
#endif
}

#endif /* BSW_HSPM */

/***************************** E N D (HSPM_priv.h) *****************************/
