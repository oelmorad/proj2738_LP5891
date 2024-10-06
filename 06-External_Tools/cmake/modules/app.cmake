cmake_minimum_required(VERSION 3.0.0)

include("${CMAKE_CURRENT_LIST_DIR}/scanrules.cmake")

set(ALL_SOURCE_FILES    "")
set(ALL_INCLUDE_DIRS    "")
set(CHILD_FILES         "")
set(SRC_DIR "03-SRC")
 set(TEST_DIR "05-SW_Tests/01-Unitary/01-VectorCast/01-VCAST_Manage")

SCAN_APP(${PROJECT_DIR})
# Classify sources and directories
foreach(FILE ${CHILD_FILES})
    if(IS_DIRECTORY ${FILE})
        list(APPEND ALL_INCLUDE_DIRS ${FILE})
    else()
        list(APPEND ALL_SOURCE_FILES ${FILE})
    endif()
endforeach()

# filter out header files and plain directories
set(file_extensions "")
foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
    set(file_extensions "${file_extensions}|\\.${EXTENSION}$")
endforeach()
STRING(SUBSTRING  ${file_extensions} 1 -1 file_extensions)
message("file_extensions: ${file_extensions}")
list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "\\.h$")
foreach(FILE ${ALL_SOURCE_FILES})
    # message("SEARCHING FOR: ${FILE}")
    if(NOT ${FILE} MATCHES "${file_extensions}")
        list(REMOVE_ITEM ALL_SOURCE_FILES ${FILE} )
    endif()
endforeach()


# add compiler include directories and compiler include source files for RL78
message("Added Compiler Include directories")
list(APPEND ALL_SOURCE_FILES ${VWS_SOURCE_FILES} ${RL78_SOURCE_FILES}) 
list(APPEND ALL_INCLUDE_DIRS ${VWS_INCLUDES} ${RL78_INCLUDES})

# Execlude Directories
foreach(EXECLUDE_DIR ${EXECLUDE_DIRS})
    list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "${EXECLUDE_DIR}/.*")
    list(FILTER ALL_INCLUDE_DIRS EXCLUDE REGEX "${EXECLUDE_DIR}")
endforeach()

foreach(EXECLUDE_DIR_EXACT ${EXECLUDE_EXACT_DIRS})

    list(REMOVE_ITEM ALL_INCLUDE_DIRS ${EXECLUDE_DIR_EXACT} )
    
endforeach(EXECLUDE_DIR_EXACT)

# Execlude Includes "added specifically for VWSRL78"
foreach(EXECLUDE_INC ${EXECLUDE_INCLUDES})
    list(FILTER ALL_INCLUDE_DIRS EXCLUDE REGEX "/${EXECLUDE_INC}$")
endforeach()


# Execlude Files
foreach(EXECLUDE_FILE ${EXECLUDE_FILES})
    list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "/${EXECLUDE_FILE}$")
endforeach()


# Sort files and include directories
list(SORT ALL_INCLUDE_DIRS)

####################### TODO: workaround to provide custom assembly flags in clang
if(${COMPILER_TYPE} STREQUAL "CLANG")
add_subdirectory(${PROJECT_DIR}/03-SRC/App/Utils/CLANG ${PROJECT_DIR}/03-SRC/App/Utils/CLANG)
endif()
####################### TODO: END

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # Handle case when there is duplicate file with the same name but in different path
    remove_duplicate_files("${ALL_SOURCE_FILES}")
    set(ALL_SOURCE_FILES ${output_list})
    # Compile Target
	list(SORT ALL_SOURCE_FILES COMPARE FILE_BASENAME)
    add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})
    list(APPEND ALL_INCLUDE_DIRS ${LINKER_INCLUDES})
    
	# if(DEFINED SORT_INCLUDES_DESC)
        # if(${SORT_INCLUDES_DESC})
            # list(SORT ALL_INCLUDE_DIRS ORDER DESCENDING)
        # endif()
    # endif()
	
	
    target_include_directories(${PROJECT_NAME} PUBLIC ${ALL_INCLUDE_DIRS} ${compiler_include_directories} ${COMPILER_INCLUDES})
    if(${COMPILER_TYPE} STREQUAL "CLANG")
    target_link_libraries(${PROJECT_NAME} PRIVATE os_asm)
    endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".${DEFAULT_EXECUTABLE_SUFFIX}")
    target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${CUSTOM_C_FLAGS} ${DEFAULT_C_FLAGS}>
    $<$<COMPILE_LANGUAGE:ASM>:${CUSTOM_ASM_FLAGS} ${DEFAULT_ASM_FLAGS}>
    )

    ## Handle custom compilation flags for specific source files
    if(DEFINED DIRECTORY_C_FLAGS_TABLE)
        foreach(pair IN LISTS DIRECTORY_C_FLAGS_TABLE)
            string(FIND "${pair}" ":" pos)
            if (pos LESS 1)
                message(WARNING "Skipping malformed pair (no var name): ${pair}")
            else()
                string(SUBSTRING "${pair}" 0 "${pos}" var)
                math(EXPR pos "${pos} + 1") # Skip the separator
                string(SUBSTRING "${pair}" "${pos}" -1 val)
                message("Flag is: ${val}")
                string(CONCAT source_path ${PROJECT_DIR} "/" ${var})
                File(GLOB filtered_sources "${source_path}/*.c")
                foreach(item ${filtered_sources})
                    list(FIND ALL_SOURCE_FILES ${item} index)
                    if(index GREATER -1)
                        # Check if variable flag is defined
                        if(NOT DEFINED ${val})
                            message(WARNING "Please define Custom variable flag: ${val}")
                        else()
                            set_source_files_properties(${item} PROPERTIES COMPILE_FLAGS ${${val}})
                        endif()
                    else()
                        # message("${item} is not found")
                    endif()                
                endforeach()
            endif()
        endforeach()

    endif()    

    ## Overwrite compilation command in case of IAR RL78 as it produce error due to added -c flag
    if(${ARCHITECTURE} STREQUAL "VWSRL78")
        set(CMAKE_C_RESPONSE_FILE_LINK_FLAG "-f ")
        set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> --dependencies=m ${CMAKE_DEP_OUTPUT_DIRECTORY} -o <OBJECT> <SOURCE>")
        set(OBJECTS ${OBJECTS} ${LDLIBRARIES})
        if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(DEFAULT_LINK_FLAGS ${DEFAULT_LINK_FLAGS_RELEASE})
        elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(DEFAULT_LINK_FLAGS ${DEFAULT_LINK_FLAGS_DEBUG})
        endif()
        set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> ${custom_binaries} ${LINKER_INCLUDES_LIST} ${DEFAULT_LINK_FLAGS} ${CUSTOM_LINK_FLAGS} ${LINKER_FILE_CFG_PAR} ${PROJECT_DIR}/${SRC_DIR}/01-Make/${LNKFILENAME} ${LDLIBRARIES} <OBJECTS>")
    elseif(${ARCHITECTURE} STREQUAL "RL78")
        set(CMAKE_C_RESPONSE_FILE_LINK_FLAG "-f ")
        set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> --dependencies=m ${CMAKE_DEP_OUTPUT_DIRECTORY} -o <OBJECT> <SOURCE>")
        set(OBJECTS ${OBJECTS} ${LDLIBRARIES})
        if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(DEFAULT_LINK_FLAGS ${DEFAULT_LINK_FLAGS_RELEASE})
        elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(DEFAULT_LINK_FLAGS ${DEFAULT_LINK_FLAGS_DEBUG})
        endif()
        set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> ${custom_binaries} ${LINKER_INCLUDES_LIST} <OBJECTS> ${EXEC_OUTPUT} ${DEFAULT_LINK_FLAGS} ${LINKER_FILE_CFG_PAR} ${PROJECT_DIR}/${SRC_DIR}/01-Make/${LNKFILENAME} ${CUSTOM_LINK_FLAGS} ${LDLIBRARIES}")
    elseif(${ARCHITECTURE} STREQUAL "MSP430")
        target_link_options(${PROJECT_NAME} BEFORE PUBLIC ${DEFAULT_LINK_FLAGS} ${CUSTOM_LINK_FLAGS} ${LINKER_FILE_CFG_PAR})
    else()
        target_link_options(${PROJECT_NAME} BEFORE PUBLIC ${DEFAULT_LINK_FLAGS} ${CUSTOM_LINK_FLAGS} ${LINKER_FILE_CFG_PAR} ${PROJECT_DIR}/${SRC_DIR}/01-Make/${LNKFILENAME})
    endif()
    ## Check if there is another POST_BUILD_COMMAND "Added for IAR ARM"
    if(DEFINED OUT_FILL_COMMAND)
        message("Executing out file fill command")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${OUT_FILL_COMMAND})
    endif()

	## remove old created vcshell.db
	file(REMOVE ${PROJECT_DIR}/${TEST_DIR}/vcshell.db)

    # Add Custom Build Command

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${POST_BUILD_COMMAND})

    if(DEFINED POST_BUILD_COMMAND_GEN_OUT_EXE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${POST_BUILD_COMMAND_GEN_OUT_EXE})
    endif()

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${GENERATE_VCSHELL} WORKING_DIRECTORY ${PROJECT_DIR}/${TEST_DIR})
	
    
endif()