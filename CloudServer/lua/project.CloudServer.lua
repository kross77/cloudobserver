project "CloudServer"
	kind "ConsoleApp"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	
	cloud.project.copyConfig()
	cloud.project.createDumpsFolder()
	cloud.project.copyHtdocsFolder()
	
	
	includedirs { "service-interface/" }

	links { "cf-server" }
	includedirs { "src/cf-server"}
	
	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}	
	
	links { "cf-http" }
	includedirs { "3rdparty/cf-http"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	configuration { "gmake" }
		linkoptions {
			"-lcf-server",
			"-lboost-sqlite",
			"-lcf-http",
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
