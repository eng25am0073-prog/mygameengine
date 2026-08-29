#pragma once

#include <string>

namespace engine {

enum class LogLevel {
    Debug = 0,
    Info,
    Warn,
    Error
};

class Log {
public:
    static void SetLevel(LogLevel level);

    static void Debug(const std::string& message);
    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);
};

} // namespace engine