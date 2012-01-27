project "FileService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()
	cloud.project.useopenSSL()

	links { "cf-http" }
	includedirs { "3rdparty/cf-http" }
	
	links { "cf-util" }
	includedirs { "src/cf-util"}
	
	links { "cf-fs" }
	includedirs { "src/cf-fs"}
	
	cloud.project.useBoost()
	
	includedirs { "service-interface/" }
	
	files { "src/default-services/file_service/**"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
