#include "pch.h"
#include "App.h"

IFrameworkView App::CreateView()
{
    return *this;
}
void App::Initialize(const CoreApplicationView& appView)
{
    appView.Activated({ this, &App::OnActivated });
    CoreApplication::Suspending({ this, &App::OnSuspending });
    CoreApplication::Resuming({ this, &App::OnResuming });
}
void App::SetWindow(const CoreWindow& window)
{
    window.Activate();

    window.PointerCursor(CoreCursor(CoreCursorType::Arrow, 0));

    UI::Input::PointerVisualizationSettings visualizationSettings
    { 
        UI::Input::PointerVisualizationSettings::GetForCurrentView() 
    };
    visualizationSettings.IsContactFeedbackEnabled(false);
    visualizationSettings.IsBarrelButtonFeedbackEnabled(false);
    
    auto rect = window.Bounds();
    engine.emplace(uint32_t(rect.Width), uint32_t(rect.Height), window); //workflow independent values

    window.Activated({ this, &App::OnWindowActivationChanged });
    window.SizeChanged({ this, &App::OnWindowSizeChanged });
    window.Closed({ this, &App::OnWindowClosed });
    window.VisibilityChanged({ this, &App::OnVisibilityChanged });

    DisplayInformation currentDisplayInformation{ DisplayInformation::GetForCurrentView() };
    currentDisplayInformation.DpiChanged({ this, &App::OnDpiChanged });
    currentDisplayInformation.OrientationChanged({ this, &App::OnOrientationChanged });
    currentDisplayInformation.StereoEnabledChanged({ this, &App::OnStereoEnabledChanged });

    DisplayInformation::DisplayContentsInvalidated({ this, &App::OnDisplayContentsInvalidated });
    rWindow = window;
}
void App::Load(hstring const&)
{
}
void App::Uninitialize()
{

}
void App::Run()
{
    CoreDispatcher dispatcher = rWindow.get().Dispatcher();
    while (1)
    {
        dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
        engine->Run();
    }
}


void App::OnActivated(const CoreApplicationView&, const IActivatedEventArgs&)
{
    rWindow.get().Activate();
}
winrt::fire_and_forget App::OnSuspending(const IInspectable&, const SuspendingEventArgs& args)
{
    auto lifetime = get_strong();

    // Save app state asynchronously after requesting a deferral. Holding a deferral
    // indicates that the application is busy performing suspending operations. Be
    // aware that a deferral may not be held indefinitely. After about five seconds,
    // the app will be forced to exit.
    SuspendingDeferral deferral = args.SuspendingOperation().GetDeferral();

    co_await winrt::resume_background();
    engine->Suspend();

    deferral.Complete();
}
void App::OnResuming(const IInspectable&, const IInspectable&)
{
    
}

void App::OnWindowActivationChanged(const CoreWindow&, const WindowActivatedEventArgs& args)
{
    engine->WindowActivationChanged(args.WindowActivationState());
}
void App::OnWindowSizeChanged(const CoreWindow&, const WindowSizeChangedEventArgs&)
{
}
void App::OnWindowClosed(const CoreWindow&, const CoreWindowEventArgs&)
{
    engine->Close(); //does not work :(
}
void App::OnVisibilityChanged(const CoreWindow&, const VisibilityChangedEventArgs& args)
{
    engine->Visibility(args.Visible());
}

//Maybe in future :D
void App::OnDpiChanged(const DisplayInformation&, const IInspectable&)
{
}
void App::OnOrientationChanged(const DisplayInformation&, const IInspectable&)
{
}
void App::OnStereoEnabledChanged(const DisplayInformation&, const IInspectable&)
{
}
void App::OnDisplayContentsInvalidated(const DisplayInformation&, const IInspectable&)
{
}
