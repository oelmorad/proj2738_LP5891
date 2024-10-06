cmake_minimum_required(VERSION 3.0.0)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) 
    file(GLOB SRC_FOLDER "${CMAKE_SOURCE_DIR}/../.."  "${CMAKE_SOURCE_DIR}/../../*SRC") 
    include(${SRC_FOLDER}/01-Make/config.cmake)
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/toolchains/root.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/modules/root.cmake")

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) 
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C ASM)
endif()