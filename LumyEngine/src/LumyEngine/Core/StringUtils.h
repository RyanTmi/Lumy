/**
 * @file StringUtils.h
 * @author Ryan Timeus
 * @brief Utility functions for string manipulation and formatting.
 * 
 * This file provides utility functions for string manipulation and formatting,
 * including a templated function for formatting strings and functions to get
 * the current date and time in a formatted manner.
 * 
 * @version 0.1
 * @date 2023-11-19
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */ 


#pragma once

#include "Types.h"

#include <sstream>

namespace Lumy::Utils
{
    /**
     * @brief Format a string using a format string and arguments.
     * @tparam Args Argument types.
     * @param outStream Output stream to write the formatted string.
     * @param format Format string.
     * @param args Arguments to format into the string.
     */
    template <typename... Args>
    void Format(std::ostringstream& outStream, std::string_view format, Args... args);

    /**
     * @brief Get the current date and format it as a string.
     * @param outStream Output stream to write the formatted date.
     */
    void GetCurrentDate(std::ostringstream& outStream);

    /**
     * @brief Get the current time and format it as a string.
     * @param outStream Output stream to write the formatted time.
     */
    void GetCurrentTime(std::ostringstream& outStream);
}

#include "StringUtils.inl"
