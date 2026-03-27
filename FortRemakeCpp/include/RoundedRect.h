#pragma once

#include "Shape.h"

class RoundedRect :public Shape {   //矩形类
private:
    const decimal width;
    const decimal height;
    const decimal start_x;
    const decimal start_y;
    const decimal radius;

public:
    RoundedRect(decimal X, decimal Y, decimal startX, decimal startY, decimal W, decimal H, decimal R, bool owned = false);   //左上角与宽高
    virtual ~RoundedRect() = default;
    virtual bool hitTestPoint(decimal X, decimal Y) override;
    virtual void draw(Graphics2D* g2d) override;
};