set SRC_FILTER_FOLDER=..\Debug
set SYS_FILTER_FOLDER=%windir%\System32
set FILTER_FILE_NAME=%SRC_FILTER_FOLDER%\renderer.ax

IF NOT EXIST %FILTER_FILE_NAME% GOTO ERROR_FILE_NOT_EXIST


@echo
@echo Install %FILTER_FILE_NAME%
@echo

copy %FILTER_FILE_NAME% %SYS_FILTER_FOLDER%
regsvr32 /s %SYS_FILTER_FOLDER%\renderer.ax
@echo
@echo Install complite
@echo
pause
GOTO EXIT
:ERROR_FILE_NOT_EXIST
@echo
@echo file not exist %FILTER_FILE_NAME%
@echo
pause
:EXIT