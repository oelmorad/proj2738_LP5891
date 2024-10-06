cmake_minimum_required(VERSION 3.0.0)

include("${CMAKE_CURRENT_LIST_DIR}/scanrules.cmake")

set(ALL_SOURCE_FILES    "")
set(ALL_INCLUDE_DIRS    "")
set(CHILD_FILES         "")
set(SRC_DIR "02-SRC")
set(TEST_DIR "04-Unit_Test/01-VectorCast/01-VCAST_Manage")
SCAN_CSAR(${PROJECT_DIR})
# Classify sources and directories
foreach(FILE ${CHILD_FILES})
    if(IS_DIRECTORY ${FILE})
        list(APPEND ALL_INCLUDE_DIRS ${FILE})
    else()
        list(APPEND ALL_SOURCE_FILES ${FILE})
    endif()
endforeach()

# Execlude Directories
foreach(EXECLUDE_DIR ${EXECLUDE_DIRS})
    list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "${EXECLUDE_DIR}/.*")
    list(FILTER ALL_INCLUDE_DIRS EXCLUDE REGEX "${EXECLUDE_DIR}")
endforeach()

# Execlude Files
foreach(EXECLUDE_FILE ${EXECLUDE_FILES})
    list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "/${EXECLUDE_FILE}$")
endforeach()

# Sort files and include directories
list(SORT ALL_SOURCE_FILES COMPARE FILE_BASENAME)
list(SORT ALL_INCLUDE_DIRS)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # No Build rule for CSAR
endif()

## remove old created vcshell.db
file(REMOVE ${PROJECT_DIR}/${TEST_DIR}vcshell.db)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${GENERATE_VCSHELL} WORKING_DIRECTORY ${PROJECT_DIR}/${TEST_DIR})


