#pragma once

namespace Lumy
{
    inline Profiler& Profiler::Instance()
    {
        static Profiler instance;
        return instance;
    }

    inline void Profiler::BeginSession(const std::string& name, const std::string& fileName)
    {
        if (m_SessionInProgress)
        {
            Log::Error("There is already a profile session : {} !", m_CurrentSession->Name);
            return;
        }

        m_OutputFile = std::ofstream("profiles/" + fileName + ".json");
        if (!m_OutputFile.is_open())
        {
            Log::Error("Cannot open file {}", fileName);
            return;
        }

        m_OutputFile << "{\"traceEvents\":[";
        m_OutputFile.flush();

        m_CurrentSession = new ProfileSession{name};
        m_SessionInProgress = true;
    }

    inline void Profiler::EndSession()
    {
        m_OutputFile << "{}]}";
        m_OutputFile.flush();
        m_OutputFile.close();

        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_SessionInProgress = false;
    }

    inline void Profiler::WriteProfile(const ProfileResult& result)
    {
        std::ostringstream ss;

        ss << "{";
        ss << R"("cat":"function",)";
        ss << "\"dur\":" << (result.End - result.Start) << ',';
        ss << R"("name":")" << result.Name << "\",";
        ss << R"("ph":"X",)";
        ss << "\"pid\":0,";
        ss << "\"tid\":" << result.ThreadID << ",";
        ss << "\"ts\":" << result.Start;
        ss << "},";

        m_OutputFile << ss.str();
        m_OutputFile.flush();
    }

    inline Profiler::Profiler()
        : m_CurrentSession(nullptr), m_SessionInProgress(false)
    {
        if (!std::filesystem::create_directory("profiles"))
        {
            // TODO - Error handling
        }
    }

    inline Profiler::~Profiler()
    {
        EndSession();
    }

    inline ProfileTimer::ProfileTimer(const char* name)
        : m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now())
    {
    }

    inline ProfileTimer::~ProfileTimer()
    {
        const auto endTime = std::chrono::high_resolution_clock::now();

        const UInt64 start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
        const UInt64 end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

        const UInt64 threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Profiler::Instance().WriteProfile({ m_Name, start, end, threadID });
    }
}