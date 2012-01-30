project "CloudServer"
	kind "ConsoleApp"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	
	cloud.project.copyAssets()
	
	includedirs { "service-interface/" }

	links { "cf-server" }
	includedirs { "src/cf-server"}
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http"}	
	
	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}	
	
	configuration { "gmake" }
		linkoptions {
			"-lcf-server",
			"-lboost-sqlite",
			"-lcf-util",
			"-lcf-fs"
		}
	configuration { }

	cloud.project.useBoost()
	cloud.project.useopenSSL()
	
	files { "src/main.cpp" }

	excludes { "src/default-services/**" , "src/cf-util/**", "src/cf-server/**" }
	
	configuration "gmake"
		linkoptions { "-Wl,-rpath,./" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
