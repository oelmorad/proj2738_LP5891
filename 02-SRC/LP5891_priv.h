/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LP5891_priv.h
*  Component: \SWC_LP5891
*  \brief     \DESIGNER_START Abstraction layer between APP. and LED Matrix Driver \DESIGNER_END
*  \n\n
*  Scope: Private
*  \n\n
*  Coding language : C
*    \copydoc _privh
*  \copydoc COPYRIGHT
*/
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _privh LP5891_priv.h History
*     | File             | Version      | Status              | Description |
*     | :-------------:  | :----------: | :-----------------: | :----------
*     |  Refer to SCM tool history log for older versions details and comments ||||
*     | LP5891_priv.h      | 1.0          | Proposed            | \verbatim $Rev::             $: Revision of last commit \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Date::           #$: Date of last commit     \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Author::          $: Author of last commit   \endverbatim |
*/
/* ************************************************************************** */
/* ************************* HEADER PROTECTION ****************************** */
/* ************************************************************************** */
#ifndef LP5891_PRIV_H
#define LP5891_PRIV_H
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/******************************************************************************/
/* !Comment  : Definition of the value of Null pointer                        */
/******************************************************************************/
#define LP5891_NULL               ((void*)0)


/** \brief \DESIGNER_START zero value casted with u8  \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-0xFF] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u8MIN  (u8)0

/** \brief \DESIGNER_START zero value casted with u16  \DESIGNER_END
*   \details \DESIGNER_START Type u16 / Range [0-0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u16MIN  (u16)0

/** \brief \DESIGNER_START Start element in loop \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-255] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u8LoopStartIdx  (u8)0


/** \brief \DESIGNER_START Start element in loop \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-255] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u8FrameIDLEBytes  (u8)0xFF

/** \brief \DESIGNER_START Start element in loop \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-255] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u8FrameSTARTByte  (u8)0xFE

/** \brief \DESIGNER_START Start element in loop \DESIGNER_END
*   \details \DESIGNER_START Type u8 / Range [0-255] / Resolution 1 / Unit NA \DESIGNER_END*/
#define LP5891_u8FrameENDByte  (u8)0xFF


/** \brief \DESIGNER_START IMAGE Start Key  \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u16STARTKEY_PATTERN         ((u16)0xA5A5)

/** \brief \DESIGNER_START IMAGE Start Key  \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u16ENDKEY_PATTERN         ((u16)0xA5A5)

/** \brief \DESIGNER_START IMAGE Start Key index  \DESIGNER_END
 *   \details \DESIGNER_START Type: NA / Range :[0, 6] / Resolution: index \DESIGNER_END
 */
#define LP5891_u32STARTKEY_INDEX         ((u32)0)



//#define send_frame(frame) LPSPI_DRV_MasterTransfer(LPSPICOM1,frame,NULL,sizeof(frame))
#define SB 0xFFFe
#define _FC0_2 ((LSD_RM_EN_0 | GRP_DLY_B_0 | GRP_DLY_G_0 | GRP_DLY_R_0 | FREQ_MUL__1) >> 32) & 0xFFFF
#define _FC0_1 ((FREQ_MUL__1 | FREQ_MOD__LF | SUBP_NUM__128 | SCAN_NUM__33) >> 16) & 0xFFFF
#define _FC0_0 ((LODRM_EN_0 | PSP_MOD_0 | PS_EN_0 | PDC_EN_0 | CHIP_NUM__12)) & 0xFFFF


#define _FC1_2 ((BLK_ADJ_0 | LINE_SWT__480 | LG_ENH_B_2 | LG_ENH_G_15) >> 32) & 0xFFFF
#define _FC1_1 ((LG_ENH_G_15 | LG_ENH_R_1 | LG_STEP_B__6 | LG_STEP_G__6) >> 16) & 0xFFFF
#define _FC1_0 ((LG_STEP_G__6 | LG_STEP_R__6 | SEG_LENGTH__128)) & 0xFFFF


#define _FC2_2 ((MPSM_EN_0 | MOD_SIZE_4 | SUBP_MAX_256_0 | CH_B_IMMUNITY_0 | CH_G_IMMUNITY_0 | CH_R_IMMUNITY_0 | LG_COLOR_B__14) >> 32) & 0xFFFF
#define _FC2_1 ((LG_COLOR_G__14 | LG_COLOR_R__1 | DE_COUPLE1_B__4 | DE_COUPLE1_G__4) >> 16) & 0xFFFF
#define _FC2_0 ((DE_COUPLE1_R__1 | V_PDC_B__0V1 | V_PDC_G__0V1 | V_PDC_R__0V1)) & 0xFFFF


#define _FC3_2 ((LSDVTH_B__0V2 | LSDVTH_G__0V2 | LSDVTH_R__0V2 | LSD_RM__16 | BC_7) >> 32) & 0xFFFF
#define _FC3_1 ((CC_B_64 | CC_G_85) >> 16) & 0xFFFF
#define _FC3_0 ((CC_R_143 | LOD_LSD_RB_1 | LODVTH_B__0V2 | LODVTH_G__0V2 | LODVTH_R__0V2)) & 0xFFFF


#define _FC4_2 ((DE_COUPLE3_EN_0 | DE_COUPLE3__1 | DE_COUPLE2_0 | FIRST_LINE_DIM__1 | CAURSE_B_1 | CAURSE_G_1 | CAURSE_R_1) >> 32) & 0xFFFF
#define _FC4_1 ((SR_ON_B_0 | SR_ON_G_0 | SR_ON_R_0 | SR_OFF_B_1 | SR_OFF_G_1 | SR_OFF_R_1 | FINE_B_1 | FINE_G_1 | FINE_R_1) >> 16) & 0xFFFF
#define _FC4_0 ((IMAX_1)) & 0xFFFF


/* ************************************************************************** */
/* ************************* TYPE_DEF/STRUCT SECTION ************************ */
/* ************************************************************************** */
/******************************************************************************/
/* !Description : This type enumerates commands                               */
/******************************************************************************/
typedef enum
{
  LBTI_CMD_RD           = (u8)0x00,     /* Read command                       */
  LBTI_CMD_WR           = (u8)0x01      /* Write command                      */
} LBTI_tenuCmd;


enum WRITE_COMMAND_ID{
    W_FC0 = 0xAA00,
    W_FC1,
    W_FC2,
    W_FC3,
    W_FC4,
    W_FC14 = 0xAA0E,
    W_FC15,
    W_CHIP_INDEX = 0xAA10,
    W_VSYNC = 0XAAF0,
    W_SOFT_RESET = 0XAA80,
    W_SRAM = 0xAA30
};


enum READ_COMMAND_ID{
    R_FC0 = 0xAA60,
    R_FC1,
    R_FC2,
    R_FC3,
    R_FC4,
    R_FC14 = 0xAA6E,
    R_FC15,
    R_FC16 = 0xAAA0,
    R_FC17,
    R_FC18,
    R_FC19,
    R_FC20,
    R_FC21,
    R_CHIP_INDEX = 0xAA70
};



typedef union {
    u16 u16UniColorData;
    struct {
        unsigned int Bit0 : 1;
        unsigned int Bit1 : 1;
        unsigned int Bit2 : 1;
        unsigned int Bit3 : 1;
        unsigned int Bit4 : 1;
        unsigned int Bit5 : 1;
        unsigned int Bit6 : 1;
        unsigned int Bit7 : 1;
        unsigned int Bit8 : 1;
        unsigned int Bit9 : 1;
        unsigned int Bit10 : 1;
        unsigned int Bit11 : 1;
        unsigned int Bit12 : 1;
        unsigned int Bit13 : 1;
        unsigned int Bit14 : 1;
        unsigned int Bit15 : 1;
    };
} RGB_tstrUniColor;



/** \brief \DESIGNER_START RGB Pixel Data   \DESIGNER_END
 *   \details \DESIGNER_START Type u8 / Range [0xFFFF] / Resolution NA / Unit NA \DESIGNER_END*/
typedef struct  {
    RGB_tstrUniColor LED_REDx;
    RGB_tstrUniColor LED_GREENx;
    RGB_tstrUniColor LED_BLUEx;
} RGB_tstrPixelData;




/** \brief \DESIGNER_START Component software state machine \DESIGNER_END */

typedef enum
{
   LP5891_UNINITIALIZED = 0x10, /**< \DESIGNER_START state  \DESIGNER_END*/
   LP5891_INITIALIZED = 0x20, /**< \DESIGNER_START state  \DESIGNER_END*/
   LP5891_IDLE = 0x30, /**< \DESIGNER_START state  \DESIGNER_END*/
   LP5891_OPERATION_MODE = 0x40, /**< \DESIGNER_START state  \DESIGNER_END*/
   LP5891_SLEEP = 0x50, /**< \DESIGNER_START state  \DESIGNER_END*/
   LP5891_DEFECT = 0x60/**< \DESIGNER_START state  \DESIGNER_END*/
} LP5891_tenuWorkingStatus;


/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */
static LBTY_tenuErrorStatus vidDrvInitFrame(u8 Driver) ;
static LBTY_tenuErrorStatus vidSendSyncFrame(u8 Driver) ;
static LBTY_tenuErrorStatus vidSendSWResetFrame(u8 Driver);
static LBTY_tenuErrorStatus vidSendPixelFrame(u8 Driver, u32 u32pixelNo) ;
static RGB_tstrPixelData vidGetPixel(u8 Driver, u32 u32pixelNo) ;

#endif /* LP5891_PRIV_H */
/* *********************** E N D (LP5891_priv.h) ************************** */
