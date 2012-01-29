project "cf-server"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "src/cf-server/**.h", "src/cf-server/**.cpp" }
	
	cloud.project.init()
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}

	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http"}
		
	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}	
	
	configuration { "gmake" }
		linkoptions {
			"-lboost-sqlite",
			"-lcf-util",
			"-lcf-fs"
		}
	configuration { }
	
	cloud.project.useBoost()
	cloud.project.useopenSSL()
	
	includedirs { "service-interface/" }
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
