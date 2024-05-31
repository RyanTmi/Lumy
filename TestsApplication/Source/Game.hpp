#pragma once

#include <LumyEngine/LumyEngine.hpp>

using namespace Lumy;

class Game : public Application
{
public:
    explicit Game(const ApplicationSpecification& applicationSpecification)
        : m_ApplicationSpecification(applicationSpecification)
    {}

    ~Game() override = default;

public:
    auto Initialize() -> bool override;

    auto Shutdown() -> void override;

    auto Update(Float64 deltaTime) -> bool override;

    auto Render(Float64 deltaTime) -> bool override;

    auto Specification() const -> const ApplicationSpecification& override
    {
        return m_ApplicationSpecification;
    }

private:
    ApplicationSpecification m_ApplicationSpecification;
};
