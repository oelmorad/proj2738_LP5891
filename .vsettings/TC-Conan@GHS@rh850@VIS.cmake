if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/ghs/comp_201355")
endif()

set(CMAKE_SYSTEM_NAME Generic)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE  "STATIC_LIBRARY")
# string(TOLOWER ${ARCHITECTURE} LC_ARCH)
# string(TOUPPER ${ARCHITECTURE} UC_ARCH)
# string(TOUPPER ${MICROCONTROLLER} UC_MCU)
# string(TOLOWER ${COMPILER_TYPE} UC_COMP)
set(VCONAN_COMPILER_FLAGS    )
SET(VCONAN_ASSEMBLER_FLAGS  )
set(VCONAN_LINKER_FLAGS )
set(VCONAN_LINKER_SCRIPT_OPTION "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# <----- TOOLCHAIN FLAGS ----->
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



# ---------------------------------------------------------------------------- #

set(VCONAN_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")
set(VCONAN_STATIC_LIB_SUFFIX "a")

## append compiler include directories
set(COMPILER_INCLUDES ${COMPILER_PATH}/src/libsys ${COMPILER_PATH}/ansi)

set(SOURCE_FILE_EXTENSIONS         c asm 850 s)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS asm 850 s)
set(INCLUDE_FILES_EXTENSIONS       h)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/ccrh850.exe)
set(CMAKE_AR                        ${COMPILER_PATH}/ccrh850.exe)
set(GSREC                           ${COMPILER_PATH}/gsrec.exe)

set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> -archive -o <TARGET> <OBJECTS>")

set(POST_BUILD_COMMAND  ${GSREC}  -o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DEFAULT_HEX_SUFFUX} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${VCONAN_EXECUTABLE_SUFFIX})

set(CMAKE_C_COMPILER_WORKS TRUE)

set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)

list(APPEND VCONAN_POST_BUILD_COMMANDS POST_BUILD_COMMAND)