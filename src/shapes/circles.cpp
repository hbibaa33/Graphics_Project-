#include <iostream>
#include "circles.h"
using namespace std;


void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color) {
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}

// ========== DirectCirclePainter ==========
void DirectCirclePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    xc = x;
    yc = y;
    gotCenter = true;
}

void DirectCirclePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    if (gotCenter) {
        int dx = x - xc, dy = y - yc;
        int r = static_cast<int>(sqrt(dx * dx + dy * dy));
        DrawCircleDirect(hdc, xc, yc, r, color);
        gotCenter = false;
    }
}

void DirectCirclePainter::handleConsole(HDC hdc) {
    cout << "Direct Circle: Click center, then point on radius." << endl;
}

void DirectCirclePainter::DrawCircleDirect(HDC hdc, int xc, int yc, int r, COLORREF color) {
    for (int x = 0; x <= r / sqrt(2); ++x) {
        int y = round(sqrt(r * r - x * x));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}




// ========== PolarCirclePainter ==========
void PolarCirclePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    xc = x;
    yc = y;
    gotCenter = true;
}

void PolarCirclePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    if (gotCenter) {
        int dx = x - xc, dy = y - yc;
        int r = static_cast<int>(sqrt(dx * dx + dy * dy));
        DrawCirclePolar(hdc, xc, yc, r, color);
        gotCenter = false;
    }
}

void PolarCirclePainter::handleConsole(HDC hdc) {
    cout << "Polar Circle: Click center, then point on radius." << endl;
}

void PolarCirclePainter::DrawCirclePolar(HDC hdc, int xc, int yc, int r, COLORREF color) {
    for (float theta = 0; theta <= 2 * 3.14159f; theta += 1.0f / r) {
        int x = round(r * cos(theta));
        int y = round(r * sin(theta));
        SetPixel(hdc, xc + x, yc + y, color);
    }
}


// ========== IterativePolarCirclePainter ==========
void IterativePolarCirclePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    xc = x;
    yc = y;
    gotCenter = true;
}

void IterativePolarCirclePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    if (gotCenter) {
        int dx = x - xc, dy = y - yc;
        int r = static_cast<int>(sqrt(dx * dx + dy * dy));
        DrawCircleIterativePolar(hdc, xc, yc, r, color);
        gotCenter = false;
    }
}

void IterativePolarCirclePainter::handleConsole(HDC hdc) {
    cout << "Iterative Polar Circle: Click center, then point on radius." << endl;
}

void IterativePolarCirclePainter::DrawCircleIterativePolar(HDC hdc, int xc, int yc, int r, COLORREF color) {
    float x = r, y = 0;
    float dTheta = 0.01f;
    float cos_d = cos(dTheta), sin_d = sin(dTheta);
    while (x >= y) {
        SetPixel(hdc, xc + round(x), yc + round(y), color);
        float x_new = x * cos_d - y * sin_d;
        y = x * sin_d + y * cos_d;
        x = x_new;
    }
}



// ========== MidpointCirclePainter ==========
void MidpointCirclePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    xc = x;
    yc = y;
    gotCenter = true;
}

void MidpointCirclePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    if (gotCenter) {
        int dx = x - xc, dy = y - yc;
        int r = static_cast<int>(sqrt(dx * dx + dy * dy));
        DrawCircleMidpoint(hdc, xc, yc, r, color);
        gotCenter = false;
    }
}

void MidpointCirclePainter::handleConsole(HDC hdc) {
    cout << "Midpoint Circle: Click center, then point on radius." << endl;
}

void MidpointCirclePainter::DrawCircleMidpoint(HDC hdc, int xc, int yc, int r, COLORREF color) {
    int x = 0, y = r, d = 1 - r;
    while (x <= y) {
        Draw8Points(hdc, xc, yc, x, y, color);
        if (d < 0) d += 2 * x + 3;
        else { d += 2 * (x - y) + 5; --y; }
        ++x;
    }
}



// ========== ModifiedMidpointCirclePainter ==========
void ModifiedMidpointCirclePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    xc = x;
    yc = y;
    gotCenter = true;
}

void ModifiedMidpointCirclePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    if (gotCenter) {
        int dx = x - xc, dy = y - yc;
        int r = static_cast<int>(sqrt(dx * dx + dy * dy));
        DrawCircleModifiedMidpoint(hdc, xc, yc, r, color);
        gotCenter = false;
    }
}

void ModifiedMidpointCirclePainter::handleConsole(HDC hdc) {
    cout << "Modified Midpoint Circle: Click center, then point on radius." << endl;
}

void ModifiedMidpointCirclePainter::DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int r, COLORREF color) {
    int x = 0, y = r, d = 1 - r, dE = 3, dSE = -2 * r + 5;
    while (x < y) {
        Draw8Points(hdc, xc, yc, x, y, color);
        if (d < 0) { d += dE; dE += 2; dSE += 2; }
        else { d += dSE; dE += 2; dSE += 4; --y; }
        ++x;
    }
}
