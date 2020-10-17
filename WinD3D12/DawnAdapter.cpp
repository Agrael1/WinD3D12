#include "pch.h"
#include "DawnAdapter.h"

#if __has_include("d3d12.h") || (_MSC_VER >= 1900)
#define DAWN_ENABLE_BACKEND_D3D12
#endif
#if __has_include("vulkan/vulkan.h") && (defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64))
#define DAWN_ENABLE_BACKEND_VULKAN
#endif

#include <dawn/dawn_proc.h>
#include <dawn/webgpu_cpp.h>
#include <dawn_native/NullBackend.h>
#ifdef DAWN_ENABLE_BACKEND_D3D12
#include <dawn_native/WebGPUWinRT.h>
#elif DAWN_ENABLE_BACKEND_VULKAN
#include <dawn_native/VulkanBackend.h>
#include <vulkan/vulkan_win32.h>
#endif

#ifdef DAWN_ENABLE_BACKEND_VULKAN
#pragma comment(lib, "vulkan-1.lib")
#endif


class VAdapter
{
	class Once
	{
	public:
		Once(bool& in) :guard(in) {};
		~Once() { guard = false; };
	private:
		bool& guard;
	};
private:
	VAdapter() = default;
	~VAdapter()
	{
		swapImpl.Destroy(swapImpl.userData);
	}
public:
	[[nodiscard]]dawn_native::Adapter QueryAdapter(wgpu::BackendType type1st, wgpu::BackendType type2nd = wgpu::BackendType::Null)
	{
		if (!once) return adapter;
		Once on{ once };

		static dawn_native::Instance instance;
		instance.DiscoverDefaultAdapters();
		wgpu::AdapterProperties properties;

		dawn_native::Adapter Fallback;
		std::vector<dawn_native::Adapter> adapters = instance.GetAdapters();
		for (auto it : adapters)
		{
			it.GetProperties(&properties);
			if (properties.backendType == type1st)
			{
				return adapter = it;
			}

			if (properties.backendType == type2nd)
				Fallback = it;
		}
		if (type2nd != wgpu::BackendType::Null)
		{
			return adapter = Fallback;
		}
		return adapter = dawn_native::Adapter();
	}
	uint64_t InitSwapChain(WGPUDevice device, XWindow window)
	{
		switch (wgpu::BackendType(adapter.GetBackendType()))
		{
#ifdef DAWN_ENABLE_BACKEND_D3D12
		case wgpu::BackendType::D3D12:
			if (swapImpl.userData == nullptr)
			{
				swapImpl = dawn_native::d3d12::win_rt::CreateNativeSwapChainImpl(
					device, window);
				swapFormat = wgpu::TextureFormat(dawn_native::d3d12::GetNativeSwapChainPreferredFormat(&swapImpl));
			}
			break;
#endif
#ifdef DAWN_ENABLE_BACKEND_VULKAN
		case wgpu::BackendType::Vulkan:
			if (swapImpl.userData == nullptr)
			{
				swapImpl = dawn_native::vulkan::CreateNativeSwapChainImpl(
					device, createVkSurface(device, window));
				swapFormat = wgpu::TextureFormat(dawn_native::vulkan::GetNativeSwapChainPreferredFormat(&swapImpl));
			}
			break;
#endif
		default:
			if (swapImpl.userData == nullptr)
			{
				swapImpl = dawn_native::null::CreateNativeSwapChainImpl();
				swapFormat = wgpu::TextureFormat::Undefined;
			}
			break;
		}
		return reinterpret_cast<uint64_t>(&swapImpl);
	}
	wgpu::TextureFormat GetSwapFormat()const
	{
		return swapFormat;
	}
public:
	static VAdapter& Get()
	{
		return xadapt;
	}
	operator dawn_native::Adapter()
	{
		return adapter;
	}
private:
	bool once = true;
	dawn_native::Adapter adapter;
	DawnSwapChainImplementation swapImpl{}; //unsafe shit
	wgpu::TextureFormat swapFormat = wgpu::TextureFormat::Undefined;
	static VAdapter xadapt;
};
VAdapter VAdapter::xadapt;

HRESULT VFactory::CreateDevice(wgpu::Device* _out_ppDevice, wgpu::BackendType type)
{
	auto adapter = VAdapter::Get().QueryAdapter(type);
	*_out_ppDevice = wgpu::Device::Acquire(adapter.CreateDevice());
	return S_OK;
}
HRESULT VFactory::CreateSwapChain(wgpu::SwapChain* _out_ppSwap, wgpu::Device device, XWindow hWnd)
{
	wgpu::SwapChainDescriptor swapChainDesc;
	swapChainDesc.implementation = VAdapter::Get().InitSwapChain(device.Get(), hWnd);
	*_out_ppSwap = device.CreateSwapChain(nullptr, &swapChainDesc);
	return E_NOTIMPL;
}
wgpu::TextureFormat VFactory::GetSwapChainFormat()
{
	return VAdapter::Get().GetSwapFormat();
}