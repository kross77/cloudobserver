project "cf-fs"
	kind "StaticLib"
	language "C++"
	location ( "projects/" .. os.get() .. "-" .. action )
	files { "src/cf-fs/**.h", "src/cf-fs/**.cpp" }

	cloud.project.init()

	links { "cf-util" }
	includedirs { "src/cf-util"}
	includedirs { "3rdparty/cf-http"}	
	includedirs { "service-interface/" }	
	
	configuration { "gmake" }
		linkoptions {
			"-lcf-util"
		}
	configuration { }
	
	cloud.project.useBoost()
	cloud.project.useopenSSL()	
	
	configuration "gmake"
		buildoptions { "-fPIC" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Unicode" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed", "Unicode" }
