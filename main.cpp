#include <windows.h>
#include <iostream>
#include <algorithm>
#include <tchar.h>
#include <memory>
#include "src/shapes/lines.h"     // adjust to match your folder structure
#include "src/shapes/circles.h"   // optional, if you've added circle painters

std::unique_ptr<Painter> painter;
COLORREF selectedColor = RGB(0, 0, 0); // Default to black


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    switch (msg) {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            if (painter) painter->onMouseLeftDown(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hwnd, hdc);
            break;
        case WM_LBUTTONUP:
            hdc = GetDC(hwnd);
            if (painter) painter->onMouseLeftUp(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hwnd, hdc);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
void chooseColor() {
    int r, g, b;
    std::cout << "=== Choose Drawing Color ===\n";
    std::cout << "Enter Red : ";
    std::cin >> r;
    std::cout << "Enter Green : ";
    std::cin >> g;
    std::cout << "Enter Blue : ";
    std::cin >> b;

    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);

    selectedColor = RGB(r, g, b);
}


void choosePainter() {
    int choice;
    std::cout << "=== Shape Drawing Menu ===\n";
    std::cout << "Lines:\n";
    std::cout << "  1. Line DDA\n";
    std::cout << "  2. Line Midpoint\n";
    std::cout << "  3. Line Parametric\n";
    std::cout << "Circles:\n";
    std::cout << "  4. Circle Direct\n";
    std::cout << "  5. Circle Polar\n";
    std::cout << "  6. Circle Iterative Polar\n";
    std::cout << "  7. Circle Midpoint\n";
    std::cout << "  8. Circle Modified Midpoint\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: painter = std::make_unique<DDALinePainter>(); break;
        case 2: painter = std::make_unique<MidpointLinePainter>(); break;
        case 3: painter = std::make_unique<ParametricLinePainter>(); break;
        case 4: painter = std::make_unique<DirectCirclePainter>(); break;
        case 5: painter = std::make_unique<PolarCirclePainter>(); break;
        case 6: painter = std::make_unique<IterativePolarCirclePainter>(); break;
        case 7: painter = std::make_unique<MidpointCirclePainter>(); break;
        case 8: painter = std::make_unique<ModifiedMidpointCirclePainter>(); break;
        default: std::cout << "Invalid choice.\n"; exit(0);
    }
    painter->setColor(selectedColor);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {

    chooseColor();
    choosePainter();

    const TCHAR CLASS_NAME[] = _T("BasicWindowClass");

    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, _T("Painter Test"),
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               800, 600, nullptr, nullptr, hInst, nullptr);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

