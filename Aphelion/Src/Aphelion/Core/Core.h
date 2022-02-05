#pragma once

/* Platform detection */
#ifdef _WIN64
#define AP_PLATFORM_WIN
#elif defined(_WIN32)
#error "x86 Builds are not supported"
#elif defined(__EMSCRIPTEN__)
#define AP_PLATFORM_WEB
#elif defined(__linux__)
#define AP_PLATFORM_UNIX
#else
#error "Unsupported platform"
#endif // End of platform detection

/**
 * Set up shared libs
 * @TODO Verify if app in runtime works on Linux systems
 */
#if defined(AP_DYNAMIC_LINK) && defined(AP_PLATFORM_WIN)
#ifdef AP_BUILD_DLL
#define APHELION_API __declspec(dllexport)
#else
#define APHELION_API __declspec(dllimport)
#endif
#else
#define APHELION_API
#endif

/* Set up the asserts and general debug macros */
#if defined(AP_DEBUG) || defined(AP_FORCE_ASSERT)

/* Set up platform specific debug break */
#ifdef AP_PLATFORM_WIN
#define AP_DEBUG_BREAK __debugbreak();
#else
#define AP_DEBUG_BREAK raise(SIGTRAP);
#endif

/* Setup asserts which will break debugger when condition is false */
#define AP_ASSERT(x, msg)                                                                                              \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            AP_ERROR("Assertion Failed: {0}", msg);                                                                    \
            ap::Log::GetClientLogger()->flush();                                                                       \
            AP_DEBUG_BREAK()                                                                                           \
        }                                                                                                              \
    }
#define AP_CORE_ASSERT(x, msg)                                                                                         \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            AP_CORE_ERROR("Assertion Failed: {0}", msg);                                                               \
            ap::Log::GetCoreLogger()->flush();                                                                         \
            AP_DEBUG_BREAK()                                                                                           \
        }                                                                                                              \
    }

/* Verify is like an assert, but will still execute the code when asserts are disabled */
#define AP_VERIFY(x, msg)                                                                                              \
    {                                                                                                                  \
        AP_ASSERT(x, msg);                                                                                             \
    }
#define AP_CORE_VERIFY(x, msg)                                                                                         \
    {                                                                                                                  \
        AP_CORE_ASSERT(x, msg);                                                                                        \
    }
#else
#define AP_ASSERT(x, msg)
#define AP_CORE_ASSERT(x, msg)
#define AP_VERIFY(x, msg)                                                                                              \
    {                                                                                                                  \
        x;                                                                                                             \
    }
#define AP_CORE_VERIFY(x, msg)                                                                                         \
    {                                                                                                                  \
        x;                                                                                                             \
    }
#endif
