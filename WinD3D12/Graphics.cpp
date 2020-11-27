#include "pch.h"
#include "DawnAdapter.h"
#include "Graphics.h"

void ErrorCallback(WGPUErrorType type, char const* message, void* userdata)
{
	if (0);
}

ver::Graphics::Graphics(uint32_t width, uint32_t height, const XWindow& wnd)
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
	device.SetUncapturedErrorCallback(ErrorCallback, nullptr);
}

void ver::Graphics::Present()
{
	commands = encoder.Finish();				// create commands
	renderQueue.Submit(1, &commands);
	swap.Present();
	colorDesc.attachment = swap.GetCurrentTextureView();
}
void ver::Graphics::ClearRenderTarget(wgpu::Color c)
{
	colorDesc.clearColor = c;
}

DirectX::XMMATRIX ver::Graphics::GetCamera() const noexcept
{
	return camera;
}

void ver::Graphics::SetCamera(DirectX::XMMATRIX Camera) noexcept
{
	camera = Camera;
}

void ver::Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX ver::Graphics::GetProjection() const noexcept
{
	return projection;
}
wgpu::TextureFormat ver::Graphics::GetSwapChainFormat()noexcept
{
	return VFactory::GetSwapChainFormat();
}