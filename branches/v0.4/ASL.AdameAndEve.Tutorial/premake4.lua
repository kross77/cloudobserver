-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

-- Options for libs search

newoption {
	trigger     = "libsPath",
	value       = "PATH",
	description = "Choose a particular directory for general libs search. ';' separators are allowed like --libsPath=C:/src/Libs;C:/src/MoreLibs"
}

newoption {
	trigger     = "TBBLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for SDL libs search"
}

newoption {
	trigger     = "ASLLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for SDL libs search"
}

newoption {
	trigger     = "BoostLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for Boost libs search"
}


-- Options for includes

newoption {
	trigger     = "includesPath",
	value       = "PATH",
	description = "Choose a particular directory for general includes search. ';' separators are allowed like --includesPath=C:/src/Libs;C:/src/MoreLibs "
}

newoption {
	trigger     = "TBBIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for SDL includes search"
}

newoption {
	trigger     = "ASLIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for SDL includes search"
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

function os.copydir(src_dir, dst_dir, filter, single_dst_dir)
	if not os.isdir(src_dir) then error(src_dir .. " is not an existing directory!") end
	filter = filter or "**"
	src_dir = src_dir .. "/"
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
		return true
	else
		printf( "Error: " .. counter .. "/" .. #matches .. " files copied.")
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

	end
end

function cloud.win.copyDLL2( folderName ,fileName)
	--
	if _OPTIONS["soPath"] then
		pa = os.pathsearch(fileName, disc .. ":/Program Files (x86)/" .. folderName .. "/lib", disc .. ":/Program Files/" .. folderName .. "/lib", string.explode( _OPTIONS["soPath"] , ";") )  .. "/".. fileName
		if pa then
			cloud.copyFileIntoBuild(pa, fileName)
		end
	else
		pa = os.pathsearch(fileName,  fileName, disc .. ":/Program Files (x86)/" .. folderName .. "/lib", disc .. ":/Program Files/" .. folderName .. "/lib") .. "/".. fileName
		if pa then
			cloud.copyFileIntoBuild(pa, fileName)
		end
	end
	if pa then

	end
end

cloud.project = {}

function cloud.project.clean()
if os.isdir( "projects" ) then
	os.rmdir("projects/**")
	os.rmdir("projects")

end
end
function cloud.project.init()
	--
 	cloud.project.clean()
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



function cloud.project.useTBB()
	--
	cloud.addIncludeDir(  _OPTIONS["TBBIncludesPath"] )
	cloud.addLibDir(  _OPTIONS["TBBLibsPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
		cloud.win.addLibFromProgrammFiles("TBB-3.0")		
	end
	if os.get() == "linux" then
		defines { "LIN" }
	end
	if os.get() == "macosx" then
		defines { "MAC" }
	end 
end

function cloud.project.useASL()
	--
	defines { "_SCL_SECURE_NO_DEPRECATE", "_CRT_SECURE_NO_DEPRECATE", "BOOST_FILESYSTEM_VERSION=2", "ADOBE_SERIALIZATION", "ADOBE_STD_SERIALIZATION" }
	cloud.addIncludeDir(  _OPTIONS["ASLIncludesPath"] )
	cloud.addLibDir(  _OPTIONS["ASLLibsPath"] )
	cloud.project.useTBB()
	if os.get() == "windows" then
		defines { "WIN" }
		cloud.win.addLibFromProgrammFiles("ASL-1.0.43")		
			links {
			"comctl32"
			}
		configuration "Debug"
			links {
			"libasl_dev_debug",
			"libadobe_widgets_debug"
			}
		configuration "Release"
			links {
			"libasl_dev_release",
			"libadobe_widgets_release"
			}
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		configuration "Debug"
			links {
			"asl_dev_debug",
			"adobe_widgets_debug"
			}
		configuration "Release"
			links {
			"asl_dev_release",
			"adobe_widgets_release"
			}
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		configuration "Debug"
			links {
			"asl_dev_debug",
			"adobe_widgets_debug"
			}
		configuration "Release"
			links {
			"asl_dev_release",
			"adobe_widgets_release"
			}
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

cloud.project.AdobeSourceLibrariesTutorial = {}

function cloud.project.AdobeSourceLibrariesTutorial.copyAassets()
	cwd = os.getcwd()
 	printf("copying assets. " .. cwd .. "/assets/" )	
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/assets" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/assets")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release/assets" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release/assets")
	end
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action .. "/bin/debug/assets") 
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action .. "/bin/release/assets") 
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action .. "/assets") 

	
end

solution "AdobeSourceLibrariesTutorial"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	configuration { "Debug" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
	
	configuration { "Release" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
	
	-- A project defines one build target
	project "AdamAndEve"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		files {"src/AdamAndEve.cpp" }
		cloud.project.init()
		cloud.project.useBoost()
		cloud.project.useASL()
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		configuration { "linux", "gmake" }
		 buildoptions { "`pkg-config --cflags --libs gtk+-2.0`"}
		 
		 	project "Alert"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		files {"src/Alert.cpp" }
		cloud.project.init()
		cloud.project.useBoost()
		cloud.project.useASL()
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
		
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			
		configuration { "linux", "gmake" }
		 buildoptions { "`pkg-config --cflags --libs gtk+-2.0`"}
