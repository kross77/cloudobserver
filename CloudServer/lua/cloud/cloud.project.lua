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
		cloud.win.addLibFromProgrammFiles("Boost-1.47.0")
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

function cloud.project.useopenSSL()
	cloud.addLibDir(  _OPTIONS["OpenSSLLibsPath"] )
	cloud.addIncludeDir(  _OPTIONS["OpenSSLIncludesPath"] )
		
	if os.get() == "windows" then
		defines { "WIN" }
		links {
		"libeay32"
		}
		cloud.win.addLibFromProgrammFiles("OpenSSL-1.0.0d")
		if  _OPTIONS["CopySharedLibraries"] then
			cloud.win.copyDLL("OpenSSL-1.0.0d/lib", "libeay32.dll")
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
