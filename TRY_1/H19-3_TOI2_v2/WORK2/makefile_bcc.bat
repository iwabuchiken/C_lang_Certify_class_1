@echo off
REM ************************************
REM * <Basics>
REM * 	1. File: makefile_cexam_1.bat
REM * 	2. Date: 20120218_174430
REM * 	3. Author: Iwabuchi Ken
REM * 	4. Path: C:\workspaces\ws_ubuntu_1\G20111104_083701_C_learn_01\C_jissen_work\Chp_08_work\sub1.bat
REM * <Aim>
REM * 	1.
REM * <Usage>
REM * <Variables>
REM * 	1.str => %1
REM * 	2. MACRO_TOI => macro option if you want to specify which question
REM *                   you are targeting for compilation
REM * 	3. MACRO_ADMIN => macro option if you want the admin menu
REM * 	4. DEBUG => debug option
REM * <File history>
REM *	1. 
REM ************************************

REM ************************************
REM * initialize vars
REM ************************************
set str=
set macro=
set MACRO_TOI=
set MACRO_ADMIN=
set DEBUG=
set MAIN_FILE=
set LIB_FILE=
set TRUNK=
set LINE=

REM ************************************
REM * Show usage
REM * Set "str" variable
REM ************************************
rem if "%1"=="" (
rem 	echo ^<Usage^>
rem 	echo   makefile_cexam_1.bat sub1~.c
rem 	echo ^<Syntax^>
rem 	echo   makefile_cexam_1.bat ^<source file^> ^<macro: TOI^> ^<macro: ADMIN^> ^<macro: DEBUG^>
rem 	echo ^<Example^>
rem 	echo   makefile_cexam_1.bat sub1~.c TOI1
rem 	echo    =^> macro "TOI1" defined	
rem 	
rem 	goto end
rem ) else (
rem 	set str=%1
rem )
set str=%1

REM ************************************
REM * Delete files
REM ************************************

if "%str%"== "rm" (
rem	 debug
rem	 echo %1
rem	 goto end

rem    set LINE=del ^*.obj ^*.tds ^*.i ^*.exe
rem    set LINE=del
rem    set LINE=obj
rem    set LINE=del ^*.obj ^*.tds ^*.i ^*.exe
rem    set LINE=del 
    echo del *.obj *.tds *.i *.exe
    del *.obj *.tds *.i *.exe
rem    @echo %LINE%
rem    set LINE=bcc32 -D%DEBUG% -e%TRUNK%_bcc.exe %1
rem    set LINE=bcc32
rem @echo abc
rem @echo %LINE%
rem @echo %abc%
rem    %LINE%
rem	del *.obj *.tds *.exe
    goto end
)

rem debug
rem echo str=%str%
rem goto end

REM ************************************
REM * Set macro: %1
REM ************************************

if "%1"=="TOI2" (
    set MACRO_TOI=TOI2
) else if "%1"=="ADMIN" (
    set MACRO_ADMIN=ADMIN
) else if "%1"=="DEBUG" (
    set DEBUG=DEBUG
) else (
    set MAIN_FILE=%1
    for /f "tokens=1,2* delims=." %%a in ("%1") do (
        set TRUNK=%%a
    )
)

rem debug
rem echo TRUNK=%TRUNK%
rem goto end

REM ************************************
REM * Set macro: %2
REM ************************************

if "%2"=="TOI2" (
    set MACRO_TOI=TOI2
) else if "%2"=="ADMIN" (
    set MACRO_ADMIN=ADMIN
) else if "%2"=="DEBUG" (
    set DEBUG=DEBUG
) else (
    set LIB_FILE=%2
)

REM ************************************
REM * Set macro: %3
REM ************************************

if "%3"=="TOI2" (
    set MACRO_TOI=TOI2
) else if "%3"=="ADMIN" (
    set MACRO_ADMIN=ADMIN
) else if "%3"=="DEBUG" (
    set DEBUG=DEBUG
)

REM ************************************
REM * Compile files into prog.exe
REM ************************************
set LINE=bcc32 -DADMIN -eprog_bcc.exe main.c nyuukai.c admin.c sakujyo.c
echo %LINE%
%LINE%

REM ************************************
REM * end module
REM ************************************
:end

set str=
set macro=
set MACRO_TOI=
set MACRO_ADMIN=
set DEBUG=
set MAIN_FILE=
set LIB_FILE=
set TRUNK=
set LINE=
