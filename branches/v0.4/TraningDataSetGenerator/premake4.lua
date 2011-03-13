-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

if action == "clean" then
  os.rmdir("projects/**")
  os.rmdir("projects")
end

-- Options for libs search

newoption {
   trigger     = "libsPath",
   value       = "PATH",
   description = "Choose a particular directory for general libs search. ';' separators are allowed like --libsPath=C:/Code/Libs;C:/Code/MoreLibs"
}

newoption {
   trigger     = "BoostLibsPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost libs search"
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
   description = "Choose a particular directory for general includes search. ';' separators are allowed like --includesPath=C:/Code/Libs;C:/Code/MoreLibs "
}

newoption {
   trigger     = "BoostIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for Boost includes search"
}

newoption {
   trigger     = "OpenCVIncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for OpenCV includes search"
}

newoption {
   trigger     = "c99IncludesPath",
   value       = "PATH",
   description = "Choose a particular directory for C99 includes search if it is not defined on your system by defauft.  Sometimes it is usefull to have them connected to project"
}

-- Main Project Code

solution "TraningDataSetGenerator"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
 
   configuration { "Debug" }
    targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
 
  configuration { "Release" }
    targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
  
   -- A project defines one build target  
   project "TraningDataSetGenerator"
      kind "ConsoleApp"
      language "C++"
      location ( "projects/" .. os.get() .. "-" .. action )
      links { "LSD-lib" }
      includedirs { "src/LSD-lib/headers" }
	
-- all libs we require, across all platforms we use  linux, macosx, windows. Support for bsd, solaris can be added.

if os.get() == "windows" then
defines { "WIN" }
    links {
 "cv210",
 "cxcore210",
 "highgui210"
  }

end

if os.get() == "linux" then
defines { "LIN" }
    links {
 "boost_filesystem",
 "boost_regex",
 "boost_system",
 "boost_thread",
 "cv",
 "cxcore",
 "highgui" }
 
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

 "opencv_core",
 "opencv_highgui",
 "opencv_imgproc",
 "Carbon.framework",
 "boost_filesystem-mt",
 "boost_regex-mt",
 "boost_system-mt",
 "boost_thread-mt"
 }
 
  libdirs {
"/opt/local/lib",
"/System/Library/Frameworks",
"/Library/Frameworks",
"/usr/lib",
"/usr/local/lib"
 }

 includedirs {
"/opt/local/include",
"/usr/include",
"/usr/local/include"
 }	 
 
end	 
 
 --  user defined libs:
 
if  _OPTIONS["libsPath"] then
   libdirs {  string.explode( _OPTIONS["libsPath"] , ";")  }
end

if _OPTIONS["BoostLibsPath"] then
  libdirs { _OPTIONS["BoostLibsPath"] }
end

if  _OPTIONS["OpenCVLibsPath"] then
 libdirs {  _OPTIONS["OpenCVLibsPath"] }
end

-- user defined include directorys

if  _OPTIONS["includesPath"] then
   includedirs {  string.explode( _OPTIONS["includesPath"] , ";") }
end

if _OPTIONS["BoostIncludesPath"] then
  includedirs { _OPTIONS["BoostIncludesPath"] }
end

if  _OPTIONS["OpenCVIncludesPath"] then
 includedirs {  _OPTIONS["OpenCVIncludesPath"] }
end

if _OPTIONS["c99IncludesPath"] then
  includedirs { _OPTIONS["c99IncludesPath"] }
end	 		 		
 	 
 -- add into project all possible code files and folders
 
    files { "src/TraningDataSetGenerator/**.c", "src/TraningDataSetGenerator/**.h", "src/TraningDataSetGenerator/**.cpp", "src/TraningDataSetGenerator/**.hpp" }

 -- set configurations
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
          
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }  
         
         
   project "LSD-lib"
      kind "ConsoleApp"
      language "C++"
      location ( "projects/" .. os.get() .. "-" .. action )
      files { "src/LSD-lib/src/**.c", "src/LSD-lib/src/**.h", "src/LSD-lib/src/**.cpp", "src/LSD-lib/src/**.hpp" }
      kind "StaticLib"

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
          
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }  
         
