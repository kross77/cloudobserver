project "UsersFilesService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	cloud.project.useopenSSL()

	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	links { "cf-http" }
	includedirs { "3rdparty/cf-http" }
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	cloud.project.useBoost()
	
	includedirs { "service-interface/" }
	
	files { "src/default-services/users_files_service/**"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
