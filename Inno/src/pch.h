#pragma once

// ---------------PreCompiled--------------- //
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <chrono>
#include <filesystem>
#include <iomanip>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Inno/Core/Core.h"
#include "Inno/Core/Log.h"

// ---------------Platform Relevant--------------- //
#ifdef INNO_PLATFORM_WINDOWS
	#include <Windows.h>
#elif INNO_PLATFORM_MACOSX
	#include <unistd.h>
#endif
