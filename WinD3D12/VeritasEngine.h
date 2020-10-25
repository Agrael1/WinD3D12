#pragma once
#include "Triangle.h"
#include "Camera.h"

namespace ver
{
	class VeritasEngine
	{
	public:
		VeritasEngine(uint32_t width, uint32_t height, XWindow wnd)
			:gfx(width, height, wnd), tri(gfx)
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
		void WindowActivationChanged(CoreWindowActivationState)
		{

		}
	private:
		void Render()
		{
			gfx.StartFrame();
			{
				auto pass = gfx.StartPass();
				tri.Submit(pass);
			}
			gfx.Present();
			tri.Step(gfx);
		}
	public:
		void Run()
		{
			if (bVisible)
				Render();
		}
	private:
		Graphics gfx;
		Camera cam;

		bool bWindowClosed = false;
		bool bVisible = true;
		Triangle tri;
	};
}