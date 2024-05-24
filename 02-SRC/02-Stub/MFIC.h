/*
 * MFIC.h
 *
 *  Created on: Jan 29, 2015
 *      Author: sragaai
 */

#ifndef MFIC_H_
#define MFIC_H_

/***************************************************************** END OF Project Signals Configuration *********************************************************************/


/*__________________________ DIO Abstraction Section ________________________*/
/*___________________________________________________________________________*/
/*__________________________ DIO Output Pin Section _________________________*/

#define DIO_CHANNEL_2_3    (0x23U)

extern LBTY_tenuErrorStatus MFIC_stdWritePinValue(u16 u16PinCpy,u8 u8PinValue);

/*___________________________________________________________________________*/
/*______________________End of DIO Abstraction Section ______________________*/










/*___________________________________________________________________________*/
/*_____________________START SPI Abstraction Section ________________________*/
/*___________________________________________________________________________*/



#define MFIC_u32SPI_CHANNEL0    (0x01U)



typedef
void (*tpfvidspiUsrJobCallBck)
(u16 u16UsrSgntrCpy, LBTY_tenuErrorStatus enuErrStat);





LBTY_tenuErrorStatus MFIC_enuSpiWrReq(u8 u8ChannelIdCpy,
   u16 *pu16UsrTxBuffCpy,
   u16 *pu16UsrRecvBuffCpy,
   u8 u8JobLengthCpy,
   tpfvidspiUsrJobCallBck pfUsrJobStartNotfCpy,
   tpfvidspiUsrJobCallBck pfUsrJobEndNotfCpy,
   u16 u16UsrSgntrCpy);



/*___________________________________________________________________________*/
/*_______________________END SPI Abstraction Section ________________________*/
/*___________________________________________________________________________*/







#endif /* MFIC_H_ */
