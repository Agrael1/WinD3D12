#include "pch.h"
#include <dawn_native/WebGPUWinRT.h>

struct
    __declspec(uuid("45D64A29-A63E-4CB6-B498-5781D298CB4F"))
    __declspec(novtable)
    ICoreWindowInterop : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE get_WindowHandle(HWND* hwnd) = 0;
    virtual HRESULT STDMETHODCALLTYPE put_MessageHandled(unsigned char value) = 0;
};

namespace dawn_native {
    namespace d3d12 {
        namespace win_rt
        {
            winrt::com_ptr<ID3D12Device> GetD3D12Device(WGPUDevice device) 
            {
                return { dawn_native::d3d12::GetD3D12Device(device).Detach(), winrt::take_ownership_from_abi };
            }
            DawnSwapChainImplementation CreateNativeSwapChainImpl(WGPUDevice device, const CoreWindow& wnd) 
            {
                winrt::com_ptr<ICoreWindowInterop> interop{};
                winrt::check_hresult(winrt::get_unknown(wnd)->QueryInterface(interop.put()));
                HWND hwnd{};
                winrt::check_hresult(interop->get_WindowHandle(&hwnd));
               
                return dawn_native::d3d12::CreateNativeSwapChainImpl(device, hwnd);
            }
            AdapterDiscoveryOptions::AdapterDiscoveryOptions(winrt::com_ptr<IDXGIAdapter> adapter)
                : AdapterDiscoveryOptionsBase(WGPUBackendType_D3D12), dxgiAdapter(std::move(adapter)) {}
        }
    }
}  // namespace dawn_native::d3d12
