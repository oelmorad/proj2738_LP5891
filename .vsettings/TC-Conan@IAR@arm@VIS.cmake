if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.3/arm")
endif()

set(CMAKE_SYSTEM_NAME Generic)

set(VCONAN_COMPILER_FLAGS --silent)
SET(VCONAN_ASSEMBLER_FLAGS )
set(DEFAULT_LINK_FLAGS --map ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map --strip)
set(DEFAULT_LINK_FLAGS_DEBUG --map ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VCONAN_LINKER_SCRIPT_OPTION --config)
set(CMAKE_C_FLAGS_RELEASE "" CACHE STRING "Description" FORCE)
set(CMAKE_C_FLAGS_RELEASE_INIT "")



# <----- TOOLCHAIN FLAGS ----->
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #

set(VCONAN_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")
set(VCONAN_STATIC_LIB_SUFFIX "a")

set(SOURCE_FILE_EXTENSIONS         c asm s)
set(INCLUDE_FILES_EXTENSIONS       h)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/iccarm.exe)
set(CMAKE_ASM_COMPILER              ${COMPILER_PATH}/bin/iasmarm.exe)
set(CMAKE_LINKER                    ${COMPILER_PATH}/bin/ilinkarm.exe)
set(ELF_TOOL                        "${COMPILER_PATH}/bin/ielftool.exe")

if(NOT DEFINED checksum)
    set(checksum --fill 0xFF\\\\\\;__checksum_begin-__checksum_end --checksum __checksum:2,sum8wide:1,0x0\\\\\\;__checksum_begin-__checksum_end)
endif()

set(OUT_FILL_COMMAND ${ELF_TOOL} ${checksum} --strip --verbose ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${VCONAN_EXECUTABLE_SUFFIX} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${VCONAN_EXECUTABLE_SUFFIX})


set(post_build_recipe ${ELF_TOOL} --strip --verbose --ihex ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${VCONAN_EXECUTABLE_SUFFIX} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DEFAULT_HEX_SUFFUX})


set(POST_BUILD_COMMAND ${post_build_recipe})

set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)

list(APPEND VCONAN_POST_BUILD_COMMANDS OUT_FILL_COMMAND POST_BUILD_COMMAND)