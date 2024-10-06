if(NOT DEFINED ENV{CLANG_PATH})
message( FATAL_ERROR "Set Enviroment variable with CLANG_Path  IE CLANG_PATH:C:/E/Clang_setup " )
endif()

set(DEFAULT_C_FLAGS    )
SET(DEFAULT_ASM_FLAGS  )
set(DEFAULT_LINK_FLAGS )

set(DEFAULT_EXECUTABLE_SUFFIX "out")
set(DEFAULT_HEX_SUFFUX        "hex")
set(SOURCE_FILE_EXTENSIONS c S)
set(INCLUDE_FILES_EXTENSIONS h inc)

set(COMPILER_PATH $ENV{CLANG_PATH})

set(CMAKE_C_COMPILER     ${COMPILER_PATH}/bin/tiarmclang.exe)

set(GENERATE_VCSHELL vcshell --inputcmds=build_db.txt putcommand)
