#pragma once
#include "DawnAdapter.h"

namespace ver
{
	class Graphics
	{
		friend class Bindable;
	public:
		struct RenderPass : public wgpu::RenderPassEncoder
		{
			RenderPass(wgpu::RenderPassEncoder&& in)
				:wgpu::RenderPassEncoder(std::forward<wgpu::RenderPassEncoder&&>(in))
			{}
			~RenderPass()
			{
				this->EndPass();
			}
		};
	public:
		Graphics(uint32_t width, uint32_t height, XWindow wnd);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
	public:
		void Present();
		void StartFrame()
		{
			encoder = device.CreateCommandEncoder(nullptr);			// create encoder
		}
		RenderPass StartPass()
		{
			wgpu::RenderPassDescriptor renderPass = {};
			renderPass.colorAttachmentCount = 1;
			renderPass.colorAttachments = &colorDesc;


			return encoder.BeginRenderPass(&renderPass);
		}
		void ClearRenderTarget(wgpu::Color c);
	private:
		wgpu::Device device;
		wgpu::SwapChain swap;
		wgpu::Queue renderQueue;
		wgpu::CommandEncoder encoder;
		wgpu::CommandBuffer commands;
	private:
		wgpu::RenderPassColorAttachmentDescriptor colorDesc = {};//unites rtv with data, maybe will be in its onw bindable
		uint32_t width;
		uint32_t height;
	};
}