if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.5/430")
endif()


set(COMPILER_INCLUDES ${COMPILER_PATH}/inc ${COMPILER_PATH}/lib)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/icc430.exe)
set(CMAKE_ASM_COMPILER              ${COMPILER_PATH}/bin/a430.exe)
set(CMAKE_LINKER                    ${COMPILER_PATH}/bin/xlink.exe)
# set(ELF_TOOL                        "${COMPILER_PATH}/bin/ielftool.exe")

set(DEFAULT_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")

set(SOURCE_FILE_EXTENSIONS c asm s)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS asm s)
set(INCLUDE_FILES_EXTENSIONS h)



set(DEFAULT_C_FLAGS )
SET(DEFAULT_ASM_FLAGS )
set(DEFAULT_LINK_FLAGS )

set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
