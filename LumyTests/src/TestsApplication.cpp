#include <LumyEngine/LumyEngine.hpp>
#include <LumyEngine/Core/EntryPoint.hpp>

class GameApplication : public Lumy::Application
{
public:
    GameApplication()
    {
        m_ApplicationConfiguration = Lumy::ApplicationConfiguration("LumyTestGame", 1920, 1080);
    }

    void Initialize() override
    {

    }

    void Update() override
    {

    }

    void Shutdown() override
    {

    }
};

Lumy::Application* Lumy::ApplicationCreate()
{
    return new GameApplication();
}
