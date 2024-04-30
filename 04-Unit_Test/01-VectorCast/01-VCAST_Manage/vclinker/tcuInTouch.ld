/*===========================================================================*/
/* Module       = App_MCU_F1K_F1KM_Sample.ld                                  */
/* Version      = V1.0.1                                                     */
/*                extracted from device file dr7f701644.dvf                  */
/*                by DeFiXRH850 0.9.0.1                                      */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2018-2019 by Renesas Electronics Europe GmbH,               */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:     Template of linker directive file                            */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* Environment:                                                              */
/*              Device:    R7F701636, R7F701644, R7F701645, R7F701646,       */
/*                         R7F701647, R7F701648, R7F701649, R7F701650,       */
/*                         R7F701651, R7F701652, R7F701653.                  */
/*                         R7F701684, R7F701685, R7F701686, R7F701687,       */
/*                         R7F701688, R7F701689, R7F701690, R7F701691,       */
/*                         R7F701692, R7F701693, R7F701694, R7F701695.       */
/*                         R7F701602, R7F701610, R7F701612, R7F701620,       */
/*                         R7F701622, R7F701603, R7F701557, R7F701611,       */
/*                         R7F701613, R7F701577, R7F701621, R7F701623,       */
/*                         R7F701597, R7F701542, R7F701546, R7F701560,       */
/*                         R7F701562, R7F701566, R7F701580, R7F701582,       */
/*                         R7F701586, R7F701543, R7F701547, R7F701561,       */
/*                         R7F701563, R7F701567, R7F701581, R7F701583,       */
/*                         R7F701587.     	   								 */

/*              IDE:       GHS Multi for V800  V6.xx or later                */
/*===========================================================================*/
/*                      Revision Control History                             */
/*===========================================================================*/
/* V1.0.0:  20-Aug-2018,    Initial Version. Manually create common .ld file */
/*                          for all supported devices.                       */
/* V1.0.1:  13-Oct-2019,    #ARDAABD-4544                                    */
/*===========================================================================*/

CONSTANTS
{
  zero_start = 0xffff8000
}

MEMORY
 {
  iROM_0         : ORIGIN = 0x00000000,  LENGTH = 4096K
  iROM_1         : ORIGIN = 0x01000000,  LENGTH = 32K
  iROM_1_TOP   : ORIGIN = .         ,   LENGTH  = 0
  iRAM_0         : ORIGIN = 0xFEBC0000,  LENGTH = 256K
  iRAM_0_TOP   : ORIGIN = .         ,   LENGTH  = 0
  iRAM_R         : ORIGIN = 0xFEF00000,  LENGTH = 64K
  iRAM_R_TOP   : ORIGIN = .         ,   LENGTH  = 0
 }

SECTIONS
 {
 .eivect        align(512) :
  {
    "*(.*osExceptionVectorTable_c0*)"
  }>iROM_0 /* start of exception vector table */ /* User must not change this */ /* User can only move this by defining a new section for the RESET vector. RESET must be placed at 0x00 */

 .intvect       align(512) :
  {
    "*(.*osEIINTVectorTable_c0*)"
  }>. /* start of interrupt vector table */ /* User can move this section to a specified address (replace "." by address */
    
    
  .rozdata                         :>.     /* constant datas in ZDA area */
  .robase   align(4)               :>.     /* initialize textpointer TP for SDA addressing */
  .rosdata  align(4)               :
  {
    "*(.*os_rosdata*)"
  }>.                                      /* constant datas in SDA area */
  .SPI_CFG_DBTOC_UNSPECIFIED       :>.     /* constant datas in SDA area for SPI */
  .SPI_CFG_DATA_UNSPECIFIED        :>.     /*from Spi_PBcfg.o -- constant datas in SDA area for SPI */
  .ADC_CFG_DATA_UNSPECIFIED        :>.

  .DIO_CFG_DATA_UNSPECIFIED        :>.     /* constant datas for DIO module based on ASIL req for AUTOSAR4.2.2 */
  .CONST_ROM_32BIT                 :>.     /* constant datas for DIO + ADC module based on ASIL req for AUTOSAR4.2.2 */
  .MCU_CFG_DATA_UNSPECIFIED        :>.     /* constant datas for MCU module based on ASIL req for AUTOSAR4.2.2 */
  .CONST_ROM_UNSPECIFIED           :>.     /* constant datas for MCU module based on ASIL req for AUTOSAR4.2.2 */
  .MCU_CFG_DBTOC_UNSPECIFIED       :>.     /* constant datas for MCU module based on ASIL req for AUTOSAR4.2.2 */
  .PORT_CFG_DATA_UNSPECIFIED       :>.     /* constant datas for PORT module based on ASIL req for AUTOSAR4.2.2 */
  .GPT_CFG_DATA_UNSPECIFIED        :>.     /* from Gpt_PBcfg.o */
  .PWM_CFG_DATA_UNSPECIFIED        :>.     /* from Pwm_Hardware.o */
  .PWM_CFG_DBTOC_UNSPECIFIED       :>.     /* from Pwm_PBcfg.o */
  .ICU_CFG_DATA_UNSPECIFIED        :>.
  .ICU_CFG_DBTOC_UNSPECIFIED       :>.
  .LIN_CFG_DATA_UNSPECIFIED        :>.     /*MAbdallah*/
  .FLS_CFG_DBTOC_UNSPECIFIED       :>.     /*MAbdallah*/
  
  .CAN_CFG_DATA_8BIT               :>.  /*MAbdElkader*/
  .CAN_CFG_DATA_UNSPECIFIED		   :>.  /*MAbdElkader*/
  .CAN_CFG_DBTOC_UNSPECIFIED       :>.  /*MAbdElkader*/
  .WDG59_A_CFG_DATA_UNSPECIFIED    :>.  /*MAbdElkader*/
  .CONST_ROM_8BIT	           	   :>.  /*MAbdElkader*/
  .RAMTST_CFG_DATA_UNSPECIFIED	   :>.  /*MAbdElkader*/
  .FLSTST_CFG_DBTOC_UNSPECIFIED    :>.  /*MAbdElkader*/
  .CORTST_CFG_DATA_UNSPECIFIED     :>.  /*MAbdElkader*/
  .FLS_CFG_DATA_UNSPECIFIED		   :>.
  

  .rodata   align(4)               :
  {
    "*(.*os_rodata*)"
  }>.                                      /* constant datas in normal area */

  .text     align(4)               :
  {
    "*(.*os_text*)"
  }>.     /* program code area */
  .DIO_CODE_ROM                    :>.     /* program code area for DIO module based on ASIL req for AUTOSAR4.2.2 */
  .DIO_CODE_ROM_LOCAL              :>.     /* program code area for DIO module based on ASIL req for AUTOSAR4.2.2 */
  .MCU_PUBLIC_CODE_ROM             :>.     /* program code area for MCU module based on ASIL req for AUTOSAR4.2.2 */
  .MCU_PRIVATE_CODE_ROM            :>.     /* program code area for MCU module based on ASIL req for AUTOSAR4.2.2 */
  .MCU_CFG_DATA_8				   :>.
  .PORT_CODE_ROM                   :>.     /* program code area for PORT module based on ASIL req for AUTOSAR4.2.2 */
  .SPI_PUBLIC_CODE_ROM             :>.     /*from Spi.o        -- program code area for SPI module based on ASIL req for AUTOSAR4.2.2 */
  .SPI_PRIVATE_CODE_ROM            :>.     /*from Spi_Driver.o -- program code area for SPI module based on ASIL req for AUTOSAR4.2.2 */
  .SPI_FAST_CODE_ROM               :>.
  .ADC_PUBLIC_CODE_ROM             :>.
  .ADC_FAST_CODE_ROM               :>.
  .GPT_CODE_ROM                    :>.    /* from Gpt.o */
  .GPT_FAST_CODE_ROM               :>.    /* Gpt_Irq.o  */
  .PWM_PUBLIC_CODE_ROM             :>.    /* from Pwm.o */
  .PWM_PRIVATE_CODE_ROM            :>.    /* from Pwm.o */
  .PWM_FAST_CODE_ROM               :>.    /* from Pwm_Irq.o */
  .ICU_PUBLIC_CODE_ROM             :>.
  .ICU_FAST_CODE_ROM               :>.
  .ICU_PRIVATE_CODE_ROM            :>.
  .LIN_CODE_ROM                    :>. 	  /*MAbdallah*/
  .LIN_FAST_CODE_ROM               :>. 	  /*MAbdallah*/
  .FLS_PUBLIC_CODE_ROM			   :>.    /*MAbdallah*/
  .FLS_PRIVATE_CODE_ROM			   :>.    /*MAbdallah*/
  .WDG59_A_PRIVATE_CODE_ROM        :>.  /*YAlshabo*/
  
  
  .CAN_PRIVATE_CODE_ROM	align(4)   :>. /*MAbdElkader*/
  .CAN_PUBLIC_CODE_ROM	align(4)   :>. /*MAbdElkader*/
  .CAN_FAST_CODE_ROM	align(4)   :>. /*MAbdElkader*/
  .WDG59_A_PUBLIC_CODE_ROM		   :>. /*MAbdElkader*/
  .WDG_59_DRIVERA_FAST_CODE		   :>. /*MAbdElkader*/
  .WDG_59_DRIVERA_FAST_CODE_ROM    :>. /*MAbdElkader*/
  .RAMTST_PUBLIC_CODE_ROM		   :>. /*MAbdElkader*/
  .FLSTST_APPL_CODE_ROM 	 	   :>. /*MAbdElkader*/
  .CORTST_APPL_CODE_ROM			   :>. /*MAbdElkader*/
  .CORTST_PRIVATE_CODE_ROM		   :>. /*MAbdElkader*/
  .CORTST_FAST_CODE_ROM		  	   :>. /*MAbdElkader*/
  .CORTST_PUBLIC_CODE_ROM		   :>. /*MAbdElkader*/
  .FLSTST_PUBLIC_CODE_ROM		   :>. /*MAbdElkader*/
  .FLSTST_PRIVATE_CODE_ROM		   :>. /*MAbdElkader*/
  
  .APPL_PARTNO                     :>.                 /* Application partnumbers */

   .MCU_CR_CODE_ROM      align(4)  :>.     /* program code area for MCU module based on ASIL req for AUTOSAR4.2.2 */
   /*The two sections "MCU_CODE_RRAM_INTVEC" & "MCU_CR_CODE_RRAM" must be consecutive in linker-file because of relative jump operation to initialization functions.*/
   .MCU_CODE_RRAM_INTVEC align(4)       :>.   /* this section contains the CStartup "Mcu_RRamCopy_asm.850" */
   .MCU_CR_CODE_RRAM     align(4)       :>.   /* program code area for PORT module based on ASIL req for AUTOSAR4.2.2 */

  .fixaddr  align(4)               :>.     /* ghs internal (compiler) */
  .fixtype  align(4)               :>.     /* ghs internal (compiler) */
  .secinfo  align(4)               :>.     /* ghs internal (runtime library) */
  .syscall  align(4)               :>.     /* ghs internal (linker) */

  .romUNSPECCIFIED ROM(.RAM_UNSPECIFIED) :>. /* constant data to initialize variables (copied to RAM in section RAM_UNSPECIFIED at startup)*/
  .romos_sdata ROM(.os_sdata) :>.            /* constant data to initialize variables (copied to RAM in section .os_sdata at startup)*/
  
  .romdata  ROM(.data)             :>.     /* constant data to initialize variables (copied to RAM at startup)*/
  .romzdata ROM(.zdata)            :>.     /* constant data to initialize variables in ZDA area (copied to RAM at startup)*/
  .romsdata ROM(.sdata)            :>.     /* constant data to initialize variables in SDA area (copied to RAM at startup)*/
  .romtdata ROM(.tdata)            :>.     /* constant data to initialize variables in TDA area (copied to RAM at startup)*/

/*******************************************************************************************************************/
  __top_of_iROM_0 = MEMENDADDR(iROM_0);                                         
  .bcode                    align(4)                                            :>iROM_1   
  .bconst                   align(4)                                            :>.        
  __top_of_iROM1 = MEMENDADDR(iROM_1);                                         
                                                                               
/********************************* Start of internal RAM area (iRAM_0) *************************************************/                                        

  .NOINIT_BL_RAM_32BIT             :>iRAM_0     /* zero initialized data in SDA area for MCU based on ASIL req for AUTOSAR4.2.2 */
  .NOINIT_RAM_8BIT                 :>.     /* zero initialized data in SDA area for MCU based on ASIL req for AUTOSAR4.2.2 */

  .data                            :>.  /* initialized data */

  .bss      align(4)               :
  {
    "*(.*os_bss*)"
  }>.     /* zero initialized data*/
  .sdabase  align(4)               :>.     /* initialize globalpointer GP for SDA addressing */
  .sdata    align(4)               :          
  { 
  "*(.RAM_1BIT*)"
  
  }>.     /* initialized data in SDA area*/
  .LOCAL_RAM_AREA1                 :>.     /*from Spi_Ram.o*/
  .RAM_8BIT                        :>.  /*MAbdElkader*/
                                                                       
  .sbss     align(4)               :                                           
  {                                                                            
    "*(.os_sbss*)",                                                            
    "*(.rm_data_section*)"                                                                                                                              
                                                                               
  }>.                                      /* zero initialized data in SDA area*/
  .NOINIT_RAM_1BIT                 :>.     /*from Spi_Ram.o -- zero initialized data in SDA area for SPI based on ASIL req for AUTOSAR4.2.2 */
  .NOINIT_RAM_16BIT                :>.     /* zero initialized data in SDA area for DIO based on ASIL req for AUTOSAR4.2.2 */
  .NOINIT_RAM_32BIT                :>.     /* zero initialized data in SDA area for MCU based on ASIL req for AUTOSAR4.2.2 */
  .NOINIT_RAM_UNSPECIFIED          :>.     /* zero initialized data in SDA area for MCU based on ASIL req for AUTOSAR4.2.2 */
  .ICU_CFG_RAM_UNSPECIFIED         :>.
  .MCU_CFG_BURAM_NO_INIT_8         :>.
  
  .RAM_UNSPECIFIED                 :>.



  .zdata    align(4)               :>.     /* initialized data in ZDA area*/
  .zbss     align(4)               :>.     /* zero initialized data in ZDA area*/

  .tdata    align(4) MAX_SIZE(2) :>.     /* initialized and zero-initialized data in TDA area */

/************************************************************************************************************/
   .os_data  align(4)  :>.
   _os_data_StartAddr = addr(.os_data);
   _os_data_EndAddr = endaddr(.os_data);
   .os_sdata  align(4)  :>.
   _os_sdata_StartAddr = addr(.os_sdata);
   _os_sdata_EndAddr = endaddr(.os_sdata);



/*****************************************************************************************************************/

  .FAST_RAM_1BIT                                      :>.
  .FAST_RAM_8BIT                                      :>.
  .FAST_RAM_16BIT                                     :>.
  .FAST_RAM_32BIT                                     :>.
  .FAST_RAM_UNSPECIFIED                               :>.
  .WDG59_A_CFG_RAM_UNSPECIFIED               	      :>.
  .MCU_CFG_RAM_UNSPECIFIED                            :>.
  .MCU_FAST_CODE_ROM                                  :>.

  .stack                    align(4) pad(0)      :>.           /* definition of stack size */

  .heapbase                 align(4)                  :>.
  __top_of_iRAM_0 = MEMENDADDR( iRAM_0);
 /* Start of internal retention RAM area (iRAM_R) */
  .rcode                    align(4) pad(0)      :>iRAM_R      /* definition RRAM of code size */
  .rdata                    align(4)                  :>.           /* user defined segment for for initialized data located in retention RAM  */
  .MCU_CFG_BURAM_NO_INIT_32       :>.
  .rbss                     align(4)                  :>.           /* user defined segment for zero initialized data located in retention RAM */
  .rsbss                    align(4)                  :>.           /* user defined segment for zero initialized data located in retention RAM */
  .rstack                   align(4) pad(0)      :>.           /* definition RRAM of stack size */
  __top_of_iRAM_R = MEMENDADDR( iRAM_R);

/*  Symbols for compiler references */
  ___ghs_romstart   = MEMADDR(iROM_0);
  ___ghs_romend     = MEMENDADDR(iROM_0);

  ___ghs_ramstart   = MEMADDR(iRAM_0);
  ___ghs_ramend     = MEMENDADDR(iRAM_0);

  ___ghs_rramstart  = MEMADDR(iRAM_R);
  ___ghs_rramend    = MEMENDADDR(iRAM_R);

 

 }

/*===========================================================================*/
/*      End of File                                                          */
/*===========================================================================*/
