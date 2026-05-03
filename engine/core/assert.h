#pragma once

#include "log.h"
#include <cstdlib>

#ifdef _DEBUG
    #define PE_DEBUG_BUILD 1
#else
    #define PE_DEBUG_BUILD 0
#endif

// 断言宏
#define PE_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            PE_LOG_FATAL("Assertion failed: {} at {}:{}", #expr, __FILE__, __LINE__); \
            std::abort(); \
        } \
    } while (0)

#define PE_ASSERT_MSG(expr, ...) \
    do { \
        if (!(expr)) { \
            PE_LOG_FATAL("Assertion failed: {} - {} at {}:{}", \
                #expr, std::format(__VA_ARGS__), __FILE__, __LINE__); \
            std::abort(); \
        } \
    } while (0)

// 仅在 Debug 模式下生效的断言
#if PE_DEBUG_BUILD
    #define PE_DASSERT(expr) PE_ASSERT(expr)
    #define PE_DASSERT_MSG(expr, ...) PE_ASSERT_MSG(expr, __VA_ARGS__)
#else
    #define PE_DASSERT(expr) ((void)0)
    #define PE_DASSERT_MSG(expr, ...) ((void)0)
#endif

// 不可达标记
#define PE_UNREACHABLE() \
    do { \
        PE_LOG_FATAL("Unreachable code reached at {}:{}", __FILE__, __LINE__); \
        std::abort(); \
    } while (0)

// 未实现标记
#define PE_NOT_IMPLEMENTED() \
    do { \
        PE_LOG_FATAL("Not implemented at {}:{}", __FILE__, __LINE__); \
        std::abort(); \
    } while (0)
