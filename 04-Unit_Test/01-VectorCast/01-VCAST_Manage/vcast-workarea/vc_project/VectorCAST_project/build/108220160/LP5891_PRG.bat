del commands.tmp
echo options C_COMPILER_CFG_SOURCE CONFIG_FILE_63 >> commands.tmp
echo options C_COMPILER_HIERARCHY_STRING Green Hills_NEC v850_Simulator_C >> commands.tmp
echo options C_COMPILER_PY_ARGS --lang c --io stdout --target sim --multi multi4 --cpu v850e >> commands.tmp
echo options C_COMPILER_TAG V850_GH_SIM >> commands.tmp
echo options C_COMPILER_VERSION_CMD ccv850e -V not.here.c >> commands.tmp
echo options C_COMPILE_CMD ccrh850 -c -G -w -Onone  -no_callt -sda=all -large_sda -reserve_r2 -Wundef --short_enum -dual_debug -delete -preprocess_assembly_files --no_wrap_diagnostics -registermode=32 -keeptempfiles -prepare_dispose -ansi  -full_debug_info -noobj -Wimplicit-int -Wshadow -Wtrigraphs -inline_prologue >> commands.tmp
echo options C_COMPILE_CMD_FLAG -c >> commands.tmp
echo options C_COMPILE_EXCLUDE_FLAGS -o^^** >> commands.tmp
echo options C_DEBUG_CMD multi >> commands.tmp
echo options C_DEFINE_LIST OS_USE_TRACE=0 OS_RELEASE_SUFFIX=OS_AS403 OS_MEMMAP=0 OS_MULTICORE=OS_SINGLE OS_USE_CLZ_QUEUE_ALGORITHM=1 OS_DEVELOPMENT_SANITY_CHECKS=0 OS_KERNEL_TYPE=OS_FUNCTION_CALL TS_ARCH_FAMILY=TS_RH850 TS_ARCH_DERIVATE=TS_RH850F1L RH850F1L=1 OS_CPU=OS_RH850F1L OS_TOOL=OS_ghs OS_ARCH=OS_RH850 __noinline= VCAST_USE_GH_SYSCALL >> commands.tmp
echo options C_EDG_FLAGS -w --c --ghs >> commands.tmp
echo options C_EXECUTE_CMD sim850 >> commands.tmp
echo options C_LINKER_VERSION_CMD elxr -V >> commands.tmp
echo options C_LINK_CMD ccrh850 -G -map=vcast.map >> commands.tmp
echo options C_OUTPUT_FLAG -o^^ >> commands.tmp
echo options C_PREPROCESS_CMD ccrh850 -E -C >> commands.tmp
echo options VCAST_ASSEMBLY_FILE_EXTENSIONS asm s >> commands.tmp
echo options VCAST_COLLAPSE_STD_HEADERS COLLAPSE_NON_SEARCH_HEADERS >> commands.tmp
echo options VCAST_COMPILER_SUPPORTS_CPP_CASTS TRUE >> commands.tmp
echo options VCAST_COVERAGE_FOR_AGGREGATE_INIT FALSE >> commands.tmp
echo options VCAST_COVERAGE_SOURCE_FILE_PERSPECTIVE FALSE >> commands.tmp
echo options VCAST_DISABLE_ASM_FUNC_TESTING TRUE >> commands.tmp
echo options VCAST_DISABLE_CPP_EXCEPTIONS TRUE >> commands.tmp
echo options VCAST_DISABLE_DIRECT_ARRAY_INDEXING FALSE >> commands.tmp
echo options VCAST_DISABLE_STD_WSTRING_DETECTION TRUE >> commands.tmp
echo options VCAST_DISPLAY_FUNCTION_COVERAGE TRUE >> commands.tmp
echo options VCAST_DISPLAY_UNINST_EXPR FALSE >> commands.tmp
echo options VCAST_ENABLE_FUNCTION_CALL_COVERAGE TRUE >> commands.tmp
echo options VCAST_ENVIRONMENT_FILES  >> commands.tmp
echo options VCAST_EXECUTE_WITH_STDIO FALSE >> commands.tmp
echo options VCAST_EXECUTE_WITH_STDOUT FALSE >> commands.tmp
echo options VCAST_HAS_LONGLONG TRUE >> commands.tmp
echo options VCAST_MICROSOFT_LONG_LONG FALSE >> commands.tmp
echo options VCAST_NO_STDIN FALSE >> commands.tmp
echo options VCAST_PRQAC_ANALYSER_BASE $(PATH_QAC) >> commands.tmp
echo options VCAST_PRQAC_COMPILER_SETTINGS_FILE $(PATH_QAC)/personalities/start.p_c >> commands.tmp
echo options VCAST_PRQAC_MESSAGE_PERSONALITY_FILE $(PATH_QAC)\\personalities\\critical.p_s >> commands.tmp
echo options VCAST_REFERENCED_GLOBALS FALSE >> commands.tmp
echo options VCAST_REPOSITORY  >> commands.tmp
echo options VCAST_RPTS_DEFAULT_FONT_FACE Arial(1) >> commands.tmp
echo options VCAST_STDIO FALSE >> commands.tmp
echo options VCAST_TEST_ALL_NON_MEMBER_INLINES FALSE >> commands.tmp
echo options VCAST_TI_IGNORE_QUALIFIERS TRUE >> commands.tmp
echo options VCAST_USE_STD_STRING FALSE >> commands.tmp
echo options VCAST_VCDB_FLAG_STRING  >> commands.tmp
echo options VCDB_CMD_VERB ccrh850 >> commands.tmp
echo options VCDB_FILENAME C:\\Users\\oelmorad\\git\\proj2738_LP5891\\04-Unit_Test\\01-VectorCast\\01-VCAST_Manage\\vcshell.db >> commands.tmp
echo options WHITEBOX YES >> commands.tmp
echo environment build LP5891_PRG.env >> commands.tmp
echo /E:LP5891_PRG tools script run LP5891_PRG.tst >> commands.tmp
echo /E:LP5891_PRG execute batch >> commands.tmp
echo /E:LP5891_PRG reports custom management LP5891_PRG_management_report.html >> commands.tmp
setlocal
set PATH=%PATH%;%VECTORCAST_DIR%
WHERE clicast
IF %ERRORLEVEL% NEQ 0 ECHO Error: clicast was not found on System PATH. Add the VectorCAST installation directory to System PATH or set the environment variable VECTORCAST_DIR to the VectorCAST installation directory. && exit /b 1
"CLICAST"  /L:C tools execute commands.tmp true
IF %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
endlocal
