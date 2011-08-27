action = _ACTION or ""

function inject (filename)
  local f = assert(loadfile(filename))
  return f()
end

-- A solution contains projects, and defines the available configurations
-- Action name is defined by os

inject  ("lua/cloud/cloud.options.lua")
inject  ("lua/cloud/cloud.system.lua")
inject  ("lua/cloud/cloud.project.lua")

solution "ConcurrentMaps"
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
	inject ("lua/project.concurrent_maps.lua")
------------------------------------------------------------------------------------------------


