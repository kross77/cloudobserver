project "UsersAccountsService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()

	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http" }
	
	links { "boost-sqlite" }
	includedirs { "3rdparty/boost-sqlite"}	
	
	configuration { "gmake" }
		linkoptions {
			"-lboost-sqlite",
			"-lcf-util"
		}
	configuration { }
	
	cloud.project.useBoost()
	cloud.project.useopenSSL()
	
	files { "src/default-services/users_accounts_service/**"}
	includedirs { "service-interface/" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
