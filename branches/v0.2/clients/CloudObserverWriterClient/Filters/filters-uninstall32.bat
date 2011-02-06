regsvr32 /s /u %windir%\System32\MatroskaSplitter.ax
erase %windir%\System32\MatroskaSplitter.ax

regsvr32 /s /u %windir%\System32\MatroskaMuxer.ax
erase %windir%\System32\MatroskaMuxer.ax

regsvr32 /s /u %windir%\System32\lame.ax
erase %windir%\System32\lame.ax

regedit /s x264vfw32u.reg
erase %windir%\System32\x264vfw.dll