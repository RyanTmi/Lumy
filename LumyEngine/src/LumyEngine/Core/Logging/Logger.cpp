#include "Logger.hpp"

#include <iostream>

namespace Lumy::ConsoleColor
{
    constexpr char RESET     [] = "\033[0m";

    constexpr char BG_BLACK  [] = "\033[30m";     /* Black */
    constexpr char BG_RED    [] = "\033[31m";     /* Red */
    constexpr char BG_GREEN  [] = "\033[32m";     /* Green */
    constexpr char BG_YELLOW [] = "\033[33m";     /* Yellow */
    constexpr char BG_BLUE   [] = "\033[34m";     /* Blue */
    constexpr char BG_MAGENTA[] = "\033[35m";     /* Magenta */
    constexpr char BG_CYAN   [] = "\033[36m";     /* Cyan */
    constexpr char BG_WHITE  [] = "\033[37m";     /* White */

    constexpr char FG_BLACK  [] = "\033[40m";     /* Black */
    constexpr char FG_RED    [] = "\033[41m";     /* Red */
    constexpr char FG_GREEN  [] = "\033[42m";     /* Green */
    constexpr char FG_YELLOW [] = "\033[43m";     /* Yellow */
    constexpr char FG_BLUE   [] = "\033[44m";     /* Blue */
    constexpr char FG_MAGENTA[] = "\033[45m";     /* Magenta */
    constexpr char FG_CYAN   [] = "\033[46m";     /* Cyan */
    constexpr char FG_WHITE  [] = "\033[47m";     /* White */
}

namespace Lumy
{
    Logger::Logger(ConfigFlag logFormat, const std::string& name, bool logToFile)
        : m_Name("[" + name + "]"), m_LogFileName(logToFile ? name + ".log" : ""), m_ConfigFlags(logFormat)
    {
    }

    std::map<Logger::Level, const char*> Logger::s_LevelToColor
    {
        { Level::Trace, ConsoleColor::BG_WHITE  },
        { Level::Debug, ConsoleColor::BG_BLUE   },
        { Level::Info,  ConsoleColor::BG_GREEN  },
        { Level::Warn,  ConsoleColor::BG_YELLOW },
        { Level::Error, ConsoleColor::BG_RED    },
        { Level::Fatal, ConsoleColor::FG_RED    }
    };

    std::map<Logger::Level, const char*> Logger::s_LevelToString
    {
        { Level::Trace, "[TRACE]" },
        { Level::Debug, "[DEBUG]" },
        { Level::Info,  "[INFO]"  },
        { Level::Warn,  "[WARN]"  },
        { Level::Error, "[ERROR]" },
        { Level::Fatal, "[FATAL]" }
    };

    void Logger::WriteConsole(Level logLevel, const std::string& message)
    {
        std::cout << s_LevelToColor[logLevel] << message << ConsoleColor::RESET << std::endl;
    }

    void Logger::ConfigFlagFormat(std::ostringstream& outStream, Level logLevel) const
    {
        bool configFormatEmpty = true;

        if (m_ConfigFlags & ConfigFlag_Date)
        {
            configFormatEmpty = false;
            outStream << "[";
            Utils::GetCurrentDate(outStream);
            outStream << "]";
        }

        if (m_ConfigFlags & ConfigFlag_Time)
        {
            if (!configFormatEmpty)
            {
                outStream << "-";
            }
            configFormatEmpty = false;
            outStream << "[";
            Utils::GetCurrentTime(outStream);
            outStream << "]";
        }

        if (m_ConfigFlags & ConfigFlag_Level)
        {
            if (!configFormatEmpty)
            {
                outStream << "-";
            }
            configFormatEmpty = false;
            outStream << s_LevelToString[logLevel];
        }

        if (m_ConfigFlags & ConfigFlag_Name)
        {
            if (!configFormatEmpty)
            {
                outStream << "-";
            }
            configFormatEmpty = false;
            outStream << m_Name;
        }

        if (!configFormatEmpty)
        {
            outStream << " : ";
        }
    }
}