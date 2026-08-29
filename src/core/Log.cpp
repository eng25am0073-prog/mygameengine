#include "core/Log.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace engine {

namespace {

LogLevel g_level = LogLevel::Debug;

#ifdef _WIN32
WORD GetConsoleColor(LogLevel level)
{
    switch (level) {
    case LogLevel::Debug: return FOREGROUND_INTENSITY;
    case LogLevel::Info:  return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    case LogLevel::Warn:  return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    case LogLevel::Error: return FOREGROUND_RED | FOREGROUND_INTENSITY;
    }
    return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
}
#endif

std::string GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch())
                        % 1000;

    std::tm localTime = {};
#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream stream;
    stream << std::put_time(&localTime, "%H:%M:%S")
           << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    return stream.str();
}

std::string LevelToString(LogLevel level)
{
    switch (level) {
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Info:  return "INFO ";
    case LogLevel::Warn:  return "WARN ";
    case LogLevel::Error: return "ERROR";
    }
    return "INFO ";
}

void Write(LogLevel level, const std::string& message)
{
    if (level < g_level) {
        return;
    }

#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalInfo = {};
    GetConsoleScreenBufferInfo(consoleHandle, &originalInfo);
    SetConsoleTextAttribute(consoleHandle, GetConsoleColor(level));
#endif

    std::cout << "[" << GetTimestamp() << "] [" << LevelToString(level) << "] " << message << std::endl;

#ifdef _WIN32
    SetConsoleTextAttribute(consoleHandle, originalInfo.wAttributes);
#endif
}

} // namespace

void Log::SetLevel(LogLevel level)
{
    g_level = level;
}

void Log::Debug(const std::string& message)
{
    Write(LogLevel::Debug, message);
}

void Log::Info(const std::string& message)
{
    Write(LogLevel::Info, message);
}

void Log::Warn(const std::string& message)
{
    Write(LogLevel::Warn, message);
}

void Log::Error(const std::string& message)
{
    Write(LogLevel::Error, message);
}

} // namespace engine