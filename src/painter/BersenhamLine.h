//
// Created by LENOVO on 6/5/2025.
//

#ifndef BERSENHAMLINE_H
#define BERSENHAMLINE_H
#include "Painter.h"


class BersenhamLine :public Painter{
public:
    void onMouseLeftDown(HDC hdc, int x, int y) override;
    void onMouseLeftUp(HDC hdc, int x, int y) override;
    void handleConsole(HDC hdc) override;
    void drawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    void drawHorizontalLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color, bool invert=false);
    void drawVertical(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    ~BersenhamLine() =default;
private:
    int x1, y1, x2, y2;
};



#endif //BERSENHAMLINE_H
