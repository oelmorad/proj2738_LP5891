cmake_minimum_required(VERSION 3.0.0)

get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
#get_filename_component(PROJECT_FOLDER ${PROJECT_DIR} NAME)

## Check if VLS or VWS according to tools and external projects folder
if(EXISTS "${PROJECT_DIR}/07-Tools" OR EXISTS "${PROJECT_DIR}/06-Tools")
	set(PROJECT_TEAM VWS)
elseif(EXISTS "${PROJECT_DIR}/07-External_Tools" OR EXISTS "${PROJECT_DIR}/06-External_Tools")
	set(PROJECT_TEAM VLS)
endif()


if(${PROJECT_TYPE} MATCHES "^CSWC_*")
    include("${CMAKE_CURRENT_LIST_DIR}/cswc.cmake")
elseif(${PROJECT_TYPE} MATCHES "^SWC_*")
include("${CMAKE_CURRENT_LIST_DIR}/swc.cmake")
elseif(${PROJECT_TYPE} MATCHES "^CSAR_*")
include("${CMAKE_CURRENT_LIST_DIR}/csar.cmake")
elseif(${PROJECT_TYPE} MATCHES "^LIB_*")
include("${CMAKE_CURRENT_LIST_DIR}/lib.cmake")
elseif(${PROJECT_TYPE} MATCHES "^STACK_*")
include("${CMAKE_CURRENT_LIST_DIR}/stack.cmake")
else()
include("${CMAKE_CURRENT_LIST_DIR}/app.cmake")
endif()

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	SET(COMPILED_SOURCES ${ALL_SOURCE_FILES})
	list(FILTER COMPILED_SOURCES EXCLUDE REGEX "\\.h$")
	list(FILTER COMPILED_SOURCES EXCLUDE REGEX "\\.asm$")
    SET(CONTENTS "")
    FOREACH(line ${COMPILED_SOURCES})
        SET(CONTENTS "${CONTENTS}${line}\n")
    ENDFOREACH(line)    
    file(WRITE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SourceFiles.txt ${CONTENTS})

    SET(CONTENTS "")
    FOREACH(line ${ALL_INCLUDE_DIRS})
        SET(CONTENTS "${CONTENTS}${line}\n")
    ENDFOREACH(line)    
    file(WRITE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Include_Dirs.txt ${CONTENTS})
endif()


if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	
	SET(CONTENTS "")
	SET(COMPILED_SOURCES ${ALL_SOURCE_FILES})
	list(FILTER COMPILED_SOURCES EXCLUDE REGEX "\\.h$")
	list(FILTER COMPILED_SOURCES EXCLUDE REGEX "\\.asm$")
	
	SET(CONTENTS "${CONTENTS}dir::${CMAKE_CURRENT_SOURCE_DIR}\n")
	SET(FLAGS_SPACED "")
	FOREACH(flag ${CUSTOM_C_FLAGS})
		SET(FLAGS_SPACED "${FLAGS_SPACED} ${flag}")
	ENDFOREACH(flag)
	FOREACH(flag ${DEFAULT_C_FLAGS})
		SET(FLAGS_SPACED "${FLAGS_SPACED} ${flag}")
	ENDFOREACH(flag)

	# Remove string "SHELL:" from flags before writing into build_db
	String(REPLACE "SHELL:" "" FLAGS_SPACED ${FLAGS_SPACED}) 
	
	SET(INC_DIRS "")
	FOREACH(inc_dir ${ALL_INCLUDE_DIRS})
		SET(INC_DIRS "${INC_DIRS} -I\"${inc_dir}\"")
	ENDFOREACH(inc_dir)
	FOREACH(inc_dir ${compiler_include_directories})
		SET(INC_DIRS "${INC_DIRS} -I${inc_dir}")
	ENDFOREACH(inc_dir)
	
	FOREACH(line ${COMPILED_SOURCES})
		string(REPLACE ":" "_" OBJ_DIR ${line})
		SET(OBJ_FILE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/${OBJ_DIR}.obj")
		if(${COMPILER_TYPE} STREQUAL "GHS")
			SET(CONTENTS "${CONTENTS}cmd::ccrh850 ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )
		elseif(${COMPILER_TYPE} STREQUAL "IAR")
    		if(${ARCHITECTURE} STREQUAL "NXP")
				SET(CONTENTS "${CONTENTS}cmd::iccarm ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )
    		elseif(${ARCHITECTURE} STREQUAL "ARMM3")
				SET(CONTENTS "${CONTENTS}cmd::iccarm ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )
    		elseif(${ARCHITECTURE} STREQUAL "VWSRL78")
				SET(CONTENTS "${CONTENTS}cmd::iccrl78 ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )
			elseif(${ARCHITECTURE} STREQUAL "RL78")
				SET(CONTENTS "${CONTENTS}cmd::iccrl78 ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )
			elseif(${ARCHITECTURE} STREQUAL "MSP430")
				SET(CONTENTS "${CONTENTS}cmd::icc430 ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )   
    		endif()
		elseif(${COMPILER_TYPE} STREQUAL "HIGHTEC")
			SET(CONTENTS "${CONTENTS}cmd::tricore-gcc ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )   
		elseif(${COMPILER_TYPE} STREQUAL "CLANG")
			SET(CONTENTS "${CONTENTS}cmd::gcc ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )  
		else()
			SET(CONTENTS "${CONTENTS}cmd::gcc ${FLAGS_SPACED} ${INC_DIRS} -o${OBJ_FILE} ${line}\n" )  
		endif()
	ENDFOREACH(line)
	

	
	file(WRITE ${PROJECT_DIR}/${TEST_DIR}/build_db.txt ${CONTENTS})
	
endif()




