project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-----------INCLUDE DIRECTORIES-----------
	includedirs 
	{ 
		"src",
		"src/include"
	}

	-----------COMPILE FILES-----------
	files
	{
		"src/include/glad/glad.h",
		"src/include/KHR/khrplatform.h",
		"src/src/glad.c"
	}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"