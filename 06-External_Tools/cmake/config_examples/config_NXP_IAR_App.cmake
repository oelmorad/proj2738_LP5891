set(PROJECT_TYPE "APP")
set(PROJECT_NAME "GOLF_CMake")

set(COMPILER_TYPE "IAR")
set(COMPILER_VER "V8.40.2.214")
set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm")
set(ARCHITECTURE "NXP")
set(MICROCONTROLLER "S32K")
set(PROCESSOR "S32K118")
set(ROM_SIZE 2000000)
set(BL_SIZE 128000)
set(RAM_SIZE 128000)
set(RAM_START_ADDRESS 0xfebd0000)
set(LNKFILENAME S32K118_25_flash.icf)
set(EXECLUDE_DIRS   
                    platform/devices/S32K116
                    # platform/devices/S32K118
                    platform/devices/S32K142
                    platform/devices/S32K142W
                    platform/devices/S32K144
                    platform/devices/S32K144W
                    platform/devices/S32K146
                    platform/devices/S32K148
                    08-External_Projects/SWC_HELMOS
                    08-External_Projects/LIB_LSME
                    08-External_Projects/CSWC_PLTF_BSW_VLS_NXPS32K1xx/08-External_Projects/STACK_STD_NXPS32K1xx_Memory
                    08-External_Projects/CSWC_PLTF_BSW_VLS_NXPS32K1xx/08-External_Projects/LIB_LDEM
                    08-External_Projects/CSWC_PLTF_BSW_VLS_NXPS32K1xx/08-External_Projects/LIB_LFIL
                    08-External_Projects/CSWC_PLTF_BSW_VLS_NXPS32K1xx/08-External_Projects/LIB_LMATH
                    )

set(EXECLUDE_FILES  peripherals_dmaController1.c Dem.c Fim.c LCRC_prg.c lin1.c peripherals_watchdog1.c 
                    peripherals_uart_pal_2.c peripherals_spi4.c peripherals_spi3.c peripherals_spi2.c 
                    peripherals_spi1.c peripherals_flexTimer_ic_3.c peripherals_i2c1.c peripherals_pwrMan1.c 
                    peripherals_flexTimer_pwm_1.c peripherals_flexTimer_pwm_2.c peripherals_flexTimer_pwm_3.c i2c_pal.c 
                    spi_pal.c can_pal.c  i2s_pal.c ic_irq.c ic_pal.c mpu_pal.c oc_irq.c oc_pal.c pwm_pal.c security_pal.c 
                    wdg_pal.c cmp_driver.c cmp_hw_access.c crc_driver.c crc_hw_access.c csec_driver.c csec_hw_access.c 
                    eim_driver.c eim_hw_access.c enet_driver.c enet_hw_access.c enet_irq.c erm_driver.c erm_hw_access.c 
                    ewm_driver.c flash_mx25l6433f_driver.c flexcan_driver.c excan_hw_access.c flexcan_irq.c flexio_i2c_driver.c 
                    flexio_i2s_driver.c flexio_uart_driver.c lin_common.c lin_driver.c lin_irq.c phy_enet_access.c phy_shared.c 
                    sbc_fs45_driver.c  lpit_driver.c mpu_driver.c mpu_hw_access.c phy_generic.c phy_tja110x.c phy.c 
                    quadspi_driver.c rtc_driver.c rtc_hw_access.c rtc_irq.c sai_driver.c osif_freertos.c sbc_uja113x.c 
                    sbc_uja1169_driver.c lin_common_api.c lin_common_proto.c lin_commontl_api.c lin_commontl_proto.c 
                    lin_diagnostic_service.c lin_j2602_proto.c lin_lin21_proto.c lin.c sbc_uja113x.c sbc_uja1169_driver.c SWC_MCAL_NXPS32K1xx/02-SRC/platform/lpuart_driver.c
                    STACK_STD_NXPS32K1xx_Memory/01-SRC/Crc.c)

set(CUSTOM_C_FLAGS  --no_wrap_diagnostics -e --cpu Cortex-M0+ --fpu None --debug --dlib_config "${COMPILER_PATH}/inc/c/DLib_Config_Normal.h" 
                    --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering 
                    --no_scheduling -DSTART_FROM_FLASH -DCPU_S32K118 --diag_suppress=Pa050,Pa082,Pe550,Pe177  
                     -DTS_ARCH_FAMILY -DTS_ARCH_DERIVATE --warnings_are_errors --silent)
set(CUSTOM_ASM_FLAGS --cpu Cortex-M0+ --fpu None  -DSTART_FROM_FLASH)
set(CUSTOM_LINK_FLAGS --no_wrap_diagnostics --entry Reset_Handler --map )
