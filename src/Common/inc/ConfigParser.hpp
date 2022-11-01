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

        [[nodiscard]] NFResolution16 GetVersion();
        [[nodiscard]] LogLevel LoggingLevel();
        [[nodiscard]] std::string LoggingType();
        [[nodiscard]] std::string LogFilePath();

        [[nodiscard]] NFResolution16 GetCarnivoreCount();
        [[nodiscard]] NFResolution16 GetHerbivoreCount();
        [[nodiscard]] NFResolution16 GetOmnivoreCount();
        [[nodiscard]] NFResolution16 GetHerbCount();

        [[nodiscard]] sf::Color GetCarnivoreSpawnColor();
        [[nodiscard]] sf::Color GetHerbivoreSpawnColor();
        [[nodiscard]] sf::Color GetOmnivoreSpawnColor();
        [[nodiscard]] sf::Color GetHerbSpawnColor();

    private:
        ConfigParser() = default;
        ~ConfigParser() = default;

        sf::Color GetColor(std::string);

        nlohmann::json m_jsonData;
    };
} // namespace Utility

#endif