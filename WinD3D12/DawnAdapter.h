#pragma once
#ifndef VERITAS_EXPORT
#define VERITAS_EXPORT
#endif // !VERITAS_EXPORT


#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu_cpp.h>

namespace winrt::Windows::UI::Core
{
	struct CoreWindow;
}

VERITAS_EXPORT using XWindow = winrt::Windows::UI::Core::CoreWindow;
VERITAS_EXPORT using VRESULT = long;
#endif




VERITAS_EXPORT namespace VFactory
{
	VRESULT CreateDevice(wgpu::Device* _out_ppDevice, wgpu::BackendType type = wgpu::BackendType::D3D12);
	VRESULT CreateSwapChain(wgpu::SwapChain* _out_ppSwap, wgpu::Device device, const XWindow& hWnd);
	wgpu::TextureFormat GetSwapChainFormat();
}