if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.3/arm")
endif()

set(DEFAULT_C_FLAGS --silent)
SET(DEFAULT_ASM_FLAGS )
set(DEFAULT_LINK_FLAGS --map ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.map )
set(LINKER_FILE_CFG_PAR --config)

set(DEFAULT_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")

set(SOURCE_FILE_EXTENSIONS         c asm s)
set(INCLUDE_FILES_EXTENSIONS       h)

set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/iccarm.exe)
set(CMAKE_ASM_COMPILER              ${COMPILER_PATH}/bin/iasmarm.exe)
set(CMAKE_LINKER                    ${COMPILER_PATH}/bin/ilinkarm.exe)
set(ELF_TOOL                        "${COMPILER_PATH}/bin/ielftool.exe")

if(NOT DEFINED checksum)
    set(checksum --fill 0xFF\\\\\\;__checksum_begin-__checksum_end --checksum __checksum:2,sum8wide:1,0x0\\\\\\;__checksum_begin-__checksum_end)
endif()

if(DEFINED checksum)
    set(OUT_FILL_COMMAND ${ELF_TOOL} ${checksum} --verbose ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX})
endif()


if(NOT DEFINED post_build_recipe)
    set(post_build_recipe ${ELF_TOOL} --verbose --ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_HEX_SUFFUX})
endif()


# if(DEFINED post_build_recipe)
#     set(post_build_recipe ${ELF_TOOL} --checksum __checksum:2,sum8wide:1,0x0\\\\\\;0x1100B000-0x1103DFF5 --verbose ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} && ${ELF_TOOL} --checksum __checksum2:4,crc32:1moi,0xFFFFFFFF\\\\\\;0x1100C000-0x1103DFFB --verbose --ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.${DEFAULT_EXECUTABLE_SUFFIX})

# endif()

set(POST_BUILD_COMMAND ${post_build_recipe})
set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
