#include "Poly.h"
using namespace std;

Poly::Poly(decimal X, decimal Y, const vector<Point>& vertices, bool owned) :Shape(X, Y, owned), localVertices(vertices) {
	minX = INFINITY;
	maxX = -INFINITY;
	minY = INFINITY;
	maxY = -INFINITY;
	for (const Point& v : localVertices) {
		if (v.x < minX) minX = v.x;
		if (v.x > maxX) maxX = v.x;
		if (v.y < minY) minY = v.y;
		if (v.y > maxY) maxY = v.y;
	}
}

vector<Point> Poly::getWorldVertices() {      //获取顶点的世界绝对坐标
	vector<Point> worldVerts;
	worldVerts.reserve(localVertices.size());
	for (int i = 0; i < localVertices.size(); i++) {
		worldVerts.push_back(Point(localVertices[i].x + x, localVertices[i].y + y));
	}
	return worldVerts;
}


bool Poly::hitTestPoint(decimal X, decimal Y) {
	X -= x;
	Y -= y;
	if (maxX < X || minX > X || maxY < Y || minY > Y) {
		return false;
	}
	bool hit = false;
	unsigned j = localVertices.size() - 1;
	for (unsigned i = 0; i < localVertices.size(); i++) {
		decimal xi = localVertices[i].x, yi = localVertices[i].y, xj = localVertices[j].x, yj = localVertices[j].y;
		if (((yi > Y) != (yj > Y)) &&
			(X < (xj - xi) * (Y - yi) / (yj - yi) + xi)) {
			hit = !hit;
		}
		j = i;
	}
	return hit;
}

void Poly::draw(Graphics2D* g2d) {
	g2d->drawPolygon(localVertices, x, y);
}

