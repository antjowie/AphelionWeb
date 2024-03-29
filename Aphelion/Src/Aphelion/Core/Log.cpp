#include "Aphelion/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ap
{
std::shared_ptr<spdlog::logger> Log::coreLogger;
std::shared_ptr<spdlog::logger> Log::clientLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n (%s:%#): %v%$");
    spdlog::set_level(spdlog::level::trace);

    coreLogger = spdlog::stdout_color_mt("CORE");
    coreLogger->set_level(spdlog::level::trace);

    clientLogger = spdlog::stdout_color_mt("APP");
    clientLogger->set_level(spdlog::level::trace);
}
std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
{
    return coreLogger;
}
std::shared_ptr<spdlog::logger>& Log::GetClientLogger()
{
    return clientLogger;
}
} // namespace ap
