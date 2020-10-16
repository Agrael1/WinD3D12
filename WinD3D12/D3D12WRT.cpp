#include "pch.h"
#include "D3D12WRT.h"
#include <dawn/webgpu_cpp.h>
#include <d3d11_2.h>
#include <d3d11on12.h>
#include <d3d12.h>

template <typename T>
DawnSwapChainImplementation CreateSwapChainImplementation(T* swapChain) 
{
    DawnSwapChainImplementation impl = {};
    impl.userData = swapChain;
    impl.Init = [](void* userData, void* wsiContext) {
        auto* ctx = static_cast<typename T::WSIContext*>(wsiContext);
        reinterpret_cast<T*>(userData)->Init(ctx);
    };
    impl.Destroy = [](void* userData) { delete reinterpret_cast<T*>(userData); };
    impl.Configure = [](void* userData, WGPUTextureFormat format, WGPUTextureUsage allowedUsage,
        uint32_t width, uint32_t height) {
            return static_cast<T*>(userData)->Configure(format, allowedUsage, width, height);
    };
    impl.GetNextTexture = [](void* userData, DawnSwapChainNextTexture* nextTexture) {
        return static_cast<T*>(userData)->GetNextTexture(nextTexture);
    };
    impl.Present = [](void* userData) { return static_cast<T*>(userData)->Present(); };
    return impl;
}


//DawnSwapChainError Configure(WGPUTextureFormat format,
//    WGPUTextureUsage usage,
//    uint32_t width,
//    uint32_t height) 
//{
//    ASSERT(width > 0);
//    ASSERT(height > 0);
//    ASSERT(format == static_cast<WGPUTextureFormat>(GetPreferredFormat()));
//
//    winrt::com_ptr<IDXGIFactory4> factory = mDevice->GetFactory();
//    winrt::com_ptr<ID3D12CommandQueue> queue = mDevice->GetCommandQueue();
//
//    mInterval = mDevice->IsToggleEnabled(Toggle::TurnOffVsync) == true ? 0 : 1;
//
//    // Create the D3D12 swapchain, assuming only two buffers for now
//    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
//    swapChainDesc.Width = width;
//    swapChainDesc.Height = height;
//    swapChainDesc.Format = D3D12TextureFormat(GetPreferredFormat());
//    swapChainDesc.BufferUsage = D3D12SwapChainBufferUsage(usage);
//    swapChainDesc.BufferCount = kFrameCount;
//    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//    swapChainDesc.SampleDesc.Count = 1;
//    swapChainDesc.SampleDesc.Quality = 0;
//
//    winrt::com_ptr<IDXGISwapChain1> swapChain1;
//    ASSERT_SUCCESS(factory->CreateSwapChainForHwnd(queue.Get(), mWindow, &swapChainDesc,
//        nullptr, nullptr, &swapChain1));
//
//    ASSERT_SUCCESS(swapChain1.As(&mSwapChain));
//
//    // Gather the resources that will be used to present to the swapchain
//    mBuffers.resize(kFrameCount);
//    for (uint32_t i = 0; i < kFrameCount; ++i) {
//        ASSERT_SUCCESS(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mBuffers[i])));
//    }
//
//    // Set the initial serial of buffers to 0 so that we don't wait on them when they are first
//    // used
//    mBufferSerials.resize(kFrameCount, 0);
//
//    return DAWN_SWAP_CHAIN_NO_ERROR;
//}
