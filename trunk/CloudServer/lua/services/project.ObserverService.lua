project "ObserverService"
	kind "SharedLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	
	cloud.project.init()

	links { "cf-http" }
	includedirs { "3rdparty/cf-http" }
	
	configuration { "gmake" }
		linkoptions {
			"-lcf-http"
		}
	configuration { }
	
	cloud.project.useBoost()
	
	files { "src/default-services/observer_service/**"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
