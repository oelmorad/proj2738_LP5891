set(PROJECT_TYPE "CSWC")
set(PROJECT_NAME "CSWC_PLTF_BSW_VLS_NXPS32K1xx")

set(COMPILER_TYPE "IAR")
set(COMPILER_VER "V8.40.2.214")
set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm")
set(ARCHITECTURE "NXP")
set(MICROCONTROLLER "S32K")
set(PROCESSOR "S32K144")
set(ROM_SIZE 2000000)
set(BL_SIZE 128000)
set(RAM_SIZE 128000)
set(RAM_START_ADDRESS 0xfebd0000)
set(LNKFILENAME S32K144_64_flash.icf)
set(EXECLUDE_DIRS   
                    platform/devices/S32K116
                    platform/devices/S32K118
                    platform/devices/S32K142
                    platform/devices/S32K142W
                    # platform/devices/S32K144
                    platform/devices/S32K144W
                    platform/devices/S32K146
                    platform/devices/S32K148
                    08-External_Projects/CSWC_PLTF_MCU_VLS_NXPS32K1xx/08-External_Projects/LIB_LCRC

                    )

set(EXECLUDE_FILES  can_pal.c  i2s_pal.c ic_irq.c ic_pal.c mpu_pal.c oc_irq.c oc_pal.c pwm_pal.c security_pal.c  wdg_pal.c cmp_driver.c cmp_hw_access.c 
                    crc_driver.c crc_hw_access.c csec_driver.c csec_hw_access.c eim_driver.c eim_hw_access.c enet_driver.c enet_hw_access.c enet_irq.c 
                    erm_driver.c erm_hw_access.c  ewm_driver.c flash_mx25l6433f_driver.c flexcan_driver.c  excan_hw_access.c flexcan_irq.c flexio_i2c_driver.c  
                    flexio_i2s_driver.c flexio_uart_driver.c lin_common.c  lin_driver.c lin_irq.c phy_enet_access.c phy_shared.c sbc_fs45_driver.c   
                    lpit_driver.c mpu_driver.c mpu_hw_access.c  phy_generic.c phy_tja110x.c phy.c quadspi_driver.c rtc_driver.c  rtc_hw_access.c rtc_irq.c 
                    sai_driver.c osif_freertos.c sbc_uja113x.c sbc_uja1169_driver.c  lin_common_api.c lin_common_proto.c lin_commontl_api.c lin_commontl_proto.c  
                    lin_diagnostic_service.c lin_j2602_proto.c lin_lin21_proto.c lin.c sbc_uja113x.c sbc_uja1169_driver.c platform/lpuart_driver.c)

set(CUSTOM_C_FLAGS  --no_wrap_diagnostics -e --cpu Cortex-M4 --fpu None --debug --dlib_config "${COMPILER_PATH}/inc/c/DLib_Config_Normal.h" 
                    --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering 
                    --no_scheduling -DSTART_FROM_FLASH -DCPU_S32K144HFT0VLLT --diag_suppress=Pa050,Pa082,Pe550,Pe177  
                     -DTS_ARCH_FAMILY -DTS_ARCH_DERIVATE --warnings_are_errors --silent)
set(CUSTOM_ASM_FLAGS --cpu Cortex-M4 --fpu None -s+ -DSTART_FROM_FLASH)
set(CUSTOM_LINK_FLAGS --no_wrap_diagnostics --entry Reset_Handler)
