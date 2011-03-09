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
if not _OPTIONS["libsPath"] then
   _OPTIONS["libsPath"] = nil
end

newoption {
   trigger     = "BoostLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost libs search"
}
if not _OPTIONS["BoostLibsPath"] then
   _OPTIONS["BoostLibsPath"] = nil
end

newoption {
   trigger     = "FFmpegLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for FFMpeg libs search"
}
if not _OPTIONS["FFmpegLibsPath"] then
   _OPTIONS["FFmpegLibsPath"] = nil
end

newoption {
   trigger     = "OpenALLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenAL libs search"
}
if not _OPTIONS["OpenALLibsPath"] then
   _OPTIONS["OpenALLibsPath"] = nil
end

newoption {
   trigger     = "OpenCVlibsPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenCV libs search"
}
if not _OPTIONS["OpenCVlibsPath"] then
   _OPTIONS["OpenCVlibsPath"] = nil
end

-- Options for includes

newoption {
   trigger     = "includesPath",
   value       = "PATH",
   description = "Choose a particular directory for general includes search"
}
if not _OPTIONS["includesPath"] then
   _OPTIONS["includesPath"] = nil
end

newoption {
   trigger     = "BoostIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost includes search"
}
if not _OPTIONS["BoostIncludesPath"] then
   _OPTIONS["BoostIncludesPath"] = nil
end

newoption {
   trigger     = "FFmpegIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for FFMpeg includes search"
}
if not _OPTIONS["FFmpegIncludesPath"] then
   _OPTIONS["FFmpegIncludesPath"] = nil
end

newoption {
   trigger     = "OpenALIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenAL includes search"
}
if not _OPTIONS["OpenALIncludesPath"] then
   _OPTIONS["OpenALIncludesPath"] = nil
end

newoption {
   trigger     = "OpenCVIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenCV includes search"
}
if not _OPTIONS["OpenCVIncludesPath"] then
   _OPTIONS["OpenCVIncludesPath"] = nil
end

newoption {
   trigger     = "c99IncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for C99 includes search if it is not defined on your system by defauft. WINDOWS-MSVC-SPECIFIC-REQUIRED-FOR-FFMPEG-OPTION! because on 2011.03.** msvc++ does not support C99 and FFmpeg release requires C99 there are errors compiling in VS environment. Choose a particular directory for C99 includes search. Problem described here: http://ffmpeg.arrozcru.org/wiki/index.php?title=Inttypes.h . Currently required files could be found here http://code.google.com/p/msinttypes/downloads/list ."
}
if not _OPTIONS["c99Includes"] then
   _OPTIONS["OpenCVIncludesPath"] = nil
end
 	
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
"/usr/lib",
"/usr/local/lib"
 }	 
 
end	 

 
 --  user defined libs:
 
 libdirs {
 _OPTIONS["libsPath"],
  _OPTIONS["BoostLibsPath"],
    _OPTIONS["FFmpegLibsPath"],
     _OPTIONS["OpenALLibsPath"],
      _OPTIONS["OpenCVlibsPath"]
 }

-- user defined include directorys

 includedirs {
 _OPTIONS["includesPath"],
  _OPTIONS["BoostIncludesPath"],
    _OPTIONS["FFmpegIncludesPath"],
     _OPTIONS["OpenALIncludesPath"],
      _OPTIONS["OpenCVIncludesPath"],
       _OPTIONS["c99IncludesPath"]
       }	 		 		
 	 
 -- add into project all possible code files and folders
 
    files { "**.c", "**.h", "**.cpp", "**.hpp" }
 
 -- set configurations
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
          
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }  
         