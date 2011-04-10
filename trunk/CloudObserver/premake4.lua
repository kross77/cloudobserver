-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

local action = _ACTION or ""

if action == "clean" then
	os.rmdir("projects/**")
	os.rmdir("projects")
end

solution "CloudServer"
	location ( "projects/".. os.get() .. "-" ..  action )
	configurations { "Debug", "Release" }
	objdir     ( "projects/" .. os.get() .. "-" .. action .. "/bin/obj" )
	
	configuration { "Debug" }
		targetdir ( "projects/" .. os.get() .. "-" .. action .. "/bin/debug" )
	
	configuration { "Release" }
		targetdir ( "projects/" .. os.get() .. "-" .. action ..  "/bin/release" )
		
project "CloudServer"
  language  "C#"
  location ( "projects/" .. os.get() .. "-" .. action )
  kind      "ConsoleApp"
  defines   { "TRACE" }
  files     { "./CloudObserver/**.cs" }
  links     { "System", "System.Configuration.Install", "System.ServiceProcess", "System.Web" }
 
  configuration { "Debug*" }
    defines { "DEBUG" }
    flags   { "Symbols" }
 
  configuration { "Release*" }
    flags   { "Optimize" }