#pragma once

/**
 * Platform detection
 */
#ifdef _WIN64
    /* Windows x64  */
    #define AP_PLATFORM_WINDOWS
#elif defined(_WIN32)
    /* Windows x86 */
    #error "x86 Builds are not supported!"
#elif defined(__APPLE__) || defined(__MACH__)
    #error "Others platforms are not yet supported"
#elif defined(__EMSCRIPTEN__)
    #define AP_PLATFORM_WEB
#endif // End of platform detection

/**
 * Set up the DLL
 */
#ifdef AP_DYNAMIC_LINK
    #ifdef AP_BUILD_DLL
        #define APHELION_API __declspec(dllexport)
    #else
        #define APHELION_API __declspec(dllimport)
    #endif
#else
    #define APHELION_API
#endif

/**
 * Set up the asserts
 *
 * It is not crossplatform yet because I don't think __debugbreak() is standard
 * Verify is used if you still want to execute the arguments in release but not 
 * stop execution of the project if failed
 */
#if defined(AP_DEBUG) || defined(FORCE_ASSERT)
    #define AP_ASSERT(x, msg) { if(!(x)) { AP_ERROR("Assertion Failed: {0}", msg); ap::Log::GetClientLogger()->flush(); __debugbreak(); } }
    #define AP_CORE_ASSERT(x, msg) { if(!(x)) { AP_CORE_ERROR("Assertion Failed: {0}", msg); ap::Log::GetCoreLogger()->flush(); __debugbreak(); } }
    #define AP_VERIFY(x, msg) { AP_ASSERT(x,msg); }
    #define AP_CORE_VERIFY(x, msg) { AP_CORE_ASSERT(x,msg); } 
#else
    #define AP_ASSERT(x, msg)
    #define AP_CORE_ASSERT(x, msg)
    #define AP_VERIFY(x, msg) { x; }
    #define AP_CORE_VERIFY(x, msg) { x; } 
#endif