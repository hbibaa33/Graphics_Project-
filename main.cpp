

#include "windows.h"


static COLORREF color = RGB(0, 0, 0);


using namespace std;



LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    switch (m) {
    case WM_CREATE:

        break;
    case WM_COMMAND:

        break;
    case WM_LBUTTONDOWN:
        {
            HDC hdc = GetDC(hwnd);
            int x = LOWORD(lp);
            int y = HIWORD(lp);



            ReleaseDC(hwnd, hdc);
        }
        break;
    case WM_LBUTTONUP:
        {
            HDC hdc = GetDC(hwnd);
            int x = LOWORD(lp);
            int y = HIWORD(lp);


            ReleaseDC(hwnd, hdc);
        }
        break;
    case WM_RBUTTONDOWN:
        {
            HDC hdc = GetDC(hwnd);
            int x = LOWORD(lp);
            int y = HIWORD(lp);



            ReleaseDC(hwnd, hdc);
        }
        break;
    case WM_RBUTTONUP:
        {
            HDC hdc = GetDC(hwnd);
            int x = LOWORD(lp);
            int y = HIWORD(lp);

            ReleaseDC(hwnd, hdc);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SETCURSOR:
        SetCursor(LoadCursor(NULL, IDC_HAND));
        return TRUE;
    default:
        return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = reinterpret_cast<LPCSTR>(L"MyWindowClass");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
    reinterpret_cast<LPCSTR>(L"MyWindowClass"),
    reinterpret_cast<LPCSTR>(L"Paint"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    600, 400,
    NULL, NULL,
    hInstance,
    NULL
);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}



