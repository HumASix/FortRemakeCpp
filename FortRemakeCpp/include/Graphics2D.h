#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <Windows.h>
#include "General.h"
#include <vector>
class Graphics2D {//豆包发力了
public:
    Graphics2D(int width, int height, const char* title);
    ~Graphics2D();

    bool isOpen() const;
    void handleEvents();

    void clear();
    void update();

    // 绘图方法
    void drawLine(decimal x1, decimal y1, decimal x2, decimal y2);
    void drawOval(decimal x, decimal y, decimal w, decimal h);
    void drawPie(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad);
    void drawRect(decimal x1, decimal y1, decimal x2, decimal y2);
    void drawPolygon(const vector<Point>& points, decimal offsetX, decimal offsetY);

private:
    HWND hwnd;
    HDC hdc;
    HDC memDC;
    HBITMAP memBitmap;
    HBITMAP oldBitmap;

    int width, height;
    bool running;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};

#endif