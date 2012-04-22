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
REM * 	1.
REM * <File history>
REM *	1. 
REM ************************************

REM ************************************
REM * Initialize vars
REM ************************************
set macro=

REM ************************************
REM * 
REM ************************************
if "%1"=="" (
	echo ^<Usage^>
	echo   makefile_cexam_1.bat go
	echo ^<Options^>
	echo   makefile_cexam_1.bat TOI1
	echo    =^> macro "TOI1" defined	
	
	goto end
) else if "%1"=="TOI1" (
	set macro=-DTOI1
) else if "%1"=="ADMIN" (
	set macro=-DADMIN
) else if "%1"=="go" (
    goto compile
) else (
    echo Unknown argument: %1
    goto end
)

REM ************************************
REM * Compile files into prog.exe
REM ************************************
:compile

rem if "%1"=="go" (
set LINE=bcc32 %macro% -eprog_bcc.exe main.c nyuukai.c keisoku.c sakujyo.c admin.c
echo bcc32 %macro% -eprog_bcc.exe main.c nyuukai.c keisoku.c sakujyo.c admin.c
rem bcc32 %macro% -eprog_bcc.exe main.c nyuukai.c keisoku.c sakujyo.c admin.c
rem echo %LINE%
%LINE%
    rem echo bcc32 %macro% -eprog_bcc.exe main.c nyuukai.c keisoku.c sakujyo.c admin.c
    rem bcc32 %macro% -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
    goto end
rem )

REM ************************************
REM * end module
REM ************************************
:end

set macro=
set LINE=
