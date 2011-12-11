project "MapsTests"
	kind "ConsoleApp"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	cloud.project.useBoost()
	-- cloud.project.useCDS()
	
	files { "src/**" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode",  "EnableSSE2", "StaticRuntime"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode", "EnableSSE2", "StaticRuntime"}
