#pragma once

#include "Shape.h"

class Rect :public Shape {   //矩形类
private:
    const float width;
    const float height;
    const float start_x;
    const float start_y;

public:
    Rect(float X, float Y, float startX, float startY, float W, float H);   //左上角与宽高
    virtual ~Rect() = default;
    virtual bool hitTestPoint(float X, float Y) override;
    virtual void draw(Graphics2D* g2d) override;
};