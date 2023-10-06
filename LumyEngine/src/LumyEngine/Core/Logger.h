#pragma once

#include "LumyEngine/Core/Base.h"

#include <iostream>
#include <sstream>

namespace Lumy
{
    class Logger
    {
    public:
        enum class Level
        {
            Trace, Debug, Info, Warn, Error, Fatal
        };

        enum class FormatFlag
        {
            None  = 0,
            Date  = BIT(0),
            Time  = BIT(1),
            Level = BIT(2),
            Name  = BIT(3),

            All
        };
    public:
        explicit Logger(FormatFlag logFormat, const std::string& name = "");

        template <typename... Args>
        void Log(Level logLevel, const std::string& format, Args... args)
        {
            std::stringstream ss;

            ApplyFormat(logLevel, ss);
            FormatStringHelper(ss, format, args...);
            PrintColored(logLevel, ss.str());
        }
    private:
        FormatFlag m_FormatFlags;
        const std::string m_Name;

        // TODO - Find better name
        void ApplyFormat(Level logLevel, std::stringstream& ss);
    private:
        // TODO - Find better name
        static void PrintColored(Level logLevel, const std::string& message);
        // TODO - Find better name
        static void FormatStringHelper(std::stringstream& ss, const std::string& format) { ss << format; }

        // TODO - Find better name
        template <typename T, typename... Args>
        static void FormatStringHelper(std::stringstream& ss, const std::string& format, T arg, Args... args)
        {
            uint64 pos = format.find("{}");
            if (pos == std::string::npos)
            {
                ss << format;
                return;
            }

            ss << format.substr(0, pos) << arg;
            FormatStringHelper(ss, format.substr(pos + 2), args...);
        }
    };
}


inline Lumy::Logger::FormatFlag operator|(Lumy::Logger::FormatFlag a, Lumy::Logger::FormatFlag b)
{
    return static_cast<Lumy::Logger::FormatFlag>(static_cast<uint8>(a) | static_cast<uint8>(b));
}

inline uint8 operator&(Lumy::Logger::FormatFlag a, Lumy::Logger::FormatFlag b)
{
    return static_cast<uint8>(a) & static_cast<uint8>(b);
}

inline Lumy::Logger::FormatFlag operator^(Lumy::Logger::FormatFlag a, Lumy::Logger::FormatFlag b)
{
    return static_cast<Lumy::Logger::FormatFlag>(static_cast<uint8>(a) ^ static_cast<uint8>(b));
}

inline void operator^=(Lumy::Logger::FormatFlag& a, Lumy::Logger::FormatFlag b)
{
    a = a ^ b;
}