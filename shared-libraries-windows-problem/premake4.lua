action = _ACTION or ""

function inject (filename)
  local f = assert(loadfile(filename))
  return f()
end

-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

inject  ("lua/cloud/cloud.options.lua")
inject  ("lua/cloud/cloud.system.lua")
inject  ("lua/cloud/cloud.project.lua")


solution "LibraryProblem"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	flags { "StaticRuntime" }
	
	configuration { "Debug" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
	
	configuration { "Release" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
		
project "DemoApp"
	kind "ConsoleApp"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	
	links { "cf-util" }
	includedirs { "src/cf-util"}

	cloud.project.useBoost()
	
	files { "src/main.cpp", "src/plug_in_interface.h"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
		
inject ("lua/cf/project.cf-util.lua")

project "DemoPlugin"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	cloud.project.useBoost()
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	files {  "src/plug_in.cpp",  "src/plug_in_interface.h"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
