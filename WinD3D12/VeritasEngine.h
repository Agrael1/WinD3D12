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
		void Test()
		{
			tri.Step(gfx);
			wgpu::RenderPassDescriptor renderPass = {};
			renderPass.colorAttachmentCount = 1;
			renderPass.colorAttachments = &gfx.colorDesc;

			wgpu::CommandEncoder encoder = gfx.device.CreateCommandEncoder(nullptr);			// create encoder
			{
				wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPass);	// create pass
				tri.Submit(pass);
				pass.EndPass();
			}

			commands = encoder.Finish(nullptr);				// create commands
			gfx.renderQueue.Submit(1, &commands);

			gfx.Present();
		}
	public:
		void Run()
		{
			if (bVisible)
				Test();
		}
	private:
		Graphics gfx;
		Camera cam;

		wgpu::CommandBuffer commands;
		bool bWindowClosed = false;
		bool bVisible = true;
		Triangle tri;
	};
}