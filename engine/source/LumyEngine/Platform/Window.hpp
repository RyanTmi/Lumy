#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Math.hpp"

#include <string_view>
#include <utility>

namespace Lumy
{
    struct WindowSpecification final
    {
        std::string_view Title;
        Rectangle<UInt32> Frame;

        WindowSpecification()
            : Title("Lumy Application"), Frame(0, 0, 1280, 720)
        {}

        WindowSpecification(std::string_view Title, const Rectangle<UInt32>& Frame)
            : Title(Title), Frame(Frame)
        {}
    };

    class Window final
    {
    public:
        Window() = default;
        Window(const WindowSpecification& specification);
        ~Window();

    public:
        auto Create(const WindowSpecification& specification) -> bool;
        auto Destroy() -> void;
        
        template <typename T>
        auto GetNativeWindow() const -> T* { return reinterpret_cast<T*>(m_NativeWindow); }

    public:
        auto Size() const -> std::pair<UInt32, UInt32>;
        auto SetTitle(std::string_view title) -> void;
        auto Show() -> void;
        auto Hide() -> void;
        auto Maximize() -> void;

    private:
        void* m_NativeWindow = nullptr;
    };
}
