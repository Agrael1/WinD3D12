#pragma once
#include "Camera.h"
#include "PointLight.h"
#include "Model.h"
#include "Panel.h"
#include "InputController.h"

namespace ver
{
	class VeritasEngine
	{
	public:
		VeritasEngine(uint32_t width, uint32_t height, const XWindow& wnd)
			:gfx(width, height, wnd), light(gfx, 0.5f),/* tri(gfx),*/
			panel(gfx), input(wnd)
			/*x(gfx, "Assets\\GoblinX.obj")*/
		{
			gfx.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, float(height) / float(width), 0.5f, 100.0f));
		}
	public:
		void Close()
		{
			
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
		InputController& GetController()
		{
			return input;
		}
	private:
		void ProcessInput(float dt)
		{
			while (const auto e = input.kbd.ReadKey())
			{
				if (!e->IsPress())
				{
					continue;
				}

				switch (e->GetCode())
				{
				case 'F':
				case VK_INSERT:
					if (input.CursorEnabled())
					{
						bFreeCam = true;
						input.HideCursor();
						input.mouse.EnableRaw();
					}
					else
					{
						bFreeCam = false;
						input.ShowCursor();
						input.mouse.DisableRaw();
					}
					break;
				case VK_ESCAPE:
					if (bFreeCam)
					{
						bFreeCam = false;
						input.ShowCursor();
						input.mouse.DisableRaw();
						break;
					}
					input.CommandClose();
					return;
				}
			}

			if (!input.CursorEnabled())
			{
				if (input.kbd.KeyIsPressed(VK_SHIFT))
				{
					dt *= 2;
				}
				if (input.kbd.KeyIsPressed('W'))
				{
					cam.Translate({ 0.0f,0.0f,dt });
				}
				if (input.kbd.KeyIsPressed('A'))
				{
					cam.Translate({ -dt,0.0f,0.0f });
				}
				if (input.kbd.KeyIsPressed('S'))
				{
					cam.Translate({ 0.0f,0.0f,-dt });
				}
				if (input.kbd.KeyIsPressed('D'))
				{
					cam.Translate({ dt,0.0f,0.0f });
				}
				if (input.kbd.KeyIsPressed(VK_SPACE))
				{
					cam.Translate({ 0.0f,dt,0.0f });
				}
				if (input.kbd.KeyIsPressed('C'))
				{
					cam.Translate({ 0.0f,-dt,0.0f });
				}
			}
			
			while (const auto delta = input.mouse.ReadRawDelta())
			{
				if (!input.CursorEnabled())
				{
					cam.Rotate((float)delta->x, (float)delta->y);
				}
			}
			/*
			if (wnd.LoadCalled())
			{
				switch (state)
				{
					using enum ModelLoadState;
				case Unloaded:
					state = InProgress;
					ReloadModelAsync();
					break;
				case Finish:
				{
					model.reset(swap.release());
					Codex::Trim();
					if (model)
						model->LinkTechniques(*rg);
					modelProbe.Reset();
					state = Unloaded;
					wnd.LoadingComplete();
					break;
				}
				default:break;
				}
			}*/
		}
		void Render()
		{
			float dt = 0.05f;
			ProcessInput(dt);

			gfx.SetCamera(cam.GetViewMatrix());
			light.Bind(gfx, cam.GetViewMatrix());
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
		InputController input;
		Graphics gfx;
		Camera cam;
		//Model x;
		Panel panel;

		bool bFreeCam = false;
		bool bVisible = true;
		PointLight light;
		//Triangle tri;
	};
}