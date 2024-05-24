/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/** \file LP5891_prg.c
 *  Component: \SWC_LP5891
 *  \brief     \DESIGNER_START Abstraction layer between App. & LED Matrix Driver \DESIGNER_END
 *  \n\n
 *  Scope: Private
 *  \n\n
 *  Coding language : C
 *    \copydoc _prgc
 *  \copydoc COPYRIGHT
 */
/* ************************************************************************** */
/* ********************** MODIFICATION LOG SECTION ************************** */
/* ************************************************************************** */
/** \page _prgc LP5891_prg.c History
 *     | File             | Version      | Status              | Description |
 *     | :-------------:  | :----------: | :-----------------: | :----------
 *     |  Refer to SCM tool history log for older versions details and comments ||||
 *     | LP5891_prg.c       | 1.0          | Proposed            | Initial creation            
*     |                  |              |                     | \verbatim $Rev::  1.0           $: Revision of last commit \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Date:: 24 May 2024          #$: Date of last commit     \endverbatim |
*     | ^                | ^            | ^                   | \verbatim $Author:: oelmorad          $: Author of last commit   \endverbatim |
*/
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "BSW_cfg.h"

#include "LFIC_LP5891_cfg.h"
#include "MFIC_LP5891_cfg.h"
#include "HFIC_LP5891_cfg.h"

#include "LP5891.h"
#include "LP5891_priv.h"
#include "LP5891_int.h"




/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
static const u8 LP5891_u8ResetFrameValues[LP5891_u8RESET_FRAMES_NO] =
{0xff,0xfe,0xaa,0x80,0xff,0xff,0xff} ;

static const u8 LP5891_u8SyncFrameValues[LP5891_u8VSYNC_FRAMES_NO]=
{0xff,0xff,0xfe,0xaa,0xf0,0xff};

static const u8 LP5891_u8InitFrameValues[LP5891_u8INIT_FRAMES_NO] =
{
    0xFF,0xFF,0xFE,0xAA,0x10,0xFF,0xFF,0xFF,0xFF,0x55,0x00,0x48,0x00,0x36,0x3D,0xE0,0x10,0xB7,0xFF,0xFF,0xFF,0xF5,0x50,0x08,0x00,0x02,0x00,0x01,0x01,0xFF,0x7F,0xFF,
    0xFF,0xFF,0x55,0x01,0x48,0xE0,0x20,0x00,0x10,0x00,0x0F,0xFF,0xFF,0xFF,0xF5,0x50,0x18,0x00,0x15,0xFD,0xFE,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0x55,0x02,0x45,0xE0,0x22,
    0xAF,0x10,0x00,0x2F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};


static const u16 DMA_LookupDelay[20] = 
{
   0,
   800,
   500,
   375,
   280,
   210,
   145 ,
   100 ,
   60 ,
   30 ,
   8 ,
   5 ,
   3,
   2 ,
   1 ,
   1 ,
   0 ,
   0 ,
   0 ,
   0,
} ;
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START Component state machine array \DESIGNER_END
 *   \details \DESIGNER_START Type HBCK_tenuWorkingStatus / Range [enum] / Resolution enum / Unit enum \DESIGNER_END
 */
static LP5891_tenuWorkingStatus LP5891_aenuDrvCurrentState[LP5891_u8MAXNo_COMPONENT];

/** \brief \DESIGNER_START Component Number of running SPI Frames \DESIGNER_END
 *   \details \DESIGNER_START Type u32 / Range [0..0x7FFF] / Resolution 1 / Unit NA \DESIGNER_END
 */
static u32 LP5891_au32NoSpiFrames[LP5891_u8MAXNo_COMPONENT] = {0} ;
static u32 LP5891_au32SpiRequestId[LP5891_u8MAXNo_COMPONENT] = {0} ;


/** \brief \DESIGNER_START Component SPI TX-Rx Buffers \DESIGNER_END
 *   \details \DESIGNER_START Type pointer to u8 / Range [1000..LP5891_U16TXRXBUFFER_MAX] / Resolution 1 / Unit NA \DESIGNER_END
 */
static u8 LP5891_pau8StatTxBuffer[LP5891_u8MAXNo_COMPONENT][LP5891_U16TXRXBUFFER_MAX] = {0};
static u8 LP5891_pau8StatRxBuffer[LP5891_u8MAXNo_COMPONENT][LP5891_U16TXRXBUFFER_MAX] = {0};


/** \brief \DESIGNER_START Image Request state \DESIGNER_END
 *   \details \DESIGNER_START Type LBTY_tenuErrorStatus / Range [NOK,OK] / Resolution 1 / Unit NA \DESIGNER_END
 */
static LBTY_tenuErrorStatus LP5891_aenuNewImageRequest[LP5891_u8MAXNo_COMPONENT] = {0} ;
static LBTY_tenuErrorStatus LP5891_u8ImageFinished[LP5891_u8MAXNo_COMPONENT] = {0} ;


/** \brief \DESIGNER_START Image Rom Address \DESIGNER_END
 *   \details \DESIGNER_START Type pointer to u8 / Range [NOK,OK] / Resolution 1 / Unit NA \DESIGNER_END
 */
static const u8 * LP5891_au8ImageLocation[LP5891_u8MAXNo_COMPONENT] = {0} ;

/** \brief \DESIGNER_START Number of pixels per image \DESIGNER_END
 *   \details \DESIGNER_START Type pointer to u32 / Range [0..64K] / Resolution 1 / Unit NA \DESIGNER_END
 */
static u32 LP5891_u32MaxImagePixels[LP5891_u8MAXNo_COMPONENT] = {0} ;


/** \brief \DESIGNER_START Pixel indexer \DESIGNER_END
 *   \details \DESIGNER_START Type  u32 / Range [0..0xFFFF] / Resolution 1 / Unit NA \DESIGNER_END
 */
static u32 LP5891_au32CrntPixelLoc[LP5891_u8MAXNo_COMPONENT] = {0} ;

/** \brief \DESIGNER_START Block data container address \DESIGNER_END
 *   \details \DESIGNER_START Type  pointer to u8 / Range [NA] / Resolution 1 / Unit NA \DESIGNER_END
 */
static const u8 * LP5891_u8CrntPixelBlock[LP5891_u8MAXNo_COMPONENT] = {0} ;



/** \brief \DESIGNER_START Block data container address \DESIGNER_END
 *   \details \DESIGNER_START Type  pointer to u8 / Range [NA] / Resolution 1 / Unit NA \DESIGNER_END
 */
static u16 DMA_NotifDelay[LP5891_u8MAXNo_COMPONENT] = {0} ;

/* ************************************************************************** */
/* ************************* PUBLIC FUNCTION SECTION ************************ */
/* ************************************************************************** */
/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void LP5891_vidInit(void)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      /**: Initialize Local Variables ;*/
   u8 LOC_u8DrvIdx = LP5891_u8MIN;

   /**: Initialize SPI Peripheral ;*/
   /*LP5891_enuSpiInit() ;*/

   /*************************  Update All Chips Configurations ***********************/

   /**: Loop on all Chips indices ;*/
   /**  repeat*/
   for (LOC_u8DrvIdx = LP5891_u8LoopStartIdx;
      LOC_u8DrvIdx < LP5891_u8MAXNo_COMPONENT; LOC_u8DrvIdx++)
   {
      /**: Set state to uninitialized ;*/
      LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_UNINITIALIZED ;

      /**: Set image request to no image requested ;*/
      LP5891_aenuNewImageRequest[LOC_u8DrvIdx] = LBTY_NOK ;

      /**: Free the image buffer ; */
      LP5891_au8ImageLocation[LOC_u8DrvIdx] = LP5891_NULL ;

      LP5891_u32MaxImagePixels[LOC_u8DrvIdx] = LP5891_u32MIN ;

      /**: Set SPI data byte to MIN 0 ; */
      LP5891_au32NoSpiFrames[LOC_u8DrvIdx] = LP5891_u32MIN ;

      /**: Set SPI data byte to MIN 0 ; */
      LP5891_au32SpiRequestId[LOC_u8DrvIdx] = LP5891_u32MIN ;

      /**: Call init driver function   ; */
       vidPrepareInitFrame(LOC_u8DrvIdx);

      /**: Disable Chip select ;*/
      LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_ON) ;

      DMA_NotifDelay[LOC_u8DrvIdx] = DMA_LookupDelay[LP5891_astrSPIConfig[LOC_u8DrvIdx].u16SpiSpeed]  ;
   }
   /**repeat while (Driver ID (LOC_u8TempDrvIdx) < Numbers of Drivers (HSMART_u8SMART_DRV_NB) ) is (yes)
    ->no;*/


   /** stop*/
   /** @enduml*/
}








/**
 *   \brief \DESIGNER_START Component  Runnable function \DESIGNER_END
 *   \details \DESIGNER_START Run Component State machine, Set SW Enable value, Read Chip Diag  and Update Defects \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START ASynchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START None\DESIGNER_END
 *   \param[out]      void \DESIGNER_START None \DESIGNER_END
 *   \param[in,out]   void \DESIGNER_START None \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *       \DESIGNER_START                  
 *       \DESIGNER_END
 *
 *   \DESIGNER_START  Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary ENV
 *      ENV -> LP5891 : LP5891_vidRunMgmt
 *      activate LP5891
 *      LP5891 ->  :
 *       --> LP5891 : return
 *      LP5891 --> ENV : return
 *      deactivate LP5891
 *   @enduml
 */
void LP5891_vidRunMgmt(void)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;
   /**: Initialize Local Variables ;*/
   u8 LOC_u8DrvIdx = LP5891_u8MIN;
   u32 LOC_u32Pixels = LP5891_u32MIN;

   /*************************  Run Comonent state machine ***********************/
   /**: Loop on all Chips indices ;*/
   /**  repeat*/
   for (LOC_u8DrvIdx = LP5891_u8LoopStartIdx; LOC_u8DrvIdx < LP5891_u8MAXNo_COMPONENT; LOC_u8DrvIdx++)
   {
      /**: Prepare pixels for all devices ;*/
      switch(LP5891_aenuDrvCurrentState[LOC_u8DrvIdx])
      {
         /**if (LP5891_UNINITIALIZED state) then (yes)*/
         case LP5891_UNINITIALIZED:

            /**: Set off the chip select ;*/
            LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_ON) ;

            /**: Prepare Init Frame, Done at init function ;*/
            vidPrepareInitFrame(LOC_u8DrvIdx) ;

            break;
         /**else if (LP5891_INITIALIZED state) then (yes)*/
         case LP5891_INITIALIZED:

            /**: Wait Init DMA Init Job finished ;*/

            break;
         /**else if (LP5891_IDLE state) then (yes)*/
         case LP5891_IDLE:

            /** if( new image is requested) then(true) */
            if ( LP5891_aenuNewImageRequest[LOC_u8DrvIdx] == LBTY_OK )
            {
               /**: Reset Image Request waiting for new one ;*/
                LP5891_aenuNewImageRequest[LOC_u8DrvIdx] = LBTY_NOK;

               /**: Load the first Pixels Block ;*/
                LP5891_u8CrntPixelBlock[LOC_u8DrvIdx] = 0 ;  
                LP5891_au32CrntPixelLoc[LOC_u8DrvIdx] = 0 ;
                LP5891_au32NoSpiFrames[LOC_u8DrvIdx] = 0 ;
                LP5891_au32SpiRequestId[LOC_u8DrvIdx]=0 ;

               LP5891_u8ImageFinished[LOC_u8DrvIdx] = LBTY_IN_PROGRESS ;

               /**: Set off the chip select ;*/
               LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_ON) ;

               /**: Set current mode to operation mode, start the transmission job ;*/
               LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_OPERATION_MODE ;

            }/** else */
            else 
            {
               /**: No job requested, wait for a new image ;*/

            }/** endif */

            break;
         /**elseif (LP5891_OPERATION_MODE state) then (yes)*/
         case LP5891_OPERATION_MODE:

            /**: Wait for the job being done, till all frames sent and update the driver working mode ;*/

            /**: Move Block indexer to the required block ;*/
            LP5891_u8CrntPixelBlock[LOC_u8DrvIdx] = &LP5891_au8ImageLocation[LOC_u8DrvIdx][LP5891_au32CrntPixelLoc[LOC_u8DrvIdx]] ;            

#if LP5891_IMAGE_TRANSFER   ==     LP5891_BLOCK_TRANSFER
            /**: Calculate pixles numbers per block ;*/
            LOC_u32Pixels = LP5891_u32PIXELPerRUN  * LP5891_u32BLOCKPerRun_No ; 
#elif LP5891_IMAGE_TRANSFER   ==     LP5891_HALFIMAGE_TRANSFER
            /**: Calculate pixles numbers per block ;*/
            LOC_u32Pixels = LP5891_u32MaxImagePixels[LOC_u8DrvIdx]/2 ; 
#elif LP5891_IMAGE_TRANSFER   ==     LP5891_FULLIMAGE_TRANSFER
            /**: Calculate pixles numbers per block ;*/
            LOC_u32Pixels = LP5891_u32MaxImagePixels[LOC_u8DrvIdx] ; 
#endif
            /**: Prepare Block to Send ;*/
            vidPrepareBlockFrame(LOC_u8DrvIdx, LP5891_u8CrntPixelBlock[LOC_u8DrvIdx], LOC_u32Pixels) ;

            /**: Reset SPI requests ;*/
            LP5891_au32SpiRequestId[LOC_u8DrvIdx] = LP5891_u32MIN; 

            /**: checkout the next block indexer ;*/
            LP5891_au32CrntPixelLoc[LOC_u8DrvIdx]+=  LOC_u32Pixels ;

#if   (LP5891_IMAGE_TRANSFER   ==     LP5891_FULLIMAGE_TRANSFER)
               /**: Prepare Sync Frame ;*/
               vidPrepareSyncFrame(LOC_u8DrvIdx) ;

               /**: Set Image To finished ;*/
               LP5891_u8ImageFinished[LOC_u8DrvIdx] = LBTY_OK ;
#elif   (LP5891_IMAGE_TRANSFER   ==     LP5891_HALFIMAGE_TRANSFER)  
               /**: Prepare Sync Frame ;*/
               vidPrepareSyncFrame(LOC_u8DrvIdx) ;

            /** if( indexer is out of range , Image has been completely parsed) then(true) */
            if (LP5891_au32CrntPixelLoc[LOC_u8DrvIdx] >=  LP5891_u32MaxImagePixels[LOC_u8DrvIdx] )
            {
               /**: Set Image To finished ;*/
               LP5891_u8ImageFinished[LOC_u8DrvIdx] = LBTY_OK ;
            }/** endif*/
#elif     (LP5891_IMAGE_TRANSFER   ==     LP5891_BLOCK_TRANSFER)
            /** if( indexer is out of range , Image has been completely parsed) then(true) */
            if (LP5891_au32CrntPixelLoc[LOC_u8DrvIdx] >=  LP5891_u32MaxImagePixels[LOC_u8DrvIdx] )
            {
               /**: Prepare Sync Frame ;*/
               vidPrepareSyncFrame(LOC_u8DrvIdx) ;

               /**: Set Image To finished ;*/
               LP5891_u8ImageFinished[LOC_u8DrvIdx] = LBTY_OK ;
            }/** endif*/
#endif  

            break;
         /**elseif (LP5891_OPERATION_MODE state) then (yes)*/
         case LP5891_SLEEP:

            /**: To be done ;*/

            break;
         /**elseif (LP5891_OPERATION_MODE state) then (yes)*/
         case LP5891_DEFECT:

            /**: To be done ;*/

            break;

         /** else */
         default:
         break;
      }/**endif*/
    }
   /**repeat while (driver ID (LOC_u8DrvIdx) < Numbers of Drivers (LP5891_u8MAXNo_COMPONENT) ) is (yes)
    ->no;*/


   /** stop*/
   /** @enduml*/
}







/**
 *   \brief \DESIGNER_START Component  Runnable function \DESIGNER_END
 *   \details \DESIGNER_START Run Component State machine, Set SW Enable value, Read Chip Diag  and Update Defects \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START ASynchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START None\DESIGNER_END
 *   \param[out]      void \DESIGNER_START None \DESIGNER_END
 *   \param[in,out]   void \DESIGNER_START None \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *       \DESIGNER_START                  
 *       \DESIGNER_END
 *
 *   \DESIGNER_START  Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary ENV
 *      ENV -> LP5891 : LP5891_vidRunMgmt
 *      activate LP5891
 *      LP5891 ->  :
 *       --> LP5891 : return
 *      LP5891 --> ENV : return
 *      deactivate LP5891
 *   @enduml
 */
extern void LP5891_vidPixelRequestsMgmt(void)
{
      /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;

   /**: Initialize Local Variables ;*/
   u8 LOC_u8DrvIdx = LP5891_u8MIN;
   u32 LOC_u32FrameTosend = LP5891_u32PIXELPerRUN;

   /**: Loop on all Chips indices ;*/
   /**  repeat*/
   for (LOC_u8DrvIdx = LP5891_u8LoopStartIdx;
      LOC_u8DrvIdx < LP5891_u8MAXNo_COMPONENT; LOC_u8DrvIdx++)
   {
         /** if( No Spi requested) then(true) */
         if (LP5891_au32NoSpiFrames[LOC_u8DrvIdx] == LP5891_u32MIN)
         {
            /**: Do nothing ;*/

         }  /** else if( current state is initialized state) then(true) */
         else if ((LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] == LP5891_INITIALIZED)
               /* && (GetSpiJob == Done) */
         )
         {
            /*************************  Send All init frames ***********************/

            /**: Start SPI Job ;*/
            LOC_enuRetErrorStatus = LP5891_enuSpiWrReq( LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiSlot,
                           &LP5891_pau8StatTxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]],  &LP5891_pau8StatRxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]] ,
                            LP5891_au32NoSpiFrames[LOC_u8DrvIdx]  , &LP5891_vidConfJobStartNotif , &LP5891_vidConfJobEndNotif,LOC_u8DrvIdx);

            /** if( DMA received the job correctly) then(true) */
            if (LOC_enuRetErrorStatus == LBTY_OK)
            {
               /**: subtract the init frames numbers ;*/
               LP5891_au32NoSpiFrames[LOC_u8DrvIdx] -= LP5891_u8INIT_FRAMES_NO ; 

               LP5891_au32SpiRequestId[LOC_u8DrvIdx] = LP5891_u8INIT_FRAMES_NO  ;

               /**: Enable the chip select to start communication ;*/
               LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_OFF) ;

               /**: Set current mode to IDLE state ;*/
               LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_IDLE ;
            }/** endif  */

         }/** else if( current state is operation state) then(true) */
         else if ( LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] == LP5891_OPERATION_MODE )
         {

#if LP5891_IMAGE_TRANSFER   ==     LP5891_FULLIMAGE_TRANSFER
            /*************************  Send All Data frames ***********************/
               LOC_u32FrameTosend = LP5891_au32NoSpiFrames[LOC_u8DrvIdx];

            /**: Start SPI Job ;*/
            /**: Start SPI Job ;*/
            LOC_enuRetErrorStatus = LP5891_enuSpiWrReq( LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiSlot,
                           &LP5891_pau8StatTxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]],  &LP5891_pau8StatRxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]] ,
                            LP5891_au32NoSpiFrames[LOC_u8DrvIdx]  , &LP5891_vidConfJobStartNotif , &LP5891_vidConfJobEndNotif,LOC_u8DrvIdx);


            /** if( DMA write request is OK) then (true) */
            if (LOC_enuRetErrorStatus == LBTY_OK)
            {
               /**: Enable the chip select to start communication ;*/
               LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_OFF) ;

               /**: Set current mode to IDLE state ;*/
               LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_IDLE ;

            }/** endif*/
#elif LP5891_IMAGE_TRANSFER   ==     LP5891_HALFIMAGE_TRANSFER
            /*************************  Send All Data frames ***********************/
            if (LP5891_au32NoSpiFrames[LOC_u8DrvIdx] >= ((LP5891_u32MaxImagePixels[LOC_u8DrvIdx]/2 + LP5891_u8VSYNC_FRAMES_NO * LP5891_u8VSYNC_FRAMES_TRIALS)) )
            {
               LOC_u32FrameTosend = ((LP5891_u32MaxImagePixels[LOC_u8DrvIdx]/2 + LP5891_u8VSYNC_FRAMES_NO * LP5891_u8VSYNC_FRAMES_TRIALS));
            }
            else
            {
               LOC_u32FrameTosend = LP5891_au32NoSpiFrames[LOC_u8DrvIdx];
            }

            /**: Start SPI Job ;*/
            /**: Start SPI Job ;*/
            LOC_enuRetErrorStatus = LP5891_enuSpiWrReq( LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiSlot,
                           &LP5891_pau8StatTxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]],  &LP5891_pau8StatRxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]] ,
                            LP5891_au32NoSpiFrames[LOC_u8DrvIdx]  , &LP5891_vidConfJobStartNotif , &LP5891_vidConfJobEndNotif,LOC_u8DrvIdx);


            /** if( DMA write request is OK) then (true) */
            if (LOC_enuRetErrorStatus == LBTY_OK)
            {
               /**: Update no of remaining spi requests ;*/
               LP5891_au32NoSpiFrames[LOC_u8DrvIdx] -= LOC_u32FrameTosend ;

               /**: Update SPI request indexer ;*/
               LP5891_au32SpiRequestId[LOC_u8DrvIdx] += LOC_u32FrameTosend; 

               /**: Enable the chip select to start communication ;*/
               LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_OFF) ;

               /** if( Image pixels have been processed successfully, and no remaining requests) then (true) */
               if ((LP5891_u8ImageFinished[LOC_u8DrvIdx] == LBTY_OK) && (LP5891_au32NoSpiFrames[LOC_u8DrvIdx] == LP5891_u32MIN) )
               {
                  /**: Reset SPI requests ;*/
                  LP5891_au32SpiRequestId[LOC_u8DrvIdx] = LP5891_u32MIN; 

                  /**: Set current mode to IDLE state ;*/
                  LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_IDLE ;
               }/** endif*/

            }/** endif*/

#elif LP5891_IMAGE_TRANSFER   ==     LP5891_BLOCK_TRANSFER
            /*************************  Send All Data frames ***********************/
            if (LP5891_au32NoSpiFrames[LOC_u8DrvIdx] >= LP5891_u32PIXELPerRUN)
            {
               LOC_u32FrameTosend = LP5891_u32PIXELPerRUN;
            }
            else
            {
               LOC_u32FrameTosend = LP5891_au32NoSpiFrames[LOC_u8DrvIdx];
            }

            /**: Start SPI Job ;*/
            /**: Start SPI Job ;*/
            LOC_enuRetErrorStatus = LP5891_enuSpiWrReq( LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiSlot,
                           &LP5891_pau8StatTxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]],  &LP5891_pau8StatRxBuffer[LOC_u8DrvIdx][LP5891_au32SpiRequestId[LOC_u8DrvIdx]] ,
                            LP5891_au32NoSpiFrames[LOC_u8DrvIdx]  , &LP5891_vidConfJobStartNotif , &LP5891_vidConfJobEndNotif,LOC_u8DrvIdx);


            /** if( DMA write request is OK) then (true) */
            if (LOC_enuRetErrorStatus == LBTY_OK)
            {
               /**: Update no of remaining spi requests ;*/
               LP5891_au32NoSpiFrames[LOC_u8DrvIdx] -= LOC_u32FrameTosend ;

               /**: Update SPI request indexer ;*/
               LP5891_au32SpiRequestId[LOC_u8DrvIdx] += LOC_u32FrameTosend; 

               /**: Enable the chip select to start communication ;*/
               LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[LOC_u8DrvIdx].u8SpiCsPin,LP5891_u8DIO_DIGITAL_OFF) ;

               /** if( Image pixels have been processed successfully, and no remaining requests) then (true) */
               if ((LP5891_u8ImageFinished[LOC_u8DrvIdx] == LBTY_OK) && (LP5891_au32NoSpiFrames[LOC_u8DrvIdx] == LP5891_u32MIN) )
               {
                  /**: Reset SPI requests ;*/
                  LP5891_au32SpiRequestId[LOC_u8DrvIdx] = LP5891_u32MIN; 

                  /**: Set current mode to IDLE state ;*/
                  LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_IDLE ;
               }/** endif*/

            }/** endif*/
#endif
         }/** endif*/

   }
   /**repeat while (driver ID (LOC_u8DrvIdx) < Numbers of Drivers (LP5891_u8MAXNo_COMPONENT) ) is (yes)
    ->no;*/

   /** stop*/
   /** @enduml*/
}











/**
 *   \brief \DESIGNER_START Component  Runnable function \DESIGNER_END
 *   \details \DESIGNER_START Run Component State machine, Set SW Enable value, Read Chip Diag  and Update Defects \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START ASynchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START None\DESIGNER_END
 *   \param[out]      void \DESIGNER_START None \DESIGNER_END
 *   \param[in,out]   void \DESIGNER_START None \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *       \DESIGNER_START                  
 *       \DESIGNER_END
 *
 *   \DESIGNER_START  Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary ENV
 *      ENV -> LP5891 : LP5891_vidRunMgmt
 *      activate LP5891
 *      LP5891 ->  :
 *       --> LP5891 : return
 *      LP5891 --> ENV : return
 *      deactivate LP5891
 *   @enduml
 */
LBTY_tenuErrorStatus LP5891_vidAnimateImage(u8 Driver, const u8 * const pu8image, u32 u32ImagepixelNo)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;
   u32 LOC_u32Max = LP5891_u32BLOCKPerRun_No * LP5891_u32PIXELPerRUN ;

   /** if( driver ID is valid) then(true) */
   if (Driver < LP5891_u8MAXNo_COMPONENT)
   {
      /**: Validate Image, Check start & exit keys ;*/

      /** if( Image is valid) then(true) */
      if (  (pu8image != LP5891_NULL) 
         && (u32ImagepixelNo!=LP5891_u32MIN)
         && (!( u32ImagepixelNo % LOC_u32Max ))
#if (LP5891_IMAGEKEY_FEATURE == LP5891_FEATURE_ON)
            && ( pu16image[0] == LP5891_u16STARTKEY_PATTERN )
            && ( pu16image[u16Imagepixels-(u16)1] == LP5891_u16ENDKEY_PATTERN )
#endif
         )
      {
         /**: Valid Image, Set status to OK ;*/
         LOC_enuRetErrorStatus = LBTY_OK ;
      }/** else */
      else 
      {
         /**: No Image, Set status to NULL_POINTER ;*/
         LOC_enuRetErrorStatus = LBTY_NULL_POINTER ;
      }/** endif */

   }/** else */
   else 
   {
      /**: Do nothing ;*/
   }
   /** endif */

   /** if( Image  is valid) then(true) */
   if ( LBTY_OK == LOC_enuRetErrorStatus )
   {
#if (LP5891_IMAGEQUEUE_FEATURE == LP5891_FEATURE_OFF)
      /** if( Driver is IDLE ) then(true) */
      if ( LP5891_aenuDrvCurrentState[Driver] == LP5891_IDLE)
      {
         /**: Load Images in local buffer to start animation  ;*/
         LP5891_au8ImageLocation[Driver] = pu8image;

         /**: Load No of pixels as indication for end DMA jobs  ;*/
         LP5891_u32MaxImagePixels[Driver] = u32ImagepixelNo;

         /**: Set new animation request flag  ;*/
         LP5891_aenuNewImageRequest[Driver] = LBTY_OK ;

      }/** else */
      else 
      {
         /**: Driver busy, Set status to BUSY ;*/
         LOC_enuRetErrorStatus = LBTY_BUSY ;
      }/** endif */
#elif (LP5891_IMAGEQUEUE_FEATURE == LP5891_FEATURE_ON)

   /**: To be done ;*/

#endif
   }
   /** endif */

   /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}






/**
 *   \brief \DESIGNER_START Component  Runnable function \DESIGNER_END
 *   \details \DESIGNER_START Run Component State machine, Set SW Enable value, Read Chip Diag  and Update Defects \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public  \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START ASynchronous  \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrante  \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START None\DESIGNER_END
 *   \param[out]      void \DESIGNER_START None \DESIGNER_END
 *   \param[in,out]   void \DESIGNER_START None \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *       \DESIGNER_START                  
 *       \DESIGNER_END
 *
 *   \DESIGNER_START  Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary ENV
 *      ENV -> LP5891 : LP5891_vidRunMgmt
 *      activate LP5891
 *      LP5891 ->  :
 *       --> LP5891 : return
 *      LP5891 --> ENV : return
 *      deactivate LP5891
 *   @enduml
 */
LBTY_tenuErrorStatus LP5891_vidStopAnimation(u8 Driver) 
{
      /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_OK;

   /**: Stop SPI Job ;*/
   //

   /**: Set SPI data byte to MIN 0 ; */
   LP5891_au32NoSpiFrames[Driver] = LP5891_u32MIN ;
   LP5891_au32SpiRequestId[Driver] = LP5891_u32MIN ;

   /**: Set state to uninitialized ;*/
   LP5891_aenuDrvCurrentState[Driver] = LP5891_IDLE ;
   
   /**: Reset new animation request flag  ;*/
   LP5891_aenuNewImageRequest[Driver] = LBTY_NOK ;

   /**: Return status ;*/
     return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/ 
}

/* ************************************************************************** */
/* ************************* PRIVATE FUNCTION SECTION *********************** */
/* ************************************************************************** */
/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidPrepareInitFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      /**: initialize error status to be not okay;*/
    u8 LOC_u8ByteIdx = LP5891_u8MIN;

   /**: Loop on all Configuration bytes  ;*/
   /**  repeat*/
   for (LOC_u8ByteIdx = LP5891_u8LoopStartIdx;
      LOC_u8ByteIdx < LP5891_u8INIT_FRAMES_NO; LOC_u8ByteIdx++)
   {
      /**: Sent the configuration data to TX buffer ;*/
      LP5891_pau8StatTxBuffer[Driver][LP5891_au32NoSpiFrames[Driver]] = LP5891_u8InitFrameValues[LOC_u8ByteIdx] ;

      /**: Add SPI Byte ;*/
      LP5891_au32NoSpiFrames[Driver]+=1; 
    }
   /**repeat while (Byte ID (LOC_u8ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
    ->no;*/

   /**: Set current mode to LP5891_INITIALIZED state ;*/
   LP5891_aenuDrvCurrentState[Driver] = LP5891_INITIALIZED ;

   /** stop*/
   /** @enduml*/
}






/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidPrepareSyncFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
    u8 LOC_u8ByteIdx = LP5891_u8MIN;
    u8 LOC_u8TryIdx = LP5891_u8MIN;

   /**: Loop on all Configuration bytes  ;*/
   /**  repeat*/
   for (LOC_u8TryIdx = LP5891_u8LoopStartIdx;
      LOC_u8TryIdx < LP5891_u8VSYNC_FRAMES_TRIALS; LOC_u8TryIdx++)
   {
         /**: Loop on all Configuration bytes  ;*/
         /**  repeat*/
         for (LOC_u8ByteIdx = LP5891_u8LoopStartIdx;
            LOC_u8ByteIdx < LP5891_u8VSYNC_FRAMES_NO; LOC_u8ByteIdx++)
         {
            /**: Sent the configuration data to TX buffer ;*/
            LP5891_pau8StatTxBuffer[Driver][LP5891_au32NoSpiFrames[Driver]] = LP5891_u8SyncFrameValues[LOC_u8ByteIdx] ;

            /**: Add SPI Byte ;*/
            LP5891_au32NoSpiFrames[Driver]+=1; 
          }
         /**repeat while (Byte ID (LOC_u8ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
          ->no;*/

   }
   /**repeat while (Byte ID (LOC_u8ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
    ->no;*/

   /** stop*/
   /** @enduml*/
}







/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidPrepareSWResetFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      /**: initialize error status to be not okay;*/
    u8 LOC_u8ByteIdx = LP5891_u8MIN;

   /**: Loop on all Configuration bytes  ;*/
   /**  repeat*/
   for (LOC_u8ByteIdx = LP5891_u8LoopStartIdx;
      LOC_u8ByteIdx < LP5891_u8RESET_FRAMES_NO; LOC_u8ByteIdx++)
   {
      /**: Sent the configuration data to TX buffer ;*/
      LP5891_pau8StatTxBuffer[Driver][LP5891_au32NoSpiFrames[Driver]] = LP5891_u8ResetFrameValues[LOC_u8ByteIdx] ;

      /**: Add SPI Byte ;*/
      LP5891_au32NoSpiFrames[Driver]+=1; 
    }
   /**repeat while (Byte ID (LOC_u8ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
    ->no;*/

   /** stop*/
   /** @enduml*/
}






/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidPrepareSinglePixelFrame (u8 Driver,const RGB_tstrPixelData * const u32pixelData)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   u8 LOC_u8ByteIdx = LP5891_u8MIN;

   /**: (3 RGB * 17 bit) + start bit + header frame ;*/
   /**: 23 Bit IDLE   +  start Bit  + Header (0xAA30) + checkbit + Red + checkbit + Green + checkbit + Blue + checkbit + 20 Bit IDLE ;*/
   u8 loc_u8Buffer[14] ;

   /**: Prepare Frame to send ;*/
   loc_u8Buffer [0] = LP5891_u8FrameIDLEBytes ;      /**: End 18 bit ;*/
   loc_u8Buffer [1] = LP5891_u8FrameIDLEBytes ;      /**: End 18 bit ;*/
   loc_u8Buffer [2] = LP5891_u8FrameSTARTByte ;    /**: Start bit ;*/
   loc_u8Buffer [3] = 0xAA ;                       /**: Set highest byte address ;*/
   loc_u8Buffer [4] = 0x30 ;                       /**: Set lowest byte address ;*/

   loc_u8Buffer [5] =   ( 0x00 | 0x80 | (u32pixelData->LED_REDx.u16Word >>9 )) ;  /**:header check bit +  Apply Red high 7 bits (15-9) ;*/
   loc_u8Buffer [6] =   ( 0x00 | (u32pixelData->LED_REDx.u16Word >> 1 ) )   ;  /**: Apply Red next 8 bits (8-1)  ;*/
   loc_u8Buffer [7] =   ( 0x00 | ((u32pixelData->LED_REDx.u16Word & 0x1) <<7 )  | ( ((!u32pixelData->LED_REDx.u16Word) & 0x1) <<6 )  )  ;  /**: Apply Red next 1 bits (bit0) + Red Check bit;*/

   loc_u8Buffer [7] =   ( 0x00 |  ((u32pixelData->LED_GREENx.u16Word >>10) &0x3F )) ;  /**:header check bit +  Apply Green high 6 bits (15-10) ;*/
   loc_u8Buffer [8] =   ( 0x00 | (u32pixelData->LED_GREENx.u16Word >> 2 ) )   ;  /**: Apply Green next 8 bits (9-2)  ;*/
   loc_u8Buffer [9] =   ( 0x00 | ((u32pixelData->LED_GREENx.u16Word & 0x3) <<6 )  | ( ((!u32pixelData->LED_GREENx.u16Word) & 0x1) <<5 )  )  ;  /**: Apply Green next 2 bits (1-0) + Green Check bit;*/

   loc_u8Buffer [9] =   ( 0x00 | ((u32pixelData->LED_BLUEx.u16Word) &0x1F >>11 )) ;  /**:header check bit +  Apply Blue high 5 bits (15-11) ;*/
   loc_u8Buffer [10] =   ( 0x00 | (u32pixelData->LED_BLUEx.u16Word >> 3 ) )   ;  /**: Apply Blue next 8 bits (10-3)  ;*/
   loc_u8Buffer [11] =   ( 0x0F | ((u32pixelData->LED_BLUEx.u16Word & 0x7) <<5 )  | ( ((!u32pixelData->LED_BLUEx.u16Word) & 0x1) <<4 )  )  ;  /**: Apply Blue next 1 bits (bit0) + Blue Check bit + fill remaining 4 bits with 1;*/

   loc_u8Buffer [12] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/
   loc_u8Buffer [13] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/

   /**: Loop on all Configuration bytes  ;*/
   /**  repeat*/
   for (LOC_u8ByteIdx = LP5891_u8LoopStartIdx;
      LOC_u8ByteIdx < (u8)14; LOC_u8ByteIdx++)
   {
      /**: Sent the configuration data to TX buffer ;*/
      LP5891_pau8StatTxBuffer[Driver][LP5891_au32NoSpiFrames[Driver]] = loc_u8Buffer[LOC_u8ByteIdx] ;

      /**: Add SPI Byte ;*/
      LP5891_au32NoSpiFrames[Driver]+=1; 
    }
   /**repeat while (Byte ID (LOC_u8ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
    ->no;*/

   /** stop*/
   /** @enduml*/
}







/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidPrepareBlockFrame(u8 Driver, const u8 * const u8BlockLoc, u32 u32BlockSize )
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   u32 LOC_u32ByteIdx = LP5891_u32MIN;

   /**: Loop on all Block bytes  ;*/
   /**  repeat*/
   for (LOC_u32ByteIdx = LP5891_u8LoopStartIdx;
      LOC_u32ByteIdx < u32BlockSize; LOC_u32ByteIdx++)
   {
      /**: Sent the data bytes to TX buffer ;*/
      LP5891_pau8StatTxBuffer[Driver][LP5891_au32NoSpiFrames[Driver]] = u8BlockLoc[LOC_u32ByteIdx] ;  

      /**: Add SPI Byte ;*/
      LP5891_au32NoSpiFrames[Driver]+=1; 
    }
   /**repeat while (Byte ID (LOC_u32ByteIdx) < Numbers of Drivers (LP5891_u8INIT_FRAMES_NO) ) is (yes)
    ->no;*/     

   /** stop*/
   /** @enduml*/
}






/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void vidGetPixel(u8 Driver, const u8 * const u8pixelLoc ,RGB_tstrPixelData * Pixel )
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: Initialize RGB Pixel colors ;*/
   RGB_tstrPixelData loc_enupixel = {0,0,0} ;

   /**: Get RGB Pixel colors ;*/
   loc_enupixel.LED_REDx.strByte.u8high = u8pixelLoc[0] ;
   loc_enupixel.LED_REDx.strByte.u8low = u8pixelLoc[1] ;

   loc_enupixel.LED_GREENx.strByte.u8high = u8pixelLoc[2] ;
   loc_enupixel.LED_GREENx.strByte.u8low = u8pixelLoc[3] ;

   loc_enupixel.LED_BLUEx.strByte.u8high = u8pixelLoc[4] ;
   loc_enupixel.LED_BLUEx.strByte.u8low = u8pixelLoc[5] ;
   
   /** stop*/
   /** @enduml*/
}





/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void LP5891_vidConfJobEndNotif(u16 u16UsrSgntrCpy, LBTY_tenuErrorStatus enuErrStat)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: Initialize delay counter ;*/
   u16 count = 0 ;

   /**: Wait a delay till DMA finish the last 2 bytes ;*/
   for (count=0;count<DMA_NotifDelay[0];count++) {}

   /**: Disable CCSI Chip select pin ;*/
   LP5891_enuDIOSetOutState(LP5891_astrSPIConfig[0].u8SpiCsPin,LP5891_u8DIO_DIGITAL_ON) ;

   /** stop*/
   /** @enduml*/
}







/**
 *   \brief \DESIGNER_START Initialize LP5891 component \DESIGNER_END
 *
 *   \par Scope:
 *        \DESIGNER_START Public \DESIGNER_END
 *   \par Synch/Asynch:
 *        \DESIGNER_START Synchronous \DESIGNER_END
 *   \par Re-entrancy:
 *        \DESIGNER_START Non Re-entrant \DESIGNER_END
 *
 *   \param[in]       void \DESIGNER_START Description of the input paramater   Type void / Range [NA] / Resolution NA / Unit NA \DESIGNER_END
 *   \return \DESIGNER_START void \n \DESIGNER_END
 *           Returned Value List:
 *           \DESIGNER_START void \DESIGNER_END
 *
 *   \par Requirement ID:
 *        \DESIGNER_START  \DESIGNER_END
 *   \par Coverage:
 *        \DESIGNER_START
 *           \DESIGNER_END
 *
 *   \DESIGNER_START Define Function main sequence diagram \DESIGNER_END
 *   @startuml
 *   title Function main sequence
 *      boundary YFIC
 *      YFIC -> LP5891 : LP5891_vidInit
 *   @enduml
 */
void LP5891_vidConfJobStartNotif (u16 u16UsrSgntrCpy, LBTY_tenuErrorStatus enuErrStat)
{
      /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */
   
   // LP5891_enuDIOSetOutState(LP5891_DRV1_CCSI_PIN,0) ;

      /** stop*/
   /** @enduml*/
}




/* *********************** E N D (LP5891_prg.c) *************************** */
