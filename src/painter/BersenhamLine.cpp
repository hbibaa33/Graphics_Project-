//
// Created by LENOVO on 6/5/2025.
//

#include "BersenhamLine.h"
#include <iostream>
using namespace std;

void BersenhamLine::onMouseLeftDown(HDC hdc, int x, int y) {
    x1 = x;
    y1 = y;
}

void BersenhamLine::onMouseLeftUp(HDC hdc,int x , int y) {
    x2 = x;
    y2 = y;
    drawLine(hdc, x1, y1, x2, y2, color);

}
void BersenhamLine::drawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) >= abs(dy))
    {
        drawHorizontalLine(hdc, x1, y1, x2, y2, color);
    }
    else
    {
        drawVertical(hdc, x1, y1, x2, y2, color);
    }
}

void BersenhamLine::drawHorizontalLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color,bool invert) {
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int incr = dy < 0 ? -1 : 1;
    dy *= incr;

    int d = 2 * dy - dx;
    int d1 = 2 * dy;
    int d2 = -2 * dx;

    int x = x1, y = y1;
    while (x < x2)
    {
        if (d >= 0)
        {
            y += incr;
            d += d2;
        }

        d += d1;
        x++;

        if (invert)
        {
            SetPixel(hdc, y, x, color);
        }
        else
        {
            SetPixel(hdc, x, y, color);
        }
    }
}

void BersenhamLine::drawVertical(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    drawHorizontalLine(hdc, y1, x1, y2, x2, color, true);
}




void BersenhamLine::handleConsole(HDC hdc) {
    std::cout << "Enter first point's x: ";
    std::cin >> x1;

    std::cout << "Enter first point's y: ";
    std::cin >> y1;

    std::cout << "Enter second point's x: ";
    std::cin >> x2;

    std::cout << "Enter second point's y: ";
    std::cin >> y2;

    drawLine(hdc, x1, y1, x2, y2, color);
}

