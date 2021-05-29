#include "VeritasEngine.h"
#include "InputController.h"
#include <optional>

class App : public implements<App, IFrameworkViewSource, IFrameworkView>
{
    struct Internal
    {
        Internal(uint32_t Width, uint32_t Height, const CoreWindow& window)
            :engine(Width, Height, window)
        {}
        ver::VeritasEngine engine;
    };
public:
    void Initialize(const CoreApplicationView& appView);
    void SetWindow(const CoreWindow& window);
    void Load(hstring const&);

    void Uninitialize();
    void Run();
    IFrameworkView CreateView();
public: //events
    void OnActivated(const CoreApplicationView&, 
        const IActivatedEventArgs& );
    winrt::fire_and_forget OnSuspending(const IInspectable&,
        const SuspendingEventArgs& args);
    void OnResuming(const IInspectable&,const IInspectable&);
    void OnWindowActivationChanged(const CoreWindow&, const WindowActivatedEventArgs& args);
    void OnWindowSizeChanged(const CoreWindow& wnd, const WindowSizeChangedEventArgs& args);
    void OnWindowClosed(const CoreWindow& wnd, const CoreWindowEventArgs& args);
    void OnVisibilityChanged(const CoreWindow& wnd, const VisibilityChangedEventArgs& args);
    void OnDpiChanged(const DisplayInformation& sender, const IInspectable& args);
    void OnOrientationChanged(const DisplayInformation& sender, const IInspectable& args);
    void OnStereoEnabledChanged(const DisplayInformation& sender, const IInspectable& args);
    void OnDisplayContentsInvalidated(const DisplayInformation& sender, const IInspectable& args);
private:
    std::optional<Internal> i;
    winrt::agile_ref<CoreWindow> rWindow;
};