

#include "windows.h"
#include <iostream>

#include "src/painter/BersenhamLine.h"
#include "src/painter/Painter.h"


Painter *currentPainter = nullptr;
COLORREF currentColor = RGB(0, 0, 0);


using namespace std;



HMENU CreatePainterMenu() {
    HMENU hMenuBar = CreateMenu();


    HMENU hColorMenu = CreateMenu();
    AppendMenu(hColorMenu, MF_STRING, 101, "Red");
    AppendMenu(hColorMenu, MF_STRING, 102, "Green");
    AppendMenu(hColorMenu, MF_STRING, 103, "Blue");
    AppendMenu(hColorMenu, MF_STRING, 104, "Black");


    HMENU hShapeMenu = CreateMenu();
    AppendMenu(hShapeMenu, MF_STRING, 201, "Line");
    AppendMenu(hShapeMenu, MF_STRING, 202, "Circle");
    AppendMenu(hShapeMenu, MF_STRING, 203, "Bezier Curve");

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hColorMenu, "Color");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hShapeMenu, "Shape");

    return hMenuBar;
}


LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    switch (m) {
    case WM_CREATE: {
        HMENU hMenu = CreatePainterMenu();
        SetMenu(hwnd, hMenu);
    }
        break;
    case WM_COMMAND: {
        switch (LOWORD(wp)) {
            // 🎨 Color choices
            case 101: currentColor = RGB(255, 0, 0); break; // Red
            case 102: currentColor = RGB(0, 255, 0); break; // Green
            case 103: currentColor = RGB(0, 0, 255); break; // Blue
            case 104: currentColor = RGB(0, 0, 0); break;   // Black


            case 201: {
                delete currentPainter;
                currentPainter = new  BersenhamLine();
            }

            break;

        }


        if (currentPainter)
            currentPainter->setColor(currentColor);
    }

        break;
        case WM_LBUTTONDOWN:
            if (currentPainter) {
                HDC hdc = GetDC(hwnd);
                currentPainter->onMouseLeftDown(hdc, LOWORD(lp), HIWORD(lp));
                ReleaseDC(hwnd, hdc);
            }
        break;

        case WM_LBUTTONUP:
            if (currentPainter) {
                HDC hdc = GetDC(hwnd);
                currentPainter->onMouseLeftUp(hdc, LOWORD(lp), HIWORD(lp));
                ReleaseDC(hwnd, hdc);
            }
        break;

        case WM_RBUTTONDOWN:
            if (currentPainter) {
                HDC hdc = GetDC(hwnd);
                currentPainter->onMouseRightDown(hdc, LOWORD(lp), HIWORD(lp));
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
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);

    std::cout << "Console attached!" << std::endl;

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


