//
// Created by habiba on 6/5/2025.
//
#ifndef CIRCLES_H
#define CIRCLES_H

#include "../painter/Painter.h"
#include <cmath>

void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color);

class DirectCirclePainter : public Painter {
    int xc, yc, radiusX, radiusY;
    bool gotCenter = false;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawCircleDirect(HDC hdc, int xc, int yc, int r, COLORREF color);
};

class PolarCirclePainter : public Painter {
    int xc, yc, radiusX, radiusY;
    bool gotCenter = false;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawCirclePolar(HDC hdc, int xc, int yc, int r, COLORREF color);
};

class IterativePolarCirclePainter : public Painter {
    int xc, yc;
    bool gotCenter = false;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawCircleIterativePolar(HDC hdc, int xc, int yc, int r, COLORREF color);
};

class MidpointCirclePainter : public Painter {
    int xc, yc;
    bool gotCenter = false;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawCircleMidpoint(HDC hdc, int xc, int yc, int r, COLORREF color);
};

class ModifiedMidpointCirclePainter : public Painter {
    int xc, yc;
    bool gotCenter = false;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int r, COLORREF color);
};



#endif // CIRCLES_H

