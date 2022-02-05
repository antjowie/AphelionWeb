#pragma once
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include "Core.h"

// Ignore the warning about shared pointer needing a dll interface
// #ifdef _MSC_VER
// #pragma warning(push)
// #pragma warning(disable : 4251)
// #endif

namespace ap
{
class Log
{
  public:
    APHELION_API static void Init();

    APHELION_API static std::shared_ptr<spdlog::logger> &GetCoreLogger();
    APHELION_API static std::shared_ptr<spdlog::logger> &GetClientLogger();

  private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;
};
} // namespace ap

// Core log macros
#define AP_CORE_TRACE(...) ::ap::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AP_CORE_INFO(...) ::ap::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AP_CORE_WARN(...) ::ap::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AP_CORE_ERROR(...) ::ap::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AP_CORE_CRITICAL(...) ::ap::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define AP_TRACE(...) ::ap::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AP_INFO(...) ::ap::Log::GetClientLogger()->info(__VA_ARGS__)
#define AP_WARN(...) ::ap::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AP_ERROR(...) ::ap::Log::GetClientLogger()->error(__VA_ARGS__)
#define AP_CRITICAL(...) ::ap::Log::GetClientLogger()->critical(__VA_ARGS__)

//#ifdef _MSC_VER
//#pragma warning(pop)
//#endif
