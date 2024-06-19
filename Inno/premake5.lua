project "Inno"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

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

	includedirs
	{
		"src",
		"%{IncludeDirs.spdlog}",
		"%{IncludeDirs.glfw}"
	}

	links
	{
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"INNO_PLATFORM_WINDOWS",
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