#include <LumyEngine.hpp>

class TestsApp : public Lumy::Application
{
public:
    TestsApp()
    {
    }
    
    ~TestsApp()
    {
    }
};

Lumy::Application* Lumy::CreateApplication()
{
    return new TestsApp();
}
