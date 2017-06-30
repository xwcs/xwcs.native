rem %1 - work dir
rem %2 - project name
rem %3 - configuration {Debug|Release}

set API_KEY=6001efcb-af96-32f3-b30f-f0aedd5a2851
set DEST_URL=https://test-www.egaf.it/nexus/repository/nuget-hosted/
set DEP_DIR=%~dp0
set DEP_DIR=%DEP_DIR:~0,-1%

:: work dir
if "%1"=="-" goto blank_build
set WD=%~1
goto next_build

:blank_build

set WD=%CD%
:next_build

:: project name
if "%2"=="-" goto blank_build1
set PR=%~2
goto next_build1

:blank_build1

for %%f in (%CD%) do set myfolder=%%~nxf
set PR=%myfolder%
:next_build1

:: build type
if "%3"=="" goto blank_build2
set BT=%~3
goto next_build2

:blank_build2

set BT=Debug
:next_build2

echo %WD%
echo %PR%
echo %BT%

:: delete old nupkg
del %WD%\*.nupkg -Y

:: set api key
"%DEP_DIR%\nuget.exe" setapikey %API_KEY% -source %DEST_URL%

:: do package
"%DEP_DIR%\nuget.exe" pack %PR%.nuspec -Verbosity detailed -Properties Configuration=%BT%

FOR %%F IN (%WD%\*.nupkg) DO (
 set filename=%%~nxF
 goto publish
)
:publish
"%DEP_DIR%\nuget.exe" push %filename% -Source %DEST_URL%

