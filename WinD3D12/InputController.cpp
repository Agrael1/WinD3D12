#include "pch.h"
#include "InputController.h"

InputController::InputController( winrt::Windows::UI::Core::CoreWindow const& window,  
    winrt::Windows::UI::Core::CoreDispatcher const& dispatcher)
    :m_dispatcher(dispatcher)
{
    Init(window);
}

InputController::InputController( winrt::Windows::UI::Core::CoreWindow const& window)
    :m_dispatcher(nullptr)
{
    Init(window);
}

void InputController::CommandClose() const
{
    auto window = CoreWindow::GetForCurrentThread();
    if (window) window.Close();
}

winrt::fire_and_forget InputController::ShowCursor()
{
    if (m_dispatcher)
    {
        // Use the CoreDispatcher to ensure that the pointer is updated on the UI thread.
        // This is needed for XAML updates in a XAML app.
        co_await winrt::resume_foreground(m_dispatcher);
    }

    
    auto window = CoreWindow::GetForCurrentThread();
    if (window)
    {
        // Protect case where there isn't a window associated with the current thread.
        // This happens on initialization or when being called from a background thread.
        window.PointerCursor(CoreCursor(CoreCursorType::Arrow, 0));
    }
    cursor = true;
}

winrt::fire_and_forget InputController::HideCursor()
{
    if (m_dispatcher)
        co_await winrt::resume_foreground(m_dispatcher);

    auto window = CoreWindow::GetForCurrentThread();
    if (window)
    {
        // Protect case where there isn't a window associated with the current thread.
        // This happens on initialization or when being called from a background thread.
        window.PointerCursor(nullptr);
    }
    cursor = false;
}

void InputController::Init(const CoreWindow& window)
{
    window.KeyDown({ this, &InputController::OnKeyDown });
    window.KeyUp({ this, &InputController::OnKeyUp });

    auto m = Windows::Devices::Input::MouseDevice::GetForCurrentView();
    m.MouseMoved({ this, &InputController::OnMouseMoved });
}

void InputController::OnKeyDown(winrt::Windows::UI::Core::CoreWindow const& sender, 
    winrt::Windows::UI::Core::KeyEventArgs const& args)
{
    kbd.OnKeyPressed(uint8_t(args.VirtualKey()));
}
void InputController::OnKeyUp(winrt::Windows::UI::Core::CoreWindow const& sender, 
    winrt::Windows::UI::Core::KeyEventArgs const& args)
{
    kbd.OnKeyReleased(uint8_t(args.VirtualKey()));
}

void InputController::OnMouseMoved(const Windows::Devices::Input::MouseDevice& mouseDevice, const Windows::Devices::Input::MouseEventArgs& args)
{
    if (mouse.RawEnabled())
    {
        auto x = args.MouseDelta();
        mouse.OnRawDelta(x.X, x.Y);
    }
}

