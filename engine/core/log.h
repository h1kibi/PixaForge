#pragma once

#include <string_view>
#include <format>
#include <iostream>

namespace pixel {

enum class LogLevel {
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

namespace log {

void set_level(LogLevel level);
LogLevel get_level();

void output(LogLevel level, const char* file, int line, std::string_view message);

} // namespace log
} // namespace pixel

// 日志宏
#define PE_LOG_DEBUG(...) \
    ::pixel::log::output(::pixel::LogLevel::Debug, __FILE__, __LINE__, \
        std::format(__VA_ARGS__))

#define PE_LOG_INFO(...) \
    ::pixel::log::output(::pixel::LogLevel::Info, __FILE__, __LINE__, \
        std::format(__VA_ARGS__))

#define PE_LOG_WARN(...) \
    ::pixel::log::output(::pixel::LogLevel::Warn, __FILE__, __LINE__, \
        std::format(__VA_ARGS__))

#define PE_LOG_ERROR(...) \
    ::pixel::log::output(::pixel::LogLevel::Error, __FILE__, __LINE__, \
        std::format(__VA_ARGS__))

#define PE_LOG_FATAL(...) \
    ::pixel::log::output(::pixel::LogLevel::Fatal, __FILE__, __LINE__, \
        std::format(__VA_ARGS__))
