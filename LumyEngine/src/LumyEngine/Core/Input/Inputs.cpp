#include "Inputs.hpp"

#include "LumyEngine/Core/Events/Events.hpp"
#include "LumyEngine/Core/Events/KeyEvent.hpp"
#include "LumyEngine/Core/Events/MouseEvent.hpp"


namespace Lumy
{
    Input& Input::Get()
    {
        static Input instance;
        return instance;
    }

    void Input::Initialize()
    {
        Events::Get().Subscribe<KeyPressedEvent>(MakeDelegate<&Input::OnKeyPressed>(this));
        Events::Get().Subscribe<KeyReleasedEvent>(MakeDelegate<&Input::OnKeyReleased>(this));

        Events::Get().Subscribe<MouseButtonPressedEvent>(MakeDelegate<&Input::OnMousePressed>(this));
        Events::Get().Subscribe<MouseButtonReleasedEvent>(MakeDelegate<&Input::OnMouseReleased>(this));
        Events::Get().Subscribe<MouseMovedEvent>(MakeDelegate<&Input::OnMouseMoved>(this));
        Events::Get().Subscribe<MouseScrolledEvent>(MakeDelegate<&Input::OnMouseScrolled>(this));
    }

    void Input::Update()
    {
        m_PreviousKeyboardState = m_CurrentKeyboardState;
        m_PreviousMouseState = m_CurrentMouseState;
    }

    void Input::Shutdown()
    {
        Events::Get().Unsubscribe<KeyPressedEvent>(MakeDelegate<&Input::OnKeyPressed>(this));
        Events::Get().Unsubscribe<KeyReleasedEvent>(MakeDelegate<&Input::OnKeyReleased>(this));

        Events::Get().Unsubscribe<MouseButtonPressedEvent>(MakeDelegate<&Input::OnMousePressed>(this));
        Events::Get().Unsubscribe<MouseButtonReleasedEvent>(MakeDelegate<&Input::OnMouseReleased>(this));
        Events::Get().Unsubscribe<MouseMovedEvent>(MakeDelegate<&Input::OnMouseMoved>(this));
        Events::Get().Unsubscribe<MouseScrolledEvent>(MakeDelegate<&Input::OnMouseScrolled>(this));

        m_PreviousKeyboardState.Keys.clear();
        m_CurrentKeyboardState.Keys.clear();
        m_PreviousMouseState.Buttons.clear();
        m_CurrentMouseState.Buttons.clear();
    }

    Bool8 Input::IsKeyDown(KeyCode keyCode)
    {
        Bool8 isKeyDown = m_CurrentKeyboardState.Keys[keyCode];
        return isKeyDown;
    }

    Bool8 Input::IsKeyUp(KeyCode keyCode)
    {
        Bool8 isKeyUp = !m_CurrentKeyboardState.Keys[keyCode];
        return isKeyUp;
    }

    Bool8 Input::WasKeyDown(KeyCode keyCode)
    {
        Bool8 wasKeyDown = m_PreviousKeyboardState.Keys[keyCode];
        return wasKeyDown;
    }

    Bool8 Input::WasKeyUp(KeyCode keyCode)
    {
        Bool8 wasKeyUp = !m_PreviousKeyboardState.Keys[keyCode];
        return wasKeyUp;
    }

    Bool8 Input::IsButtonDown(MouseButton mouseButton)
    {
        Bool8 isButtonDown = m_CurrentMouseState.Buttons[mouseButton];
        return isButtonDown;
    }

    Bool8 Input::IsButtonUp(MouseButton mouseButton)
    {
        Bool8 isButtonUp = !m_CurrentMouseState.Buttons[mouseButton];
        return isButtonUp;
    }

    Bool8 Input::WasButtonDown(MouseButton mouseButton)
    {
        Bool8 wasButtonDown = m_PreviousMouseState.Buttons[mouseButton];
        return wasButtonDown;
    }

    Bool8 Input::WasButtonUp(MouseButton mouseButton)
    {
        Bool8 wasButtonUp = !m_PreviousMouseState.Buttons[mouseButton];
        return wasButtonUp;
    }
    
    Float32 Input::MouseX()
    {
        return m_CurrentMouseState.X;
    }

    Float32 Input::MouseY()
    {
        return m_CurrentMouseState.Y;
    }
    
    Float32 Input::PreviousMouseX()
    {
        return m_PreviousMouseState.X;
    }

    Float32 Input::PreviousMouseY()
    {
        return m_PreviousMouseState.Y;
    }

    void Input::OnKeyPressed(const KeyPressedEvent& event)
    {
        // Log::Trace("{}", event.ToString());

        m_CurrentKeyboardState.Keys[event.Code] = true;
    }

    void Input::OnKeyReleased(const KeyReleasedEvent& event)
    {
        // Log::Trace("{}", event.ToString());

        m_CurrentKeyboardState.Keys[event.Code] = false;
    }

    void Input::OnMousePressed(const MouseButtonPressedEvent& event)
    {
        // Log::Trace("{}", event.ToString());

        m_CurrentMouseState.Buttons[event.Button] = true;
    }

    void Input::OnMouseReleased(const MouseButtonReleasedEvent& event)
    {
        // Log::Trace("{}", event.ToString());

        m_CurrentMouseState.Buttons[event.Button] = false;
    }

    void Input::OnMouseMoved(const MouseMovedEvent& event)
    {
        // Log::Trace("{}", event.ToString());

        m_CurrentMouseState.X = event.MouseX;
        m_CurrentMouseState.Y = event.MouseY;
    }

    void Input::OnMouseScrolled(const MouseScrolledEvent& event)
    {
        // Log::Trace("{}", event.ToString());
    }
}
