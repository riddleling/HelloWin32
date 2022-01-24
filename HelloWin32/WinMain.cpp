#include "pch.h"
#include "Window.h"

using namespace winrt;
using namespace Windows::Foundation;

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE,
    _In_ LPWSTR,
    _In_ int)
{
    init_apartment(apartment_type::single_threaded);

    auto window = std::make_unique<Window>(hInstance, L"MainWindow", L"Window");
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}