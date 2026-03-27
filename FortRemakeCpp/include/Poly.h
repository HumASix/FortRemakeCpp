#pragma once
#include "Shape.h"
#include <vector>

class Poly :public Shape {     //多边形，存储各个顶点坐标数据
public:
    const vector<Point> localVertices;
    Poly(decimal X, decimal Y, const vector<Point>& vertices);
    virtual ~Poly() = default;
    vector<Point> getWorldVertices();
    virtual bool hitTestPoint(decimal X, decimal Y) override;
    virtual void draw(Graphics2D* g2d) override;

protected:
    decimal minX;
    decimal maxX;
    decimal minY;
    decimal maxY;
};
