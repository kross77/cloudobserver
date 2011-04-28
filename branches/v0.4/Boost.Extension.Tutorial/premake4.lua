-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

if action == "clean" then
	os.rmdir("projects/**")
	os.rmdir("projects")
end

-- Options for libs search

newoption {
	trigger     = "libsPath",
	value       = "PATH",
	description = "Choose a particular directory for general libs search. ';' separators are allowed like --libsPath=C:/src/Libs;C:/src/MoreLibs"
}

newoption {
	trigger     = "BoostLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for Boost libs search (do not forget Boost-Extension and Boost-Reflection which are required by samples we try to re-create following instructions given here http://boost-extension.redshoelace.com/docs/boost/extension/index.html in this solution, also remember that we adress them as part of boost: 'boost/reflection/**', 'boost/extension/**')"
}

-- Options for includes

newoption {
	trigger     = "includesPath",
	value       = "PATH",
	description = "Choose a particular directory for general includes search. ';' separators are allowed like --includesPath=C:/src/Libs;C:/src/MoreLibs "
}

newoption {
	trigger     = "BoostIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for Boost includes search"
}

-- Options for Shared Libs

newoption {
	trigger     = "soPath",
	value       = "PATH",
	description = "Choose a particular directory for general Shared Libs (dll, so...) search. ';' separators are allowed"
}

-- Script Options

newoption {
	trigger     = "CopySharedLibraries",
	value       = "true",
	description = "Set if we shall copy shared librarys into application build folders"
}

newoption {
	trigger     = "DiscLetterWithOs",
	value       = "L",
	description = "Choose a particular disc letter where the system is installed (used only in case you followed read me and installed all librarys into your system Programm Files folder but system disc letter is not 'C' )"
}

if  _OPTIONS["DiscLetterWithOs"] then
	disc = _OPTIONS["DiscLetterWithOs"] 
else
	disc = "C"
end

cloud = { }

function cloud.addLibDir(path)
	--
	if  path then
		libdirs {  string.explode(path , ";") }
	end
end

function cloud.addIncludeDir(path)
	--
	if path then
		includedirs {  string.explode(path , ";") }
	end
end

function cloud.copyFileIntoBuild(filePath, fileName)
	--
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release")
	end
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/debug/" .. fileName  )
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/release/" .. fileName )
end

cloud.win = { }

function cloud.win.addLibDirFromProgrammFiles(relativePath)
	--
	if os.isdir( disc .. ":/Program Files (x86)/" .. relativePath ) then
		libdirs{disc .. ":/Program Files (x86)/" .. relativePath}
	end
	if os.isdir( disc .. ":/Program Files/" .. relativePath ) then
		libdirs{disc .. ":/Program Files/" .. relativePath}
	end
end

function cloud.win.addIncludeDirFromProgrammFiles(relativePath)
	--
	if os.isdir( disc .. ":/Program Files (x86)/" .. relativePath ) then
		includedirs{disc .. ":/Program Files (x86)/" .. relativePath}
	end
	if os.isdir( disc .. ":/Program Files/" .. relativePath ) then
		includedirs{disc .. ":/Program Files/" .. relativePath}
	end
end

function cloud.win.addLibFromProgrammFiles(folderName)
	--
	cloud.win.addIncludeDirFromProgrammFiles(folderName .. "/include")
	cloud.win.addLibDirFromProgrammFiles(folderName .. "/lib")
end

function cloud.win.addLibFromProgrammFiles2(folderName, specialLibraryFolder)
	--
	cloud.win.addIncludeDirFromProgrammFiles(folderName .. "/include")
	cloud.win.addLibDirFromProgrammFiles(folderName .. "/" .. specialLibraryFolder)
end

function cloud.win.copyDLL( folderName ,fileName)
	--
	if _OPTIONS["soPath"] then
		pa = os.pathsearch(fileName, disc .. ":/Program Files (x86)/" .. folderName .. "/bin", disc .. ":/Program Files/" .. folderName .. "/bin", string.explode( _OPTIONS["soPath"] , ";") )  .. "/".. fileName
		if pa then
			cloud.copyFileIntoBuild(pa, fileName)
		end
	else
		pa = os.pathsearch(fileName,  fileName, disc .. ":/Program Files (x86)/" .. folderName .. "/bin", disc .. ":/Program Files/" .. folderName .. "/bin") .. "/".. fileName
		if pa then
			cloud.copyFileIntoBuild(pa, fileName)
		end
	end
	if pa then
		printf("file: ".. fileName.. " copied into builds dirs" )
	end
end

cloud.project = {}

function cloud.project.init()
	--
	cloud.addLibDir(  _OPTIONS["libsPath"] )
	cloud.addIncludeDir( _OPTIONS["includesPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		libdirs {
		"/opt/local/lib",
		"/usr/lib",
		"/usr/local/lib"
		}
		
		includedirs {
		"/opt/local/include",
		"/usr/include",
		"/usr/local/include"
		}
		links{"dl"} 
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
		"Carbon.framework"
		}
		
		libdirs {
		"/usr/lib",
		"/usr/local/lib"
		}
		
		includedirs {
		"/usr/include",
		"/usr/local/include"
		}
		links{"dl"}
	end 
end
	
function cloud.project.useBoost()
	--
	cloud.addIncludeDir( _OPTIONS["BoostIncludesPath"] )
	cloud.addLibDir( _OPTIONS["BoostLibsPath"])
	if os.get() == "windows" then
		defines { "WIN" } 
		cloud.win.addLibFromProgrammFiles("Boost-1.46.1")
	end	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread"
		}
	end
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread"
		}	
	end 
end

solution "Boost.Extension.Tutorials"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	configuration { "Debug" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
	
	configuration { "Release" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
	
--Interoperability---------------------------------------------------------------------	

	project "Interoperability"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files {  "src/interoperability_main.cpp" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		project "lib-interoperability"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-interoperability/**"}
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

--Mltiple-Inheritance---------------------------------------------------------------------	

	project "Mltiple-Inheritance"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files {  "src/multiple-inheritance_main.cpp" ,"src/headers-interfaces/computer.hpp" ,"src/headers-interfaces/vehicle.hpp"}
		
		-- next 2 lines actually should not be needed
		links { "lib-multiple-inheritance-Vehicle" }
		links { "lib-multiple-inheritance-Computer" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		project "lib-multiple-inheritance-Vehicle"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/vehicle.cpp" ,"src/headers-interfaces/vehicle.hpp" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		project "lib-multiple-inheritance-Car"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files {"src/lib-multiple-inheritance/car.**" ,"src/headers-interfaces/vehicle.hpp" }
		links { "lib-multiple-inheritance-Vehicle" }
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		project "lib-multiple-inheritance-Computer"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/computer.cpp" ,"src/headers-interfaces/computer.hpp" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		project "lib-multiple-inheritance-Boat"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/boat.**" ,"src/headers-interfaces/vehicle.hpp" }
		links { "lib-multiple-inheritance-Vehicle" }
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		project "lib-multiple-inheritance-Plane"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/plane.**"  ,"src/headers-interfaces/vehicle.hpp" }
		links { "lib-multiple-inheritance-Vehicle" }
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		project "lib-multiple-inheritance-Flying-Car"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/flying_car.**" ,"src/lib-multiple-inheritance/plane.hpp"}
		links { "lib-multiple-inheritance-Vehicle" }
		links { "lib-multiple-inheritance-Plane" }
		links { "lib-multiple-inheritance-Car" }
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		project "lib-multiple-inheritance-Car-Of-The-Future"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-multiple-inheritance/car_of_the_future.**" ,"src/lib-multiple-inheritance/boat.hpp"  ,"src/lib-multiple-inheritance/flying_car.hpp" ,"src/headers-interfaces/computer.hpp"  }
		links { "lib-multiple-inheritance-Vehicle" }
		links { "lib-multiple-inheritance-Plane" }
		links { "lib-multiple-inheritance-Car" }
		links { "lib-multiple-inheritance-Flying-Car", "lib-multiple-inheritance-Boat", "lib-multiple-inheritance-Computer" }
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

--Simple-Inheritance---------------------------------------------------------------------

	project "Simple-Inheritance"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files {  "src/simple-inheritance_main.cpp" ,"src/headers-interfaces/animal.h"}
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		project "lib-simple-inheritance"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-simple-inheritance/animals.cpp" ,"src/headers-interfaces/animal.h" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
--Hello-World---------------------------------------------------------------------
		
			project "Hello-World"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files {  "src/hello-world_main.cpp"}
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		project "lib-hello-world"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useBoost()
		files { "src/lib-hello-world/c-style-functions.cpp"  }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
-----------------------------------------------------------------------
