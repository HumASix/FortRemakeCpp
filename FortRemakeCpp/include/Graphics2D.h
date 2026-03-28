#pragma once
#include <Windows.h>
#include "General.h"

constexpr float G2DSCALE = .75F;
constexpr float G2DTRANSX = 0.F;
constexpr float G2DTRANSY = 0.F;

class Game;
class Graphics2D {//豆包发力了
public:
    Graphics2D(int width, int height, const char* title);
    ~Graphics2D();

    bool isOpen() const;
    void handleEvents();
    void clear();
    void update();
    bool tryToOccupyBy(Game* const game);
    //bool isOccupiedBy(Game* const game);
    void release(Game* const game);
    // 绘图方法
    void drawLine(decimal x1, decimal y1, decimal x2, decimal y2);
    void drawOval(decimal x, decimal y, decimal w, decimal h);
    void drawPie(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad);
    void drawArc(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad);
    void drawRect(decimal x1, decimal y1, decimal x2, decimal y2);
    void drawPolygon(const std::vector<Point>& points, decimal offsetX, decimal offsetY);

private:
    HWND hwnd;
    HDC hdc;
    HDC memDC;
    HBITMAP memBitmap;
    HBITMAP oldBitmap;
    HBRUSH hDefaultBrush;
    Game* whoIsUsingThis = nullptr;



    int width, height;
    bool running;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};
