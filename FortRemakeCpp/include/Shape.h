#pragma once
#include "Graphics2D.h"
#include "General.h"

class Shape {   //最基本的抽象形状类
    friend class CompositeShape;
private:
    bool owned;
public:
    decimal x;
    decimal y;
    int id;

    Shape(decimal X, decimal Y, bool owned = false);

    virtual ~Shape() = default;

    /*
        可能的优化：可以使用n叉树分而治之图形碰撞，太大的（如核弹）或处在边界的留在父节点，检测时只检测当前节点和父节点所有图形
        可能的优化：使用对象池处理弹幕产生和销毁
     */

    virtual bool hitTestPoint(decimal X, decimal Y) = 0;     //点碰撞

    virtual void move(decimal X, decimal Y);

    virtual void moveTo(decimal X, decimal Y);

    void xySync();

    void xSync();

    void ySync();

    virtual void step();

    virtual void draw(Graphics2D* g2d) = 0;
};
