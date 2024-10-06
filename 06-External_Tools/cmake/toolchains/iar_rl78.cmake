message("PROJECT_DIR: ${PROJECT_DIR}")
## CHeck what is the external projects folder 
## TODO: This should be in the root.cmake of modules "To be fixed"
if(EXISTS "${PROJECT_DIR}/08-Ext")
	set(EXTDIR "08-Ext")
elseif(EXISTS "${PROJECT_DIR}/07-Ext")
    set(EXTDIR "07-Ext")
elseif(EXISTS "${PROJECT_DIR}/08-External_Projects")
	set(EXTDIR "08-External_Projects")
elseif(EXISTS "${PROJECT_DIR}/07-External_Projects")
    set(EXTDIR "07-External_Projects")
endif()


## add iar_vwsrl78 specific includes
include("${CMAKE_CURRENT_LIST_DIR}/../includes/iar_rl78_includes.cmake")

set(CMAKE_C_OUTPUT_EXTENSION ".r34")

if(NOT COMPILER_PATH)
    set(COMPILER_PATH "C:/Program Files (x86)/IAR Systems/Embedded Workbench 7.0/rl78")
endif()

## append compiler include directories
# set(COMPILER_INCLUDES "")
# list(APPEND COMPILER_INCLUDES ${COMPILER_PATH}/inc)
# list(APPEND COMPILER_INCLUDES ${COMPILER_PATH}/inc/c)
# list(APPEND COMPILER_INCLUDES ${COMPILER_PATH}/lib)
set(COMPILER_INCLUDES ${COMPILER_PATH}/inc ${COMPILER_PATH}/inc/c ${COMPILER_PATH}/lib)



set(DEFAULT_EXECUTABLE_SUFFIX "elf")
set(DEFAULT_HEX_SUFFUX        "mot")
set(DEFAULT_DEBUG_SUFFUX        "d87")

set(LINKER_FILE_CFG_PAR -f)


set(CMAKE_C_COMPILER                ${COMPILER_PATH}/bin/iccrl78.exe)
set(CMAKE_LINKER                    "${COMPILER_PATH}/bin/xlink.exe")
set(CMAKE_ASM_COMPILER              ${COMPILER_PATH}/bin/arl78.exe)
set(ELF_TOOL                        ${COMPILER_PATH}/bin/ielftool.exe)



INCLUDE(CMakeForceCompiler)

set(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
set(CMAKE_C_COMPILER_FORCED TRUE CACHE INTERNAL "")
set(CMAKE_C_COMPILER_ID_RUN TRUE CACHE INTERNAL "")

## force compiler for IAR RL78
CMAKE_FORCE_C_COMPILER (${CMAKE_C_COMPILER} RL78)
set(CMAKE_C_COMPILER_ID "Tasking")



set(SOURCE_FILE_EXTENSIONS         c asm s s87)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS asm s s87)
set(INCLUDE_FILES_EXTENSIONS       h)



## Filter from CFLAGS and LDFLAGS the ones that are specific to the core (rl78_1 & rl78_2) to avoid 
## duplicating flags
# string(REPLACE --dlib_config "" CUSTOM_C_FLAGS ${CUSTOM_C_FLAGS})
# string(REPLACE "dlrl78fn1n.h" "" CUSTOM_C_FLAGS ${CUSTOM_C_FLAGS})
# string(REPLACE "dlrl78fn2n.h" "" CUSTOM_C_FLAGS ${CUSTOM_C_FLAGS})

# if(CUSTOM_LINK_FLAGS STREQUAL "")
#     message("Empty linker flags script")
# else()
#     message("Not Empty linker flags script")
#     string(REPLACE "dlrl78fn1n.r87" "" CUSTOM_LINK_FLAGS ${CUSTOM_LINK_FLAGS})
#     string(REPLACE "dlrl78fn2n.r87" "" CUSTOM_LINK_FLAGS ${CUSTOM_LINK_FLAGS})
# endif()

if (NOT DEFINED DEVICE_FILE)
    set(DEVICE_FILE "ior5f10pmh.h")
endif()

if (NOT DEFINED DEVICE_FILE_EXT)
    set(DEVICE_FILE "ior5f10pmh_ext.h")
endif()

set(MCU ${MICROCONTROLLER})

# Adding mandatory flags
# set(DEFAULT_ASM_FLAGS --core ${MCU} -D__DEVICE_FILE__=\"${DEVICE_FILE}\" -D__DEVICE_FILE_EXT__=\"${DEVICE_FILE_EXT}\" -ld ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --silent --dependencies=m ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(DEFAULT_ASM_FLAGS --core ${MCU} -D__DEVICE_FILE__=\"${DEVICE_FILE}\" -D__DEVICE_FILE_EXT__=\"${DEVICE_FILE_EXT}\" -ld ${CMAKE_LST_OUTPUT_DIRECTORY} --silent)

# add a flag customized for vcshell
set(VCCPPFLAGS := ${CPPFLAGS})
# set(CPPFLAGS ${CPPFLAGS} -I${COMPILER_PATH}\inc -I${COMPILER_PATH}\inc\c -I${COMPILER_PATH}\lib)

# set(CFLAGS_First_Part ${CUSTOM_C_FLAGS})

set(CFLAGS_First_Part --core=${MCU} --no_wrap_diagnostics -l ${CMAKE_LST_OUTPUT_DIRECTORY}) #--code_model=far --data_model=near --near_const_location ROM0 -Om --no_tbaa -e -l)
# set(CFLAGS_Second_Part --core=${MICROCONTROLLER} --code_model=far --data_model=near --near_const_location ROM0 -Om --no_tbaa -e)
# set(CFLAGS_Third_Part --no_system_include --remarks --no_wrap_diagnostics --macro_positions_in_diagnostics --diag_error=Pe223 --debug)


## Append CLAGS First , second and third part
set(DEFAULT_C_FLAGS ${CFLAGS_First_Part})# ${CFLAGS_Second_Part} ${CFLAGS_Third_Part})

set(Binary_FLAGS ${custom_binaries})

## append 





file(GLOB LINKER_INCLUDES "${PROJECT_DIR}/${EXTDIR}/SWC_EEL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_FDL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_FSL_T01E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_CMP_Specific_RL78*/02-SRC/" "${PROJECT_DIR}/${EXTDIR}/CSWC_BLD_RL78*/03-SRC/00-Out/")
if(NOT PROJECT_REUSE STREQUAL "")
    message("PROJECT_REUSE defined")
    file(GLOB LINKER_INCLUDES "${PROJECT_DIR}/${EXTDIR}/${PROJECT_REUSE}/${EXTDIR}/SWC_EEL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/${PROJECT_REUSE}/${EXTDIR}/SWC_FDL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/${PROJECT_REUSE}/${EXTDIR}/SWC_FSL_T01E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/${PROJECT_REUSE}/${EXTDIR}/SWC_CMP_Specific_RL78*/02-SRC/" "${PROJECT_DIR}/${EXTDIR}/${PROJECT_REUSE}/${EXTDIR}/CSWC_BLD_RL78*/03-SRC/00-Out/")
else()
    file(GLOB LINKER_INCLUDES "${PROJECT_DIR}/${EXTDIR}/SWC_EEL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_FDL_T02E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_FSL_T01E_RL78*/src/" "${PROJECT_DIR}/${EXTDIR}/SWC_CMP_Specific_RL78*/02-SRC/" "${PROJECT_DIR}/${EXTDIR}/CSWC_BLD_RL78*/03-SRC/00-Out/")
endif()


# message("Linker Includes: ${LINKER_INCLUDES}dfsdf")

set(LINKER_INCLUDES_LIST "")
foreach(LINKER_INCLUDE ${LINKER_INCLUDES})
    set(LINKER_INCLUDES_LIST "${LINKER_INCLUDES_LIST} -I\"${LINKER_INCLUDE}\"")
endforeach()
# message("LINKER_INCLUDES_LIST: ${LINKER_INCLUDES_LIST}")

## append custom linker includes
# set(LINKER_INCLUDES "${LINKER_INCLUDES} ${Custom_Linker_Includes}")
list(APPEND LINKER_INCLUDES ${Custom_Linker_Includes})
list(APPEND LINKER_INCLUDES "${LINKER_INCLUDES}")

# Adding linker options to replace default multiplication/division functions
# with the HW multiplication/division functions
#et(DEFAULT_LINK_FLAGS )#"-eHWDIV_8_8_8=?UC_DIV_L01 -eHWMOD_8_8_8=?UC_MOD_L01 -eHWSDIV_8_8_8=?SC_DIV_L01 -eHWSMOD_8_8_8=?SC_MOD_L01 -eHWSDIV_16_16_16=?SI_DIV_L02 -eHWSMOD_16_16_16=?SI_MOD_L02 -eHWSDIV_32_32_32=?SL_DIV_L03 -eHWSMOD_32_32_32=?SL_MOD_L03")
set(DEFAULT_LINK_FLAGS_DEBUG "-Fmotorola -l ${PROJECT_DIR}/Make_Exe/04-Exe/STD_SWC.map")#"${DEFAULT_LINK_FLAGS} -cRL78 ${checksum} -HFFFF -l ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.map -xeimns -rt -Oieee695,lbm=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.695 -Oelf,spc=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf -z")
set(DEFAULT_LINK_FLAGS_RELEASE )#"${DEFAULT_LINK_FLAGS} -cRL78 ${checksum} -HFFFF -l ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.map -xeimns -rt -Oieee695,lbm=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.695 -Oelf,spc=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf -z -Omotorola-s28=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.s28")

set(EXEC_OUTPUT "-o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.mot")
set(LIBS ${LDLIBRARIES})


set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
