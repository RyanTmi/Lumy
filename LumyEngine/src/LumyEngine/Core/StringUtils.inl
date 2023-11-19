namespace Lumy::Utils
{
    template <typename... Args>
    void Format(std::ostringstream& outStream, std::string_view format, Args... args)
    {
        static auto format_helper = [](std::ostringstream& oss, std::string_view& str, const auto& value)
        {
            lm_size openBracket = str.find('{');
            if (openBracket == std::string::npos)
            {
                return;
            }
            lm_size closeBracket = str.find('}', openBracket + 1);
            if (closeBracket == std::string::npos)
            {
                return;
            }
            oss << str.substr(0, openBracket) << value;
            str = str.substr(closeBracket + 1);
        };

        (format_helper(outStream, format, args), ...);
        outStream << format;
    }
}