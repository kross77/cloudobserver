project "FileService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()

	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
		
	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http" }	
	
	configuration { "gmake" }
		linkoptions {
			"-lcf-util",
			"-lcf-fs"
		}
	configuration { }
	
	cloud.project.useBoost()
	cloud.project.useopenSSL()
		
	includedirs { "service-interface/" }
	
	files { "src/default-services/file_service/**"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
