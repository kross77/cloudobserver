project "cf-http"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "3rdparty/cf-http/**.h", "3rdparty/cf-http/**.cpp" }
	
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
