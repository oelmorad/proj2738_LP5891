#---------------------------------------------
#-- Copyright 2020 Vector Informatik, GmbH. --
#---------------------------------------------

''' 
This is a simple shell script that can be used to provide a choices menu 
of what automation command to run
 
    - build a demo VC Project using the command: $VECTORCAST_DIR/vpython vcdb2vcm.py
    - copy this python script into the directory where you ran vcdb2vcm.py
    - run this script using the command: $VECTORCAST_DIR/vpython startAutomation.py

Respond to the menu of command choices    
 
'''


import argparse
import collections
import os
import re
import shutil
import subprocess
import traceback

from vector.lib.cover import BaseDirectory
from vector.apps.AutomationController import AutomationController
import vcdb2vcm


# This is the startup directory where the script is being run
# It is assumed that this directory contains vcshell.db file
originalWorkingDirectory=os.getcwd()

globalMakeCommand = ''
vceBaseDirectory = ''
coverBaseDirs = None


def merge_basedir_args(args):
    base_dirs = args.base_dirs
    allowed_list = args.allow_list
    denied_list = args.deny_list

    if base_dirs:
        path_arg_re = re.compile(r'(?P<root>.+)=(?P<path>.+)')
        parsed_bases = {}

        def parse_list(source_list, allow_method):
            allow_map = collections.defaultdict(list)
            for item in source_list:
                match = path_arg_re.search(item)
                if match.group:
                    root = match.group('root')
                    path = match.group('path')

                    if root in parsed_bases:
                        allow_map[root].append(path)

            for root, paths in allow_map.items():
                getattr(parsed_bases[root], allow_method)(paths)

        for name_path in base_dirs:
            if '=' in name_path:
                name, path = name_path.split('=')
                parsed_bases[name] = BaseDirectory(name, path)

        if allowed_list:
            parse_list(allowed_list, 'allow')

        if denied_list:
            parse_list(denied_list, 'deny')

        # "Flatten" the dictionary to match BASE_DIRECTORY format in vdb2vcm.
        parsed_bases = list(parsed_bases.values())

    else:
        parsed_bases = None

    return parsed_bases


def setupArgs (toolName):
    '''
    '''
    
    parser = argparse.ArgumentParser(description=toolName)
    
    group = parser.add_mutually_exclusive_group(required=True)
    
    # Base directory for building and vc projects and scripts.
    group.add_argument ('--interactive', dest='interactive', action='store_true', default=False,
                           help='Interactive mode')    

    # Command to run -- for non Interactive mode
    commandChoices=['make', 'clean', 'build-db', 'build-vce', 'vcast', 'analytics', 'enable', 'disable', 'toolbar', 'enterprise']
    group.add_argument ('--command', dest='command', action='store', default='full',
                           choices=commandChoices, help='Command Choice')

    # Make command
    parser.add_argument ('--makecmd', dest='makecmd', action='store', default='',
                           help='Comand to make the application')

    # VCE Root Directory
    parser.add_argument ('--vceroot', dest='vceroot', action='store', default='',
                           help='Root path to VectorCAST environments')

    # Path to the VC project file: .vcm, .vce, .vcp (used for command='toolbar')
    parser.add_argument ('--project', dest='project', action='store', default='',
                           help='Full path to the VectorCAST project file')
                           
    # Path to the environment script file (used for command='enterprise')
    parser.add_argument ('--script', dest='script', action='store', default='',
                           help='Root path to the VectorCAST workarea')                              
                           
    # Root for vcast-workarea directory (used for command='toolbar' || 'enterprise')
    parser.add_argument ('--workarea', dest='workarea', action='store', default='',
                           help='Root path to the VectorCAST workarea')    
                           
    parser.add_argument ('--verbose', dest='verbose', action='store_true', default=False,
                           help='Root path to VectorCAST environments')    

    parser.add_argument ('--abort-on-error', dest='abort_on_error', action='store_true',
                           help='Abort the command when an error occurs')

    parser.add_argument ('--base-dir', dest='base_dirs', action='append',
                         help='Specifies the location where source files reside. This can be '
                              'set to an environment variable or relative path. <NAME>=<PATH>')
    parser.add_argument ('--allow-list', '-al', dest='allow_list', action='append',
                         help='The given path will be included in the given base '
                              'directory\'s allowlist. <BASE_DIR_NAME>=<PATH>')
    parser.add_argument ('--deny-list', '-dl', dest='deny_list', action='append',
                         help='Deny-listed files and directories will be excluded from the '
                         'file list found within the allow list. <BASE_DIR_NAME>=<PATH>')

    return parser



def solicitChoice():

    AutomationController.sectionBreak('');
    print('VectorCAST Automation Controller Script')
    print('   (1) Build Application under vcShell')
    print('   (2) Delete VectorCAST Project and un-instrument files')
    print('   (3) Build/Extend a VectorCAST Project from vcshell.db')
    print('   (4) Build/Extend a VectorCAST Project from .vce')
    print('   (5) Start VectorCAST')
    print('   (6) Start the Analytics Server')
    print('   (7) Disable Coverage')
    print('   (8) Enable Coverage')
    print('   (9) Quit')
    
    try:
        listChoiceString = ( input ('Action to take: '))
        listChoice = int (listChoiceString)
    except:
        # 0 means do nothing
        listChoice = 0

    return listChoice

    
def clean ():
    '''
    This function will un-instrument all of the files that are in the cover project
    and then remove the vcast-workarea directory.  We do this rather than using
    the clicast un-instrument, because this is _MUCH_ faster
    '''
    workArea = vcdb2vcm.VCAST_WORKAREA 
    
    # Un-instument any instrumented source files
    AutomationController.unInstrumentSourceFiles() 
    
    if os.path.isdir (workArea):
        print('Removing the previous vcast-workarea')
        shutil.rmtree (workArea)

    
def performTask (whatToDo, verbose):
    '''
    This function will do the real work
    '''
    exe_env = os.environ.copy()
    if 'VECTORCAST_DIR' in os.environ:
        exe_env['PATH'] = os.pathsep.join([exe_env.get('PATH', ''), exe_env['VECTORCAST_DIR']])

    if whatToDo == 'make':
        if vcdb2vcm.VCSHELL_DB_LOCATION!=originalWorkingDirectory:
            os.chdir (vcdb2vcm.VCSHELL_DB_LOCATION)
        if not os.path.isfile ('CCAST_.CFG'):
            AutomationController.initializeCFGfile(
                vcdb2vcm.GetCompilerConfig(), vcdb2vcm.VCAST_VCDB_FLAG_STRING)
        commandToRun = 'vcshell' + ' ' + globalMakeCommand + ' --db=%s' % vcdb2vcm.VCSHELL_DB_NAME
        print('Running: ' + commandToRun)
        subprocess.call (commandToRun, shell=True, env=exe_env)
        if vcdb2vcm.VCDB_METRICS:
            commandToRun = 'vcutil' + ' addmetrics --all --db=%s' % vcdb2vcm.VCSHELL_DB_NAME
            print('Running: ' + commandToRun)
            subprocess.call (commandToRun, shell=True, env=exe_env)
        os.chdir (originalWorkingDirectory)

    elif whatToDo == 'clean':
        clean()

    elif whatToDo == 'build-db' or whatToDo=='build-vce':
        # Run the vcdb2vcm script to create the project
        try:
            vcdb2vcm.vcdb2vcm(whatToDo,
                              vceBaseDirectory.strip('"').strip("'"),
                              coverBaseDir=coverBaseDirs,
                              verbose=verbose)
        except Exception as e:
            print(e)
  
    elif whatToDo == 'vcast':
        # Start VC for the project
        AutomationController.startManageGUI()      
    
    elif whatToDo == 'analytics':
        # Start Analytics for the project
        AutomationController.startAnalytics(vcdb2vcm.VCSHELL_DB_LOCATION)
        
    elif whatToDo == 'disable':
        # Start Analytics for the project
        AutomationController.disableCoverage()

    elif whatToDo == 'enable':
        AutomationController.enableCoverage()  



    
def interactiveMode(verbose):
    '''
    This function will run in an infinite loop to solicit input from the
    user and execute the command chosen
    '''
    global globalMakeCommand
    global vceBaseDirectory
    while (True):
    
        whatToDo = solicitChoice()
        command='none'
        
        if whatToDo == 1:
            # Solicit the build command
            makeCommand =  input ('Enter the command to build your application: ')
            if len(makeCommand)>0:
                globalMakeCommand = makeCommand
                command = 'make'

        elif whatToDo == 2:
            try:
                listChoiceString = ( input ('Enter "yes" to confirm clean action: '))
                if listChoiceString == 'yes':
                   command = 'clean'
            except:
                command = 'none'
                pass
           
        elif whatToDo == 3:
            command = 'build-db'

        elif whatToDo == 4:
            vceBaseDirectory = ( input ('Enter base directory for environment search: '))
            if len(vceBaseDirectory)>0:
                command = 'build-vce'

        elif whatToDo == 5:
            command = 'vcast'
        
        elif whatToDo == 6:
            command = 'analytics'
        
        elif whatToDo == 7:
            command = 'disable'
        
        elif whatToDo == 8:
            command = 'enable'
        
        elif whatToDo == 9:
            break
        
        performTask (command, verbose)
    

def argsAreValid (args):

    if not os.path.isdir (args.workarea):
        print('--workarea arg: "' + args.workarea + '" is invalid')
        return False
    else:
        return True

    
def main():
    '''
    '''
    global coverBaseDirs
    global globalMakeCommand
    global vceBaseDirectory
    
    parser = setupArgs ('startAutomation') 
    # Read the arguments
    try:
        args = parser.parse_args()
    except SystemExit:
        raise

    vcdb2vcm.ABORT_ON_ALL_ERRORS = vcdb2vcm.ABORT_ON_ALL_ERRORS or args.abort_on_error
    AutomationController.setVcWorkArea(vcdb2vcm.VCAST_WORKAREA)
    AutomationController.setVcshellDbName(vcdb2vcm.VCSHELL_DB_NAME)
    AutomationController.setVcshellCommandVerb(vcdb2vcm.VCSHELL_COMMAND_VERB)
    if args.interactive:
        interactiveMode(args.verbose)
    elif args.command == 'make' and len (args.makecmd)==0:
        print('Error: --makecmd not provided')
    elif args.command == 'build-vce' and len (args.vceroot)==0:
        print('Error: --vceroot not provided')
    elif args.command =='toolbar':
        # Tool-bar mode starts an Analytics dashboard for the current project
        # This is only used by the toolbar icon
        if argsAreValid (args):
            AutomationController.toolBarDashIcon (workareaBaseDirectory=args.workarea, vcProjectFile=args.project)
    elif args.command =='enterprise':
        # enterprise mode builds a VectorCAST project, adds the environment script, and builds the environment
        if argsAreValid (args):
            AutomationController.enterpriseEnvironmentBuild (workareaBaseDirectory=args.workarea, projectName=args.project, scriptFile=args.script)
    else:
        globalMakeCommand = args.makecmd
        vceBaseDirectory = args.vceroot
        coverBaseDirs = merge_basedir_args(args)
        performTask (args.command, args.verbose)
    

if __name__ == "__main__":
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
    try:
        main()
    except Exception as err:
        if str(err) != 'VCAST Termination Error':
            print(Exception, err)
            print(traceback.format_exc())




