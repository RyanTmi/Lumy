#include <LumyEngine.hpp>

int main()
{
    Lumy::Log::Init();

    LM_PROFILE_BEGIN_SESSION("Startup", "LumyEngine-Startup");

    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Runtime", "LumyEngine-Runtime");

    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Shutdown", "LumyEngine-Shutdown");

    LM_PROFILE_END_SESSION();

    return 0;
}
