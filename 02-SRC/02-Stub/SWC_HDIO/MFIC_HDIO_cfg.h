/*
 * MFIC_HDIO_cfg.h
 *
 *  Created on: Jan 29, 2015
 *      Author: sragaai
 */

#ifndef MFIC_HDIO_CFG_H_
#define MFIC_HDIO_CFG_H_

#include "LBTY_int.h"
#include "LCTY_int.h"
#include "PLTF_MCU_F14_cfg.h"

/*________________________ DIO Abstraction Section __________________________*/
#ifdef PLTF_MCU_F14_DDIO
#include "DDIO_int.h"

#ifdef PLTF_MCU_F14_80PIN
#define MFIC_u8IO_PIN_1         (u8)DDIO_u8PIN_1
#define MFIC_u8IO_PIN_2         (u8)DDIO_u8PIN_2
#define MFIC_u8IO_PIN_3         (u8)DDIO_u8PIN_3
#define MFIC_u8IO_PIN_4         (u8)DDIO_u8PIN_4
#define MFIC_u8IO_PIN_5         (u8)DDIO_u8PIN_5
#define MFIC_u8IO_PIN_6         (u8)DDIO_u8PIN_6
#define MFIC_u8IO_PIN_7         (u8)DDIO_u8PIN_7
#define MFIC_u8IO_PIN_8         (u8)DDIO_u8PIN_8
#define MFIC_u8IO_PIN_9         (u8)DDIO_u8PIN_9
#define MFIC_u8IO_PIN_10        (u8)DDIO_u8PIN_10
#define MFIC_u8IO_ST_TI         (u8)DDIO_u8PIN_11
#define MFIC_u8IO_ST_TAIL_2P    (u8)DDIO_u8PIN_12
#define MFIC_u8IO_ST_TAIL_2T    (u8)DDIO_u8PIN_13
#define MFIC_u8IO_ST_TAIL_3T    (u8)DDIO_u8PIN_14
#define MFIC_u8IO_PIN_15        (u8)DDIO_u8PIN_15
#define MFIC_u8IO_PIN_16        (u8)DDIO_u8PIN_16
#define MFIC_u8IO_PIN_17        (u8)DDIO_u8PIN_17
#define MFIC_u8IO_PIN_18        (u8)DDIO_u8PIN_18
#define MFIC_u8IO_PIN_19        (u8)DDIO_u8PIN_19
#define MFIC_u8IO_PIN_20        (u8)DDIO_u8PIN_20
#define MFIC_u8IO_DUMMYTI       (u8)DDIO_u8PIN_21
#define MFIC_u8IO_PIN_22        (u8)DDIO_u8PIN_22
#define MFIC_u8IO_PIN_23        (u8)DDIO_u8PIN_23
#define MFIC_u8IO_PIN_24        (u8)DDIO_u8PIN_24
#define MFIC_u8IO_PIN_25        (u8)DDIO_u8PIN_25
#define MFIC_u8IO_PIN_26        (u8)DDIO_u8PIN_26
#define MFIC_u8IO_PIN_27        (u8)DDIO_u8PIN_27
#define MFIC_u8IO_PIN_28        (u8)DDIO_u8PIN_28
#define MFIC_u8IO_PIN_29        (u8)DDIO_u8PIN_29
#define MFIC_u8IO_EN_TI         (u8)DDIO_u8PIN_30
#define MFIC_u8IO_ENAREV        (u8)DDIO_u8PIN_31
#define MFIC_u8IO_EN_KL30G      (u8)DDIO_u8PIN_32
#define MFIC_u8IO_PIN_33        (u8)DDIO_u8PIN_33
#define MFIC_u8IO_PIN_34        (u8)DDIO_u8PIN_34
#define MFIC_u8IO_PIN_35        (u8)DDIO_u8PIN_35
#define MFIC_u8IO_PIN_36        (u8)DDIO_u8PIN_36
#define MFIC_u8IO_DUMMYTAIL     (u8)DDIO_u8PIN_37
#define MFIC_u8IO_PIN_38        (u8)DDIO_u8PIN_38
#define MFIC_u8IO_PIN_39        (u8)DDIO_u8PIN_39
#define MFIC_u8IO_PIN_40        (u8)DDIO_u8PIN_40
#define MFIC_u8IO_PIN_41        (u8)DDIO_u8PIN_41
#define MFIC_u8IO_PIN_42        (u8)DDIO_u8PIN_42
#define MFIC_u8IO_PIN_43        (u8)DDIO_u8PIN_43
#define MFIC_u8IO_PIN_44        (u8)DDIO_u8PIN_44
#define MFIC_u8IO_PIN_45        (u8)DDIO_u8PIN_45
#define MFIC_u8IO_HW_L_H        (u8)DDIO_u8PIN_46
#define MFIC_u8IO_HW_F_T        (u8)DDIO_u8PIN_47
#define MFIC_u8IO_HW_L_R        (u8)DDIO_u8PIN_48
#define MFIC_u8IO_HW_E_S        (u8)DDIO_u8PIN_49
#define MFIC_u8IO_PIN_50        (u8)DDIO_u8PIN_50
#define MFIC_u8IO_PIN_51        (u8)DDIO_u8PIN_51
#define MFIC_u8IO_PIN_52        (u8)DDIO_u8PIN_52
#define MFIC_u8IO_PIN_53        (u8)DDIO_u8PIN_53
#define MFIC_u8IO_PIN_54        (u8)DDIO_u8PIN_54
#define MFIC_u8IO_PIN_55        (u8)DDIO_u8PIN_55
#define MFIC_u8IO_PIN_56        (u8)DDIO_u8PIN_56
#define MFIC_u8IO_PIN_57        (u8)DDIO_u8PIN_57
#define MFIC_u8IO_PIN_58        (u8)DDIO_u8PIN_58
#define MFIC_u8IO_PIN_59        (u8)DDIO_u8PIN_59
#define MFIC_u8IO_PIN_60        (u8)DDIO_u8PIN_60
#define MFIC_u8IO_PIN_61        (u8)DDIO_u8PIN_61
#define MFIC_u8IO_PIN_62        (u8)DDIO_u8PIN_62
#define MFIC_u8IO_PIN_63        (u8)DDIO_u8PIN_63
#define MFIC_u8IO_BL1TI         (u8)DDIO_u8PIN_64
#define MFIC_u8IO_BL2TI         (u8)DDIO_u8PIN_65
#define MFIC_u8IO_BL3TI         (u8)DDIO_u8PIN_66
#define MFIC_u8IO_BL4TI         (u8)DDIO_u8PIN_67
#define MFIC_u8IO_BL5TI         (u8)DDIO_u8PIN_68
#define MFIC_u8IO_ENATAIL       (u8)DDIO_u8PIN_69
#define MFIC_u8IO_EN_STOP       (u8)DDIO_u8PIN_70
#define MFIC_u8IO_ENA_1_STOP    (u8)DDIO_u8PIN_71
#define MFIC_u8IO_PIN_72        (u8)DDIO_u8PIN_72
#define MFIC_u8IO_PIN_X         (u8)DDIO_u8PIN_73
#define MFIC_u8IO_PIN_Y         (u8)DDIO_u8PIN_74
#define MFIC_u8IO_PIN_75        (u8)DDIO_u8PIN_75
#define MFIC_u8IO_PIN_76        (u8)DDIO_u8PIN_76
#define MFIC_u8IO_PIN_77        (u8)DDIO_u8PIN_77
#define MFIC_u8IO_PIN_78        (u8)DDIO_u8PIN_78
#define MFIC_u8IO_PIN_79        (u8)DDIO_u8PIN_79
#define MFIC_u8IO_PIN_80        (u8)DDIO_u8PIN_80
#endif
/*********************** Number of Digital In-Out Pins ***********************/
#define MFIC_u8IO_PIN_NB        (u8)DDIO_u8NBR_PIN
/*****************************************************************************/

/************************* Digital In-Out Levels *****************************/
#define MFIC_u8IO_PIN_HIGH      (u8)DDIO_u8VALUE_HIGH
#define MFIC_u8IO_PIN_LOW       (u8)DDIO_u8VALUE_LOW

/************************* Define controller Ports****************************/

#define MFIC_u8PORT_0           DDIO_u8PORT_0
#define MFIC_u8PORT_1           DDIO_u8PORT_1
#define MFIC_u8PORT_3           DDIO_u8PORT_3
#define MFIC_u8PORT_4           DDIO_u8PORT_4
#define MFIC_u8PORT_5           DDIO_u8PORT_5
#define MFIC_u8PORT_6           DDIO_u8PORT_6
#define MFIC_u8PORT_7           DDIO_u8PORT_7
#define MFIC_u8PORT_8           DDIO_u8PORT_8
#define MFIC_u8PORT_9           DDIO_u8PORT_9
#define MFIC_u8PORT_12          DDIO_u8PORT_12
#define MFIC_u8PORT_13          DDIO_u8PORT_13
#define MFIC_u8PORT_14          DDIO_u8PORT_14
#define MFIC_u8PORT_NB          DDIO_u8PORT_NB
/***************************** DIO Interfaces ********************************/

/* Get value of I/O pin                                                      */
#define MFIC_stdGetIoPinValue    DDIO_enuGetPinVal

/* Set value of I/O pin                                                      */
#define MFIC_stdSetIoPinValue(u8ioPin)\
        DDIO_enuSetPin((u8ioPin))

/* Reset value of I/O pin                                                    */
#define MFIC_stdRstIoPinValue(ioPin )\
        DDIO_enuRstPin((ioPin))

/* Toggle value of I/O pin                                                    */
#define MFIC_stdToggleIoPinValue(ioPin )\
		DDIO_enuTogglepin((ioPin))
/* Update value of I/O port                                                  */
#define MIFC_stdSetIoPortValue(port, value)\
        DDIO_enuSetPortVal((port), (value))

/* Get value of I/O port                                                     */
#define MFIC_stdGetIoPortValue(pu8ValOutLatch, port)\
        DDIO_enuGetPortVal ( (port),(pu8ValOutLatch))
/*****************************************************************************/

/*_____________________ End of DIO Abstraction Section ______________________*/
/*___________________________________________________________________________*/
#endif
/*________________________ End of DIO Abstraction __________________________*/
/*___________________________________________________________________________*/

#endif /* MFIC_HDIO_CFG_H_ */
