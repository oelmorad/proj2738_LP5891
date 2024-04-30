/******************************************************************************/
/* !Layer           : HAL                                                     */
/*                                                                            */
/* !Component       : HDIO                                                    */
/* !Description     : Digital input Manager                                   */
/*                                                                            */
/* !Module          : HDIO_int.h                                              */
/* !Revision        : 1.3                                                     */
/* !Date            : 23 Nov 2020                                             */
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
/* Ahmed Assaf  -- 9  MAR 2017    Public and private configurations           */
/* Soha Wagdy  --  13/ 1 /2019 -- Update code after applying MISRA            */
/*             --              -- issues remarks                              */
/* Soha Wagdy  -- 10/12/2019   -- Fix Mandatory KL issues                     */
/* Soha Wagdy  -- 23 Nov 2020  -- Updates for the following ACRs:             */
/*                                  [artf1067933 artf267567 artf794236 ]      */
/*             --              --                                             */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Assaf                         !Date : 28 NOV 2016 */
/* !Coded by        : Ahmed Assaf                         !Date : 28 NOV 2016 */
/*                                                                            */
/******************************************************************************/

#ifndef HDIO_INT_H
#define HDIO_INT_H

/*****************************************************************************/
/********************************** zone define ******************************/
/*****************************************************************************/

/******************************************************************************/
/* !Comment  : Digital input/output state                                     */
/******************************************************************************/
#define HDIO_OFF          ((u8)0)
#define HDIO_ON           ((u8)1)
#define HDIO_UNDEFINED    ((u8)2)

/******************************************************************************/
/*                              Function zone                                 */
/******************************************************************************/

/******************************************************************************/
/* !Description : This function shall Initialize the HDIO Parameters          */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/******************************************************************************/
void HDIO_vidInit(void);

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Read DIO pins and apply the filteration mechanism         */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
void HDIO_vidRunnableUpdateInput(void);
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Refresh the output pins                                   */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
void HDIO_vidRunnableUpdateOutput(void);
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Return Fault notification to user SWC for                 */
/*      plausibility checks to Output signals                                 */
/* !Input       : None                                                        */
/* !Output      : None                                                        */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
#if HDIO_OUT_PLAUSIBILITY_CHECK == HDIO_ENABLED
void HDIO_vidRunnableReadOutput(void);
#endif
#endif

/******************************************************************************/
/* !Description : This function return the HDIO software version information  */
/* !Input       : pstrVersionInfo -> Pointer to return the version information*/
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
LBTY_tenuErrorStatus HDIO_enuGetVersionInfo(LBTY_tstrVersionInfoType* pstrVersionInfo);

/******************************************************************************/
/* !Description : This function shall get the unfiltered state for input      */
/*                digital pin                                                 */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the unfiltered state   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputUnfiltered(u8 u8InputIdCpy, u8 *pu8SigStateCpy);
#endif

/******************************************************************************/
/* !Description : This function shall get the unfiltered one shot state for   */
/*                input digital pin                                           */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the unfiltered state   */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputOneShot(u8 u8InputIdCpy, u8 *pu8SigStateCpy);
#endif

/******************************************************************************/
/* !Description : This function shall get the filtered state for input        */
/*                digital pin                                                 */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy  -> Pointer to return the filtered state     */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetInputfiltered(u8 u8InputIdCpy, u8 *pu8SigStateCpy);
#endif

/******************************************************************************/
/* !Description : Get HDIO Input Pin defect status                            */
/* !Input       : u8IdCpy -> Index of defect                                  */
/*                penuDefect -> Pointer to return the status in it            */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuGetDefectState(u8 u8IdCpy, LDEM_tenuDefectState *penuDefect);
#endif

/******************************************************************************/
/* !Description : Freeze/Unfreeze defect for Input pins defects               */
/* !Input       : u8IdCpy  -> Index of the defect                             */
/*                enuState -> Required freezing state                         */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuSetFreezeDfctState(u8 u8IdCpy, LDEM_tenuFreezeState enuState);
#endif

/******************************************************************************/
/* !Description : Reset Input pins defects                                    */
/* !Input       : u8IdCpy  -> Index of the defect                             */
/* !Output      : LBTY_tenuErrorStatus -> operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_INPUT
LBTY_tenuErrorStatus HDIO_enuResetDefect(u8 u8IdCpy);
#endif

/******************************************************************************/
/* !Description : This function shall set the digital state for output pin    */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                u8SigStateCpy-> Required digital state                      */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
LBTY_tenuErrorStatus HDIO_enuSetOutputState(u8 u8OutputIdCpy, u8 u8SigStateCpy);
#endif

/******************************************************************************/
/* !Description : This function shall get the digital state for output pin    */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8SigStateCpy-> pointer to the digital state               */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
LBTY_tenuErrorStatus HDIO_enuGetOutputState(u8 u8OutputIdCpy, u8* pu8SigStateCpy);
#endif

/******************************************************************************/
/* !Description : This function shall do the following:                       */
/*                - Return Fault Flag for Output signals check                */
/* !Input       : u8InputIdCpy -> Channel Index                               */
/*                pu8FaultFlagCpy-> pointer to the Flag state                 */
/* !Output      : LBTY_tenuErrorStatus -> Operation status                    */
/* !Scope       : Public                                                      */
/* !Trace_To    :                                                             */
/******************************************************************************/
#ifdef BSW_HDIO_OUTPUT
LBTY_tenuBoolean HDIO_enuGetOutputFault(void);
#endif
#endif /* HDIO_INT_H */
/*************************** E N D (HDIO_int.c) ******************************/
