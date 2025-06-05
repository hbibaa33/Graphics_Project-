//
// Created by habiba on 6/5/2025.
//

#ifndef LINES_H
#define LINES_H

#include "../painter/Painter.h"


class DDALinePainter : public Painter {
    int x0, y0, x1, y1;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawLineDDA(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color);
};

class MidpointLinePainter : public Painter {
    int x0, y0, x1, y1;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawLineMidpoint(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color);
};

class ParametricLinePainter : public Painter {
    int x0, y0, x1, y1;
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void DrawLineParametric(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color);
};

#endif // LINES_H
