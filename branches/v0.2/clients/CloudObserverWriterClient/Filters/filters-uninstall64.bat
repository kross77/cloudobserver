regsvr32 /s /u %windir%\SysWOW64\MatroskaSplitter.ax
erase %windir%\SysWOW64\MatroskaSplitter.ax

regsvr32 /s /u %windir%\SysWOW64\MatroskaMuxer.ax
erase %windir%\SysWOW64\MatroskaMuxer.ax

regsvr32 /s /u %windir%\SysWOW64\lame.ax
erase %windir%\SysWOW64\lame.ax

regedit /s x264vfw64u.reg
erase %windir%\SysWOW64\x264vfw.dll