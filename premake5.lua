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
	include "Dependencies/glfw"
group ""

group "Core"
	include "Inno"
group ""

group "Misc"
	include "SandBox"
group ""