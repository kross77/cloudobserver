pushd ..
call %WNETBASE%\bin\setenv.bat %WNETBASE% chk x86 WXP
popd
nmake
