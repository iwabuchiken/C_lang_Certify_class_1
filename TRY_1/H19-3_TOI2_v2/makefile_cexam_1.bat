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
REM * 	2. macro => macro option
REM * <File history>
REM *	1. 
REM ************************************

REM ************************************
REM * Show usage
REM * Set "str" variable
REM ************************************
if "%1"=="" (
	echo ^<Usage^>
	echo   makefile_cexam_1.bat go
	echo ^<Options^>
	echo   makefile_cexam_1.bat TOI1
	echo    =^> macro "TOI1" defined	
	
	goto end
) else (
	set str=%1
)

REM ************************************
REM * Delete files
REM ************************************

if "%str%"== "rm" (
    echo del *.obj *.tds *.exe
	del *.obj *.tds *.exe
    goto end
)

rem debug
rem echo str=%str%
rem goto end

rem ) else if "%1"=="TOI2" (
rem 	set macro=-DTOI2
rem ) else (
rem 	set macro=
rem )

rem debug
rem set str=%1%
rem echo %str:~0,3%
rem echo %1:~0,2%
rem if "%str:~0,3%"== "TOI" (
rem 	echo yes
rem 	echo %str:~0,3%
rem ) else (
rem 	echo no
rem 	echo %str:~0,3%
rem )
rem if "%1:~0,3%"=="TOI" (
rem 	echo yes
rem ) else (
rem 	echo no
rem 	echo "%1:~0,3%"
rem )

REM ************************************
REM * Compile files into prog.exe
REM ************************************
echo gcc %macro% -o prog_gcc.exe main.c nyuukai.c keisoku.c sakujyo.c
gcc %macro% -o prog_gcc.exe main.c nyuukai.c keisoku.c sakujyo.c
rem echo bcc32 %macro% -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
rem bcc32 %macro% -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
REM bcc32 %macro% -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c admin.c

REM ************************************
REM * end module
REM ************************************
set str=
set macro=

:end
