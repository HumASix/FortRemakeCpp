#include "CompositeShape.h"
using namespace std;
CompositeShape::CompositeShape(decimal X, decimal Y, bool owned) :Shape(X, Y, owned), shapes(vector<Shape*>()) { }

CompositeShape::~CompositeShape() {
	for (auto it = shapes.begin(); it != shapes.end(); ++it) {
		if ((*it)->owned) {
			delete (*it);
		}
	}
}

CompositeShape& CompositeShape::addShape(Shape* s) {
	shapes.push_back(s);
	return *this;
}

CompositeShape& CompositeShape::operator<<(Shape* s) {
	shapes.push_back(s);
	return *this;
}

CompositeShape& CompositeShape::removeShape(Shape* s) {
	for (auto it = shapes.begin(); it != shapes.end(); ++it) {
		if (*it == s) {
			if (s->owned) {
				delete s;
			}
			shapes.erase(it);
			break;
		}
	}
	return *this;
}

CompositeShape& CompositeShape::shift() {
	if (shapes.size() > 0) {
		auto s = shapes.begin();
		if ((*s)->owned) {
			delete* s;
		}
		shapes.erase(s);
	}
	return *this;
}

Round* CompositeShape::circle(decimal X, decimal Y, decimal R) {      //增加一个圆
	return new Round(X + x, Y + y, R, true);
}

Poly* CompositeShape::polygon(decimal X, decimal Y, const vector<Point>& points) {       //增加一个多边形
	return new Poly(X + x, Y + y, points, true);
};

Rect* CompositeShape::rectangle(decimal X, decimal Y, decimal W, decimal H) {      //增加一个矩形
	return new Rect(X + x, Y + y, 0, 0, W, H, true);
}

RoundedRect* CompositeShape::roundedRectangle(decimal X, decimal Y, decimal W, decimal H, decimal R) {      //增加一个矩形
	return new RoundedRect(X + x, Y + y, 0, 0, W, H, R, true);
}

Sector* CompositeShape::sector(decimal X, decimal Y, decimal R, decimal angle, decimal direction) {     //增加一个扇形
	return new Sector(X + x, Y + y, R, angle, direction, true);
}

const vector<Shape*>& CompositeShape::getShapes() const {
	return shapes;
}

void CompositeShape::move(decimal X, decimal Y) {
	Shape::move(X, Y);
	for (Shape* s : shapes) {
		s->move(X, Y);
	}
}

void CompositeShape::moveTo(decimal X, decimal Y) {
	for (Shape* s : shapes) {
		s->move(X - x, Y - y);
	}
	Shape::moveTo(X, Y);
}

bool CompositeShape::hitTestPoint(decimal X, decimal Y) {
	for (Shape* s : shapes) {
		if (s->hitTestPoint(X, Y)) return true;
	}
	return false;
}

void CompositeShape::draw(Graphics2D* g2d) {
	for (Shape* s : shapes) {
		s->draw(g2d);
	}
}
