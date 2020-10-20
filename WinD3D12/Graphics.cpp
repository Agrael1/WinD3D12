#include "pch.h"
#include "Graphics.h"

ver::Graphics::Graphics(uint32_t width, uint32_t height, XWindow wnd)
	:width(width), height(height)
{
	winrt::check_hresult(VFactory::CreateDevice(&device));
	renderQueue = device.GetDefaultQueue();
	winrt::check_hresult(VFactory::CreateSwapChain(&swap, device, wnd));
	swap.Configure(VFactory::GetSwapChainFormat(), wgpu::TextureUsage::OutputAttachment,
		width, height);

	colorDesc.attachment = swap.GetCurrentTextureView();
	colorDesc.loadOp = wgpu::LoadOp::Clear;
	colorDesc.storeOp = wgpu::StoreOp::Store;
	colorDesc.clearColor.r = 0.3f;
	colorDesc.clearColor.g = 0.3f;
	colorDesc.clearColor.b = 0.3f;
	colorDesc.clearColor.a = 1.0f;
}

void ver::Graphics::Present()
{
	swap.Present();
	colorDesc.attachment = swap.GetCurrentTextureView();
}
void ver::Graphics::ClearRenderTarget(wgpu::Color c)
{
	colorDesc.clearColor = c;
}

