/**
 * @file Logger.hpp
 * @author Ryan Timeus
 * @brief Logging utility for Lumy Game Engine.
 * 
 * The Logger class provides a flexible logging utility for Lumy Game Engine,
 * supporting various log levels, console output formatting, and configurable options.
 * 
 * @version 0.1
 * @date 2023-11-19
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Core/Containers/Map.hpp"
#include "LumyEngine/Core/Memory/Memory.hpp"
#include "LumyEngine/Core/StringFormat.hpp"

#include <fstream>

namespace Lumy
{
    // TODO - Make this class thread safe
    class Logger
    {
    public:
        enum class Level
        {
            Trace, Debug, Info, Warn, Error, Fatal
        };

        enum FormatFlag
        {
            FormatFlag_None  = 0,
            FormatFlag_Date  = BIT(0),
            FormatFlag_Time  = BIT(1),
            FormatFlag_Level = BIT(2),
            FormatFlag_Name  = BIT(3),
            FormatFlag_All   = ~0
        };

        struct Config
        {
            FormatFlag FormatFlag;
            bool Enabled;
        };
    public:
        Logger(const std::string& name, Config consoleConfig);
        Logger(const std::string& name, Config consoleConfig, Config logFileConfig);

        ~Logger();

        /**
         * @brief Log a message with the specified log level.
         * @tparam Args Argument types.
         * @param logLevel The log level of the message.
         * @param format The format string for the message.
         * @param args Arguments to format into the message.
         */
        template <typename... Args>
        void Log(Level logLevel, std::string_view format, Args... args);

        void ConsoleSetEnabled(const bool enabled) { m_ConsoleConfig.Enabled = enabled; }
        void LogFileSetEnabled(const bool enabled) { m_LogFileConfig.Enabled = enabled; }
    private:
        static void WriteToConsole(Level logLevel, const std::string& message);
        void WriteToFile(const std::string& message);
        void ApplyFlagFormat(FormatFlag formatFlag, Level logLevel, std::ostringstream& outStream) const;

        static UnorderedMap<Level, const char*> s_LevelToColor;
        static UnorderedMap<Level, const char*> s_LevelToString;
    private:
        const std::string m_Name;
        std::ofstream m_LogFile;

        Config m_ConsoleConfig;
        Config m_LogFileConfig;
    };
}

#include "Logger.inl"
