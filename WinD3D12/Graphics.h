#pragma once
#include "DawnAdapter.h"
#include <optional>

namespace ver
{
	class Graphics
	{
		friend class Bindable;
	public:
		Graphics(uint32_t width, uint32_t height, XWindow wnd);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
	public:
		void Present();
		void ClearRenderTarget(wgpu::Color c);
	public:
		wgpu::Device device;
		wgpu::SwapChain swap;
		wgpu::Queue renderQueue;
	public:
		wgpu::RenderPassColorAttachmentDescriptor colorDesc = {};//unites rtv with data, maybe will be in its onw bindable
		uint32_t width;
		uint32_t height;
	};
}