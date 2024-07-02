--- Solving Issue From: https://blog.csdn.net/m0_74242407/article/details/136439366 ---

project "GLFW"
	kind "StaticLib"
	language "C"
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
		"src/include/GLFW/glfw3.h",
		"src/include/GLFW/glfw3native.h",
		"src/src/glfw_config.h",
		"src/src/internal.h",
        "src/src/platform.h",
        "src/src/mappings.h",
		"src/src/context.c",
		"src/src/init.c",
		"src/src/input.c",
		"src/src/monitor.c",
		"src/src/platform.c",
		"src/src/vulkan.c",
		"src/src/window.c",
		"src/src/egl_context.c",
        "src/src/osmesa_context.c",
        "src/src/null_platform.h",
        "src/src/null_joystick.h",
        "src/src/null_init.c",
		"src/src/null_monitor.c",
        "src/src/null_window.c",
        "src/src/null_joystick.c",
	}

	-----------PLATFORMS-----------
	filter "system:windows"
		systemversion "latest"

		files
		{
			"src/src/win32_init.c",
			"src/src/win32_module.c",
			"src/src/win32_joystick.c",
			"src/src/win32_monitor.c",
			"src/src/win32_time.h",
			"src/src/win32_time.c",
			"src/src/win32_thread.h",
			"src/src/win32_thread.c",
			"src/src/win32_window.c",
			"src/src/wgl_context.c",
			"src/src/egl_context.c",
			"src/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	-----------CONFIGURATIONS-----------
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"