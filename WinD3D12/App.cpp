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
    
    //m_deviceResources->SetWindow(window);

    window.Activated({ this, &App::OnWindowActivationChanged });
    window.SizeChanged({ this, &App::OnWindowSizeChanged });
    window.Closed({ this, &App::OnWindowClosed });
    window.VisibilityChanged({ this, &App::OnVisibilityChanged });

    DisplayInformation currentDisplayInformation{ DisplayInformation::GetForCurrentView() };
    currentDisplayInformation.DpiChanged({ this, &App::OnDpiChanged });
    currentDisplayInformation.OrientationChanged({ this, &App::OnOrientationChanged });
    currentDisplayInformation.StereoEnabledChanged({ this, &App::OnStereoEnabledChanged });

    DisplayInformation::DisplayContentsInvalidated({ this, &App::OnDisplayContentsInvalidated });
}
void App::Load(hstring const&)
{
}
void App::Uninitialize()
{

}
void App::Run()
{
}



void App::OnActivated(const CoreApplicationView&, const IActivatedEventArgs&)
{
    CoreWindow::GetForCurrentThread().Activate();
}
winrt::fire_and_forget App::OnSuspending(const IInspectable&, const SuspendingEventArgs& args)
{
    return winrt::fire_and_forget();
}

void App::OnResuming(const IInspectable&, const IInspectable&)
{
}

void App::OnWindowActivationChanged(const CoreWindow&, const WindowActivatedEventArgs& args)
{
}

void App::OnWindowSizeChanged(const CoreWindow& wnd, const WindowSizeChangedEventArgs& args)
{
}

void App::OnWindowClosed(const CoreWindow& wnd, const CoreWindowEventArgs& args)
{
}

void App::OnVisibilityChanged(const CoreWindow& wnd, const VisibilityChangedEventArgs& args)
{
}

void App::OnDpiChanged(const DisplayInformation& sender, const IInspectable& args)
{
}

void App::OnOrientationChanged(const DisplayInformation& sender, const IInspectable& args)
{
}

void App::OnStereoEnabledChanged(const DisplayInformation& sender, const IInspectable& args)
{
}

void App::OnDisplayContentsInvalidated(const DisplayInformation& sender, const IInspectable& args)
{
}
