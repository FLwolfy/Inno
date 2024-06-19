include "dependencies.lua"

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

group "Core"
	include "Inno"
group ""

group "Dependencies"
	include "Inno/dependencies/glfw"
group ""

group "Misc"
	include "SandBox"
group ""