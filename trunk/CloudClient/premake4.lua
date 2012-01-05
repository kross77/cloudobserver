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
	description = "Choose a particular directory for Boost libs search"
}

newoption {
	trigger     = "FFmpegLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for FFMpeg libs search"
}

newoption {
	trigger     = "OpenALLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenAL libs search"
}

newoption {
	trigger     = "OpenCVLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenCV libs search"
}

newoption {
	trigger     = "TclLibsPath",
	value       = "PATH",
	description = "Choose a particular directory for Tcl libs search"
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
	trigger     = "FFmpegIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for FFMpeg includes search"
}

newoption {
	trigger     = "OpenALIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenAL includes search"
}


newoption {
	trigger     = "OpenCVIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for OpenCV includes search"
}

newoption {
	trigger     = "TclIncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for Tcl includes search"
}

newoption {
	trigger     = "c99IncludesPath",
	value       = "PATH",
	description = "Choose a particular directory for C99 includes search if it is not defined on your system by defauft. WINDOWS-MSVC-SPECIFIC-REQUIRED-FOR-FFMPEG-OPTION! because on 2011.03.** msvc++ does not support C99 and FFmpeg release requires C99 there are errors compiling in VS environment. Choose a particular directory for C99 includes search. Problem described here: http://ffmpeg.arrozcru.org/wiki/index.php?title=Inttypes.h . Currently required files could be found here http://code.google.com/p/msinttypes/downloads/list ."
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
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug-shared" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug-shared")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug-static" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug-static")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/release-shared" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release-shared")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/release-static" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release-static")
	end
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/debug-shared/" .. fileName  )
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/debug-static/" .. fileName  )
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/release-shared/" .. fileName )
	os.copyfile(filePath , "projects/" .. os.get() .. "-" .. action .. "/bin/release-static/" .. fileName )
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

function cloud.project.useCV()
	--
	cloud.addLibDir( _OPTIONS["OpenCVLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["OpenCVIncludesPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
		configuration { "DebugShared or ReleaseShared" }
			links {
				"opencv_core231",
				"opencv_highgui231",
				"opencv_imgproc231"
			}
			
			if  _OPTIONS["CopySharedLibraries"] then
				cloud.win.copyDLL("OpenCV", "opencv_core231.dll")
				cloud.win.copyDLL("OpenCV", "opencv_highgui231.dll")
				cloud.win.copyDLL("OpenCV", "opencv_imgproc231.dll")
			end
		configuration { }
		
		configuration { "DebugStatic" }
			links {
				"opencv_core231d",
				"opencv_highgui231d",
				"opencv_imgproc231d",
				"libjasperd",
				"libjpegd",
				"libpngd",
				"libtiffd",
				"zlibd",
				"vfw32",
				"comctl32"
			}
		configuration { }
		
		configuration { "ReleaseStatic" }
			links {
				"opencv_core231",
				"opencv_highgui231",
				"opencv_imgproc231",
				"libjasper",
				"libjpeg",
				"libpng",
				"libtiff",
				"zlib",
				"vfw32",
				"comctl32"
			}
		configuration { }
		
		cloud.win.addLibFromProgrammFiles("OpenCV")
		cloud.win.addLibDirFromProgrammFiles("OpenCV/share/OpenCV/3rdparty/lib")
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
			"opencv_imgproc",
			"opencv_core",
			"opencv_highgui"
		}
		
		configuration { "DebugStatic or ReleaseStatic" }
			links {
				"libjasper",
				"libjpeg",
				"libpng",
				"libtiff",
				"zlib"
			}
		configuration { }
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
			"opencv_imgproc",
			"opencv_core",
			"opencv_highgui",
			"QuickTime.framework"
		}
		
		configuration { "DebugStatic or ReleaseStatic" }
			links {
				"libjasper",
				"libjpeg",
				"libpng",
				"libtiff",
				"zlib",
				"AppKit.framework",
				"CoreVideo.framework",
				"QTKit.framework",
			}
		configuration { }
	end 
end

function cloud.project.useAL()
	--
	cloud.addIncludeDir(  _OPTIONS["OpenALIncludesPath"] )
	cloud.addLibDir(  _OPTIONS["OpenALLibsPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
		
		configuration { "not DebugStatic" }
			links { "OpenAL32" }
		configuration { }
		
		configuration { "DebugStatic" }
			links { "OpenAL32d" }
		configuration { }
		
		configuration { "DebugStatic or ReleaseStatic" }
			defines { "AL_LIBTYPE_STATIC" }
			links { "winmm" }
		configuration { }
		
		configuration { "DebugShared or ReleaseShared" }
			if  _OPTIONS["CopySharedLibraries"] then
				cloud.win.copyDLL("OpenAL Soft", "OpenAL32.dll")
			end
		configuration { }
		
		cloud.win.addLibFromProgrammFiles("OpenAL Soft")
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links { "openal" }
		
		configuration { "DebugStatic or ReleaseStatic" }
			links {
				"dl",
				"pthread",
				"rt"
			}
		configuration { }
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links { "OpenAL.framework" }
	end 
end
	
function cloud.project.useBoost()
	--
	cloud.addIncludeDir( _OPTIONS["BoostIncludesPath"] )
	cloud.addLibDir( _OPTIONS["BoostLibsPath"])
	if os.get() == "windows" then
		defines { "WIN" }
		cloud.win.addIncludeDirFromProgrammFiles("Boost/include/boost-1_48")
		cloud.win.addLibDirFromProgrammFiles("Boost/lib")
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

function cloud.project.useFFmpeg()
	--
	cloud.addLibDir(  _OPTIONS["FFmpegLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["FFmpegIncludesPath"] )
	cloud.addIncludeDir( _OPTIONS["c99IncludesPath"] 	) 
	if os.get() == "windows" then
		defines { "WIN" }
		
		configuration { "DebugStatic or ReleaseStatic" }
			links {
				"libavformat",
				"libavcodec",
				"libavutil",
				"libswscale",
				"libgcc",
				"libmingwex"
			}
			
			cloud.win.addLibFromProgrammFiles2("FFmpeg", "lib")
		configuration { }
		
		configuration { "DebugShared or ReleaseShared" }
			links {
				"avformat",
				"avcodec",
				"avutil",
				"swscale"
			}
			
			cloud.win.addLibFromProgrammFiles2("FFmpeg", "bin")
			
			if  _OPTIONS["CopySharedLibraries"] then
				cloud.win.copyDLL("FFmpeg", "avformat-53.dll")
				cloud.win.copyDLL("FFmpeg", "avcodec-53.dll")
				cloud.win.copyDLL("FFmpeg", "avutil-51.dll")
				cloud.win.copyDLL("FFmpeg", "swscale-2.dll")
			end
		configuration { }
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
			"avdevice",
			"avformat",
			"avcodec",
			"avutil",
			"swscale"
		}
		
		configuration { "DebugStatic or ReleaseStatic" }
			links { "bz2" }
		configuration { }
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
			"avdevice",
			"avformat",
			"avcodec",
			"avutil",
			"swscale"
		}
		
		configuration { "DebugStatic or ReleaseStatic" }
			links { "bz2" }
		configuration { }
	end 	
end

function cloud.project.useTcl()
	--
	cloud.addLibDir( _OPTIONS["TclLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["TclIncludesPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
		links {
		"tcl85",
		"tk85"
		}
		cloud.win.addLibFromProgrammFiles("Tcl")
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"tcl8.5",
		"tk8.5"
		}	
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
		"tcl8.5",
		"tk8.5"
		}	 
	end
end

solution "CloudClient"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "DebugShared", "DebugStatic", "ReleaseShared", "ReleaseStatic" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	flags { "StaticRuntime" }
	
	configuration { "DebugShared" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug-shared" )
	configuration { }
	
	configuration { "DebugStatic" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug-static" )
	configuration { }
	
	configuration { "ReleaseShared" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release-shared" )
	configuration { }
	
	configuration { "ReleaseStatic" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release-static" )
	configuration { }
	
	configuration { "DebugShared or DebugStatic" }
		defines { "DEBUG" }
		flags { "Symbols" }
	configuration { }
	
	configuration { "ReleaseShared or ReleaseStatic" }
		defines { "NDEBUG" }
		flags { "Optimize" }
	configuration { }
	
	configuration { "windows", "vs*" }
		defines { "_WIN32_WINNT=0x0501", "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS" }
	configuration { }
	
	configuration { "windows", "vs*", "DebugStatic" }
		linkoptions { "/IGNORE:4049", "/IGNORE:4217" }
	configuration { }
	
	configuration { "windows", "vs*", "ReleaseStatic" }
		linkoptions { "/OPT:NOREF", "/IGNORE:4049" }
	configuration { }
	
	configuration { "linux", "gmake", "DebugStatic or ReleaseStatic" }
		linkoptions { "-static" }
	configuration { }
	
	-- A project defines one build target
	
	project "CloudClient"
		kind "ConsoleApp"
		language "C++"
		location ( "projects/" .. os.get() .. "-" .. action )
		cloud.project.init()
		cloud.project.useFFmpeg()
		cloud.project.useBoost()
		cloud.project.useAL()
		cloud.project.useCV()
		--cloud.project.useTcl()
		
		includedirs { "src/3rdparty/ffmpeg"}
		
		files { "src/**.h", "src/**.cpp" }
		excludes { "src/3rdparty/cpptcl/**", "src/3rdparty/cpptk/**" }
