----------------------------Inno All Dependencies----------------------------
IncludeDirs = {}

IncludeDirs["spdlog"] = "%{wks.location}/Dependencies/spdlog/src/include"
IncludeDirs["glfw"] = "%{wks.location}/Dependencies/glfw/src/include"

----------------------------Inno All Libraries----------------------------
Libraries = {}

Libraries["openGL"] = "opengl32.lib"
