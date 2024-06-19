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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Dependencies/glfw"
group ""

group "Core"
	include "Inno"
group ""

group "Misc"
	include "SandBox"
group ""