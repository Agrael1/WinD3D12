#include "pch.h"
#include "VeritasEngine.h"

ver::VeritasEngine::VeritasEngine(uint32_t width, uint32_t height, const XWindow& wnd)
	:gfx(width, height, wnd), light(gfx, 0.1f),
	panel(gfx), input(wnd)
{
	gfx.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, float(height) / float(width), 0.5f, 100.0f));
}

void ver::VeritasEngine::ProcessInput(float dt)
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
				camst = CamState::FreeCam;
				bFreeCam = true;
				input.HideCursor();
				input.mouse.EnableRaw();
			}
			else
			{
				camst = CamState::Regular;
				bFreeCam = false;
				input.ShowCursor();
				input.mouse.DisableRaw();
			}
			break;
		case 'L':
			bL = true;
			break;
		case VK_ESCAPE:
			if (camst == CamState::FreeCam)
			{
				camst = CamState::Regular;
				input.ShowCursor();
				input.mouse.DisableRaw();
				break;
			}
			input.CommandClose();
			return;
		}
	}
	while (const auto e = input.mouse.Read())
	{
		switch (e->GetType())
		{
		case Mouse::Event::Type::LPress:
			break;
		case Mouse::Event::Type::LRelease:
			break;
		case Mouse::Event::Type::RPress:
			if (camst == CamState::Regular)
			{
				camst = CamState::Orbit;
				input.HideCursor();
				input.mouse.EnableRaw();
			}
			break;
		case Mouse::Event::Type::RRelease:
			if (camst == CamState::Orbit)
			{
				camst = CamState::Regular;
				input.ShowCursor();
				input.mouse.DisableRaw();
			}
			break;
		case Mouse::Event::Type::WheelUp:
			break;
		case Mouse::Event::Type::WheelDown:
			break;
		case Mouse::Event::Type::Move:
			break;
		case Mouse::Event::Type::Enter:
			break;
		case Mouse::Event::Type::Leave:
			break;
		default:
			break;
		}
	}

	if (camst == CamState::FreeCam)
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

		if (input.kbd.KeyIsPressed(VK_NUMPAD5))
		{
			light.Translate({ 0.0f,0.0f,dt });
		}
		if (input.kbd.KeyIsPressed(VK_NUMPAD4))
		{
			light.Translate({ -dt,0.0f,0.0f });
		}
		if (input.kbd.KeyIsPressed(VK_NUMPAD0))
		{
			light.Translate({ 0.0f,0.0f,-dt });
		}
		if (input.kbd.KeyIsPressed(VK_NUMPAD6))
		{
			light.Translate({ dt,0.0f,0.0f });
		}
		if (input.kbd.KeyIsPressed(VK_NUMPAD8))
		{
			light.Translate({ 0.0f,dt,0.0f });
		}
		if (input.kbd.KeyIsPressed(VK_NUMPAD2))
		{
			light.Translate({ 0.0f,-dt,0.0f });
		}
	}


	while (const auto delta = input.mouse.ReadRawDelta())
	{
		switch (camst)
		{
		case ver::VeritasEngine::CamState::FreeCam:
			cam.Rotate((float)delta->x, (float)delta->y);
			break;
		case ver::VeritasEngine::CamState::Orbit:
			cam.Orbit((float)delta->x, (float)delta->y);
			break;
		case ver::VeritasEngine::CamState::Regular:
		default:
			break;
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

void ver::VeritasEngine::Render()
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

winrt::fire_and_forget ver::VeritasEngine::ReloadModelAsync()
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
