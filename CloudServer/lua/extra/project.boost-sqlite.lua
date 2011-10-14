project "boost-sqlite"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "3rdparty/boost-sqlite/**.h",  "3rdparty/boost-sqlite/**.c", "3rdparty/boost-sqlite/**.cpp" }
	
	cloud.project.init()
	cloud.project.useBoost()
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
