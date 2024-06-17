#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Inno
{
	class INNO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// ---------------Core Logs Macros--------------- //
#define INNO_CORE_LOGTRACE(...) ::Inno::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define INNO_CORE_LOGINFO(...) ::Inno::Log::GetCoreLogger()->info(__VA_ARGS__)
#define INNO_CORE_LOGWARN(...) ::Inno::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define INNO_CORE_LOGERROR(...) ::Inno::Log::GetCoreLogger()->error(__VA_ARGS__)
#define INNO_CORE_LOGFATAL(...) ::Inno::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// ---------------Client Logs Macros--------------- //
#define INNO_LOGTRACE(...) ::Inno::Log::GetClientLogger()->trace(__VA_ARGS__)
#define INNO_LOGINFO(...) ::Inno::Log::GetClientLogger()->info(__VA_ARGS__)
#define INNO_LOGWARN(...) ::Inno::Log::GetClientLogger()->warn(__VA_ARGS__)
#define INNO_LOGERROR(...) ::Inno::Log::GetClientLogger()->error(__VA_ARGS__)
#define INNO_LOGFATAL(...) ::Inno::Log::GetClientLogger()->fatal(__VA_ARGS__)


