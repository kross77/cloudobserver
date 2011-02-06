copy MatroskaSplitter.ax %windir%\System32
regsvr32 /s %windir%\System32\MatroskaSplitter.ax

copy MatroskaMuxer.ax %windir%\System32
regsvr32 /s %windir%\System32\MatroskaMuxer.ax

copy lame.ax %windir%\System32
regsvr32 /s %windir%\System32\lame.ax

copy x264vfw.dll %windir%\System32
regedit /s x264vfw32.reg