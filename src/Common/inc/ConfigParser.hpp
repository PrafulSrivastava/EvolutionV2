#ifndef CONFIG_PARSER
#define CONFIG_PARSER

#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>
#include "IConfig.hpp"

namespace Evolution::Utility
{
    class ConfigParser
    {
    public:
        static ConfigParser &GetInstance();
        bool LoadConfig();

        [[nodiscard]] Resolution GetVersion();
        [[nodiscard]] LogLevel LoggingLevel();
        [[nodiscard]] std::string LoggingType();
        [[nodiscard]] std::string LogFilePath();

    private:
        ConfigParser() = default;
        ~ConfigParser() = default;

        nlohmann::json m_jsonData;
    };
} // namespace Utility

#endif