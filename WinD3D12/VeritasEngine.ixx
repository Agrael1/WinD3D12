module;
#include "DawnAdapter.h"
#include "Camera.h"
#include "PointLight.h"
//#include "Model.h"
#include "Panel.h"
export module VeritasEngine;

export namespace ver
{
	class VeritasEngine
	{
	public:
		VeritasEngine(uint32_t width, uint32_t height, const XWindow& wnd)
			:gfx(width, height, wnd), light(gfx, 0.5f)/* tri(gfx),*/
			,panel(gfx)
			/*x(gfx, "Assets\\GoblinX.obj")*/
		{
			gfx.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, float(height) / float(width), 0.5f, 100.0f));
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
		void WindowActivationChanged(int)
		{

		}
	private:
		void Render()
		{
			gfx.SetCamera(cam.GetViewMatrix());
			light.Bind(gfx, cam.GetViewMatrix());
			float dt = 0.05f;
			panel.Step(gfx, dt);

			gfx.StartFrame();
			{
				auto pass = gfx.StartPass();
				light.Submit(pass);
				panel.Submit(pass);
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
		//Model x;
		Panel panel;

		bool bWindowClosed = false;
		bool bVisible = true;
		PointLight light;
		//Triangle tri;
	};
}