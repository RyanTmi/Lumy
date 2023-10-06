#include <LumyEngine/LumyEngine.h>

int main()
{
    Lumy::Log::Init();

    LM_CORE_LOG_TRACE("This is a Trace log");
    LM_CORE_LOG_DEBUG("This is a Debug log");
    LM_CORE_LOG_INFO("This is a Info log");
    LM_CORE_LOG_WARN("This is a Warn log");
    LM_CORE_LOG_ERROR("This is a Error log");
    LM_CORE_LOG_FATAL("This is a Fatal log");

    return 0;
}
