#pragma once
#include "Keyboard.h"
#include "Mouse.h"

class InputController
{
	friend class App;
	InputController() = delete;
	InputController(const InputController&) = delete;
	InputController& operator=(const InputController&) = delete;
public:
	InputController(
		winrt::Windows::UI::Core::CoreWindow const& window,
		winrt::Windows::UI::Core::CoreDispatcher const& dispatcher
	);
	InputController(
		winrt::Windows::UI::Core::CoreWindow const& window
	);
public:
	void CommandClose()const;
	winrt::fire_and_forget ShowCursor();
	winrt::fire_and_forget HideCursor();
	bool CursorEnabled()const noexcept { return cursor; }
private:
	void Init(const CoreWindow& window);
	void OnKeyDown(
		winrt::Windows::UI::Core::CoreWindow const& sender,
		winrt::Windows::UI::Core::KeyEventArgs const& args
	);
	void OnKeyUp(
		winrt::Windows::UI::Core::CoreWindow const& sender,
		winrt::Windows::UI::Core::KeyEventArgs const& args
	);
	void OnMouseMoved(
		const Windows::Devices::Input::MouseDevice& mouseDevice,
		const Windows::Devices::Input::MouseEventArgs& args
	);	

	void OnMousePressed(
		const winrt::Windows::UI::Core::CoreWindow& sender,
		const winrt::Windows::UI::Core::PointerEventArgs& args
	);	
	void OnMouseReleased(
		const winrt::Windows::UI::Core::CoreWindow& mouseDevice,
		const winrt::Windows::UI::Core::PointerEventArgs& args
	);
private:
	winrt::Windows::UI::Core::CoreDispatcher  m_dispatcher;
	bool cursor = true;
public:
	Keyboard kbd;
	Mouse mouse;
};