#pragma once
#include "SolidSphere.h"
#include "Triangle.h"
#include "Camera.h"
#include "PointLight.h"

namespace ver
{
	class VeritasEngine
	{
	public:
		VeritasEngine(uint32_t width, uint32_t height, XWindow wnd)
			:gfx(width, height, wnd), light(gfx, 0.5f), tri(gfx)
		{
			gfx.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, float(720.0f / 1280.0f), 0.5f, 100.0f));
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
			gfx.SetCamera(cam.GetViewMatrix());
			light.Bind(gfx, cam.GetViewMatrix());
			float dt = 0.05f;
			tri.Step(gfx, dt);


			gfx.StartFrame();
			{
				auto pass = gfx.StartPass();
				tri.Submit(pass);
				light.Submit(pass);
			}
			gfx.Present();
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
		PointLight light;
		Triangle tri;
	};
}