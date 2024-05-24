/*****************************************************************************/
/* !Layer          : Service Layer                                           */
/*                                                                           */
/* !Component      :                                                      */
/* !Description    :                                                         */
/*                                                                           */
/* !Module         : Stub.c                                               */
/*                                                                           */
/* !Scope          : stub                                    */
/*                                                                           */
/* !Vendor         : Valeo                                                   */
/*                                                                           */
/* !Coding language : C                                                      */
/* !Project         :                                                        */
/* !Target          : NXPS32K1xx                                             */
/*                                                                           */
/* !COPYRIGHT 2018 VALEO LIGHTING SYSTEM                                     */
/* all rights reserved                                                       */
/*                                                                           */
/*****************************************************************************/
#include "BSW_cfg.h"

#include "LBTY_int.h"
#include "SDET_int.h"

#include "MFIC.h"

#include "HDIO_int.h"
#include "HPWM_int.h"
#include "HSPM_int.h"

void  SDET_vidReportError
(u16 ModuleID, u8 PltfID, u8 ApiId, u8 ErrorId)
{
    return ;
}



LBTY_tenuErrorStatus HDIO_enuSetOutputState(u8 u8OutputIdCpy, u8 u8SigStateCpy)
{

    return 0 ;
}



LBTY_tenuErrorStatus HPWM_enuSetOutDutyCycle (u8 u8ChannelCpy, u16 u16DutyCycleCpy)
{

    return 0 ;
}



LBTY_tenuErrorStatus MFIC_stdWritePinValue(u16 u16PinCpy,u8 u8PinValue)
{
    return 0 ;
}





LBTY_tenuErrorStatus MFIC_enuSpiWrReq(
    /* !Comment : Channel ID                                                  */
    u8 u8ChannelIdCpy             ,
    /* !Comment : User TX Buffer                                              */
    u16* pu16UsrTxBuffCpy         ,
    /* !Comment : User RX Buffer                                              */
    u16* pu16UsrRecvBuffCpy       ,
    /* !Comment : Job Length (No of Frames)                                   */
    u8 u8JobLengthCpy             ,
    /* !Comment : User Job Start Call Back Notification Function                */
    tpfvidspiUsrJobCallBck pfUsrJobStartNotfCpy,
    /* !Comment : User Job End Call Back Notification Function                */
    tpfvidspiUsrJobCallBck pfUsrJobEndNotfCpy,
    /* !Comment : User Call Back Signature                                    */
    u16 u16UsrSgntrCpy
)
{

    return 0 ;
}




LBTY_tenuErrorStatus
HSPM_enuSpiJobRqst(
    /* !Comment : Channel ID                                                  */
    u8 u8ChannelIdCpy             ,
    /* !Comment : User TX Buffer                                              */
    u16* pu16UsrTxBuffCpy         ,
    /* !Comment : User RX Buffer                                              */
    u16* pu16UsrRecvBuffCpy       ,
    /* !Comment : Job Length (No of Frames)                                   */
    u8 u8JobLengthCpy             ,
    /* !Comment : User Job Start Call Back Notification Function                */
    tpfvidHspmUsrJobCallBck pfUsrJobStartNotfCpy,
    /* !Comment : User Job End Call Back Notification Function                */
    tpfvidHspmUsrJobCallBck pfUsrJobEndNotfCpy,
    /* !Comment : User Call Back Signature                                    */
    u16 u16UsrSgntrCpy
)
{

    return 0 ;
}

