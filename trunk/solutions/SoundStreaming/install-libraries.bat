@echo off

set MICROSOFT_SDKS_DIR=C:\Program Files\Microsoft SDKs
set REFERENCE_ASSEMBLIES_DIR=C:\Program Files\Reference Assemblies

echo Copying additional libraries into Reference Assemblies directory...
copy "%MICROSOFT_SDKS_DIR%\Silverlight\v3.0\Libraries\Server\System.ServiceModel.PollingDuplex.dll" "%REFERENCE_ASSEMBLIES_DIR%\Microsoft\Framework\v3.0\"
echo.

echo Installing additional libraries into global assembly cache...
gacutil /i "%REFERENCE_ASSEMBLIES_DIR%\Microsoft\Framework\v3.0\System.ServiceModel.PollingDuplex.dll"
echo.

echo Done.