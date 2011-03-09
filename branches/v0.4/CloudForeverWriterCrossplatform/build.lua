-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

if action == "clean" then
  os.rmdir("build")
end

-- Options for libs search

newoption {
   trigger     = "libsPath",
   value       = "PATH",
   description = "Choose a particular directory for general libs search"
}

newoption {
   trigger     = "BoostLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost libs search"
}

newoption {
   trigger     = "FFmpegLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for FFMpeg libs search"
}

newoption {
   trigger     = "OpenALLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenAL libs search"
}

newoption {
   trigger     = "OpenCVLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenCV libs search"
}

-- Options for includes

newoption {
   trigger     = "includesPath",
   value       = "PATH",
   description = "Choose a particular directory for general includes search"
}

newoption {
   trigger     = "BoostIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost includes search"
}

newoption {
   trigger     = "FFmpegIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for FFMpeg includes search"
}

newoption {
   trigger     = "OpenALIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenAL includes search"
}


newoption {
   trigger     = "OpenCVIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenCV includes search"
}

newoption {
   trigger     = "c99IncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for C99 includes search if it is not defined on your system by defauft. WINDOWS-MSVC-SPECIFIC-REQUIRED-FOR-FFMPEG-OPTION! because on 2011.03.** msvc++ does not support C99 and FFmpeg release requires C99 there are errors compiling in VS environment. Choose a particular directory for C99 includes search. Problem described here: http://ffmpeg.arrozcru.org/wiki/index.php?title=Inttypes.h . Currently required files could be found here http://code.google.com/p/msinttypes/downloads/list ."
}

-- Main Project Code

solution "CloudForeverWriter"
	location ( "build/" .. action )
	configurations { "Debug", "Release" }
	objdir     ( "build/" .. action .. "/bin/obj" )
 
   configuration { "Debug" }
    targetdir ( "build/" .. action .. "/bin/debug" )
 
  configuration { "Release" }
    targetdir ( "build/" .. action ..  "/bin/release" )
    
   -- A project defines one build target
   
   project "CloudForeverWriter"
      kind "ConsoleApp"
      language "C++"
      location ( "build/" .. action )
      
 

 	
-- all libs we require, across all platforms we use  linux, macosx, windows. Support for bsd, solaris can be added.

if os.get() == "windows" then
defines { "WIN" }
    links {
 "avcodec",
 "avformat",
 "avutil",
 "swscale",
 "cv210",
 "cxcore210",
 "highgui210",
 "openal32"
  }

end

if os.get() == "linux" then
defines { "LIN" }
    links {
 "avcodec", 
 "avformat",
 "avutil",
 "swscale",
 "boost_regex-mt",
 "boost_system-mt",
 "boost_thread-mt",
 "cv",
 "cxcore",
 "highgui",
 "openal" }
 
  libdirs {
"/opt/local/lib",
"/usr/lib",
"/usr/local/lib"
 }

 includedirs {
"/opt/local/include",
"/usr/include",
"/usr/local/include",
 }	 
 
end

if os.get() == "macosx" then
defines { "MAC" }
    links {
 "avcodec", 
 "avformat",
 "avutil",
 "swscale",
 "opencv_core",
 "opencv_highgui",
 "opencv_imgproc",
 "Carbon.framework",
 "OpenAL.framework",
 "QuickTime.framework",
 "boost_regex",
 "boost_system",
 "boost_thread"
 }
 
  libdirs {
"/opt/local/lib",
"/System/Libarary/Frameworks",
"/Library/Frameworks",
"/usr/lib",
"/usr/local/lib"
 }

 includedirs {
"/opt/local/include",
"/usr/include",
"/usr/local/include",
 }	 
 
end	 

 
 --  user defined libs:
 
if  _OPTIONS["libsPath"] then
   libdirs {  _OPTIONS["libsPath"] }
end

if _OPTIONS["BoostLibsPath"] then
  libdirs { _OPTIONS["BoostLibsPath"] }
end

if  _OPTIONS["FFmpegLibsPath"] then
  libdirs {  _OPTIONS["FFmpegLibsPath"] }
end

if  _OPTIONS["OpenALLibsPath"] then
 libdirs {   _OPTIONS["OpenALLibsPath"] }
end

if  _OPTIONS["OpenCVLibsPath"] then
 libdirs {  _OPTIONS["OpenCVLibsPath"] }
end

-- user defined include directorys

if  _OPTIONS["includesPath"] then
   includedirs {  _OPTIONS["includesPath"] }
end

if _OPTIONS["BoostIncludesPath"] then
  includedirs { _OPTIONS["BoostIncludesPath"] }
end

if  _OPTIONS["FFmpegIncludesPath"] then
  includedirs {  _OPTIONS["FFmpegIncludesPath"] }
end

if  _OPTIONS["OpenALIncludesPath"] then
 includedirs {   _OPTIONS["OpenALIncludesPath"] }
end

if  _OPTIONS["OpenCVIncludesPath"] then
 includedirs {  _OPTIONS["OpenCVIncludesPath"] }
end

if _OPTIONS["c99IncludesPath"] then
  includedirs { _OPTIONS["c99IncludesPath"] }
end	 		 		
 	 
 -- add into project all possible code files and folders
 
    files { "**.c", "**.h", "**.cpp", "**.hpp" }
 
 -- set configurations
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
          
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }  
         