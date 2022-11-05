#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>

namespace Evolution::Utility
{
    enum LogLevel : uint8_t
    {
        DISABLE = 0,
        FATAL,
        WARN,
        ERROR,
        INFO,
        DEBUG,
        VERBOSE
    };

    using Stream = std::ostream *;

    class Logger
    {
    public:
        Logger() = delete;
        ~Logger() = delete;
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(Logger &&) = delete;

        template <typename T>
        static void init(LogLevel, T *file = nullptr);

        template <typename... Args>
        static void Logging(LogLevel, Args &&...);

    private:
        static std::ostream *os;
        static std::string GetEnumName(LogLevel);
        static LogLevel m_logLevel;
    };

    template <typename T>
    void Logger::init(LogLevel level, T *file)
    {
        m_logLevel = level;
        os = file == nullptr ? &std::cout : file;
    }

    template <typename... Args>
    void Logger::Logging(LogLevel level, Args &&...args)
    {
        if (m_logLevel >= level)
        {
            *os << "[" << GetEnumName(level) << "] ";
            ((*os << args << " "), ...);
            *os << "\n";
        }
    }

} // namespace Evolution::Utility

#endif