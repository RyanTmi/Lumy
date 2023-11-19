/**
 * @file Profiler.h
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Profiling utility for Lumy Game Engine using Chrome Tracing.
 * 
 * The Profiler module provides a simple yet effective profiling system for Lumy Game Engine,
 * utilizing Chrome Tracing format for visualization. It includes a Profiler class for managing
 * profiling sessions and timers, as well as a ProfileTimer class for convenient scoped profiling.
 * 
 * @version 0.1
 * @date 2023-11-19
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "LumyEngine/Core/Foundation.hpp"

#include <string>
#include <fstream>
#include <thread>

namespace Lumy
{
    /**
     * @brief Structure to store profiling results.
     */
    struct ProfileResult
    {
        /** @brief Name of the profile event. */
        std::string Name;
        /** @brief Start time of the profile event. */
        lm_u64 Start;
        /** @brief End time of the profile event. */
        lm_u64 End;
        /** @brief Thread ID of the profile event. */
        lm_u64 ThreadID;
    };

    /**
     * @brief Structure to represent a profiling session.
     */
    struct ProfileSession
    {
        /** @brief Name of the profiling session. */
        std::string Name;
    };

    /**
     * @brief The Profiler class manages profiling sessions and writes profiling data to a file.
     */
    class Profiler
    {
    public:
        /**
         * @brief Get the singleton instance of the Profiler.
         * @return Profiler& Reference to the Profiler instance.
         */
        static Profiler& Instance();

        Profiler(const Profiler&) = delete;
        Profiler& operator=(const Profiler&) = delete;
    public:
        /**
         * @brief Begin a new profiling session.
         * @param name Name of the profiling session.
         * @param fileName Name of the file to write profiling data.
         */
        void BeginSession(const std::string& name, const std::string& fileName = "profile");

        /**
         * @brief End the current profiling session.
         */
        void EndSession();

        /**
         * @brief Write profiling data to the output file.
         * @param result Profiling result to be written.
         */
        void WriteProfile(const ProfileResult& result);
    private:
        Profiler();
        ~Profiler();
    private:
        ProfileSession* m_CurrentSession;
        std::ofstream m_OutputFile;
        bool m_SessionInProgress;
    };

    /**
     * @brief The ProfileTimer class is a scoped timer for profiling events.
     */
    class ProfileTimer
    {
    public:
        /**
         * @brief Constructor for ProfileTimer.
         * @param name Name of the profiling event.
         */
        explicit ProfileTimer(const char* name);

        /**
         * @brief Destructor for ProfileTimer.
         * Ends the profiling event and writes the result to the Profiler.
         */
        ~ProfileTimer();
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    };
}

#if defined(LM_DEBUG)
    #define LM_PROFILE
#endif

/**
 * @brief Macros to simplify the usage of the Profiler class.
 */
#if defined(LM_PROFILE)
    #define LM_PROFILE_BEGIN_SESSION(name, filepath) ::Lumy::Profiler::Instance().BeginSession(name, filepath)
    #define LM_PROFILE_END_SESSION()                 ::Lumy::Profiler::Instance().EndSession()

    #define LM_PROFILE_SCOPE(name)                   ::Lumy::ProfileTimer timer##__LINE__(name)
    #define LM_PROFILE_FUNCTION()                    LM_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define LM_PROFILE_BEGIN_SESSION(name, filepath)
    #define LM_PROFILE_END_SESSION()

    #define LM_PROFILE_SCOPE(name)
    #define LM_PROFILE_FUNCTION()
#endif

#include "Profiler.inl"