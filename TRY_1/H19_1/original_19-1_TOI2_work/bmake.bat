@echo off
if "%1"=="TOI2" (
	if "%2"=="DEBUG_NYUUKAI" (
		bcc32 -DTOI2 -DDEBUG_NYUUKAI -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
	) else if "%2"=="DEBUG" (
		bcc32 -DTOI2 -DDEBUG -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
	) else (
		bcc32 -DTOI2 -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
	)
) else (
	bcc32 -eprog.exe main.c nyuukai.c keisoku.c sakujyo.c
)