outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Dependencies/dependencies.lua"

workspace "Inno"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	-----------PLATFORMS-----------
	filter "system:windows"
		systemversion "latest"
		architecture "x64"

	filter "system:macosx"
		architecture "arm64"

		xcodebuildsettings 
		{
            ["HEADER_SEARCH_PATHS"] = 
			{
				"$(inherited)",
				"$(USER_HEADER_SEARCH_PATHS)"
			}
        }

	-----------PROJECT GROUPS-----------
	group "Dependencies"
		for _, lua in pairs(IncludeLuas) do
			include(lua)
		end

	group ""

	group "Core"
		include "Inno"
	group ""

	group "Misc"
		include "SandBox"
	group ""