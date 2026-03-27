#pragma once

#include "Shape.h"
#include "Poly.h"
#include "Rect.h"
#include "Round.h"
#include "Sector.h"
#include "RoundedRect.h"

class CompositeShape :public Shape {     //复合形状类
protected:
    std::vector<Shape*> shapes;   //所有包含的子形状
public:
    CompositeShape(decimal X, decimal Y, bool owned = false);
    virtual ~CompositeShape();

    CompositeShape& addShape(Shape* s);

    CompositeShape& operator<<(Shape* s);

    CompositeShape& removeShape(Shape* s);//删除元素

    CompositeShape& shift();//删除第一个元素

    Round* circle(decimal x, decimal y, decimal r);//以相对坐标构建圆形

    Poly* polygon(decimal x, decimal y, const std::vector<Point>& points);//以相对坐标构建多边形

    Rect* rectangle(decimal x, decimal y, decimal w, decimal h);//以相对坐标构建矩形

    RoundedRect* roundedRectangle(decimal x, decimal y, decimal w, decimal h,decimal r);//以相对坐标构建矩形

    Sector* sector(decimal x, decimal y, decimal r, decimal angle, decimal direction);//以相对坐标构建扇形

    const std::vector<Shape*>& getShapes() const;

    virtual void move(decimal X, decimal Y) override;

    virtual void moveTo(decimal X, decimal Y) override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;

    virtual void draw(Graphics2D* g2d) override;
};