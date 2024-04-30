/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HPWM                                                    */
/* !Description     : Pulse width modulation driver                           */
/*                                                                            */
/* !Module          : HPWM_int.h                                              */
/* !Revision        : 1.5                                                     */
/* !Date            : 27 Dec 2020                                             */
/*                                                                            */
/* !Scope           : Program                                                 */
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
/*    Author   --     Date    --          Modification                        */
/* Ahmed Assaf -- 24 OCT 2016 -- Initial Creation                             */
/* MDESOKY     -- 03 MAR 2017 -- Add calculations of PWM and ICU              */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Ahmed Abdelmageed                                                          */
/*                 08/ 4 / 2019   added conditional macros to protect against */
/*                                unused variable compiler warnings           */
/* Soha Wagdy  --  10/12/2019  -- Fix Mandatory KL issues                     */
/* Ahmed Ramadan-- 8 Nov 2020  -- Min frequency detection ACR [artf1104778 ]  */
/* Soha Wagdy  --  27 Dec 2020 -- Fixing APR [artf1162990] for Mean Filter    */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 24 OCT 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 24 OCT 2016 */
/*                                                                            */
/******************************************************************************/

#ifndef HPWM_INT_H
#define HPWM_INT_H

// #include "HPWM_cfg.h"
/*****************************************************************************/
/********************************* zone type_def *****************************/
/*****************************************************************************/

/* !Comment : maximum duty cycle of HPWM */
#define HPWM_u16MAXIMMUM_DUTY_CYCLE             ((u16)0x2710)

/* !Comment : Default period to return when channel is Defect, Period = 0*/
#define HPWM_u16DEFECT_PER_VAL                  ((u16)0x0000U)

/* !Comment : Default duty to return when channel is defect. Duty > 100% (0xFFFF) */
#define HPWM_u16DEFECT_DUTY_VAL                 ((u16)0xFFFFU)

/*****************************************************************************/
/********************************** zone macro *******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone constant *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone struct/union *************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone variable *****************************/
/*****************************************************************************/

/*****************************************************************************/
/********************************* zone function *****************************/
/*****************************************************************************/


/******************************************************************************/
/* !Description : Initialize component parameters                             */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void HPWM_vidInit(void);

#ifdef BSW_PWM_IN
/******************************************************************************/
/* !Description : update input PWM value and apply filtration                 */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void HPWM_vidRunnable(void);
#endif /* BSW_PWM_IN */

/******************************************************************************/
/* !Description : This function return the HPWM software version information  */
/* !Input       : pVersionInfo -> Pointer to return the version information   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetVersionInfo(LBTY_tstrVersionInfoType *pVersionInfo);

#ifdef BSW_PWM_OUT
/******************************************************************************/
/* !Description : refresh output PWM value                                    */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
void HPWM_vidRefreshOutputDutyRunnable(void);

/******************************************************************************/
/* !Description : Set duty cycle for output PWM channel                       */
/* !Input       : u8ChannelCpy    -> Channel index                            */
/*                u16DutyCycleCpy -> Duty cycle value to set                  */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuSetOutDutyCycle (u8 u8ChannelCpy, u16 u16DutyCycleCpy);

/******************************************************************************/
/* !Description : Set duty and period for output PWM channel                  */
/* !Input       : u8ChannelCpy    -> Channel index                            */
/*                u32PeriodCpy    -> Period value to set                      */
/*                u16DutyCpy      -> Duty to be set                           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuSetOutPeriodAndDuty(u8 u8ChannelCpy, u16 u16PeriodCpy, u16 u16DutyCpy);
#endif /* BSW_PWM_OUT */

#ifdef BSW_PWM_IN
/******************************************************************************/
/* !Description : Get duty cycle for input PWM channel                        */
/* !Input       : u8ChannelCpy -> Channel index                               */
/*                pu16DutyCpy  -> Pointer to return duty cycle value          */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetInDutyCycle (u8 u8ChannelCpy, u16* pu16DutyCpy);

/******************************************************************************/
/* !Description : Get Period for input PWM channel                            */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu32PeriodCpy   -> Pointer to return period value           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetInPeriod(u8 u8ChannelCpy, u32* pu32PeriodCpy);

/******************************************************************************/
/* !Description : Get filtered duty cycle for input PWM channel               */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu16DutyCpy   -> Pointer to return duty cycle value         */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetFilteredInDuty(u8 u8ChannelCpy, u16* pu16DutyCpy);


/******************************************************************************/
/* !Description : Get filtered Period for input PWM channel                   */
/* !Input       : u8ChannelCpy  -> Channel index                              */
/*                pu32PeriodCpy   -> Pointer to return period value           */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
LBTY_tenuErrorStatus HPWM_enuGetFilteredInPeriod(u8 u8ChannelCpy, u32* pu32PeriodCpy);
#endif /* BSW_PWM_IN */


#endif /* HPWM_INT_H */

/************************** E N D (HPWM_int.h) ********************************/
