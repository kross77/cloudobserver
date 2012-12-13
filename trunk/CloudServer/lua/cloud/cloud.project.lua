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
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_imgproc.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_core.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_highgui.a"
			}
			linkoptions {
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibjasper.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibjpeg.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibpng.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibtiff.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libzlib.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"opencv_imgproc",
				"opencv_core",
				"opencv_highgui"
			}
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
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_imgproc.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_core.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libopencv_highgui.a"
			}
			linkoptions {
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibjasper.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibjpeg.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibpng.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/liblibtiff.a",
				path.getabsolute(_OPTIONS["OpenCVLibsPath"]) .. "/libzlib.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"opencv_imgproc",
				"opencv_core",
				"opencv_highgui"
			}
			links {
				"libjasper",
				"libjpeg",
				"libpng",
				"libtiff",
				"zlib"
			}
		configuration { }
		
		links {
			"QuickTime.framework",
			"AppKit.framework",
			"CoreVideo.framework",
			"QTKit.framework"
		}
	end 
end



function cloud.project.useBoost()
	--
	cloud.addIncludeDir( _OPTIONS["BoostIncludesPath"] )
	cloud.addLibDir( _OPTIONS["BoostLibsPath"])
		includedirs {"3rdparty/header-only"}
		--defines{ "BOOST_ASIO_DISABLE_IOCP" }
	if os.get() == "windows" then
		defines { "WIN" } 
		cloud.win.addIncludeDirFromProgrammFiles("Boost/include/boost-1_48")
		cloud.win.addLibDirFromProgrammFiles("Boost/lib")
	end	
	if os.get() == "linux" then
		defines { "LIN" }
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_regex.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_system.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_thread.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_chrono.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_date_time.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_filesystem.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_program_options.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_iostreams.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_serialization.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_zlib.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"boost_regex",
				"boost_system",
				"boost_thread",
				"boost_chrono",
				"boost_date_time",
				"boost_filesystem",
				"boost_program_options",
				"boost_iostreams",
				"boost_serialization",
				"boost_zlib"
			}
		configuration { }
		
		links {
			"dl",
			"pthread"
		}
	end
	if os.get() == "macosx" then
		defines { "MAC" }
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_regex.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_system.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_thread.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_chrono.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_date_time.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_filesystem.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_program_options.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_iostreams.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_serialization.a",
				path.getabsolute(_OPTIONS["BoostLibsPath"]) .. "/libboost_zlib.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"boost_regex",
				"boost_system",
				"boost_thread",
				"boost_chrono",
				"boost_date_time",
				"boost_filesystem",
				"boost_program_options",
				"boost_iostreams",
				"boost_serialization",
				"boost_zlib"
			}
		configuration { }
		
		links {
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
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["OpenSSLLibsPath"]) .. "/libcrypto.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"crypto"
			}
		configuration { }
	end
	
	if os.get() == "macosx" then
		defines { "MAC" }
		configuration { "gmake" }
			linkoptions {
				path.getabsolute(_OPTIONS["OpenSSLLibsPath"]) .. "/libcrypto.a"
			}
		configuration { }
		
		configuration { "not gmake" }
			links {
				"crypto"
			}
		configuration { }
	end 
	
end

function cloud.project.copyAssets()
	if not os.isdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/htdocs" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/debug/htdocs")
	end
	if not os.isdir("projects/" .. os.get() .. "-" .. action .."/bin/release/htdocs" ) then
		os.mkdir("projects/" .. os.get() .. "-" .. action .. "/bin/release/htdocs")
	end
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action .. "/bin/debug")
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action .. "/bin/release")
	os.copydir("assets",  "projects/" .. os.get() .. "-" .. action)
end
