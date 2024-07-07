project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-----------COMPILE FILES-----------
	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
	}

	-----------DEPENDENCIES-----------
	includedirs{ "%{wks.location}/Inno/src" }
	for _, dir in pairs(IncludeDirs) do
		includedirs { dir }
	end

	-----------PROJECTS LINKS-----------
	links
	{
		"Inno"
	}

	-----------PLATFORMS-----------
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"INNO_PLATFORM_WINDOWS"
		}
	
	filter "system:macosx"
		defines
		{
			"INNO_PLATFORM_MACOSX",
		}

		links
		{
			"OpenGL.framework",
			"CoreFoundation.framework",
			"IOKit.framework",
			"Cocoa.framework",
			"QuartzCore.framework"
		}

	-----------CONFIGURATIONS-----------
	filter "configurations:Debug"
		defines "INNO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "INNO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "INNO_DIST"
		optimize "on"