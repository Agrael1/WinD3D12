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
			:gfx(width, height, wnd), light(gfx, 0.1f),/* tri(gfx),*/
			panel(gfx), input(wnd)
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
				case 'L':
					bL = true;
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
				if (input.kbd.KeyIsPressed(VK_CONTROL))
				{
					dt /= 2;
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

			if (bL)
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
					x.reset(swap.release());
					state = Unloaded;
					bL = false;
					break;
				}
				default:break;
				}
			}
		}
		void Render()
		{
			if (state == ModelLoadState::InProgress)return;
			float dt = 0.05f;
			ProcessInput(dt);

			gfx.SetCamera(cam.GetViewMatrix());
			light.Bind(gfx, cam.GetViewMatrix());
			if (x)x->Step(gfx, dt);
			panel.Step(gfx, dt);

			gfx.StartFrame();
			{
				auto pass = gfx.StartPass();
				light.Submit(pass);
				if (x)x->Submit(pass);
				panel.Submit(pass);
			}
			gfx.Present();
		}
		winrt::fire_and_forget ReloadModelAsync()
		{
			co_await winrt::resume_background();
			//auto wfilename = L"Assets\\GoblinX.obj";
			//if (!wfilename.empty())
			{
				co_await Model::MakeAsync(swap, gfx, "Assets\\brick_wall.obj");

				//if (!swap) MessageBox(nullptr, "Model file was corrupted or empty",
					//"Model Exception", MB_OK | MB_ICONEXCLAMATION);
			}
			state = ModelLoadState::Finish;
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
		std::unique_ptr<Model> x, swap;
		Panel panel;

		bool bFreeCam = false;
		bool bVisible = true;
		PointLight light;
		//Triangle tri;

		enum class ModelLoadState : uint8_t
		{
			Unloaded,
			InProgress,
			Finish
		};
		std::atomic<ModelLoadState> state = ModelLoadState::Unloaded;
		bool bL = false;
	};
}