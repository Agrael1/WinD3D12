#pragma once
#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu_cpp.h>
#include "App.h"
using XWindow = const CoreWindow&;
#endif




namespace VFactory
{
	HRESULT CreateDevice(wgpu::Device* _out_ppDevice, wgpu::BackendType type = wgpu::BackendType::D3D12);
	HRESULT CreateSwapChain(wgpu::SwapChain* _out_ppSwap, wgpu::Device device, XWindow hWnd);
	wgpu::TextureFormat GetSwapChainFormat();
}