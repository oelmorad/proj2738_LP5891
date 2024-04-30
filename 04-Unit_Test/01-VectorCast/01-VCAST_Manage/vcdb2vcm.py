#---------------------------------------------^M
#-- Copyright 2020 Vector Informatik, GmbH. --^M
#---------------------------------------------^M



'''
This is a simple configuration files that will allow you to build a complete set
of VectorCAST projects automatically from the build settings gathered by vcShell
The following workflow should be used:
 
    - Copy this file and the other files located in: VECTORCAST_DIR/examples/AutomationController
    -     into the build directory root, or some other work directory
    - edit the constants at the top of this script to match your application
    - run the startAutomation.py file using the command: $VECTORCAST_DIR/vpython startAutomation.py
    -     (for windows, double click on the runShell.bat file to open a shell first)
'''


import traceback
import os
import re
import subprocess
import sys

from vector.apps.AutomationController import AutomationController
from vector.lib.cover import BaseDirectory


#######################################################################################
#######################################################################################
# If you are building the VC project from existing VC/C++ environments, 
# you only need to setup the configuration variables in this first section.  
# If you are building from a VCShell database, then please review all 
# configuration variables.

### Project name is any ASCII string that is used by
### VectorCAST as the prefix the various projects
### Change this to something meaningful for your project
PROJECT_NAME='VectorCAST'

### Set this variable to True for CUDA env build
### If this is set to 
###     False -> VCAST_COMPILER_CONFIGURATION is used as compiler template
###     True  -> VCAST_CUDA_COMPILER_CONFIGURATION is used as compiler templatee
IS_CUDA=False


#######################################################################################
# The following set of options will take care of most normal use cases

### Project Limits (for first time use to make things faster)
### To test the configuration, we recommend using the default values of 1,1,0
### This will provide a FAST initial test of the build and build settings.
### If the first run works nicely and you get a VC project, bump the 
### numbers up to 50, 50, 5, for a second run, which will generate a cover 
### project with 50 files, 50 unit test environments and 5 fully built unit test environments.
### You can set these variables to 'max' or 'all' to process all files from the vcshell.db
### If you only want to do System Testing set MAXIMUM_FILES_TO_UNIT_TEST to 0
### If you only want to do Unit Testing, set MAXIMUM_FILES_TO_SYSTEM_TEST to 0

class DefaultMode:

    def __init__(self):
        ### VectorCAST Compiler Tag
        ### Must be consistent with the compiler that was used to build the app.
        ### This variable can be set to 
        ###    a. A VectorCAST Compiler Tag: 'GNU_C_46'
        ###    b: The full path to an existing CFG file: /home/VC/CCAST_.CFG
        self.compiler_cfg='CCAST_.CFG'
        self.maximum_files_to_system_test=0
        self.maximum_files_to_unit_test=all
        self.maximum_unit_tests_to_build=0

### Change the below class only for CUDA projects
class CudaMode:

    def __init__(self):
        self.compiler_cfg='CUDA_X86-LINUX_CPP_48'
        self.maximum_files_to_system_test=sys.maxsize
        self.maximum_files_to_unit_test=0
        self.maximum_unit_tests_to_build=0

### Specify the files to be prioritized when building the VectorCAST project
### If you specify ['foo.c', .bar.c', 'main.c'] these will be the first 3
### units processed.  If you specify a file limit of 2, we will process foo.c
### and bar.c in the first invocation, and main.c next time
FILES_OF_INTEREST=[AutomationController.parameterNotSetString]


### VCShell DataBase Location
### The vcshell.db file should always be generated at the build area root directory
### (the place where you normally run the make command).  The default workflow is to run
### the Automation Controller scripts in that build area root directory, which results
### in the VectorCAST workarea (vcast-workarea) being generated there also.
### If you wish to run create the VectorCAST workarea in some other place, copy
### the automation controller files to that alternate location, and set VCSHELL_DB_LOCATION
### to point at location of the vcshell.db (the build area root)
### You must use an absolute path for this file (not relative)
VCSHELL_DB_LOCATION=os.getcwd()

### This variable allows you to over-ride the default name for the vcShell database 
VCSHELL_DB_NAME='vcshell.db'

### This variable allows you to over-ride the default command verb for you compiler
### configuration. This is a comma separated list of all executabled used to compile
### your project. Ex: "gcc,g++"
### None represets using the default verb for the compiler cfg
VCSHELL_COMMAND_VERB=None

### This variable allows you to run vcutil addmetrics after vcShell database creation
VCDB_METRICS=False

### This variable allows you to over-ride the default name of the VectorCAST workarea
VCAST_WORKAREA='vcast-workarea'

### Code Coverage
### Choices are: none, statement, branch, mcdc, statement+branch, statement+mcdc, basis_paths, probe_point, coupling
VCAST_COVERAGE_TYPE='statement+branch'

### This will construct the .env files with the path to the vcshell, rather than the search paths and unit options
### Change it to False if you wish to construct .env files with search paths and unit options
### Default value is True which uses ENVIRO.VCDB_FILENAME
ENV_FILES_USE_VCDB=True

### Instrument in place means that the original file foo.c is backed up
### to foo.c.vcast.bak, and an instrumented foo.c is stored in its place
INSTRUMENT_IN_PLACE=False

### BASIS_PATH_TEST if True will add and execute basis path test for unit env
### if False will skip the creation and excution of basis path test
BASIS_PATH_TEST=False

### The VCDB_FLAG_STRING flags will be used as "extra" flags when we call vcdb
### to get the unit options.  If nothing is passed we will use the -I and -D flags only
### A common value for this for GNU is "-isystem=1"
VCAST_VCDB_FLAG_STRING=''

### The USE_PARALLEL_INSTRUMENTOR option when set to True speeds-up the cover project
### creation if the user has already run vcutil instrument and has instrumented files.
### When set to False uses the legacy way of building cover environment.
USE_PARALLEL_INSTRUMENTOR=True

# Controls the failing/continuing of the scripts after a VectorCAST command fails
# By default we abort only on critical errors
# Set this to True to abort on any failures
ABORT_ON_ALL_ERRORS=False

# Controls the updating of system_test.py
UPDATE_SYSTEM_TEST_PY_FILE=True

# This list of main files will be used to automatically append the c_cover_io.c file
# to one file in each application that is being instrumented.
# If you want VectorCAST to automatically compute the insert locations for c_cover_io:
LIST_OF_MAIN_FILES = [AutomationController.parameterNotSetString]
# If you want to manually choose the files where c_cover_io is inserted do this:
# LIST_OF_MAIN_FILES = ['firstMain.c', 'secondMain.c']
# To disable the insert of the c_cover_io.c completely, do this:
# LIST_OF_MAIN_FILES = []


### You can optionally run Lint analysis on the files in the project
LINT=False

### This value will be used to set a TCAST_CASE_TIMEOUT option for the UnitTest node
### This is useful, especially for basis path tests that sometimes loop foreever.
### If you do not want to use a timeout value, set this variable to 0
TEST_TIMEOUT=1800

### This variable allows to create whitebox or blackbox unit test environment 
### if this is set to True ENVIRO.WHITEBOX will be set as NO in .env files
BLACKBOX_ENV=False

#######################################################################################
# The follow set of configuration option supports advanced workflows

### When vcshell creates a settings database, it makes all of the -I paths that it finds
### VectorCAST search paths.  In some cases, you may want to over-ride this default behavior
### The INCLUDE_PATH_OVERRIDE feature allows you to exactly control how Include Paths 
### are handled by the automation controller.  The INCLUDE_PATH_OVERRIDE variable
### is a list of tuples which contain the include path and the OverRide Action.
### Possible OverRide Action values are: 
###             NONE:   Do not use this Include Path
###             SEARCH: Consider the path a Search Path (default)
###             LIB:    Consider the path a Library Include Path
###             TYPE:   Consider the path a Type Handled Path
### If the list contains a path that is not in the vcshell database, we will add that path
### INCLUDE_PATH_OVERRIDE = [('/home/mySourceCode/libDir', 'LIB'), ('/home/mySourceCode/newPath', 'SEARCH')
INCLUDE_PATH_OVERRIDE = []

### This filter function below can be used to limit the files that are processed.
### You can use the FILTER_PATTERNS objects with the default filterFiles 
### function, or you can completely replace the filterFiles function.
###
### The filter strings will OR'd and applied to the absolute file paths
### This allows you to filter down to a set or directories or files
### whose names contain any one of the strings.  For example, if you
### have a file structure like this: /home/source/subSystem1  
### /home/source/subSystem2, then the following filter pattern:
### FILTER_PATTERNS = ['/subSystem2', 'foo']  
### would yield all of the files in subSystem2, and any other file
### whose path contains the string foo.  MAXIMUM_FILES_TO_SYSTEM_TEST 
### and MAXIMUM_FILES_FOR_UNIT_TEST 
### still control the maximum number of files to be processed.
###
FILTER_PATTERNS = []
def matchesFilter(filePath):
    for filter in FILTER_PATTERNS:
        if filter in filePath:
            return True


def __filterFileList(original_list):
    local_files = []

    if len (FILTER_PATTERNS) > 0:
        for file_path in original_list:
            if matchesFilter(file_path):
                local_files.append(file_path)
    else:
        local_files = original_list

    return local_files


def getBaseDirectories():
    """Enumerate base directories here."""
    # base = BaseDirectory("BASE_DIR_NAME", "$(ROOT_DIR)")
    # base.allow(["lib"
    #             "progs",
    #             "progs/xyz"])
    # base.deny(["lib/abc"])
    # bases.append(base)
    bases = []

    return bases


BASE_DIRECTORIES = getBaseDirectories()


def filterFileList(originalList):
    """
    This function is a white-list function.  It will spin through
    the full file list and "keep" any files that have a pattern
    from the FILTER_PATTERNS. You can easily turn this function
    into a black-list function that will omit file patterns.

    To make use of Base Directories, you must populate them in the
    getBaseDirectories function.
    """
    if BASE_DIRECTORIES:
        return BaseDirectory.filter(BASE_DIRECTORIES, originalList)

    return __filterFileList(originalList)


### This envFileEditor function can be used to change the configuration of the 
### default .env files that are generated by the Automation Controller.
### This function will be called once for each .env file.
def envFileEditor(pathToEnvFile):
    '''
    There are two common edits that you might want to make to environment script
        1. Change the value of an existing line in the script
           For example, change ENVIRO.STUB: ALL_BY_PROTOTYPE to 
                               ENVIRO.STUB: NONE
        2. Add new lines to the script
           For example, ENVIRO.APPENDIX_USER_CODE 
    '''
    #This function will do no work by default ...
    return
    # To change an existing command, use this function call
    AutomationController.editEnvCommand (pathToEnvFile=pathToEnvFile, flag='ENVIRO.STUB', oldValue='ALL_BY_PROTOTYPE', newValue='NONE')
    # To insert a totally new line or block, use this function call
    AutomationController.insertEnvCommand (pathToEnvFile=pathToEnvFile, newCommand= \
        'ENVIRO.UNIT_APPENDIX_USER_CODE:\n' + \
        'ENVIRO.UNIT_APPENDIX_USER_CODE_FILE:manager \n'+ \
        '/* here is some appendix user code for manager */\n'+ \
        'ENVIRO.END_UNIT_APPENDIX_USER_CODE_FILE:\n' + \
        'ENVIRO.END_UNIT_APPENDIX_USER_CODE:\n' )
        
      
#######################################################################################
#######################################################################################
# The code below this comment should not be modified.

def expandEnvVarInConfigVariables():
    '''
    Here we loop through all of the variables defined in global scope to check
    if any of the "vector" or "string"  ones contain environment variable syntax ${VAR}
    '''
    for key, value in list(globals().items()):
        # All our configurable variables are in UPPER case
        # Avoid built-in variables which start wtih __
        if key.isupper() and not key.startswith("__"):
            # We have list as well as string variables that could be configured
            if type(globals()[key]) == list:
                expandedValue = []
                for val in value:
                    try:
                        expandedValue.append(os.path.expandvars(val))
                    except TypeError:
                        expandedValue.append(val)
                globals()[key] = expandedValue
            elif type(globals()[key]) == str:
                globals()[key] = os.path.expandvars(value)

def get_mode():
    if IS_CUDA:
        return CudaMode()
    else:
        return DefaultMode()

def convertMaxToInt(maxParam):
    try:
        intVal = int(maxParam)
        # if the MAX variable is an integer, then return the arg
        return maxParam
    except:
        return sys.maxsize


def vcdb2vcm(whatToDo='build-db', vceBaseDirectory="", verbose=False, coverBaseDir=None):
    '''
    Calling arguments:
        command     command-arg      Verbose
        build-vce   root-directory   True|False
    '''
    global BASE_DIRECTORIES

    expandEnvVarInConfigVariables()
    AutomationController.setVcWorkArea(VCAST_WORKAREA)
    AutomationController.setVcshellDbName(VCSHELL_DB_NAME)
    status_file = '{}-automation-status.txt'.format(PROJECT_NAME)
    if whatToDo == 'build-vce':
        try:
            AutomationController.vcmFromEnvironments(
                projectName=PROJECT_NAME,
                rootDirectory=vceBaseDirectory,
                statusfile=status_file,
                verbose=verbose)
        except Exception as e:
            print(e)
            raise
    elif whatToDo == 'build-db':
        if coverBaseDir:
            BASE_DIRECTORIES = coverBaseDir

        mode = get_mode()
        try:
            AutomationController.automationController(
                projectName=PROJECT_NAME,
                vcshellLocation=VCSHELL_DB_LOCATION,
                listOfMainFiles=LIST_OF_MAIN_FILES,
                runLint=LINT,
                maxToSystemTest=convertMaxToInt(
                    mode.maximum_files_to_system_test),
                maxToUnitTest=convertMaxToInt(mode.maximum_files_to_unit_test),
                maxToBuild=convertMaxToInt(mode.maximum_unit_tests_to_build),
                filterFunction=filterFileList,
                compilerCFG=mode.compiler_cfg,
                coverageType=VCAST_COVERAGE_TYPE,
                inplace=INSTRUMENT_IN_PLACE,
                vcdbFlagString=VCAST_VCDB_FLAG_STRING,
                tcTimeOut=TEST_TIMEOUT,
                includePathOverRide=INCLUDE_PATH_OVERRIDE,
                envFileEditor=envFileEditor,
                statusfile=status_file,
                verbose=verbose,
                filesOfInterest=FILES_OF_INTEREST,
                envFilesUseVcdb=ENV_FILES_USE_VCDB,
                basisPathTest=BASIS_PATH_TEST,
                parallelInst=USE_PARALLEL_INSTRUMENTOR,
                abortOnError=ABORT_ON_ALL_ERRORS,
                updateSystemTest=UPDATE_SYSTEM_TEST_PY_FILE,
                blackboxenv=BLACKBOX_ENV,
                coverBaseDir=BASE_DIRECTORIES)
        except Exception as e:
            print(e)
            raise
    else:
        raise RuntimeError('Invalid whatToDo call to vcdb2vcm.vcdb2vcm call')

     
if __name__ == '__main__':
    # The default Windows encoding on Python 3.7 is cp1252, which is undesired.
    encoding = 'utf-8'
    import sys
    try:
        if sys.stdout.encoding.lower() != encoding:
            sys.stdout.reconfigure(encoding=encoding)
        if sys.stderr.encoding.lower() != encoding:
            sys.stderr.reconfigure(encoding=encoding)
    except AttributeError:
        pass
    raise RuntimeError('Call vcdb2vcm.py through startAutomation.py')
