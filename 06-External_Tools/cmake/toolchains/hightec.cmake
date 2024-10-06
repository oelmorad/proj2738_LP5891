if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/HighTec/toolchains/tricore/v4.9.4.1")
endif()

set(DEFAULT_C_FLAGS -g -Wall -std=c99 -Og -mtc162 -meabi -fno-short-enums -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -save-temps=obj -MMD)
SET(DEFAULT_ASM_FLAGS -g -Wall -std=c99 -Og -mtc162 -meabi -fno-short-enums -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -save-temps=obj -MMD)
set(DEFAULT_LINK_FLAGS -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.map -Wl,--mcpu=tc162 -Wl,--gc-sections -nostartfiles -Wl,-n  -Wl,-T )
set(LINKER_FILE_CFG_PAR "")

set(DEFAULT_EXECUTABLE_SUFFIX "elf")
set(DEFAULT_HEX_SUFFUX        "hex")

set(SOURCE_FILE_EXTENSIONS         c asm)
set(INCLUDE_FILES_EXTENSIONS       h)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/tricore-gcc.exe)
set(OBJCPY                           ${COMPILER_PATH}/bin/tricore-objcopy.exe)

set(POST_BUILD_COMMAND ${OBJCPY} -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_HEX_SUFFUX})
set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
