#include <windows.h>
#include "renderer/vk_renderer"
#include "defines.h"
#include "platform.h"

// global variable is just static type but makes it easier to understand
global_variable bool is_running = true;
global_variable HWND window;

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

bool platform_create_window()
{
    HINSTANCE instance = GetModuleHandleA(0);
    WNDCLASSA wc = {};
    wc.lpfnWndProc = platform_window_callback;
    wc.hInstance = instance;
    wc.lpszClassName = "vulkan_window";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        MessageBoxA(window, "Failed registering window class", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    window = CreateWindowExA(
        WS_EX_APPWINDOW,
        "vulkan_window",
        "vulkan_app",
        WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED,
        100, 100, 1600, 720, 0, 0, instance, 0);

    if (window == 0)
    {
        MessageBoxA(window, "Failed creating window", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    ShowWindow(window, SW_SHOW);
    return true;
}

void platform_update_window(HWND window)
{
    MSG msg;
    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

int main()
{
    VkContext vkcontext = {};

    if (!platform_create_window())
    {
        return -1;
    }

    if (!vk_init(&vkcontext, window))
    {
        return -1;
    }

    while (is_running)
    {
        platform_update_window(window);
        if (!vk_render(&vkcontext))
        {
            return -1;
        }
    }

    return 0;
}

void platform_get_window_size(uint32_t *pWidth, uint32_t *pHeight)
{
    RECT rect;
    GetClientRect(window, &rect);

    *pWidth = rect.right - rect.left;
    *pHeight =      rect.bottom - rect.top;
}