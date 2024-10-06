set(PROJECT_TYPE "LIB")
set(PROJECT_NAME "LIB_LDEM")

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
set(EXECLUDE_DIRS   )

set(EXECLUDE_FILES )

set(CUSTOM_C_FLAGS  --no_wrap_diagnostics -e --cpu Cortex-M4 --fpu None --debug --dlib_config "${COMPILER_PATH}/inc/c/DLib_Config_Normal.h" 
                    --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering 
                    --no_scheduling -DSTART_FROM_FLASH -DCPU_S32K144LFT0MLLT --diag_suppress=Pa050,Pa082,Pe550,Pe177  
                     -DTS_ARCH_FAMILY -DTS_ARCH_DERIVATE --warnings_are_errors --silent)
set(CUSTOM_ASM_FLAGS --cpu Cortex-M4 --fpu None -s+ -DSTART_FROM_FLASH)
set(CUSTOM_LINK_FLAGS --no_wrap_diagnostics --entry Reset_Handler --map )
