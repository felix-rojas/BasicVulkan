#include <windows.h>

static bool is_running = true;

LRESULT CALLBACK platform_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        is_running = false;
        break;
    }

    return DefWindowProcA(window, msg, wParam, lParam);
}

bool platform_create_window(HWND window)
{
    HINSTANCE instance = GetModuleHandleA(0);
    WNDCLASSA wc = {};
    wc.lpfnWndProc = platform_window_callback;
    wc.hInstance = instance;
    wc.lpszClassName = "vulkan_window";

    if (!RegisterClassA(&wc))
    {
        MessageBoxA(window, "Failed registering window class", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    window = CreateWindowExA(
        WS_EX_APPWINDOW,
        "vulkan_window",
        "Pong",
        0, 100, 100, 1600, 720, 0, 0, instance, 0);

    if (window == 0)
    {
        MessageBoxA(window, "Failed creating window", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    ShowWindow(window, SW_SHOW);
}

int main()
{
    HWND window = 0;
    if (platform_create_window(window))
    {
        return -1;
    }

    while (is_running)
    {
        /* code */
    }

    return 0;
}