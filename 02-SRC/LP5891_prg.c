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
 *     | LP5891_prg.c       | 1.0          | Proposed            | \verbatim $Rev::              $: Revision of last commit \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Date::            #$: Date of last commit     \endverbatim |
 *     | ^                | ^            | ^                   | \verbatim $Author::           $: Author of last commit   \endverbatim |
 */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "BSW_cfg.h"

#include "LFIC_LP5891_cfg.h"
#include "MFIC_LP5891_cfg.h"
#include "HFIC_LP5891_cfg.h"

#include "LP5891_priv.h"
#include "LP5891_cfg.h"
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

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */
/** \brief \DESIGNER_START Component state machine array \DESIGNER_END
 *   \details \DESIGNER_START Type HBCK_tenuWorkingStatus / Range [enum] / Resolution enum / Unit enum \DESIGNER_END
 */
static LP5891_tenuWorkingStatus LP5891_aenuDrvCurrentState[LP5891_u8MAXNo_COMPONENT];

static u16 LP5891_au16NoSpiFrames[LP5891_u8MAXNo_COMPONENT] = {0} ;
static u16 LP5891_au16StatTxBuffer[LP5891_u8MAXNo_COMPONENT][85] = {0};
static u16 LP5891_au16StatRxBuffer[LP5891_u8MAXNo_COMPONENT][85] = {0};



static const u16 * LP5891_au16ImageLocation[LP5891_u8MAXNo_COMPONENT] = {0} ;
static u16 LP5891_au16PixelsBuffer[LP5891_u8MAXNo_COMPONENT][85] = {0} ;


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

   /*************************  Update All Chips Configurations ***********************/

   /**: Loop on all Chips indices ;*/
   /**  repeat*/
   for (LOC_u8DrvIdx = LP5891_u8LoopStartIdx;
      LOC_u8DrvIdx < LP5891_u8MAXNo_COMPONENT; LOC_u8DrvIdx++)
   {
      /**: Set state to uninitialized ;*/
      LP5891_aenuDrvCurrentState[LOC_u8DrvIdx] = LP5891_UNINITIALIZED ;

      LP5891_au16ImageLocation[LOC_u8DrvIdx] = LP5891_NULL ;

      /**: Call init driver function   ; */
      vidDrvInitFrame(LOC_u8DrvIdx);

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

   LP5891_au16NoSpiFrames[0] = 1 ;

   (void) LP5891_enuHDIOSetOutDigitalState( 0,  LP5891_u8HDIO_DIGITAL_OFF);

   (void) LP5891_enuHPWMSetOutDUTY(0,0);


     (void) LP5891_enuHspmSpiWrReq(0,LP5891_au16StatTxBuffer,
         LP5891_au16StatRxBuffer[0],
         LP5891_au16NoSpiFrames[0],
         0,
         (tpfvidHspmUsrJobCallBck)&LP5891_vidConfJobEndNotif,
         0);

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
void LP5891_vidConfJobEndNotif(u16 u8SgntrCpy, LBTY_tenuErrorStatus enuErrStat)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */




   /** stop*/
   /** @enduml*/
}



LBTY_tenuErrorStatus LP5891_vidAnimateImage(u8 Driver, const u16 * pu16image, u16 u16image_no, u16 u16pixels_no, u16 u16animationspeed)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;

   /**: Validate Image, Check start & exit keys ;*/
   // pu16image[u16image_no][u16pixels_no];

   /** if( driver ID is valid) then(true) */
   if (Driver < LP5891_u8MAXNo_COMPONENT)
   {
      /** if( Image is valid) then(true) */
      if ((pu16image != LP5891_NULL) && ( pu16image[0] == LP5891_u16STARTKEY_PATTERN ))
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
      /** if( Driver is IDLE ) then(true) */
      if ( LP5891_aenuDrvCurrentState[Driver] == LP5891_IDLE)
      {
         /**: Load Images in local buffer to start animation  ;*/
         LP5891_au16ImageLocation[Driver] = pu16image;

      }/** else */
      else 
      {
         /**: Driver busy, Set status to BUSY ;*/
         LOC_enuRetErrorStatus = LBTY_BUSY ;
      }/** endif */
   }
   /** endif */

   /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}



LBTY_tenuErrorStatus LP5891_vidStopAnimation(u8 Driver) 
{
      /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;




   /**: Return status ;*/
     return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/ 
}

/* ************************************************************************** */
/* ************************* PRIVATE FUNCTION SECTION *********************** */
/* ************************************************************************** */
LBTY_tenuErrorStatus vidDrvInitFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;

   /**: Set initialization no of frames to send ;*/
   LP5891_au16NoSpiFrames[Driver] = 1 ;






   /**: Set state to uninitialized ;*/
   LP5891_aenuDrvCurrentState[Driver] = LP5891_INITIALIZED ;

   /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}



LBTY_tenuErrorStatus vidSendSyncFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;
   u8 loc_u8Buffer [6] ;

   /**: Prepare Frame to send ;*/
   loc_u8Buffer [0] = LP5891_u8FrameIDLEBytes ;    /**: IDLE byte ;*/
   loc_u8Buffer [1] = LP5891_u8FrameIDLEBytes ;    /**: IDLE byte ;*/
   loc_u8Buffer [2] = LP5891_u8FrameSTARTByte ;    /**: Start 1 bit ;*/
   loc_u8Buffer [3] = 0xAA ;                       /**: Set highest byte address ;*/
   loc_u8Buffer [4] = 0xF0 ;                       /**: Set lowest byte address ;*/
   loc_u8Buffer [5] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/

      /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}




LBTY_tenuErrorStatus vidSendSWResetFrame(u8 Driver)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

      /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;
   u8 loc_u8Buffer [7] ;

   /**: Prepare Frame to send ;*/
   loc_u8Buffer [0] = LP5891_u8FrameIDLEBytes ;    /**: IDLE byte ;*/
   loc_u8Buffer [1] = LP5891_u8FrameSTARTByte ;    /**: Start bit ;*/
   loc_u8Buffer [2] = 0xAA ;                       /**: Set highest byte address ;*/
   loc_u8Buffer [3] = 0x80 ;                       /**: Set lowest byte address ;*/
   loc_u8Buffer [4] = 0xFF;                        /**: Reset command value at 0xAA80 ;*/
   loc_u8Buffer [5] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/
   loc_u8Buffer [6] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/

      /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}



LBTY_tenuErrorStatus vidSendPixelFrame(u8 Driver, u32 u32pixelNo)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: initialize error status to be not okay;*/
   LBTY_tenuErrorStatus LOC_enuRetErrorStatus = LBTY_NOK;

   RGB_tstrPixelData loc_enupixel = vidGetPixel(Driver, u32pixelNo) ;

   /**: (3 RGB * 17 bit) + start bit + header frame ;*/
   u8 loc_u8Buffer[10] ;

   /**: Prepare Frame to send ;*/
   loc_u8Buffer [0] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/
   loc_u8Buffer [1] = LP5891_u8FrameENDByte ;      /**: End 18 bit ;*/
   loc_u8Buffer [2] = LP5891_u8FrameSTARTByte ;    /**: Start bit ;*/
   loc_u8Buffer [3] = 0xAA ;                       /**: Set highest byte address ;*/
   loc_u8Buffer [4] = 0x30 ;                       /**: Set lowest byte address ;*/
   loc_u8Buffer [5] = loc_enupixel.LED_REDx.u16UniColorData ;  /**: Apply Red ;*/
   loc_u8Buffer [6] = (!loc_enupixel.LED_REDx.u16UniColorData <<15 ) |(loc_enupixel.LED_GREENx.u16UniColorData >> 1 ) ;  /**: Apply Green ;*/
   loc_u8Buffer [7] = ((loc_enupixel.LED_GREENx.u16UniColorData&0x1)<<15) |(!loc_enupixel.LED_GREENx.u16UniColorData <<14 ) |(loc_enupixel.LED_BLUEx.u16UniColorData >> 2 ) ;  /**: Apply Blue ;*/
   loc_u8Buffer [8] = ((loc_enupixel.LED_BLUEx.u16UniColorData&0x3)<<14) |(!loc_enupixel.LED_BLUEx.u16UniColorData <<13 ) |( 0x1F  ) ;  /**: Apply Blue ;*/
   loc_u8Buffer [9] = LP5891_u8FrameENDByte ;      /**: End bit ;*/

   /**: Return status ;*/
   return LOC_enuRetErrorStatus;
   /** stop*/
   /** @enduml*/
}




RGB_tstrPixelData vidGetPixel(u8 Driver, u32 u32pixelNo)
{
   /**
    * \DESIGNER_START Define Function activity diagram \DESIGNER_END
    * @startuml
    * title Function activity diagram
    * start */

   /**: Initialize RGB Pixel colors ;*/
   RGB_tstrPixelData loc_enupixel = {0,0,0} ;
   u32 loc_pixelindex = (LP5891_u32STARTKEY_INDEX +(u32)1 ) + (u32)3 * u32pixelNo  ;

   /**: Get RGB Pixel colors ;*/
   loc_enupixel.LED_REDx.u16UniColorData = LP5891_au16ImageLocation[Driver][loc_pixelindex] ;
   loc_enupixel.LED_GREENx.u16UniColorData = LP5891_au16ImageLocation[Driver][loc_pixelindex+1] ;
   loc_enupixel.LED_BLUEx.u16UniColorData = LP5891_au16ImageLocation[Driver][loc_pixelindex+2] ; 
   
   /**: Return status ;*/
   return loc_enupixel ;
   /** stop*/
   /** @enduml*/
}





/* *********************** E N D (LP5891_prg.c) *************************** */
