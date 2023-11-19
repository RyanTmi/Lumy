/**
 * @file Logger.h
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

#include "LumyEngine/Core/Types.h"
#include "LumyEngine/Core/StringUtils.h"

#include <map>

namespace Lumy
{
    // TODO - Make this class thread safe
    // TODO - Add a log file support
    class Logger
    {
    public:
        enum class Level
        {
            Trace, Debug, Info, Warn, Error, Fatal
        };

        enum ConfigFlag
        {
            ConfigFlag_None  = 0,
            ConfigFlag_Date  = BIT(0),
            ConfigFlag_Time  = BIT(1),
            ConfigFlag_Level = BIT(2),
            ConfigFlag_Name  = BIT(3),
            ConfigFlag_All   = ~0
        };
    public:
        /**
         * @brief Constructor for the Logger class.
         * @param logFormat Configuration flags for log formatting.
         * @param name The name associated with the logger.
         * @param logToFile Whether to log messages to a file.
         */
        explicit Logger(ConfigFlag logFormat = ConfigFlag_None, const std::string& name = "", bool logToFile = false);

        /**
         * @brief Log a message with the specified log level.
         * @tparam Args Argument types.
         * @param logLevel The log level of the message.
         * @param format The format string for the message.
         * @param args Arguments to format into the message.
         */
        template <typename... Args>
        void Log(Level logLevel, std::string_view format, Args... args);

        /**
         * @brief Enable or disable the logger.
         * @param enabled True to enable the logger, false to disable.
         */
        void SetEnabled(bool enabled) { m_Enabled = enabled; }
    private:
        static void WriteConsole(Level logLevel, const std::string& message);
        void ConfigFlagFormat(std::ostringstream& outStream, Level logLevel) const;

        static std::map<Level, const char*> s_LevelToColor;
        static std::map<Level, const char*> s_LevelToString;
    private:
        const std::string m_Name;
        const std::string m_LogFileName;
        ConfigFlag m_ConfigFlags;
        bool m_Enabled = true;
    };
}

#include "Logger.inl"
