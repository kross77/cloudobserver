copy MatroskaSplitter.ax %windir%\SysWOW64
regsvr32 /s %windir%\SysWOW64\MatroskaSplitter.ax

copy MatroskaMuxer.ax %windir%\SysWOW64
regsvr32 /s %windir%\SysWOW64\MatroskaMuxer.ax

copy lame.ax %windir%\SysWOW64
regsvr32 /s %windir%\SysWOW64\lame.ax

copy x264vfw.dll %windir%\SysWOW64
regedit /s x264vfw64.reg