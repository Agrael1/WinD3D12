#pragma once
#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu_cpp.h>
#include "App.h"
#endif



namespace VFactory
{
	HRESULT CreateDevice(wgpu::Device* _out_ppDevice, wgpu::BackendType type = wgpu::BackendType::D3D12);
	HRESULT CreateSwapChainForHWND(wgpu::SwapChain* _out_ppSwap, wgpu::SwapChainDescriptor* swapDesc, wgpu::Device device, HWND hWnd);
	WGPUTextureFormat getSwapChainFormat(WGPUDevice device);
}