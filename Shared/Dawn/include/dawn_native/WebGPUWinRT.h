#pragma once
#include <dawn/dawn_wsi.h>
#include <dawn_native/DawnNative.h>
#include <dawn_native/D3D12Backend.h>
#include <DXGI1_4.h>

struct ID3D12Device;

using namespace winrt::Windows::UI::Core;

namespace dawn_native 
{
    namespace d3d12
    {
        namespace win_rt
        {
            DAWN_NATIVE_EXPORT winrt::com_ptr<ID3D12Device> GetD3D12Device(WGPUDevice device);
            DAWN_NATIVE_EXPORT DawnSwapChainImplementation CreateNativeSwapChainImpl(WGPUDevice device,
                const CoreWindow& wnd);

            struct DAWN_NATIVE_EXPORT AdapterDiscoveryOptions : public AdapterDiscoveryOptionsBase
            {
                AdapterDiscoveryOptions(winrt::com_ptr<IDXGIAdapter> adapter);

                winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
            };
        }
    }
}  // namespace dawn_native::d3d12
