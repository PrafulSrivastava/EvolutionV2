#include "Logger.hpp"

namespace Evolution::Utility
{
    LogLevel Logger::m_logLevel = LogLevel::DISABLE;
    std::ostream *Logger::os = nullptr;

    std::string Logger::GetEnumName(LogLevel enumVal)
    {
        std::string name{};
        switch (enumVal)
        {
        case LogLevel::FATAL:
            name = "FATAL";
            break;
        case LogLevel::WARN:
            name = "WARN";
            break;
        case LogLevel::ERROR:
            name = "ERROR";
            break;
        case LogLevel::INFO:
            name = "INFO";
            break;
        case LogLevel::DEBUG:
            name = "DEBUG";
            break;
        case LogLevel::VERBOSE:
            name = "VERBOSE";
            break;
        }
        return name;
    }
}