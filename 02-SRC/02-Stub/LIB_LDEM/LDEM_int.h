/* ************************************************************************** */
/* *************** COMPONENT DESIGN DEFINITION SECTION ********************** */
/* ************************************************************************** */
/** \mainpage <em>\swc_name</em> Components Design Document
 * \tableofcontents
 * \section intro 1 - Introduction
 *   \par 1.1 - Document Scope
 *     This document is the Components Design Document for <em><b>\swc_name</b></em> Library developed on <em><b>\CorePRJ</b></em> project.
 *     \copydoc _cfgprj
 *   \par 1.2 - Reference Documents
 *     \# |  Core/Standard Document reference    | Version   | Status      | Description                                                                                                      |
 *     -- | :-----------------------------------:|:---------:|:-----------:|:----------------------------------------------------------------------------------------------------------------:|
 *     1  | [Doxygen Guidelines]                 | V1.1      | Released    | (https://docs.google.com/document/d/11H9bLdIPRVhDOuVjXYYh4VZyxFfaH96t96EHnnS1vZc/edit#heading=h.hidgczfnngw)     |
 *     2  | [SRS]                                | V2.1      | Released    | (https://forge.vnet.valeo.com/sf/go/doc869758?nav=1&pagenum=1&pagesize=15)                                       |
 *     3  | [GDD]                                | V3.0      | Released    | (https://forge.vnet.valeo.com/sf/go/doc868172)                                                                   |
 *     \copydoc _cfgdoc
 *
 *   \par 1.3 - Component Description
 *     Description for the component role and behaviors:
 *       - Role description\n
 *         \DESIGNER_START This Software library is used to detect the defect by comparing the value given to the configured threshold and configured operator.
 *                          - Can detect one threshold defect.
 *                          - Can detect two thresholds defects.  \DESIGNER_END
 *       - Nominal behavior description\n
 *         \DESIGNER_START Software library detects the defect through comparing the given value to the threshold and the operator configured . \DESIGNER_END
 *       - Functional safety protections realized\n
 *         \DESIGNER_START Software component does not realize safety protection. \DESIGNER_END
 *       - Behavior in case of failure description\n
 *         \DESIGNER_START In case of safety failure detection, Software library notifies Error Handler module. \DESIGNER_END
 *
 * \section asil 2 - Safety Integrity Level
 *   \par
 *     \DESIGNER_START <b> QM </b>  \DESIGNER_END
 *
 *
 * \section context 3 - Software Context
 * @startuml
 *   skinparam componentStyle uml2
 *
 *     [COMPONENT_USER]
 *     [LIB_LDEM]
 *     [STD_TYP]
 *     [DET]
 *     [YECU]
 *
 *     [YECU]            ..> LDEM_enuInitDefect         :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuDefectDetection1D  :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuDefectDetection2D  :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuUpdateDefect       :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuSetFreezingState   :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuGetInsState        :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuGetValidState      :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuSetCntrParams      :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuSetDfctValTh       :  <<use>>
 *     [COMPONENT_USER]  ..> LDEM_enuGetVersionInfo     :  <<use>>
 *
 *     LDEM_enuInitDefect        -- [LIB_LDEM]
 *     LDEM_enuUpdateDefect      -- [LIB_LDEM]
 *     LDEM_enuSetFreezingState  -- [LIB_LDEM]
 *     LDEM_enuGetInsState       -- [LIB_LDEM]
 *     LDEM_enuGetValidState     -- [LIB_LDEM]
 *     LDEM_enuSetCntrParams     -- [LIB_LDEM]
 *     LDEM_enuSetDfctValTh      -- [LIB_LDEM]
 *     LDEM_enuGetVersionInfo    -- [LIB_LDEM]
 *     LDEM_enuDefectDetection1D -- [LIB_LDEM]
 *     LDEM_enuDefectDetection2D -- [LIB_LDEM]
 *
 *     [LIB_LDEM] ..> StandardType : <<use>>
 *     [LIB_LDEM] ..> ErrorTrace   : <<use>>
 *     StandardType -- [STD_TYP]
 *     ErrorTrace   -- [DET]
 *
 *   @enduml
 *
 *
 * \section usecase 4 - Component Use Cases
 *
 *  \DESIGNER_START LDME Component Use Case 1: Initialization diagram \DESIGNER_END
 *   @startuml
 *   skinparam componentStyle uml2
 *
 *     :LDEM: as User
 *     (LDEM services) as SRV
 *     LDEM --> (Initialize the driver) : << LDEM_enuInitDefect() >>
 *   @enduml
 *
 *    LDEM Component Use Case 2: Nominal diagram
 *   @startuml
 *   skinparam componentStyle uml2
 *
 *     :Component User: as User
 *     (LDEM services) as SRV
 *   User --> LDEM                    : <<use>>
 *   LDEM --> (Update defects)        : <<LDEM_enuUpdateDefect()>>
 *   LDEM --> (freezing state)        : <<<LDEM_enuSetFreezingState()>>
 *   LDEM --> (instantaneous state)   : <<LDEM_enuGetInsState()>>
 *   LDEM --> (valid state)           : <<LDEM_enuGetValidState()>>
 *   LDEM --> (counter attributes)    : <<LDEM_enuSetCntrParams()>>
 *   LDEM --> (reading defect values) : <<LDEM_enuSetDfctValTh()>>
 *   LDEM --> (Get version info)      : <<LDEM_enuGetVersionInfo()>>
 *   LDEM --> (Detect one defect)     : <<LDEM_enuDefectDetection1D()>>
 *   LDEM --> (Detect two defects)    : <<LDEM_enuDefectDetection2D()>>
 *   @enduml
 *
 ** \section DCchoices 5 - Design Choices and justification
 *     Description for the component design choices with justification:
 *       \DESIGNER_START
 *       - Detection API design:\n
 *             - \DESIGNER_START 1- Create a switch case to each and every case to all the possible cases of detection. \DESIGNER_END
 *             - \DESIGNER_START 2- Create a general cases depending on the operator.\DESIGNER_END
 *             - \DESIGNER_START Design choice (2), so the code size would be smaller. \DESIGNER_END
 *
 *
 * \section DConstraints 6 - Design Constraints
 *
 *  \DESIGNER_START [SW_001] \DESIGNER_END
 *       \DESIGNER_START  \DESIGNER_END
 *   \n\b Description:\n
 *        Function  **LDEM_vidInitDefect** each defect must be initialized using LDEM_vidInitDefect prior to using it  \DESIGNER_END
 *   \n\b Constraint \b Type:\n
 *       \DESIGNER_START Initialization \DESIGNER_END
 *
 *   \par Constraint ID:
 *        \DESIGNER_START [DIAG_001] \DESIGNER_END
 *   \n\b Description:\n
 *       \DESIGNER_START DET module shall be integrated to report errors. \DESIGNER_END
 *   \n\b Constraint \b Type:\n
 *       \DESIGNER_START Diagnostic \DESIGNER_END
 *
 *   \par Constraint ID:
 *       \DESIGNER_START [SW_001] \DESIGNER_END
 *   \n\b Description:\n
 *       \DESIGNER_START Defect configuration must be implemented in the module that will use the DEM library before using it. \DESIGNER_END
 *   \n\b Constraint \b Type:\n
 *       \DESIGNER_START Design \DESIGNER_END
 *   \par Rational:
 *        \DESIGNER_START Each module have its own specific defect configuration.  \DESIGNER_END
 *
 *
 * \section mode 7 - Mode Management
 *   \par 7.1 - Component's behavior in software modes
 *     @startuml
 *     skinparam componentStyle uml2
 *       note "Transitions are handled by software mode manager" as N1
 *       [*] -->  All_Modes
 *       All_Modes --> [*]
 *       All_Modes  : SW Component nominal behavior (All call-able runs normally)
 *     @enduml
 *   \par 7.2 - Component's state machine
 *     LIB_LDEM does not have state machine as it serves the call once it's called. No initialization (idle state) and no busy state.
 *     @enduml
 *
 *  \section sequence 8 - Component global sequence
 *     Component global sequence diagram:
 *     \DESIGNER_START
 *     @startuml
 *     title LDEM library global sequence
 *
 *     alt
 *                   == PLTF_DEFECT_HANDLER ==
 *      Caller  -> LDEM        : LDEM_enuDefectDetection1D()
 *      activate LDEM
 *       LDEM   -> LDEM        : enuGetDefectStatus()
 *       LDEM  --> Caller      : return status
 *      deactivate LDEM
 *
 *     else
 *                  == Defect detection for 2 defect monitored values ==
 *      Caller  -> LDEM        : LDEM_enuDefectDetection2D()
 *      activate LDEM
 *       LDEM   -> LDEM        : enuGetDefectStatus()
 *       LDEM  --> Caller      : return status
 *      deactivate LDEM
 *
 *      else
 *       == PLTF_DEFECT_LDEM  ==
 *      Caller          -> LDEM       : LDEM_enuInitDefect()
 *      Caller          -> LDEM       : LDEM_enuUpdateDefect()
 *      Caller          -> LDEM       : LDEM_enuSetFreezingState()
 *      Caller          -> LDEM       : LDEM_enuGetInsState()
 *      Caller          -> LDEM       : LDEM_enuGetValidState()
 *      Caller          -> LDEM       : LDEM_enuSetCntrParams()
 *      Caller          -> LDEM       : LDEM_enuSetDfctValTh()
 *      Caller          -> LDEM       : LDEM_enuGetVersionInfo()
 *
 *       end
 *
 *     @enduml
 *
 *
 * \section RManagement 9 - Resources Management
 *   \par 9.1 - Hardware resources
 *     \DESIGNER_START  LIB_LDEM is a library and does not depend on specific hardware to detect the defect.\DESIGNER_END

 *   \par 9.2 - Resources consumption objectives
 *     Estimation of RAM / ROM consumption:
 *       - Estimation of RAM consumption:   \DESIGNER_START 20 bytes \DESIGNER_END
 *       - Estimation of ROM consumption:   \DESIGNER_START 1500 bytes \DESIGNER_END
 *       - Estimation of STACK consumption: \DESIGNER_START 100 bytes \DESIGNER_END
 *
 *   \par 9.3 - Shared resources analysis
 *     \DESIGNER_START No shared resources \DESIGNER_END
 *
 *   \par 9.4 - Protection mechanisms
 *     \DESIGNER_START NA \DESIGNER_END
 *
 *  \section IConstraints 10 - Integration Constraints

 *
 * \section history 11 - Document Information
 *   \par 11.1 - Core/Standard part information
 *     Current Core/Standard Version   | Current Core/Standard Status
 *     :-----------------------------: | :---------------------------:
 *     \CoreVersion                    | \CoreVersion_Status
 *
 *     \copydoc _inth
 *     \copydoc _privh
 *     \copydoc _prgc
 *     \copydoc _cfginf
 *     \copydoc _cfgh
 *     \copydoc _cfgc
 * \copydoc COPYRIGHT
 * \copydoc Templatehisto
 */

/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _inth LDEM_int.h History
 *     | File             | Version    | Status              | Description |
 *     | :-------------:  | :--------: | :-----------------: | :----------
 *     | 						 Initial Creation ||||
 *     |  LDEM_int.h      | V1.0       | proposed            | \verbatim $Rev:: 11             $: Revision of last commit \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Date::11-10-2016     #$: Date of last commit     \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Author:: Ahmed Assaf    $: Author of last commit   \endverbatim |
 */

/** \page _inth LDEM_int.h History
 *     | File             | Version    | Status              | Description |
 *     | :-------------:  | :--------: | :-----------------: | :----------
 *     |  update code after applying review remarks of tag 59.20-01.00.00-04.01 ||||
 *     |  LDEM_int.h      | V1.1       | proposed            | \verbatim $Rev:: 12            $: Revision of last commit \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Date::19-06-2018    #$: Date of last commit     \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Author:: Ahmed abdelmageed   $: Author of last commit   \endverbatim |
 */

/** \page _inth LDEM_int.h History
 *     | File             | Version    | Status              | Description |
 *     | :-------------:  | :--------: | :-----------------: | :----------
 *     |  Update code after applying MISRA issues remarks ||||
 *     |  LDEM_int.h      | V1.2       | proposed            | \verbatim $Rev:: 13            $: Revision of last commit \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Date::13-01-2019     #$: Date of last commit     \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Author:: Soha Wagdy   $: Author of last commit   \endverbatim |
 */

/** \page _inth LDEM_int.h History
 *     | File             | Version    | Status              | Description |
 *     | :-------------:  | :--------: | :-----------------: | :----------
 *     | 								 migration to Doxygen ||||
 *     |  LDEM_int.h      | V1.3       | proposed            | \verbatim $Rev:: 14                    $: Revision of last commit \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Date::13-04-2020     		  #$: Date of last commit     \endverbatim |
 *     | ^                | ^          | ^                   | \verbatim $Author:: Dina Shinaishin    $: Author of last commit   \endverbatim |
 */
/** \page _prgc LDEM_int.h History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     | Update the module with 2APIs LDEM_enuDefectDetection1D and LDEM_enuDefectDetection2D and update the CDD.        ||||
 *     | LDEM_int.h       |\CoreVersion | \CoreVersion_Status  | \verbatim $Rev::    249              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::   23/05/2021      #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author:: Youstina SORIAL  $: Author of last commit   \endverbatim |
 */

/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */

#ifndef LDEM_INT_H
#define LDEM_INT_H

/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "LDEM_cfg.h"


/****************************************************************************/
/****************************************************************************/
/**************************** Type_def declarations *************************/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/******************************** Enumerators *******************************/
/****************************************************************************/

/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */

/** \brief \DESIGNER_START Detection status \DESIGNER_END
 *   \details \DESIGNER_START Defines the detection status of the configured defect \DESIGNER_END
 */
typedef enum
{
   LDEM_enuDetectionStatus_UNKNOWN         = 0x01,  /**< \DESIGNER_START Detection status is unknown, only exists in deadzone 2D detection type   / 0x01 \DESIGNER_END*/
   LDEM_enuDetectionStatus_RAW_DETECTED    = 0x02,  /**< \DESIGNER_START Detection status is detected                                             / 0x02 \DESIGNER_END*/
   LDEM_enuDetectionStatus_RAW_NOTDETECTED = 0X03   /**< \DESIGNER_START Detection status is not detected                                         / 0X03 \DESIGNER_END*/
} LDEM_tenuDetectionStatus ;


/** \brief \DESIGNER_START Detection types \DESIGNER_END
 *   \details \DESIGNER_START Defines the detection types of the configured defect \DESIGNER_END
 */
typedef enum
{
   LDEM_enuDetectionType_NotSTD     =  0x01,    /**< \DESIGNER_START Detection status not standard                             /  0x01 \DESIGNER_END*/
   LDEM_enuDetectionType_1D         =  0x0E,    /**< \DESIGNER_START Detection type is one dimension  (one threshold)          /  0x0E \DESIGNER_END*/
   LDEM_enuDetectionType_2D         =  0X32,    /**< \DESIGNER_START Detection type is two dimensions (two thresholds -range-) /  0X32 \DESIGNER_END*/
   LDEM_enuDetectionType_2DHyst     =  0x3D,    /**< \DESIGNER_START Detection type is two dimensions with hysteresis          /  0x3D \DESIGNER_END*/
   LDEM_enuDetectionType_2DInRange  =  0x54,    /**< \DESIGNER_START Detection type is two dimensions with hysteresis          / 0x54  \DESIGNER_END*/
   LDEM_enuDetectionType_2DOutRange =  0x5B     /**< \DESIGNER_START Detection type is two dimensions with hysteresis          / 0x5B  \DESIGNER_END*/

} LDEM_tenuDetectionType;


/** \brief \DESIGNER_START Detection Operators \DESIGNER_END
 *   \details \DESIGNER_START Defines the used operator that the value will be compared with for defect detection \DESIGNER_END
 */
typedef enum
{
   LDEM_enuOP_EQUALS        = 0x01, /**< \DESIGNER_START Equal operator                 / 0x01 \DESIGNER_END*/
   LDEM_enuOP_DIFF          = 0x0E, /**< \DESIGNER_START Different operator             / 0x0E \DESIGNER_END*/
   LDEM_enuOP_GREATER_THAN  = 0X32, /**< \DESIGNER_START Greater than operator          / 0X32 \DESIGNER_END*/
   LDEM_enuOP_LOWER_THAN    = 0x3D, /**< \DESIGNER_START Lower than operator            / 0x3D \DESIGNER_END*/
   LDEM_enuOP_GREATER_OR_EQ = 0x54, /**< \DESIGNER_START Greater than or equal operator / 0x54 \DESIGNER_END*/
   LDEM_enuOP_LOWER_OR_EQ   = 0x5B  /**< \DESIGNER_START lower than or equal operator   / 0x5B \DESIGNER_END*/
} LDEM_tenuDetectOperator;


#ifdef AUTOSAR_USED
#include "Rte_MFIC_Type.h"

#else
typedef enum {
   LDEM_enuDEFECT_ABSENT=0,
   LDEM_enuDEFECT_PRESENT=1
} LDEM_tenuDefectState;


typedef enum {
   LDEM_enuRUNNING=0,
   LDEM_enuFREEZED=1
} LDEM_tenuFreezeState;

#endif

typedef enum {
   LDEM_enuCounter_Only_Reset       =0,
   LDEM_enuTotal_Reset              =1,
   LDEM_enuCounter_Continue         =2
} LDEM_tenuUnfreezAction;

typedef enum {
   LDEM_enuREVERSIBLE=0,
   LDEM_enuIRREVERSIBLE=1
} LDEM_tenuIrreversibleState;


typedef enum {
   LDEM_enuMoreThan = 0 ,
   LDEM_enuMoreThOrEq = 1,
   LDEM_enuLessThan = 2 ,
   LDEM_enuLessThOrEq = 3,
   LDEM_enuEqualsTo = 4,

   /* Old operators left for backward compatibility */
   LDEM_enuRIGHTSIDE= 1,
   LDEM_enuLEFTSIDE= 3

} LDEM_tenuOperator;

/****************************************************************************/
/******************************** Structures ********************************/
/****************************************************************************/


typedef struct {
      /* Parameters */
      u16 u16Increment;
      u16 u16Decrement;
      u16 u16CounterThreshold;
      u16 u16ThresholdLow;
      u16 u16ThresholdHigh;

      LDEM_tenuIrreversibleState enuReverseState;
      LDEM_tenuOperator enuOperator;
      LDEM_tenuUnfreezAction enuUnfreezeAction;

      /* Intializations values */
      LDEM_tenuDefectState enuIntialState;
      u16 u16CounterInitialValue;
      LDEM_tenuFreezeState enuFreezeInitialValue;
} LDEM_tstrDefectConfig;

typedef struct {
      u16 u16Counter;
      LDEM_tenuDefectState enuValidState;
      LDEM_tenuDefectState enuInsState;
      LDEM_tenuFreezeState enuFreezeState;
      u16 u16Threshold;
} LDEM_tstrDefectValue;



typedef struct {
      const LDEM_tstrDefectConfig *pstrConfig;
      LDEM_tstrDefectValue  strValue;
} LDEM_tstrDefect;


/** \brief \DESIGNER_START Defect detection configuration for one threshold value.  \DESIGNER_END
 *   \details \DESIGNER_START Configuration of one threshold value to detect the defect \DESIGNER_END
 */
typedef struct {
      const s32 * kps32Threshold;                /**< \DESIGNER_START Constant pointer to the defect threshold value      / Type const u32*                    / Range [NA] / Resolution NA / Unit NA \DESIGNER_END*/
      const LDEM_tenuDetectOperator   kenuOp;    /**< \DESIGNER_START Constant variable that hold the the defect operator / Type const LDEM_tenuDetectOperator / Range [LDEM_enuDetectionType_NotSTD, LDEM_enuDetectionType_1D, LDEM_enuDetectionType_2D, LDEM_enuDetectionType_2DHyst, LDEM_enuDetectionType_2DInRange, LDEM_enuDetectionType_2DOutRange] / Resolution NA / Unit NA \DESIGNER_END*/
} LDEM_tstrDetectionConfig1D;

/** \brief \DESIGNER_START Defect detection configuration for two thresholds values.  \DESIGNER_END
 *   \details \DESIGNER_START Configuration of two thresholds value to detect the defect \DESIGNER_END
 */
typedef struct {
      const s32 * kps32Threshold1;               /**< \DESIGNER_START Constant pointer to the defect threshold 1 value                 / Type const u32*                    / Range [NA] / Resolution NA / Unit NA \DESIGNER_END*/
      const s32 * kps32Threshold2;               /**< \DESIGNER_START Constant pointer to the defect threshold 2 value                 / Type const u32*                    / Range [NA] / Resolution NA / Unit NA \DESIGNER_END*/
      const LDEM_tenuDetectOperator kenuOp1;     /**< \DESIGNER_START Constant variable that holds the defect operator of threshold 1  / Type const LDEM_tenuDetectOperator / Range [LDEM_enuOP_EQUALS, LDEM_enuOP_DIFF, LDEM_enuOP_GREATER_THAN, LDEM_enuOP_LOWER_THAN, LDEM_enuOP_GREATER_OR_EQ, LDEM_enuOP_LOWER_OR_EQ] / Resolution NA / Unit NA \DESIGNER_END*/
      const LDEM_tenuDetectOperator kenuOp2;     /**< \DESIGNER_START Constant variable that holds the defect operator of threshold 2  / Type const LDEM_tenuDetectOperator / Range [LDEM_enuOP_EQUALS, LDEM_enuOP_DIFF, LDEM_enuOP_GREATER_THAN, LDEM_enuOP_LOWER_THAN, LDEM_enuOP_GREATER_OR_EQ, LDEM_enuOP_LOWER_OR_EQ] / Resolution NA / Unit NA \DESIGNER_END*/
      const LDEM_tenuDetectionType  kenuDetectionType2D; /**< \DESIGNER_START Constant variable that holds the detection type          / Type const LDEM_tenuDetectionType  / Range [LDEM_enuDetectionType_NotSTD, LDEM_enuDetectionType_1D,LDEM_enuDetectionType_2D, LDEM_enuDetectionType_2DHyst, LDEM_enuDetectionType_2DInRange, LDEM_enuDetectionType_2DOutRange] / Resolution NA / Unit NA \DESIGNER_END*/
} LDEM_tstrDetectionConfig2D;


/****************************************************************************/
/****************************************************************************/
/***************************** Macro declarations ***************************/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/***************************** Define declarations **************************/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/***************************** Constant declarations ************************/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/***************************** Variable declarations ************************/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/***************************** Function declarations ************************/
/****************************************************************************/
/****************************************************************************/


extern LBTY_tenuErrorStatus LDEM_enuInitDefect(LDEM_tstrDefect *pstrDefect);

extern LBTY_tenuErrorStatus LDEM_enuUpdateDefect(LDEM_tstrDefect *pstrDefect, u16 u16ReadValue);

extern LBTY_tenuErrorStatus LDEM_enuGetVersionInfo(LBTY_tstrVersionInfoType *pstrVersionInfo);

extern LBTY_tenuErrorStatus LDEM_enuSetFreezingState(LDEM_tstrDefect *pstrDefect, LDEM_tenuFreezeState enuState);

extern LBTY_tenuErrorStatus LDEM_enuGetInsState  (const LDEM_tstrDefect *pstrDefect, LDEM_tenuDefectState *penuState);

extern LBTY_tenuErrorStatus LDEM_enuGetValidState  (const LDEM_tstrDefect *pstrDefect, LDEM_tenuDefectState *penuState);

extern LBTY_tenuErrorStatus LDEM_enuSetCntrParams(LDEM_tstrDefectConfig *pstrDefectConfig, u16 u16IncCpy, u16 u16DecCpy,
   u16 u16InitVal, u16 u16CtrTh );

extern LBTY_tenuErrorStatus LDEM_enuSetDfctValTh(LDEM_tstrDefectConfig *pstrDefectConfig, u16 u16LowThCpy,
   u16 u16HighThCpy);


extern LBTY_tenuErrorStatus LDEM_enuDefectDetection1D(
   LDEM_tstrDetectionConfig1D *pstrDetectionConfig, s32 s32ReadValue,
   LDEM_tenuDetectionStatus *penuDetectionStatus);

extern LBTY_tenuErrorStatus LDEM_enuDefectDetection2D(
   LDEM_tstrDetectionConfig2D *pstrDetectionConfig, s32 s32ReadValue,
   LDEM_tenuDetectionStatus *penuDetectionStatus);

#endif
