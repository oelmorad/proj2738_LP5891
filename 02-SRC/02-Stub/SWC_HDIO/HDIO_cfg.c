/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HDIO                                                    */
/* !Description     : Digital input Manager                                   */
/*                                                                            */
/* !Module          : HDIO_cfg.c                                              */
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
/* Nuha bahaa  -- 1/10/2017     -- Fix bugs                                   */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  --  14/ 3 /2019 -- Fixed "Release_14-03-2019" artifacts        */
/*                         Updated Software version/Updated AUTOSAR headers   */
/* Soha Wagdy  -- 10/12/2019   -- Fix Mandatory KL issues                     */
/* Soha Wagdy  -- 11 Nov 2020  -- Fix Configurations to RAM [artf1067933]     */
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

#define HAL_LAYER
#include "BSW_cfg.h"
#ifdef BSW_HDIO

/******************************************************************************/
/*                          Header Files included                             */
/******************************************************************************/

#include "LBTY_int.h"
#include "LCTY_int.h"
#include "LFIL_int.h"
#include "LDEM_int.h"

#ifdef AUTOSAR_USED
#include "Rte_HDIO.h"
#include "HFIC_IoHwAb.h"
#endif

#include "MFIC_HDIO_cfg.h"

#include "HDIO_int.h"
#include "HDIO_priv.h"

/******************************************************************************/
/********************************* zone constant ******************************/
/******************************************************************************/

/****************************** Variant 1 Configurations **********************/
/******************************************************************************/
/* The activation state for each digital input                                */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT

static const HDIO_tstrDioSig HDIO_kastrDigitalInputConfig_Var1[HDIO_u8IN_NB_SIG_VAR1]=
{
   {MFIC_u8IO_PIN_1, HDIO_u8ACTIVE_HIGH},
   {MFIC_u8IO_PIN_2, HDIO_u8ACTIVE_LOW },
   {MFIC_u8IO_PIN_3, HDIO_u8ACTIVE_HIGH},
   {MFIC_u8IO_PIN_4, HDIO_u8ACTIVE_LOW }
};

#endif

/******************************************************************************/
/* The activation state for each digital output                               */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT

static const HDIO_tstrDioSig HDIO_kastrDigitalOutputConfig_Var1[HDIO_u8OUT_NB_SIG_VAR1]=
{
   {MFIC_u8IO_PIN_50,     HDIO_u8ACTIVE_LOW },
   {MFIC_u8IO_PIN_51,     HDIO_u8ACTIVE_HIGH},
   {MFIC_u8IO_PIN_52,     HDIO_u8ACTIVE_LOW },
   {MFIC_u8IO_PIN_53,     HDIO_u8ACTIVE_HIGH}

};

#endif

#ifdef BSW_HDIO_INPUT
/*****************************************************************************/
/* Configuration of the filtration mechanism for input channels.             */
/* Implemented filtration types: Majority - Consecutive - No filtration      */
/*****************************************************************************/
static HDIO_CONST HDIO_tstrDIOFilterConfig HDIO_kastrInSigFltrMechanism_V1[HDIO_u8IN_NB_SIG_VAR1]=
{
   /*  Init Filt mechanism  - Init Filt Nominal Vals -   Filteration Mechanism    - Number of Samples */
   { HDIO_u8FROM_UNFILT_BUFR,      HDIO_u8OFF        ,  HDIO_u8MAJORITY_FILTER    ,      8 },
   { HDIO_u8FROM_UNFILT_BUFR,      HDIO_u8ON         ,  HDIO_u8CONSECUTIVE_FILTER ,      8 },
   { HDIO_u8FROM_NOMINAL_VAL,      HDIO_u8OFF        ,  HDIO_u8MAJORITY_FILTER    ,      8 },
   { HDIO_u8FROM_NOMINAL_VAL,      HDIO_u8ON         ,  HDIO_u8NO_FILTER          ,      8 }
};


/*****************************************************************************/
/* Majority cap parameter for majority filter                                */
/*****************************************************************************/
static HDIO_CONST u8 HDIO_au8MajorityCap_Var1[HDIO_u8IN_NB_SIG_VAR1]=
{
   5,
   0, /* Not majority filter */
   7,
   0  /* Not majority filter */
};


/*****************************************************************************/
/* Consecutive cap parameter for consecutive filter                          */
/*****************************************************************************/
static HDIO_CONST u8 HDIO_au8ConsecutiveCap_Var1[HDIO_u8IN_NB_SIG_VAR1]=
{
   0, /* Not consecutive filter */
   5,
   0, /* Not consecutive filter */
   0  /* Not consecutive filter */
};

/******************************************************************************/
/* !Description : Defect Configurations                                       */
/******************************************************************************/
static const LDEM_tstrDefectConfig HDIO_akstrDefectConfig_Var1[HDIO_u8DEFECTNB_VAR1]={

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       },

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       },

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       },

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       }
};

/******************************************************************************/
/* !Description : link between each defect and its associated Pin ID          */
/******************************************************************************/
static const u8 HDIO_u8DefectToPinLink_Var1[HDIO_u8DEFECTNB_VAR1] = {
   HDIO_u8IN_PIN0_VAR1,
   HDIO_u8IN_PIN1_VAR1,
   HDIO_u8IN_PIN2_VAR1,
   HDIO_u8IN_PIN3_VAR1
};

/******************************************************************************/
/* !Description : Array for setting the type of each defect update.           */
/* i.e Whether the defect will be updated from filtered or unfiltered buffer  */
/*  Range: [HDIO_u8UNFILT_VAL/HDIO_u8FILT_VAL]                                */
/******************************************************************************/
static const u8 HDIO_u8DefectType_Var1[HDIO_u8DEFECTNB_VAR1]=
{
   HDIO_u8UNFILT_VAL,      /* Defect Type (HDIO_u8UNFILT_VAL/HDIO_u8FILT_VAL) */
   HDIO_u8FILT_VAL,
   HDIO_u8UNFILT_VAL,
   HDIO_u8FILT_VAL
};

#endif

/****************************** Variant 1 Configurations **********************/




/****************************** Variant 2 Configurations **********************/
/******************************************************************************/
/* The activation state for each digital input                                */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT

static const HDIO_tstrDioSig HDIO_kastrDigitalInputConfig_Var2[HDIO_u8IN_NB_SIG_VAR2]=
{
   {MFIC_u8IO_PIN_1, HDIO_u8ACTIVE_HIGH},
   {MFIC_u8IO_PIN_2, HDIO_u8ACTIVE_LOW }
};

#endif

/******************************************************************************/
/* The activation state for each digital output                               */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT

static const HDIO_tstrDioSig HDIO_kastrDigitalOutputConfig_Var2[HDIO_u8OUT_NB_SIG_VAR2]=
{
   {MFIC_u8IO_PIN_50,     HDIO_u8ACTIVE_LOW },
   {MFIC_u8IO_PIN_51,     HDIO_u8ACTIVE_HIGH}

};

#endif

#ifdef BSW_HDIO_INPUT
/*****************************************************************************/
/* Configuration of the filteration mechanism for input channels             */
/*****************************************************************************/
static HDIO_CONST HDIO_tstrDIOFilterConfig HDIO_kastrInSigFltrMechanism_V2[HDIO_u8IN_NB_SIG_VAR2]=
{
   /*  Init Filt mechanism  - Init Filt Nominal Vals -   Filteration Mechanism    - Number of Samples */
   { HDIO_u8FROM_UNFILT_BUFR,      HDIO_u8OFF        ,  HDIO_u8MAJORITY_FILTER    ,      8 },
   { HDIO_u8FROM_NOMINAL_VAL,      HDIO_u8ON         ,  HDIO_u8CONSECUTIVE_FILTER ,      8 }
};


/*****************************************************************************/
/* Majority cap parameter for majority filter                                */
/*****************************************************************************/
static HDIO_CONST u8 HDIO_au8MajorityCap_Var2[HDIO_u8IN_NB_SIG_VAR2]=
{
   5,
   0 /* Not majority filter */
};


/*****************************************************************************/
/* Consecutive cap parameter for consecutive filter                          */
/*****************************************************************************/
static HDIO_CONST u8 HDIO_au8ConsecutiveCap_Var2[HDIO_u8IN_NB_SIG_VAR2]=
{
   0, /* Not consecutive filter */
   5
};

/******************************************************************************/
/* !Description : Defect Configurations                                       */
/******************************************************************************/
static const LDEM_tstrDefectConfig HDIO_akstrDefectConfig_Var2[HDIO_u8DEFECTNB_VAR2]={

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       },

   /* Increment , Decrement , CounterThreshold , thresholdLow , thresholdHigh ,   Reversibility    ,     Condition  */
   {    1       ,     1     ,        3         ,      1       ,       1       , LDEM_enuREVERSIBLE ,  LDEM_enuRIGHTSIDE
   /*    Unfreeze Action       ,  Initial Defect State ,   Initial Counter , Initial Freeze State */
   ,  LDEM_enuCounter_Continue , LDEM_enuDEFECT_ABSENT ,      0            , LDEM_enuRUNNING       }
};

/******************************************************************************/
/* !Description : link between each defect and its associated Pin ID          */
/******************************************************************************/
static const u8 HDIO_u8DefectToPinLink_Var2[HDIO_u8DEFECTNB_VAR2] = {
   HDIO_u8IN_PIN0_VAR2,
   HDIO_u8IN_PIN1_VAR2
};

/******************************************************************************/
/* !Description : Array for setting the type of each defect update.           */
/* i.e Whether the defect will be updated from filtered or unfiltered buffer  */
/*  Range: [HDIO_u8UNFILT_VAL/HDIO_u8FILT_VAL]                                */
/******************************************************************************/
static const u8 HDIO_u8DefectType_Var2[HDIO_u8DEFECTNB_VAR2]=
{
   HDIO_u8UNFILT_VAL,      /* Defect Type (HDIO_u8UNFILT_VAL/HDIO_u8FILT_VAL) */
   HDIO_u8FILT_VAL
};

#endif

/****************************** Variant 2 Configurations **********************/

#ifdef BSW_HDIO_INPUT
/******************************************************************************/
/* !Description : Structure for all Input pins configurations                 */
/******************************************************************************/
HDIO_tstrInputCompConfig HDIO_astrInputCompConfigp[HDIO_u8VARIANT_NB]=
{
   { HDIO_u8IN_NB_SIG_VAR1, HDIO_u8DEFECTNB_VAR1, HDIO_kastrDigitalInputConfig_Var1,
     HDIO_kastrInSigFltrMechanism_V1, HDIO_au8MajorityCap_Var1, HDIO_au8ConsecutiveCap_Var1,
     HDIO_akstrDefectConfig_Var1, HDIO_u8DefectToPinLink_Var1, HDIO_u8DefectType_Var1},

   { HDIO_u8IN_NB_SIG_VAR2, HDIO_u8DEFECTNB_VAR2, HDIO_kastrDigitalInputConfig_Var2,
     HDIO_kastrInSigFltrMechanism_V2, HDIO_au8MajorityCap_Var2, HDIO_au8ConsecutiveCap_Var2,
     HDIO_akstrDefectConfig_Var2, HDIO_u8DefectToPinLink_Var2, HDIO_u8DefectType_Var2 }
};
#endif

/******************************************************************************/
/* !Description : Structure for all Output pins configurations                */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
HDIO_tstrOutputCompConfig HDIO_astrOutputCompConfigp[HDIO_u8VARIANT_NB]=
{
   { HDIO_u8OUT_NB_SIG_VAR1, HDIO_kastrDigitalOutputConfig_Var1 },

   { HDIO_u8OUT_NB_SIG_VAR2, HDIO_kastrDigitalOutputConfig_Var2 }
};
#endif

#endif
/*************************** E N D (HDIO_cfg.c) ******************************/
