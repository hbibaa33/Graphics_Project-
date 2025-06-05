//
// Created by habiba on 6/5/2025.
//

#include "lines.h"
#include <cmath>
#include <algorithm>

// Utility function
void SetPixelHDC(HDC hdc, int x, int y, COLORREF color) {
    SetPixel(hdc, x, y, color);
}

// ----------- DDA Line -----------
void DDALinePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    x0 = x;
    y0 = y;
}

void DDALinePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    x1 = x;
    y1 = y;
    DrawLineDDA(hdc, x0, y0, x1, y1, color);
}

void DDALinePainter::DrawLineDDA(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color) {
    int dx = x1 - x0, dy = y1 - y0;
    int steps = std::max(abs(dx), abs(dy));
    float xInc = dx / (float)steps, yInc = dy / (float)steps;
    float x = x0, y = y0;
    for (int i = 0; i <= steps; ++i, x += xInc, y += yInc)
        SetPixelHDC(hdc, round(x), round(y), color);
}

void DDALinePainter::handleConsole(HDC hdc) {
    // Optional: print instructions or console mode
}


// ----------- Midpoint Line -----------
void MidpointLinePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    x0 = x;
    y0 = y;
}

void MidpointLinePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    x1 = x;
    y1 = y;
    DrawLineMidpoint(hdc, x0, y0, x1, y1, color);
}

void MidpointLinePainter::DrawLineMidpoint(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (true) {
        SetPixelHDC(hdc, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void MidpointLinePainter::handleConsole(HDC hdc) {
    // Optional
}


// ----------- Parametric Line -----------
void ParametricLinePainter::onMouseLeftDown(HDC hdc, int x, int y) {
    x0 = x;
    y0 = y;
}

void ParametricLinePainter::onMouseLeftUp(HDC hdc, int x, int y) {
    x1 = x;
    y1 = y;
    DrawLineParametric(hdc, x0, y0, x1, y1, color);
}

void ParametricLinePainter::DrawLineParametric(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color) {
    for (int i = 0; i <= 1000; ++i) {
        float t = i / 1000.0f;
        int x = round(x0 + (x1 - x0) * t);
        int y = round(y0 + (y1 - y0) * t);
        SetPixelHDC(hdc, x, y, color);
    }
}

void ParametricLinePainter::handleConsole(HDC hdc) {
    // Optional
}

