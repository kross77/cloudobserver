project "cf-util"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "src/cf-util/**.h", "src/cf-util/**.cpp" }
	files { "3rdparty/cf-http/**.h", "3rdparty/cf-http/**.cpp" }

	cloud.project.init()
	
	includedirs { "3rdparty/cf-http"}
	
	cloud.project.useBoost()
	cloud.project.useopenSSL()
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
