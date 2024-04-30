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
 *             File:  Rte_MFIC_Type.h
 *           Config:  Hepta.dpa
 *      ECU-Project:  Hepta
 *
 *        Generator:  MICROSAR RTE Generator Version 4.24.0
 *                    RTE Core Version 1.24.0
 *          License:  PAI2633
 *
 *      Description:  Application types header file for SW-C <MFIC>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_MFIC_TYPE_H
# define RTE_MFIC_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef LBTY_TRUE
#   define LBTY_TRUE (85U)
#  endif

#  ifndef LBTY_FALSE
#   define LBTY_FALSE (170U)
#  endif

#  ifndef LBTY_OK
#   define LBTY_OK (0U)
#  endif

#  ifndef LBTY_NOK
#   define LBTY_NOK (1U)
#  endif

#  ifndef LBTY_NULL_POINTER
#   define LBTY_NULL_POINTER (2U)
#  endif

#  ifndef LBTY_INDEX_OUT_OF_RANGE
#   define LBTY_INDEX_OUT_OF_RANGE (3U)
#  endif

#  ifndef LBTY_NO_MASTER_CHANNEL
#   define LBTY_NO_MASTER_CHANNEL (4U)
#  endif

#  ifndef LBTY_READ_ERROR
#   define LBTY_READ_ERROR (5U)
#  endif

#  ifndef LBTY_WRITE_ERROR
#   define LBTY_WRITE_ERROR (6U)
#  endif

#  ifndef LBTY_UNDEFINED_ERROR
#   define LBTY_UNDEFINED_ERROR (7U)
#  endif

#  ifndef LBTY_IN_PROGRESS
#   define LBTY_IN_PROGRESS (8U)
#  endif

#  ifndef LBTY_INITIALIZED
#   define LBTY_INITIALIZED (0U)
#  endif

#  ifndef LBTY_IDLE
#   define LBTY_IDLE (1U)
#  endif

#  ifndef LBTY_BUSY
#   define LBTY_BUSY (2U)
#  endif

#  ifndef LBTY_UNINITIALIZED
#   define LBTY_UNINITIALIZED (3U)
#  endif

#  ifndef LBTY_DEFECT
#   define LBTY_DEFECT (4U)
#  endif

#  ifndef LBTY_FAILSAFE
#   define LBTY_FAILSAFE (5U)
#  endif

#  ifndef LBTY_OFF
#   define LBTY_OFF (6U)
#  endif

#  ifndef LDEM_enuDEFECT_ABSENT
#   define LDEM_enuDEFECT_ABSENT (0U)
#  endif

#  ifndef LDEM_enuDEFECT_PRESENT
#   define LDEM_enuDEFECT_PRESENT (1U)
#  endif

#  ifndef LDEM_enuRUNNING
#   define LDEM_enuRUNNING (0U)
#  endif

#  ifndef LDEM_enuFREEZED
#   define LDEM_enuFREEZED (1U)
#  endif

# endif /* RTE_CORE */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_MFIC_TYPE_H */
