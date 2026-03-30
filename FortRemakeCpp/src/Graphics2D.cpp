#include "Graphics2D.h"
using namespace std;
Graphics2D::Graphics2D(int w, int h, const char* title)
    : width(w), height(h)
{
    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "Graphics2DClass";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, "Graphics2DClass", title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, GetModuleHandle(NULL), this
    );
    initFont(20);
    hdc = GetDC(hwnd);
    memDC = CreateCompatibleDC(hdc);
    memBitmap = CreateCompatibleBitmap(hdc, w, h);
    oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);
    hDefaultBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    SelectObject(memDC, hDefaultBrush);
    running = true;
    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);
}

Graphics2D::~Graphics2D() {
    SelectObject(memDC, oldBitmap);
    DeleteObject(memBitmap);
    DeleteDC(memDC);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}


bool Graphics2D::tryToOccupyBy(Game* const game) {
    if (whoIsUsingThis == nullptr) {
        whoIsUsingThis = game;
        return true;
    }
    return false;
}
//bool Graphics2D::isOccupiedBy(Game* const game);
void Graphics2D::release(Game* const game) {
    if (whoIsUsingThis == game) {
        whoIsUsingThis = nullptr;
    }
}

bool Graphics2D::isOpen() const {
    return running;
}


void Graphics2D::handleEvents() {
    MSG msg{};
    while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            running = false;
    }
}

void Graphics2D::clear() {
    RECT rc = { 0,0,width,height };
    FillRect(memDC, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
}

void Graphics2D::update() {
    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

void Graphics2D::drawLine(decimal x1, decimal y1, decimal x2, decimal y2) {
    MoveToEx(memDC, (int)(G2DSCALE * x1 + G2DTRANSX), (int)(G2DSCALE * y1 + G2DTRANSY), NULL);
    LineTo(memDC, (int)(G2DSCALE * x2 + G2DTRANSX), (int)(G2DSCALE * y2 + G2DTRANSY));
}

void Graphics2D::drawPie(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad) {
    decimal startRad = centerAngleRad - sweepRad * 0.5F;
    decimal endRad = centerAngleRad + sweepRad * 0.5F;
    int x1 = (int)(G2DSCALE * (x + r * cos(startRad)) + G2DTRANSX);
    int y1 = (int)(G2DSCALE * (y + r * sin(startRad)) + G2DTRANSY);
    int x2 = (int)(G2DSCALE * (x + r * cos(endRad)) + G2DTRANSX);
    int y2 = (int)(G2DSCALE * (y + r * sin(endRad)) + G2DTRANSY);
    Pie(memDC, (int)(G2DSCALE * (x - r) + G2DTRANSX), (int)(G2DSCALE * (y - r) + G2DTRANSY), (int)(G2DSCALE * (x + r) + G2DTRANSX), (int)(G2DSCALE * (y + r) + G2DTRANSY), x2, y2, x1, y1);
}

void Graphics2D::drawArc(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad) {
    decimal startRad = centerAngleRad - sweepRad * 0.5F;
    decimal endRad = centerAngleRad + sweepRad * 0.5F;
    int x1 = (int)(G2DSCALE * (x + r * cos(startRad)) + G2DTRANSX);
    int y1 = (int)(G2DSCALE * (y + r * sin(startRad)) + G2DTRANSY);
    int x2 = (int)(G2DSCALE * (x + r * cos(endRad)) + G2DTRANSX);
    int y2 = (int)(G2DSCALE * (y + r * sin(endRad)) + G2DTRANSY);
    Arc(memDC, (int)(G2DSCALE * (x - r) + G2DTRANSX), (int)(G2DSCALE * (y - r) + G2DTRANSY), (int)(G2DSCALE * (x + r) + G2DTRANSX), (int)(G2DSCALE * (y + r) + G2DTRANSY), x2, y2, x1, y1);
}

void Graphics2D::drawOval(decimal x, decimal y, decimal w, decimal h) {
    Ellipse(memDC, (int)(G2DSCALE * x + G2DTRANSX), (int)(G2DSCALE * y + G2DTRANSY), (int)(G2DSCALE * (x + w) + G2DTRANSX), (int)(G2DSCALE * (y + h) + G2DTRANSY));
}

void Graphics2D::drawRect(decimal x1, decimal y1, decimal x2, decimal y2) {
    Rectangle(memDC, (int)(G2DSCALE * x1 + G2DTRANSX), (int)(G2DSCALE * y1 + G2DTRANSY), (int)(G2DSCALE * x2 + G2DTRANSX), (int)(G2DSCALE * y2 + G2DTRANSY));
}

void Graphics2D::drawPolygon(const vector<Point>& points, decimal offsetX, decimal offsetY) {
    if (points.size() < 2) return;
    MoveToEx(memDC, (int)(G2DSCALE * (points[0].x + offsetX + G2DTRANSX)), (int)(G2DSCALE * (points[0].y + offsetY) + G2DTRANSY), NULL);
    for (unsigned i = 1;i < points.size();i++) {
        LineTo(memDC, (int)(G2DSCALE * (points[i].x + offsetX) + G2DTRANSX), (int)(G2DSCALE * (points[i].y + offsetY) + G2DTRANSY));
    }
    LineTo(memDC, (int)(G2DSCALE * (points[0].x + offsetX + G2DTRANSX)), (int)(G2DSCALE * (points[0].y + offsetY) + G2DTRANSY));
}

void Graphics2D::drawText(decimal x, decimal y, const char* text)
{
    drawText(x, y, text, RGB(0, 0, 0));
}

void Graphics2D::drawText(decimal x, decimal y, const char* text, COLORREF color)
{
    if (!text || !*text) return;

    // 应用超采样缩放
    int px = (int)(x * G2DSCALE + G2DTRANSX);
    int py = (int)(y * G2DSCALE + G2DTRANSY);

    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, color);
    TextOutA(memDC, px, py, text, (int)strlen(text));
}

void Graphics2D::initFont(int size) {
    
    // 关键：字体大小 * 超采样倍率，保证高清
    int realSize = (int)(size * G2DSCALE);

    if (hfont) DeleteObject(hfont);

    hfont = CreateFontA(
        realSize,           // 高度 = 字号（你控制的）
        0,                  // 宽度自动
        0, 0,
        FW_NORMAL,          // 粗细：400正常，700加粗
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        "Arial"   // 字体：微软雅黑（清晰）
    );

    // 选入画布
    SelectObject(memDC, hfont);
}

LRESULT CALLBACK Graphics2D::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_CREATE) {
        CREATESTRUCT* cs = (CREATESTRUCT*)lp;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
    }

    Graphics2D* g = (Graphics2D*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (g && msg == WM_DESTROY) {
        g->running = false;
        PostQuitMessage(0);
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}