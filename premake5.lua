outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Dependencies/dependencies.lua"

workspace "Inno"
	architecture "x64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

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