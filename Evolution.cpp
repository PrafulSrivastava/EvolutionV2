#include "IManager.hpp"
#include "Manager.hpp"
#include <fstream>
#include "ConfigParser.hpp"
#include <sstream>

using namespace Evolution::Utility;

int main()
{
    srand(time(nullptr));
    ConfigParser::GetInstance().LoadConfig();
    std::ofstream fs;

    if (ConfigParser::GetInstance().LoggingType() == "File")
    {
        fs.open(ConfigParser::GetInstance().LogFilePath());

        Logger::init<std::ofstream>(ConfigParser::GetInstance().LoggingLevel(), &fs);
    }
    else if (ConfigParser::GetInstance().LoggingType() == "Console")
    {
        Logger::init<std::ostream>(ConfigParser::GetInstance().LoggingLevel());
    }
    else if (ConfigParser::GetInstance().LoggingType() == "SStream")
    {
        Logger::init<std::stringstream>(ConfigParser::GetInstance().LoggingLevel());
    }

    Evolution::Manager::Manager obj;
    obj.Init();
    obj.RunGameLoop();
    fs.close();
}