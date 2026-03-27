#include "Shape.h"
using namespace std;

Shape::Shape(decimal X, decimal Y, bool owned) :x(X), y(Y), owned(owned) {
	id = -2147483648;
}

/*
	可能的优化：可以使用n叉树分而治之图形碰撞，太大的（如核弹）或处在边界的留在父节点，检测时只检测当前节点和父节点所有图形
	可能的优化：使用对象池处理弹幕产生和销毁
 */

void Shape::move(decimal X, decimal Y) {
	x += X;
	y += Y;
}

void Shape::moveTo(decimal X, decimal Y) {
	x = X;
	y = Y;
}

void Shape::xySync() {       //复刻 flash引擎量子化特性，在任何非0.05倍数移动时调用
	x = (int)(20 * x) * 0.05F;
	y = (int)(20 * y) * 0.05F;
}

void Shape::xSync() {       //仅针对 x 值的量子化
	x = (int)(20 * x) * 0.05F;
}

void Shape::ySync() {       //仅针对 y 值的量子化
	y = (int)(20 * y) * 0.05F;
}

void Shape::step() {     //每帧执行的代码
}

