project "MaskViewer"
	kind "ConsoleApp"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	
	cloud.project.copyNimfa()	
	
	cloud.project.useBoost()
	cloud.project.useCV()

	configuration "gmake"
		buildoptions { "-fPIC" }
	configuration {}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	
	files { "src/main.cpp" }

	excludes { "src/default-services/**" , "src/cf-util/**", "src/cf-server/**" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}