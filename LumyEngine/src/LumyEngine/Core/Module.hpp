#pragma once

namespace Lumy
{
    class Module
    {
    public:
        virtual ~Module() = default;
    public:
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Shutdown() = 0;
    };
}
