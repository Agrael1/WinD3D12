#include "pch.h"
#include "Graphics.h"
#include "Shader.h"

ver::Graphics::Graphics(uint32_t width, uint32_t height, XWindow wnd)
	:width(width), height(height)
{
	winrt::check_hresult(VFactory::CreateDevice(&device));
	renderQueue = device.GetDefaultQueue();
	winrt::check_hresult(VFactory::CreateSwapChain(&swap, device, wnd));
	swap.Configure(VFactory::GetSwapChainFormat(), wgpu::TextureUsage::OutputAttachment,
		width, height);
}

