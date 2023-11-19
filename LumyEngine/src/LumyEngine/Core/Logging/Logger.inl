namespace Lumy
{
    template <typename... Args>
    void Logger::Log(Level logLevel, std::string_view format, Args... args)
    {
        if (!m_Enabled)
        {
            return;
        }
        std::ostringstream outStream {};

        ConfigFlagFormat(outStream, logLevel);
        Utils::Format(outStream, format, args...);
        WriteConsole(logLevel, outStream.str());
    }
}
