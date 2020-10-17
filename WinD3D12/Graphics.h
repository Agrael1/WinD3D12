#pragma once
#include "DawnAdapter.h"

namespace ver
{
	class Graphics
	{
	public:
		Graphics(uint32_t width, uint32_t height, XWindow wnd);
	private:
		wgpu::Device device;
		wgpu::SwapChain swap;
		wgpu::Queue renderQueue;
		uint32_t width;
		uint32_t height;
	};
}