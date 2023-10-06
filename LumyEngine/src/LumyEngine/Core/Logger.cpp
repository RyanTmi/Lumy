#include "Logger.h"

static std::string GetTime()
{
    std::time_t now = std::time(nullptr);
    int8 buffer[80];
    std::strftime(buffer, sizeof(buffer), "[%H:%M:%S]", std::localtime(&now));
    return {buffer};
}

static std::string GetDate()
{
    std::time_t now = std::time(nullptr);
    int8 buffer[80];
    std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d]", std::localtime(&now));
    return {buffer};
}

namespace Lumy
{
    Logger::Logger(FormatFlag logFormat, const std::string& name)
            : m_FormatFlags(logFormat), m_Name("[" + name + "]")
    {
        if (name.empty())
        {
            m_FormatFlags ^= FormatFlag::Name;
        }
    }

    void Logger::ApplyFormat(Level logLevel, std::stringstream& ss)
    {
        static const int8* const StringLogLevel[] = { "[Trace]", "[Debug]", "[Info]", "[Warn]", "[Error]", "[Fatal]" };
        static const int8* const Delimiter = "-";

        FormatFlag formatFlag = m_FormatFlags;

        ss.clear();
        if (formatFlag & FormatFlag::Date) {
            ss << GetDate();
            formatFlag ^= FormatFlag::Date;
        }
        if (!ss.str().empty() && formatFlag != FormatFlag::None) { ss << Delimiter; }

        if (formatFlag & FormatFlag::Time) {
            ss << GetTime();
            formatFlag ^= FormatFlag::Time;
        }
        if (!ss.str().empty() && formatFlag != FormatFlag::None) { ss << Delimiter; }

        if (formatFlag & FormatFlag::Level) {
            ss << StringLogLevel[static_cast<int>(logLevel)];
            formatFlag ^= FormatFlag::Level;
        }
        if (!ss.str().empty() && formatFlag != FormatFlag::None) { ss << Delimiter; }

        if (formatFlag & FormatFlag::Name) {
            ss << m_Name;
            formatFlag ^= FormatFlag::Name;
        }
        if (m_FormatFlags != FormatFlag::None) { ss << " : "; }
    }

    void Logger::PrintColored(Level logLevel, const std::string& message)
    {
        static const int8* const ColorLogLevel[] = { "37", "34", "32", "33", "31", "41" };

        std::cout << "\033[1;" << ColorLogLevel[static_cast<int>(logLevel)] << "m";
        std::cout << message;
        std::cout << "\033[0m" << std::endl;
    }
}