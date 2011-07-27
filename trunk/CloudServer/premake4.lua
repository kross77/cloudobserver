-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

if action == "clean" then
	os.rmdir("projects/**")
	os.rmdir("projects/")
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
	description = "Choose a particular directory for Boost libs search"
}

newoption {
	trigger     = "OpenSSLLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenSSL libs search"
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

newoption {
	trigger     = "OpenSSLIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenSSL includes search"
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

function os.copydir(src_dir, dst_dir, filter, single_dst_dir)
	if not os.isdir(src_dir) then error(src_dir .. " is not an existing directory!") end
	filter = filter or "**"
	src_dir = src_dir .. "/"
	print('copy "' .. src_dir .. filter .. '" to "' .. dst_dir .. '".')
	dst_dir = dst_dir .. "/"
	local dir = path.rebase(".",path.getabsolute("."), src_dir) -- root dir, relative from src_dir
 
	os.chdir( src_dir ) -- change current directory to src_dir
		local matches = os.matchfiles(filter)
	os.chdir( dir ) -- change current directory back to root
 
	local counter = 0
	for k, v in ipairs(matches) do
		local target = iif(single_dst_dir, path.getname(v), v)
		--make sure, that directory exists or os.copyfile() fails
		os.mkdir( path.getdirectory(dst_dir .. target))
		if os.copyfile( src_dir .. v, dst_dir .. target) then
			counter = counter + 1
		end
	end
 
	if counter == #matches then
		print( counter .. " files copied.")
		return true
	else
		print( "Error: " .. counter .. "/" .. #matches .. " files copied.")
		return nil
	end
end

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
		pa = os.pathsearch(fileName, disc .. ":/Program Files (x86)/" .. folderName , disc .. ":/Program Files/" .. folderName , string.explode( _OPTIONS["soPath"] , ";") )  .. "/".. fileName
		if pa then
			cloud.copyFileIntoBuild(pa, fileName)
		end
	else
		pa = os.pathsearch(fileName,  fileName, disc .. ":/Program Files (x86)/" .. folderName , disc .. ":/Program Files/" .. folderName ) .. "/".. fileName
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
	libdirs {
		"./"
		}
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
	end 
end

function cloud.project.useBoost()
	--
	cloud.addIncludeDir( _OPTIONS["BoostIncludesPath"] )
	cloud.addLibDir( _OPTIONS["BoostLibsPath"])
		includedirs {"3rdparty/header-only"}
		defines{ "BOOST_ASIO_DISABLE_IOCP" }
	if os.get() == "windows" then
		defines { "WIN" } 
		cloud.win.addLibFromProgrammFiles("Boost-1.46.1")
	end	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread",
		"boost_filesystem",
		"boost_program_options",
		"dl"
		}
	end
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread",
		"boost_filesystem",
		"boost_program_options",
		"dl"
		}	
	end 
end

function cloud.project.useopenSSL()
	cloud.addLibDir(  _OPTIONS["OpenSSLLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["OpenSSLIncludesPath"] )
		
	if os.get() == "windows" then
		defines { "WIN" }
		links {
		"libeay32",
		"ssleay32"
		}
		cloud.win.addLibFromProgrammFiles("openssl-1.0.0d")
		if  _OPTIONS["CopySharedLibraries"] then
			cloud.win.copyDLL("openssl-1.0.0d/lib", "libeay32.dll")
			cloud.win.copyDLL("openssl-1.0.0d/lib", "ssleay32.dll")
		end
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"ssl",
		"crypto"
		}
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
		"ssl",
		"crypto"
		}
	end 
	
end

function cloud.project.copyConfig()
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release")
	end
	os.copyfile("assets/config.xml" , "projects/" .. os.get() .. "-" .. action .. "/config.xml" )
	os.copyfile("assets/config.xml" , "projects/" .. os.get() .. "-" .. action .. "/bin/debug/config.xml" )
	os.copyfile("assets/config.xml" , "projects/" .. os.get() .. "-" .. action .. "/bin/release/config.xml" )
end

function cloud.project.createDumpsFolder()
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release")
	end
	os.mkdir("projects/" .. os.get() .. "-" .. action .. "/dumps")
	os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/dumps")
	os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release/dumps")
end

function cloud.project.copyHtdocsFolder()
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/htdocs" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/htdocs")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release/htdocs" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release/htdocs")
	end
	os.copydir("assets/htdocs",  "projects/" .. os.get() .. "-" .. action .. "/bin/debug/htdocs")
	os.copydir("assets/htdocs",  "projects/" .. os.get() .. "-" .. action .. "/bin/release/htdocs")
	os.copydir("assets/htdocs",  "projects/" .. os.get() .. "-" .. action .. "/htdocs")
end

solution "CloudServer"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	configuration { "Debug" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
	
	configuration { "Release" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
	
	-- A project defines one build target


----------------------------------------------------------------------------------------------
-- server ------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------			
		
	project "CloudServer"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		
		cloud.project.init()
		cloud.project.useBoost()
		cloud.project.useopenSSL()
		
		cloud.project.copyConfig()
		cloud.project.createDumpsFolder()
		cloud.project.copyHtdocsFolder()
		
		links { "cf-http" }
		includedirs { "3rdparty/cf-http"}
		
		links { "sqlite" }
		includedirs { "3rdparty/sqlite"}
		
		links { "cf-util" }
		includedirs { "src/cf-util"}
		
		includedirs { "service-interface/" }
		
		files { "src/**.h", "src/**.hpp", "src/**.cpp" }

		excludes { "src/default-services/**" , "src/cf-util/**" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" , "Unicode"}
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "OptimizeSpeed" , "Unicode"}

------------------------------------------------------------------------------------------------

	project "cf-util"
		kind "StaticLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		files { "src/cf-util/**.h", "src/cf-util/**.cpp" }
		cloud.project.init()
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
			
------------------------------------------------------------------------------------------------

	project "cf-http"
		kind "StaticLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		files { "3rdparty/cf-http/**.h", "3rdparty/cf-http/**.cpp" }
		cloud.project.init()
		cloud.project.useBoost()
		
		configuration "gmake"
			buildoptions { "-fPIC" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols", "Unicode" }
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "OptimizeSpeed", "Unicode" }

------------------------------------------------------------------------------------------------

	project "sqlite"
		kind "StaticLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		files { "3rdparty/sqlite/**.h",  "3rdparty/sqlite/**.c", "3rdparty/sqlite/**.cpp" }
		cloud.project.init()
		cloud.project.useBoost()
		
		configuration "gmake"
			buildoptions { "-fPIC" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols", "Unicode" }
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "OptimizeSpeed", "Unicode" }
			
----------------------------------------------------------------------------------------------
-- services ----------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------			
-- DO NOT CREATE SERVICE PROJECT NAMES WITH "." IN THAM USE "_" INSTEAD			
----------------------------------------------------------------------------------------------			
	
	project "FileService"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		
		cloud.project.init()
		cloud.project.useBoost()
		cloud.project.useopenSSL()

		links { "cf-http" }
		includedirs { "3rdparty/cf-http" }
		
		links { "cf-util" }
		includedirs { "src/cf-util"}
		
		includedirs { "service-interface/" }
		
		files { "src/default-services/file_service/**"}

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" , "Unicode"}
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "OptimizeSpeed" , "Unicode"}

------------------------------------------------------------------------------------------------

	project "CloudService"
		kind "SharedLib"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		
		cloud.project.init()
		cloud.project.useBoost()

		links { "cf-http" }
		includedirs { "3rdparty/cf-http" }
		
		files { "src/default-services/cloud_service/**"}

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" , "Unicode"}
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "OptimizeSpeed" , "Unicode"}