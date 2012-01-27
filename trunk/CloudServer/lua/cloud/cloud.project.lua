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

function cloud.project.useCV()
	--
	cloud.addLibDir( _OPTIONS["OpenCVLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["OpenCVIncludesPath"] )
	if os.get() == "windows" then
		defines { "WIN" }
		if  _OPTIONS["OpenCVshared"] then
				links {
					"opencv_core231",
					"opencv_highgui231",
					"opencv_imgproc231"
				}
			
				cloud.win.copyDLL("OpenCV", "opencv_core231.dll")
				cloud.win.copyDLL("OpenCV", "opencv_highgui231.dll")
				cloud.win.copyDLL("OpenCV", "opencv_imgproc231.dll")
			else	
				configuration { }
				
				configuration { "Debug" }
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
				
				configuration { "Release" }
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
			end
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
		if  _OPTIONS["OpenCVshared"] then else
			links {
				"libjasper",
				"libjpeg",
				"libpng",
				"libtiff",
				"zlib"
			}

		end
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
			"opencv_imgproc",
			"opencv_core",
			"opencv_highgui",
			"QuickTime.framework"
		}
		
		if  _OPTIONS["OpenCVshared"] then else
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
		end
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
		cloud.win.addIncludeDirFromProgrammFiles("Boost/include/boost-1_48")
		cloud.win.addLibDirFromProgrammFiles("Boost/lib")
	end	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread",
		"boost_date_time",
		"boost_filesystem",
		"boost_program_options",
		"boost_iostreams",
		"boost_serialization",
		"boost_zlib",
		"dl",
		"pthread"
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
		"boost_date_time",
		"boost_iostreams",
		"boost_serialization",
		"boost_zlib",
		"dl",
		"pthread"
		}	
	end 
end


function cloud.project.useMPI()
	--
	cloud.project.useBoost()
	defines { "MPI" }
	if os.get() == "windows" then
		links
		{
			"msmpi"
		}
		libdirs 
		{
		"C:/Program Files/Microsoft HPC Pack 2008 SDK/Lib/i386" -- there is also "C:/Program Files/Microsoft HPC Pack 2008 SDK/Lib/amd64"
		}
		
		includedirs 
		{
		"C:/Program Files/Microsoft HPC Pack 2008 SDK/Include"
		}
		
	end	
	if os.get() == "linux" then
		links {
		"boost_mpi",
		"boost_serialization"
		}
	end
	if os.get() == "macosx" then
		links {
		"boost_mpi",
		"boost_serialization"
		}	
	end 
end



function cloud.project.useopenSSL()
	cloud.addLibDir(  _OPTIONS["OpenSSLLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["OpenSSLIncludesPath"] )
		
	if os.get() == "windows" then
		defines { "WIN" }
		links {
		"libeay32"
		}
		cloud.win.addLibFromProgrammFiles("OpenSSL")
		if  _OPTIONS["CopySharedLibraries"] then
			cloud.win.copyDLL("OpenSSL/lib", "libeay32.dll")
		end
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"crypto"
		}
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		links {
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
