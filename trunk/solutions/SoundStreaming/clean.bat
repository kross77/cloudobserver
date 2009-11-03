@echo off

echo Cleaning solution...

taskkill /f /im SoundStreaming.
if exist .\bin rmdir /s /q .\bin
for /d %%i in (*) do if exist %%i\bin rmdir /s /q %%i\bin
for /d %%i in (*) do if exist %%i\obj rmdir /s /q %%i\obj
for /d %%i in (*) do if exist %%i\*.csproj.user del %%i\*.csproj.user

echo Done.