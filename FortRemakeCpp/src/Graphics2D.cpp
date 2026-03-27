#include "Graphics2D.h"

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

    hdc = GetDC(hwnd);

    memDC = CreateCompatibleDC(hdc);
    memBitmap = CreateCompatibleBitmap(hdc, w, h);
    oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

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
    MoveToEx(memDC, (int)x1, (int)y1, NULL);
    LineTo(memDC, (int)x2, (int)y2);
}

void Graphics2D::drawPie(decimal x, decimal y, decimal r, decimal centerAngleRad, decimal sweepRad) {
    decimal startRad = centerAngleRad - sweepRad * 0.5F;
    decimal endRad = centerAngleRad + sweepRad * 0.5F;
    int x1 = (int)(x + r * cos(startRad));
    int y1 = (int)(y + r * sin(startRad));
    int x2 = (int)(x + r * cos(endRad));
    int y2 = (int)(y + r * sin(endRad));
    Pie(memDC, (int)(x - r), (int)(y - r), (int)(x + r), (int)(y + r), x2, y2, x1, y1);
}

void Graphics2D::drawOval(decimal x, decimal y, decimal w, decimal h) {
    Ellipse(memDC, (int)x, (int)y, (int)(x + w), (int)(y + h));
}

void Graphics2D::drawRect(decimal x1, decimal y1, decimal x2, decimal y2) {
    Rectangle(memDC, (int)x1, (int)y1, (int)x2, (int)y2);
}

void Graphics2D::drawPolygon(const vector<Point>& points, decimal offsetX, decimal offsetY) {
    if (points.size() < 2) return;
    MoveToEx(memDC, (int)(points[0].x + offsetX), (int)(points[0].y + offsetY), NULL);
    for (int i = 1;i < points.size();i++) {
        LineTo(memDC, (int)(points[i].x + offsetX), (int)(points[i].y + offsetY));
    }
    LineTo(memDC, (int)(points[0].x + offsetX), (int)(points[0].y + offsetY));
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