----------------------------Inno All Dependencies----------------------------
IncludeLuas = {}
IncludeDirs = {}
IncludeProjs = {}

IncludeLuas["glfw"] = "Dependencies/glfw"
IncludeLuas["glad"] = "Dependencies/glad"
IncludeLuas["imgui"] = "Dependencies/imgui"
IncludeLuas["stb_image"] = "Dependencies/stb_image"

IncludeDirs["spdlog"] = "%{wks.location}/Dependencies/spdlog/src/include"
IncludeDirs["glfw"] = "%{wks.location}/Dependencies/glfw/src/include"
IncludeDirs["glad"] = "%{wks.location}/Dependencies/glad/src/include"
IncludeDirs["glm"] = "%{wks.location}/Dependencies/glm/src"
IncludeDirs["imgui"] = "%{wks.location}/Dependencies/imgui/src"
IncludeDirs["stb_image"] = "%{wks.location}/Dependencies/stb_image/src"

IncludeProjs["glfw"] = "GLFW"
IncludeProjs["glad"] = "GLAD"
IncludeProjs["imgui"] = "IMGUI"
IncludeProjs["stb_image"] = "STB_IMAGE"

----------------------------Inno All Libraries----------------------------
Libraries = {}

Libraries["openGL"] = "opengl32.lib"
