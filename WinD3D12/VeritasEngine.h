#pragma once
#include "Graphics.h"

namespace ver
{

class VeritasEngine
{
public:
	VeritasEngine(uint32_t width, uint32_t height, XWindow wnd)
		:gfx(width, height, wnd)
	{

	}
public:
	void Close()
	{
		bWindowClosed = true;
	}
	void Suspend()
	{

	}
	void Visibility(bool Visible)
	{
		bVisible = Visible;
	}
	void WindowActivationChanged(CoreWindowActivationState activationState)
	{

	}
public:
	void Run()
	{
		while (!bWindowClosed)
		{
			if (bVisible)
			{

			}
			else
			{

			}
		}
	}
private:
	Graphics gfx;
	bool bWindowClosed = false;
	bool bVisible = true;
};
}