project "IMGUI"
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
		"src/imconfig.h",
		"src/imgui.cpp",
		"src/imgui.h",
		"src/imgui_demo.cpp",
		"src/imgui_draw.cpp",
		"src/imgui_internal.h",
		"src/imgui_tables.cpp",
		"src/imgui_widgets.cpp",
		"src/imstb_rectpack.h",
		"src/imstb_textedit.h",
		"src/imstb_truetype.h",
		"src/backends/imgui_impl_opengl3.cpp",
        "src/backends/imgui_impl_glfw.cpp"
	}

	-----------DEPENDENCIES-----------
	includedirs
	{
		"%{IncludeDirs.glfw}"
	}

	-----------CONFIGURATIONS-----------
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"