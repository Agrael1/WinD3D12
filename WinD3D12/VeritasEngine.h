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
		VeritasEngine(uint32_t width, uint32_t height, const XWindow& wnd);
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
		void ProcessInput(float dt);
		void Render();
		winrt::fire_and_forget ReloadModelAsync();
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

		enum class CamState
		{
			Regular,
			FreeCam,
			Orbit
		}camst;
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