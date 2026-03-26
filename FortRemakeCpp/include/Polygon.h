#pragma once
#include "Shape.h"
#include <vector>

class Polygon :public Shape {     //多边形，存储各个顶点坐标数据
public:
    const vector<Point> localVertices;
    Polygon(decimal X, decimal Y, vector<Point>& vertices);
    vector<Point> getWorldVertices();
    virtual boolean hitTestPoint(decimal X, decimal Y) override;
    virtual void draw(Graphics2D g2d) override;

protected:
    decimal minX;
    decimal maxX;
    decimal minY;
    decimal maxY;
};
