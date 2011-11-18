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
		if  _OPTIONS["OpenCV-Shared"] then
				links {
					"opencv_core230",
					"opencv_highgui230",
					"opencv_imgproc230"
				}
			
				cloud.win.copyDLL("OpenCV-2.3.0", "opencv_core230.dll")
				cloud.win.copyDLL("OpenCV-2.3.0", "opencv_highgui230.dll")
				cloud.win.copyDLL("OpenCV-2.3.0", "opencv_imgproc230.dll")
			else	
				configuration { }
				
				configuration { "Debug" }
					links {
						"opencv_core230d",
						"opencv_highgui230d",
						"opencv_imgproc230d",
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
						"opencv_core230",
						"opencv_highgui230",
						"opencv_imgproc230",
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
		cloud.win.addLibFromProgrammFiles("OpenCV-2.3.0")
	end
	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
			"opencv_imgproc",
			"opencv_core",
			"opencv_highgui"
		}
		if  _OPTIONS["OpenCV-Shared"] then else
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
		
		if  _OPTIONS["OpenCV-Shared"] then else
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
		cloud.win.addLibFromProgrammFiles("Boost")
	end	
	if os.get() == "linux" then
		defines { "LIN" }
		links {
		"boost_regex",
		"boost_system",
		"boost_thread",
		"boost_filesystem",
		"boost_program_options",
		"boost_date_time",
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
		"dl",
		"pthread"
		}	
	end 
end

function cloud.project.copyNimfa()
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release")
	end
	os.copyfile("assets/nimfa.mask" , "projects/" .. os.get() .. "-" .. action .. "/nimfa.mask" )
	os.copyfile("assets/nimfa.mask" , "projects/" .. os.get() .. "-" .. action .. "/bin/debug/nimfa.mask" )
	os.copyfile("assets/nimfa.mask" , "projects/" .. os.get() .. "-" .. action .. "/bin/release/nimfa.mask" )
end