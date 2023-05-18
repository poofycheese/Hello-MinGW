//============================================================================
// Name        : Hello.cpp
// Author      : Poof
// Version     : 0
// Copyright   : 2023
// Description : Hello World inside windows app.
//				 I used ChatGPT to crap this out in less then an hour.
//============================================================================

#include <iostream>
#include <windows.h>

using namespace std;

// Window Procedure callback function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Display the "Hello, World!" message
            string hellostr = "Hello, World!";
            char helloary[hellostr.size() +1 ];
            strncpy(helloary, hellostr.c_str(), sizeof( helloary ));

            cout << "helloary=[" << hellostr << "]";
            TextOut( hdc, 10, 25, helloary, hellostr.length() );


            EndPaint(hwnd, &ps);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    const char* CLASS_NAME = "MyWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                      // Optional window styles
        CLASS_NAME,             // Window class name
        "Hello MinGW",        // Window title
        WS_OVERLAPPEDWINDOW,    // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Display the window
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

