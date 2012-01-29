project "UsersFilesService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()

	links { "cf-fs" }
	includedirs { "src/cf-fs"}	
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http" }
	
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
	
	files { "src/default-services/users_files_service/**"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
