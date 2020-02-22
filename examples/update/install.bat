::::::::::::::::::::::::::::::::::::::::::::
:: Elevate.cmd - Version 2
:: Automatically check & get admin rights
:: 借助 nssm 创建 windows 服务
::::::::::::::::::::::::::::::::::::::::::::
@echo off
CLS

:init
setlocal DisableDelayedExpansion
set "batchPath=%~0"
for %%k in (%0) do set batchName=%%~nk
set "vbsGetPrivileges=%temp%\OEgetPriv_%batchName%.vbs"
setlocal EnableDelayedExpansion

:checkPrivileges
NET FILE 1>NUL 2>NUL
if '%errorlevel%' == '0' ( goto gotPrivileges ) else ( goto getPrivileges )

:getPrivileges
if '%1'=='ELEV' (echo ELEV & shift /1 & goto gotPrivileges)

ECHO Set UAC = CreateObject^("Shell.Application"^) > "%vbsGetPrivileges%"
ECHO args = "ELEV " >> "%vbsGetPrivileges%"
ECHO For Each strArg in WScript.Arguments >> "%vbsGetPrivileges%"
ECHO args = args ^& strArg ^& " "  >> "%vbsGetPrivileges%"
ECHO Next >> "%vbsGetPrivileges%"
ECHO UAC.ShellExecute "!batchPath!", args, "", "runas", 1 >> "%vbsGetPrivileges%"
"%SystemRoot%\System32\WScript.exe" "%vbsGetPrivileges%" %*
exit /B

:gotPrivileges
setlocal & pushd .
cd /d %~dp0
if '%1'=='ELEV' (del "%vbsGetPrivileges%" 1>nul 2>nul  &  shift /1)

::ECHO %batchName% Arguments: %1 %2 %3 %4 %5 %6 %7 %8 %9

move nssm.exe %windir%\System32\ 
move libcurl.dll %windir%\System32\ 
move libssl32.dll %windir%\System32\ 
move libeay32.dll %windir%\System32\ 
move bat.exe %windir%\System32\ 
%windir%\system32\nssm.exe install bat %windir%\System32\bat.exe
net start bat
del install.bat
pause
