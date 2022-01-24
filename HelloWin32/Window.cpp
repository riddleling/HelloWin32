#include "pch.h"
#include "Window.h"

#define ID_LABEL   10
#define ID_BUTTON  11

Window::Window(HINSTANCE hInstance, LPCWSTR lpszClassName, LPCWSTR lpWindowName)
{
    hLabel_  = nullptr;
    hButton_ = nullptr;

    WNDCLASSW wc{};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = lpszClassName;
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName = nullptr;
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassW(&wc);

    hWnd_ = CreateWindowExW(
        0,
        wc.lpszClassName,
        lpWindowName,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 0, 0,
        nullptr,
        nullptr,
        hInstance,
        this
    );

    ShowWindow(hWnd_, SW_SHOWNORMAL);
    EnumChildWindows(hWnd_, EnumChildProc, 0);
    UpdateWindow(hWnd_);
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* pThis = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->hWnd_ = hwnd;
    }
    else {
        LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pThis = reinterpret_cast<Window*>(ptr);
    }

    switch (msg) {
    case WM_CREATE: {
        pThis->SetWindowSize();

        pThis->hLabel_ = CreateWindowW(
            L"static",
            L"This is a label.",
            WS_VISIBLE | WS_CHILD,
            0, 0, 0, 0,
            hwnd,
            (HMENU)ID_LABEL,
            nullptr,
            nullptr
        );
        if (pThis->hLabel_) {
            pThis->SetLabelPos();
        }

        pThis->hButton_ = CreateWindowW(
            L"Button",
            L"Say hello",
            WS_VISIBLE | WS_CHILD,
            0, 0, 0, 0,
            hwnd,
            (HMENU)ID_BUTTON,
            nullptr,
            nullptr
        );
        if (pThis->hButton_) {
            pThis->SetButtonPos();
        }
    } break;
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BUTTON) {
            pThis->SayHello();
        }
    } break;
    case WM_DESTROY: {
        PostQuitMessage(0);
    } break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

BOOL CALLBACK Window::EnumChildProc(HWND hWnd, LPARAM)
{
    HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));
    return TRUE;
}

void Window::SetWindowSize()
{
    int dpi = GetDpiForWindow(hWnd_);
    int dpiScaledX = MulDiv(100, dpi, 96);
    int dpiScaledY = MulDiv(100, dpi, 96);
    int dpiScaledW = MulDiv(400, dpi, 96);
    int dpiScaledH = MulDiv(300, dpi, 96);
    SetWindowPos(
        hWnd_,
        hWnd_,
        dpiScaledX,
        dpiScaledY,
        dpiScaledW,
        dpiScaledH,
        SWP_NOZORDER | SWP_NOACTIVATE
    );
}

void Window::SetLabelPos()
{
    int dpi = GetDpiForWindow(hWnd_);
    int dpiScaledX = MulDiv(40, dpi, 96);
    int dpiScaledY = MulDiv(40, dpi, 96);
    int dpiScaledW = MulDiv(200, dpi, 96);
    int dpiScaledH = MulDiv(30, dpi, 96);

    SetWindowPos(
        hLabel_,
        hLabel_,
        dpiScaledX,
        dpiScaledY,
        dpiScaledW,
        dpiScaledH,
        SWP_NOZORDER | SWP_NOACTIVATE
    );
}

void Window::SetButtonPos()
{
    int dpi = GetDpiForWindow(hWnd_);
    int dpiScaledX = MulDiv(40, dpi, 96);
    int dpiScaledY = MulDiv(80, dpi, 96);
    int dpiScaledW = MulDiv(100, dpi, 96);
    int dpiScaledH = MulDiv(28, dpi, 96);

    SetWindowPos(
        hButton_,
        hButton_,
        dpiScaledX,
        dpiScaledY,
        dpiScaledW,
        dpiScaledH,
        SWP_NOZORDER | SWP_NOACTIVATE
    );
}

void Window::SayHello()
{
    if (hLabel_) {
        SetWindowTextW(hLabel_, L"Hello Win32!");
    }
}