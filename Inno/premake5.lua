project "Inno"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	-----------INCLUDE DIRECTORIES-----------
	includedirs 
	{ 
		"src" 
	}

	-----------COMPILE FILES-----------
	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	-----------DEPENDENCIES-----------
	for _, dir in pairs(IncludeDirs) do
		includedirs { dir }
	end

	-----------LIBRARIES-----------
	for _, dir in pairs(Libraries) do
		links { dir }
	end

	-----------PROJECTS LINKS-----------
	for _, proj in pairs(IncludeProjs) do
		links { proj }
	end

	-----------PLATFORMS-----------
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"INNO_PLATFORM_WINDOWS",
		}

	filter "system:linux"
		defines
		{
			"INNO_PLATFORM_LINUX",
		}
	
	filter "system:macosx"
		defines
		{
			"INNO_PLATFORM_MACOS",
		}
	
	-----------CONFIGURATIONS-----------
	filter "configurations:Debug"
		defines "INNO_DEBUG"
		symbols "on"

		defines
		{
			"INNO_DEBUG"
		}

	filter "configurations:Release"
		defines "INNO_RELEASE"
		optimize "on"

		defines
		{
			"INNO_RELEASE"
		}

	filter "configurations:Dist"
		defines "INNO_DIST"
		optimize "on"

		defines
		{
			"INNO_DIST"
		}