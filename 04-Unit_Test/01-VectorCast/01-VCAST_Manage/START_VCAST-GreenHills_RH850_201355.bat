REM ##########################################################
REM
REM			VALEO comfort & driving assistance systems
REM
REM ##########################################################
REM
REM    VectorCast should always be started with a script
REM    All needed variables will be set in this script
REM    For each module and each compiler is one script
REM    and directory necessary !!
REM
REM ##########################################################
REM
REM			compiler:	GreenHills - Version: comp_201355
REM
REM ##########################################################

REM ##########################################################
REM path of the tool-directory
SET PATH_T=C:

REM ##########################################################
REM path of the QAC installation
SET PATH_QAC=%PATH_T%\PRQA\QAC-7.1

REM ##########################################################
REM install directory of VectorCAST
SET vectorcast_dir=%VECTORCAST_DIR%

REM ##########################################################
REM The client will look for a license according to any data 
REM saved in the registry. We can prevent that by setting an
REM environment variable LM_APP_DISABLE_CACHE_READ
REM set LM_APP_DISABLE_CACHE_READ=1

REM Kill lm_license_file by putting a newline after the equals
REM Later you may want to change this to @server or port@server
REM    e.g.   set LM_LICENSE_FILE= 27002@server
REM    or     set LM_LICENSE_FILE= @server
REM set LM_LICENSE_FILE=

REM use a local license file or the name of the license server
REM SET VECTOR_LICENSE_FILE=27002@CAI1-LICENSE
SET LM_LICENSE_FILE=27002@CAI1-License
REM ##########################################################
REM complier path
SET MAKE_PATH=C:\ghs\comp_201355

REM Put the compiler in the path that is shipped with VectorCAST
SET GHRH850_COMPILER_PATH=%PATH_T%\ghs\comp_201355
SET GHRH850_COMPILER_LIBRARY_PATH=%GHRH850_COMPILER_PATH%\lib\rh850
SET GHRH850_COMPILER_ANSI_INCLUDE=%GHRH850_COMPILER_PATH%\ansi
SET GHRH850_MULTI = %PATH_T%\ghs\multi_616
REM ##########################################################
REM working directory
%~d1 :
cd %CD%

REM ##########################################################
REM create %PATH% variable
SET PATH=%MAKE_PATH%;%GHRH850_COMPILER_LIBRARY_PATH%;%GHRH850_COMPILER_PATH%;%GHRH850_COMPILER_ANSI_INCLUDE%;%GHRH850_MULTI%;%PATH%

REM ##########################################################
REM start cmd for VectorCAST with language C (option I)
start %vectorcast_dir%\vcastqt -lc

REM ##########################################################
REM start cmd for VectorCAST with language C to open directly
REM the working environment (option II)

REM for /r %%i in (*.vce) do start %vectorcast_dir%\vcastqt -e %%i

REM ##########################################################
REM
REM					END of start-script
REM
REM ##########################################################