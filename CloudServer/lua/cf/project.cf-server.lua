project "cf-server"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "src/cf-server/**.h", "src/cf-server/**.cpp" }
	
	cloud.project.init()
	cloud.project.useopenSSL()
	cloud.project.useBoost()

	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}	
	
	links { "cf-http" }
	includedirs { "3rdparty/cf-http"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	includedirs { "service-interface/" }
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
