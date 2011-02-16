-- A solution contains projects, and defines the available configurations

solution "CloudForeverWriter"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   
   project "CloudForeverWriter"
      kind "ConsoleApp"
      language "C++"
 

 		libdirs { "../LibsAndHeaders/lib" }	
 		links {"avcodec-52" , "avdevice-52" , "avformat-52" , "avutil-50" , "swscale-0" , "cv210" , "cxcore210" , "highgui210" , "openal32" }
 		includedirs { "../LibsAndHeaders/include" }    
 	 
 -- all possible code files
 
    files { "**.h", "**.cpp", "**.hpp" }
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         targetdir  "bin/debug" 
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }  
         targetdir "bin/release"