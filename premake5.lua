workspace "Inno"
	architecture "x64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Inno"
	location "Inno"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"Inno/dependencies/spdlog/include"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"INNO_PLATFORM_WINDOWS",
			"INNO_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}
		
	filter "configurations:Debug"
		defines "INNO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "INNO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "INNO_DIST"
		optimize "on"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"Inno/dependencies/spdlog/include",
		"Inno/src"
	}

	links
	{
		"Inno"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"INNO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "INNO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "INNO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "INNO_DIST"
		optimize "on"