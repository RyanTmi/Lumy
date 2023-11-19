namespace Lumy
{
    template <typename... Args>
    void Logger::Log(Level logLevel, std::string_view format, Args... args)
    {
        if (!m_ConsoleConfig.Enabled && !m_LogFileConfig.Enabled)
        {
            return;
        }

        /* NOTE - Check if the log message is the same on both configurations for optimization. */
        if (m_ConsoleConfig.Enabled && m_LogFileConfig.Enabled &&
            m_ConsoleConfig.FormatFlag == m_LogFileConfig.FormatFlag)
        {
            std::ostringstream outStream {};

            ApplyFlagFormat(m_ConsoleConfig.FormatFlag, logLevel, outStream);
            Utils::Format(outStream, format, args...);

            WriteToConsole(logLevel, outStream.str());
            WriteToFile(outStream.str());
            return;
        }

        if (m_ConsoleConfig.Enabled)
        {
            std::ostringstream outStream {};

            ApplyFlagFormat(m_ConsoleConfig.FormatFlag, logLevel, outStream);
            Utils::Format(outStream, format, args...);

            WriteToConsole(logLevel, outStream.str());
        }

        if (m_LogFileConfig.Enabled)
        {
            std::ostringstream outStream {};

            ApplyFlagFormat(m_LogFileConfig.FormatFlag, logLevel, outStream);
            Utils::Format(outStream, format, args...);

            WriteToFile(outStream.str());
        }
    }
}
