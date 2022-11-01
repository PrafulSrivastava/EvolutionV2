#include "ConfigParser.hpp"

namespace Evolution::Utility
{
    ConfigParser &ConfigParser::GetInstance()
    {
        static ConfigParser obj;
        return obj;
    }

    bool ConfigParser::LoadConfig()
    {
        std::ifstream config;
        config.open(Evolution::Utility::ConfigPath);

        if (config.is_open())
        {
            m_jsonData = nlohmann::json::parse(config);
            config.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    NFResolution16 ConfigParser::GetVersion()
    {
        return m_jsonData["Version"];
    }
    LogLevel ConfigParser::LoggingLevel()
    {
        // Fetching Log level
        LogLevel level = LogLevel::DISABLE;
        uint8_t val = m_jsonData["LoggingLevel"];
        switch (val)
        {
        case 1:
            level = LogLevel::FATAL;
            break;
        case 2:
            level = LogLevel::WARN;
            break;
        case 3:
            level = LogLevel::ERROR;
            break;
        case 4:
            level = LogLevel::INFO;
            break;
        case 5:
            level = LogLevel::DEBUG;
            break;
        case 6:
            level = LogLevel::VERBOSE;
            break;
        }

        return level;
    }
    std::string ConfigParser::LoggingType()
    {
        return m_jsonData["LoggingType"];
    }
    std::string ConfigParser::LogFilePath()
    {
        return m_jsonData["LogFilePath"];
    }
    NFResolution16 ConfigParser::GetCarnivoreCount()
    {
        return m_jsonData["CarnivoreCount"];
    }
    NFResolution16 ConfigParser::GetHerbivoreCount()
    {
        return m_jsonData["HerbivoreCount"];
    }
    NFResolution16 ConfigParser::GetOmnivoreCount()
    {
        return m_jsonData["OmnivoreCount"];
    }
    NFResolution16 ConfigParser::GetHerbCount()
    {
        return m_jsonData["HerbCount"];
    }
    sf::Color ConfigParser::GetCarnivoreSpawnColor()
    {
        return GetColor(m_jsonData["CarnivoreSpawnColor"]);
    }
    sf::Color ConfigParser::GetHerbivoreSpawnColor()
    {
        return GetColor(m_jsonData["HerbivoreSpawnColor"]);
    }
    sf::Color ConfigParser::GetOmnivoreSpawnColor()
    {
        return GetColor(m_jsonData["OmnivoreSpawnColor"]);
    }
    sf::Color ConfigParser::GetHerbSpawnColor()
    {
        return GetColor(m_jsonData["HerbSpawnColor"]);
    }
    sf::Color ConfigParser::GetColor(std::string color)
    {
        if (color == "White")
            return sf::Color::White;

        else if (color == "Red")
            return sf::Color::Red;

        else if (color == "Green")
            return sf::Color::Green;

        else if (color == "Yellow")
            return sf::Color::Yellow;

        else if (color == "Blue")
            return sf::Color::Blue;

        else
            return sf::Color::Black;
    }
}