if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.5/430")
endif()

set(CMAKE_SYSTEM_NAME Generic)

set(COMPILER_INCLUDES ${COMPILER_PATH}/inc ${COMPILER_PATH}/lib)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/icc430.exe)
set(CMAKE_ASM_COMPILER              ${COMPILER_PATH}/bin/a430.exe)
set(CMAKE_LINKER                    ${COMPILER_PATH}/bin/xlink.exe)
# set(ELF_TOOL                        "${COMPILER_PATH}/bin/ielftool.exe")

set(VCONAN_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")
set(VCONAN_STATIC_LIB_SUFFIX "a")

set(SOURCE_FILE_EXTENSIONS c asm s)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS asm s)
set(INCLUDE_FILES_EXTENSIONS h)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(VCONAN_COMPILER_FLAGS )
SET(VCONAN_ASSEMBLER_FLAGS )
set(VCONAN_LINKER_FLAGS )


get_filename_component(ROOT_DIR "../../../../" ABSOLUTE)
message("------------- ROOT_DIR: ${CONAN_PROJECT_ROOT} -------------------")

file(GLOB MAKE_FOLDER "${CONAN_PROJECT_ROOT}/03-SRC/01-Make"  "${CONAN_PROJECT_ROOT}/02-SRC/01-Make")
message("------------- MAKE_FOLDER: ${MAKE_FOLDER} -------------------")


# <----- TOOLCHAIN FLAGS ----->
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #


set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
