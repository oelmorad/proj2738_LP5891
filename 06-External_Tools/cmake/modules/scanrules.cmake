cmake_minimum_required(VERSION 3.0.0)

function(remove_duplicate_files FILE_LIST)
    cmake_policy(SET CMP0057 NEW) ## This policy exists in new versions of cmake
    set(duplicate_list "")
    set(uniq_list "")
    foreach(FILE_PATH ${FILE_LIST})
        # Extract the file name
        get_filename_component(FILE_NAME ${FILE_PATH} NAME)
        # Check if this file was already handled before
        if("${FILE_NAME}" IN_LIST duplicate_list)
            message("File: ${FILE_NAME} was already handled before")
            continue()
        endif()        
        list(APPEND duplicate_list ${FILE_NAME})

        # Search for file with the same name but different paths
        foreach(file ${FILE_LIST})
            if(file STREQUAL ${FILE_PATH})
                ## This is exact match then it is the first occurence
                # message("First Match for: ${FILE_NAME} in ${file}")
                list(APPEND uniq_list "${file}")
                break()
            endif()
        endforeach()
    endforeach()
    set(output_list ${uniq_list} PARENT_SCOPE)
endfunction()

# Helper function to remove duplicate files from list of source files
function(remove_duplicates input_list)
    cmake_policy(SET CMP0057 NEW) ## This policy exists in new versions of cmake
    # message("Parsing list: ${input_list}")
    set(uniq_list "")
    foreach(item ${input_list})
        # message("Currently parsing: ${item}")
        if(NOT "${item}" IN_LIST uniq_list)
            list(APPEND uniq_list "${item}")
        else()
            message("File ${item} already exists and will be ignored!")
        endif()
    endforeach()
    set(output_list ${uniq_list} PARENT_SCOPE)
endfunction()



# Rules functions for scanning directories
function(SCAN_LIB CURR_DIR)
    set(SRC_DIR "02-SRC")
    if(${PROJECT_TEAM} STREQUAL "VLS")
    set(EXTERNAL_TOOLS_DIR "06-External_Tools")
    set(EXTERNAL_PROJECTS_DIR "07-External_Projects")    
    elseif(${PROJECT_TEAM} STREQUAL "VWS")
    set(EXTERNAL_TOOLS_DIR "06-Tools")
    set(EXTERNAL_PROJECTS_DIR "07-Ext")    
    endif()

    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")

    # Get All files including paths
    foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
        file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
    endforeach()
    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make" )

    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)
endfunction()

function(SCAN_SWC CURR_DIR)
    set(SRC_DIR "02-SRC")
    if(${PROJECT_TEAM} STREQUAL "VLS")
        set(EXTERNAL_TOOLS_DIR "06-External_Tools")
        set(EXTERNAL_PROJECTS_DIR "07-External_Projects")    
    elseif(${PROJECT_TEAM} STREQUAL "VWS")
        set(EXTERNAL_TOOLS_DIR "06-Tools")
        set(EXTERNAL_PROJECTS_DIR "07-Ext")    
    endif()    

    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")

    # Get All files including paths
    foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
        file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
    endforeach()
    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Out/.*")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Out")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/02-Make/.*")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/02-Make")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/03-Stub/.*")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/03-Stub")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/04-Cfg/.*")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/04-Cfg")       

    # Get External LIBs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/LIB_*)
    foreach(DIR ${EXTERNALS})
        SCAN_LIB(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()
    
    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)

endfunction()

function(SCAN_STACK CURR_DIR)
    set(SRC_DIR "01-SRC")
    set(EXTERNAL_TOOLS_DIR "03-External_Tools")
    set(EXTERNAL_PROJECTS_DIR "04-External_Projects")
    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")

    # Get All files including paths
    foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
        file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
    endforeach()
    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make" )

    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)

endfunction()

function(SCAN_CSAR CURR_DIR)
    set(SRC_DIR "02-SRC")
    if(${PROJECT_TEAM} STREQUAL "VLS")
    set(EXTERNAL_TOOLS_DIR "06-External_Tools")
    set(EXTERNAL_PROJECTS_DIR "07-External_Projects")    
    elseif(${PROJECT_TEAM} STREQUAL "VWS")
    set(EXTERNAL_TOOLS_DIR "06-Tools")
    set(EXTERNAL_PROJECTS_DIR "07-Ext")    
    endif()    

    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")
    set(CSAR_REGEX ".*/CSAR_[^/\\]+/02-SRC/CAN/CanIf|.*/CSAR_[^/\\]+/02-SRC/CAN/CanNm|.*/CSAR_[^/\\]+/02-SRC/CAN/CanSM|.*/CSAR_[^/\\]+/02-SRC/CAN/CanTp|.*/CSAR_[^/\\]+/02-SRC/CAN/CanTrcv|.*/CSAR_[^/\\]+/02-SRC/LIN/LinIF|.*/CSAR_[^/\\]+/02-SRC/LIN/Lin|.*/CSAR_[^/\\]+/02-SRC/LIN/LinIf|.*/CSAR_[^/\\]+/02-SRC/LIN/LinNM|.*/CSAR_[^/\\]+/02-SRC/LIN/LinSM|.*/CSAR_[^/\\]+/02-SRC/LIN/LinTrcv|.*/CSAR_[^/\\]+/02-SRC/COM/ComXf|.*/CSAR_[^/\\]+/02-SRC/COM/Com|.*/CSAR_[^/\\]+/02-SRC/COM/Dcm|.*/CSAR_[^/\\]+/02-SRC/COM/Dlt|.*/CSAR_[^/\\]+/02-SRC/COM/PduR|.*/CSAR_[^/\\]+/02-SRC/COM/IpduM|.*/CSAR_[^/\\]+/02-SRC/COM/Nm|.*/CSAR_[^/\\]+/02-SRC/COM/E2EXf|.*/CSAR_[^/\\]+/02-SRC/NVM/Fee|.*/CSAR_[^/\\]+/02-SRC/NVM/NvM|.*/CSAR_[^/\\]+/02-SRC/NVM/Ea|.*/CSAR_[^/\\]+/02-SRC/NVM/MemIf|.*/CSAR_[^/\\]+/02-SRC/NVM/Eep|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Adc|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Bfx|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Can_17_McmCan|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Can|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Crc|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Dio|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Dma|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Dsadc|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Eth_17_GEthMac|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Eth|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Fls_17_Dmu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Fls|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/FlsLoader|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Fr_17_Eray|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Fr|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Gpt|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Hssl|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/I2C|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Icu_17_TimerIp|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Icu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Iom|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Lin_17_AscLin|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Lin|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/McalLib|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Mcu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Ocu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Port|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Pwm_17_GtmCcu6|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Pwm|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Sent|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Smu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Spi|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Stm|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Uart|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Wdg_17_Scu|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Wdg|.*/CSAR_[^/\\]+/02-SRC/MCU/MCAL/Irq|.*/CSAR_[^/\\]+/02-SRC/MCU/McalSafErr|.*/CSAR_[^/\\]+/02-SRC/MCU/TC3xx_Reg|.*/CSAR_[^/\\]+/02-SRC/MCU/Platform|.*/CSAR_[^/\\]+/02-SRC/MCU/Ssw|.*/CSAR_[^/\\]+/02-SRC/MCU/MemMap|.*/CSAR_[^/\\]+/02-SRC/MCU|.*/CSAR_[^/\\]+/02-SRC/System/WdgM|.*/CSAR_[^/\\]+/02-SRC/System/WdgIf|.*/CSAR_[^/\\]+/02-SRC/System/Os|.*/CSAR_[^/\\]+/02-SRC/System/Os/loc|.*/CSAR_[^/\\]+/02-SRC/System/Os/memmap|.*/CSAR_[^/\\]+/02-SRC/System/Os/Os_Asm|.*/CSAR_[^/\\]+/02-SRC/System/Os/Os_Include|.*/CSAR_[^/\\]+/02-SRC/System/Os/Os_Src|.*/CSAR_[^/\\]+/02-SRC/System/Os/RH850|.*/CSAR_[^/\\]+/02-SRC/System/Os/RH850/RH850F1L|.*/CSAR_[^/\\]+/02-SRC/System/SchM|.*/CSAR_[^/\\]+/02-SRC/System/BswM|.*/CSAR_[^/\\]+/02-SRC/System/EcuM|.*/CSAR_[^/\\]+/02-SRC/System/Det|.*/CSAR_[^/\\]+/02-SRC/System/Dem|.*/CSAR_[^/\\]+/02-SRC/System/FiM|.*/CSAR_[^/\\]+/02-SRC/System/ComM|.*/CSAR_[^/\\]+/02-SRC/System/Tm|.*/CSAR_[^/\\]+/02-SRC/System/StbM|.*/CSAR_[^/\\]+/02-SRC/Rte|.*/CSAR_[^/\\]+/02-SRC/XCP/Xcp|.*/CSAR_[^/\\]+/02-SRC/XCP/CanXcp|.*/CSAR_[^/\\]+/02-SRC/Libraries/Crc|.*/CSAR_[^/\\]+/02-SRC/Libraries/E2E|.*/CSAR_[^/\\]+/02-SRC/Libraries/Comtype|.*/CSAR_[^/\\]+/02-SRC/Libraries/VStdLib|.*/CSAR_[^/\\]+/02-SRC/Crypto/Csm|.*/CSAR_[^/\\]+/02-SRC/Crypto/CryIf|.*/CSAR_[^/\\]+/02-SRC/Crypto/Crypto_30_LibCv|.*/CSAR_[^/\\]+/02-SRC/Crypto/vSecPrim|.*/CSAR_[^/\\]+/02-SRC/Ethernet/UpdNm|.*/CSAR_[^/\\]+/02-SRC/Ethernet/EthIf|.*/CSAR_[^/\\]+/02-SRC/Ethernet/EthSM|.*/CSAR_[^/\\]+/02-SRC/Ethernet/EthTrcv|.*/CSAR_[^/\\]+/02-SRC/Ethernet/TcpIp|.*/CSAR_[^/\\]+/02-SRC/Ethernet/EthSwt|.*/CSAR_[^/\\]+/02-SRC/Ethernet/SocktAdapter|.*/CSAR_[^/\\]+/02-SRC/J1939|.*/CSAR_[^/\\]+/02-SRC/CanFD")
    # Get All files including paths
    foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
        file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
    endforeach()
    
    #message("CSAR PATHS BEFORE: ${MY_SOURCE_FILES}")
    list(FILTER MY_SOURCE_FILES INCLUDE REGEX ${CSAR_REGEX})
    #message("CSAR PATHS AFTER: ${MY_SOURCE_FILES}")
    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make" )

    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)

endfunction()

function(SCAN_CSWC CURR_DIR)
    set(SRC_DIR "03-SRC")
    if(${PROJECT_TEAM} STREQUAL "VLS")
        set(EXTERNAL_TOOLS_DIR "07-External_Tools")
        set(EXTERNAL_PROJECTS_DIR "08-External_Projects")    
    elseif(${PROJECT_TEAM} STREQUAL "VWS")
        set(EXTERNAL_TOOLS_DIR "07-Tools")
        set(EXTERNAL_PROJECTS_DIR "08-Ext")    
    endif()

    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")

    # Get All files including paths	
	foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
		file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
	endforeach()	

    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make" )

    # Get External SWCs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/SWC_*)
    foreach(DIR ${EXTERNALS})
        SCAN_SWC(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "07-External_Projects/.*" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()
    
    # Get External LIBs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/LIB_*)
    foreach(DIR ${EXTERNALS})
        SCAN_LIB(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External CSARs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/CSAR_*)
    foreach(DIR ${EXTERNALS})
        SCAN_CSAR(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External CSWCs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/CSWC_*)
    foreach(DIR ${EXTERNALS})
        SCAN_CSWC(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External STACKs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/STACK_*)
    foreach(DIR ${EXTERNALS})
        SCAN_STACK(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)

endfunction()

function(SCAN_APP CURR_DIR)
    set(SRC_DIR "03-SRC")
    if(${PROJECT_TEAM} STREQUAL "VLS")
        set(EXTERNAL_TOOLS_DIR "07-External_Tools")
        set(EXTERNAL_PROJECTS_DIR "08-External_Projects")    
    elseif(${PROJECT_TEAM} STREQUAL "VWS")
        set(EXTERNAL_TOOLS_DIR "07-Tools")
        set(EXTERNAL_PROJECTS_DIR "08-Ext")    
    endif()    

    set(MY_SOURCE_FILES         "")
    set(CHILD_FILES             "")

    # Get All files including paths
    foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
        file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${CURR_DIR}/${SRC_DIR}/*.${EXTENSION})
        list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
    endforeach()

    ## Add specific includes for IAR VWS RL78
    if(${ARCHITECTURE} STREQUAL "VWSRL78")
        foreach(INCLUDE_VWS ${VWS_INCLUDES})
            foreach(EXTENSION ${ALL_FILES_EXTENSIONS})
                file(GLOB_RECURSE FILES_RECURSE LIST_DIRECTORIES true ${INCLUDE_VWS}/*.${EXTENSION})
                list(APPEND MY_SOURCE_FILES ${FILES_RECURSE})
            endforeach()
        endforeach()
    endif()

    # Remove duplicated
    list(REMOVE_DUPLICATES MY_SOURCE_FILES)
    # Add current search directory
    list(APPEND MY_SOURCE_FILES ${CURR_DIR}/${SRC_DIR})
    # Remove include files (leaving only source files)
    foreach(EXTENSION ${INCLUDE_FILES_EXTENSIONS})
        list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "/.${EXTENSION}$")
    endforeach()

    # Remove unwanted pathes and files
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make/.*" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/01-Make" )
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/02-Stub")
    list(FILTER MY_SOURCE_FILES EXCLUDE REGEX "${CURR_DIR}/${SRC_DIR}/02-Stub/.*")

    # Get External SWCs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/SWC_*)
    foreach(DIR ${EXTERNALS})
        SCAN_SWC(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "07-External_Projects/.*" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()
    
    # Get External LIBs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/LIB_*)
    foreach(DIR ${EXTERNALS})
        SCAN_LIB(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External CSARs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/CSAR_*)
    foreach(DIR ${EXTERNALS})
        SCAN_CSAR(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External CSWCs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/CSWC_*)
    set(CSWC_AS_EXTERNAL "YES")
    foreach(DIR ${EXTERNALS})
        SCAN_CSWC(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        if(${ARCHITECTURE} STREQUAL "VWSRL78")
            list(FILTER CHILD_FILES EXCLUDE REGEX "/DSR/.*" ) ## added to adapt to vwsrl78 folder structure
        endif()
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    # Get External STACKs
    file(GLOB EXTERNALS ${CURR_DIR}/${EXTERNAL_PROJECTS_DIR}/STACK_*)
    foreach(DIR ${EXTERNALS})
        SCAN_STACK(${DIR})
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg/.*" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "02-Stub" )
        list(FILTER CHILD_FILES EXCLUDE REGEX "03-Cfg" )
        list(APPEND MY_SOURCE_FILES ${CHILD_FILES})
    endforeach()

    set(CHILD_FILES ${MY_SOURCE_FILES} PARENT_SCOPE)

endfunction()


