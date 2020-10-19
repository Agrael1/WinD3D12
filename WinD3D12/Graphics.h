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
	private:
		wgpu::Device device;
		wgpu::SwapChain swap;
		wgpu::Queue renderQueue;
		uint32_t width;
		uint32_t height;
	};
}