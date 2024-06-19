project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/include/GLFW/glfw3.h",
		"src/include/GLFW/glfw3native.h",
		"src/src/glfw_config.h",
		"src/src/context.c",
		"src/src/init.c",
		"src/src/input.c",
		"src/src/monitor.c",
		"src/src/vulkan.c",
		"src/src/window.c"
	}

	filter "system:linux"
		pic "on"

		systemversion "latest"

		files
		{
			"src/src/x11_init.c",
			"src/src/x11_monitor.c",
			"src/src/x11_window.c",
			"src/src/xkb_unicode.c",
			"src/src/posix_time.c",
			"src/src/posix_thread.c",
			"src/src/glx_context.c",
			"src/src/egl_context.c",
			"src/src/osmesa_context.c",
			"src/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"src/src/win32_init.c",
			"src/src/win32_joystick.c",
			"src/src/win32_monitor.c",
			"src/src/win32_time.c",
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

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"