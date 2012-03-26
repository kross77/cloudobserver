project "ImageRendererService"
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
			"-lcf-fs",
			"-lcf-util",
			"-lboost-sqlite"
		}
	configuration { }

	cloud.project.useBoost()
	cloud.project.useopenSSL()
	cloud.project.useCV()
	
	includedirs { "service-interface/" }
	
	files { "src/default-services/image_renderer_service/**"}

	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" , "Unicode"}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" , "Unicode"}
