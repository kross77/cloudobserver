premake4.exe  --file=build.lua --os=windows  --libsPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/lib" --includesPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/include" --OpenCVIncludesPath="C:/OpenCV2.1/include" --OpenALIncludesPath="C:/Program Files (x86)/OpenAL 1.1 SDK/include" --c99IncludesPath="C:/Users/Avesta/Downloads/msinttypes-r26" --platform=x32 vs2008
premake4.exe  --file=build.lua --os=windows  --libsPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/lib" --includesPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/include" --OpenCVIncludesPath="C:/OpenCV2.1/include" --OpenALIncludesPath="C:/Program Files (x86)/OpenAL 1.1 SDK/include" --c99IncludesPath="C:/Users/Avesta/Downloads/msinttypes-r26" --platform=x32 vs2005
premake4.exe  --file=build.lua --os=windows  --libsPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/lib" --includesPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/include" --OpenCVIncludesPath="C:/OpenCV2.1/include" --OpenALIncludesPath="C:/Program Files (x86)/OpenAL 1.1 SDK/include" --c99IncludesPath="C:/Users/Avesta/Downloads/msinttypes-r26" --platform=x32 gmake
premake4.exe  --file=build.lua --os=windows  --libsPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/lib" --includesPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/include" --OpenCVIncludesPath="C:/OpenCV2.1/include" --OpenALIncludesPath="C:/Program Files (x86)/OpenAL 1.1 SDK/include" --c99IncludesPath="C:/Users/Avesta/Downloads/msinttypes-r26" --platform=x32 codeblocks
premake4.exe  --file=build.lua --os=windows  --libsPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/lib" --includesPath="C:/Users/Avesta/Documents/Visual Studio 2008/Projects/LibsAndHeaders/include" --OpenCVIncludesPath="C:/OpenCV2.1/include" --OpenALIncludesPath="C:/Program Files (x86)/OpenAL 1.1 SDK/include" --c99IncludesPath="C:/Users/Avesta/Downloads/msinttypes-r26" --platform=x32 codelite


::GOTO LinuxComment
::Not Tested
premake4.exe  --file=build.lua --os=linux  --platform=x32 gmake
premake4.exe  --file=build.lua --os=linux  --platform=x32 codeblocks
premake4.exe  --file=build.lua --os=linux  --platform=x32 codelite
:LinuxComment

::GOTO MacOsComment
::Not Tested
premake4.exe  --file=build.lua --os=macosx  --platform=x32 gmake
premake4.exe  --file=build.lua --os=macosx  --platform=x32 codeblocks
premake4.exe  --file=build.lua --os=macosx  --platform=x32 xcode3
premake4.exe  --file=build.lua --os=macosx  --platform=x32 codelite
:MacOsComment