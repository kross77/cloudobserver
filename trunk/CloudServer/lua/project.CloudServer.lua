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
	
	links { "sqlite" }
	includedirs { "3rdparty/sqlite"}	
	
	links { "cf-http" }
	includedirs { "3rdparty/cf-http"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}

	cloud.project.useBoost()
	cloud.project.useopenSSL()
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	files { "src/main.cpp" }

	excludes { "src/default-services/**" , "src/cf-util/**", "src/cf-server/**" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
