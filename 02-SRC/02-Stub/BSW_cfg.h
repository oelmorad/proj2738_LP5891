/*
 * BSW_cfg.h
 *
 *  Created on: Oct 15, 2018
 *      Author: wkadry1
 */

#ifndef BSW_CFG_H_
#define BSW_CFG_H_

/** \brief \DESIGNER_START Define that activate the DIO PINs Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_HDIO] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_HDIO

/** \brief \DESIGNER_START Define that activate the DIO PINs Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_HDIO] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_HDIO_OUTPUT


/** \brief \DESIGNER_START Define that activate the PWM Input/Output Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_HPWM] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_HPWM

/** \brief \DESIGNER_START Define that activate the PWM Input/Output Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_HPWM] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_PWM_OUT

/** \brief \DESIGNER_START Define that activate the Double inverse storage Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_SSAF] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_HSPM

/** \brief \DESIGNER_START Define that activate the Double inverse storage Manager Module \DESIGNER_END
 *   \details \DESIGNER_START NA / Range [BSW_SSAF] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_HLP5891


/** \brief \DESIGNER_START Enable LDEM Defect management \DESIGNER_END
*   \details \DESIGNER_START u8 / Range [0x55] / Resolution 1 / Unit NA \DESIGNER_END */
#define PLTF_DEFECT_LDEM         0x55U
/** \brief \DESIGNER_START Enable Defect Handler management \DESIGNER_END
*   \details \DESIGNER_START u8 / Range [0xAA] / Resolution 1 / Unit NA \DESIGNER_END */
#define PLTF_DEFECT_HANDLER      0xAAU
/** \brief \DESIGNER_START Enable Defect Handler management \DESIGNER_END
 *   \details \DESIGNER_START u8 / Range [0xAA] / Resolution 1 / Unit NA \DESIGNER_END */
#define PLTF_DEFECT_OFF      0xDDU
/** \brief \DESIGNER_START Define LDEM Defect management or Defect Handler management \DESIGNER_END
*   \details \DESIGNER_START u8 / Range [PLTF_DEFECT_LDEM,PLTF_DEFECT_HANDLER] / Resolution NA / Unit NA \DESIGNER_END */
#define PLTF_DEFECTMNG           PLTF_DEFECT_LDEM

#if (PLTF_DEFECTMNG ==  PLTF_DEFECT_HANDLER)
/** \brief \DESIGNER_START Define that activate the defect handler manager \DESIGNER_END
*   \details \DESIGNER_START NA / Range [BSW_YDEMX] / Resolution NA / Unit NA \DESIGNER_END */
#define BSW_YDEMx


#endif /*PLTF_DEFECTMNG*/


#endif /* BSW_CFG_H_ */
