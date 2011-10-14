project "cf-fs"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "src/cf-fs/**.h", "src/cf-fs/**.cpp" }
	
	cloud.project.init()
	cloud.project.useopenSSL()
	cloud.project.useBoost()
	
	links { "cf-http" }
	includedirs { "3rdparty/cf-http"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
