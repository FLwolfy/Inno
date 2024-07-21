project "Inno"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
		pchheader "pch.h"
		pchsource "src/pch.cpp"

	filter "system:macosx"
		pchheader "src/pch.h"

	
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