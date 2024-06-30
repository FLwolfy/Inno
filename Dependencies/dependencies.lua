----------------------------Inno All Dependencies----------------------------
IncludeLuas = {}
IncludeDirs = {}
IncludeProjs = {}

IncludeLuas["glfw"] = "Dependencies/glfw"
IncludeLuas["glad"] = "Dependencies/glad"
IncludeLuas["imgui"] = "Dependencies/imgui"

IncludeDirs["spdlog"] = "%{wks.location}/Dependencies/spdlog/src/include"
IncludeDirs["glfw"] = "%{wks.location}/Dependencies/glfw/src/include"
IncludeDirs["glad"] = "%{wks.location}/Dependencies/glad/src/include"
IncludeDirs["glm"] = "%{wks.location}/Dependencies/glm/src"
IncludeDirs["imgui"] = "%{wks.location}/Dependencies/imgui/src"

IncludeProjs["glfw"] = "GLFW"
IncludeProjs["glad"] = "GLAD"
IncludeProjs["imgui"] = "IMGUI"

----------------------------Inno All Libraries----------------------------
Libraries = {}

Libraries["openGL"] = "opengl32.lib"
