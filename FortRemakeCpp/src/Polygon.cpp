#include "Polygon.h"


Polygon::Polygon(decimal X, decimal Y, vector<Point>& vertices) :Shape(X, Y), localVertices(vertices) {
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

vector<Point> Polygon::getWorldVertices() {      //获取顶点的世界绝对坐标
	vector<Point> worldVerts;
	worldVerts.reserve(localVertices.size());
	for (int i = 0; i < localVertices.size(); i++) {
		worldVerts.push_back(Point(localVertices[i].x + x, localVertices[i].y + y));
	}
	return worldVerts;
}


boolean Polygon::hitTestPoint(decimal X, decimal Y) {
	X -= x;
	Y -= y;
	if (maxX < X || minX > X || maxY < Y || minY > Y) {
		return false;
	}
	boolean hit = false;
	int j = localVertices.size() - 1;
	for (int i = 0; i < localVertices.size(); i++) {
		decimal xi = localVertices[i].x, yi = localVertices[i].y, xj = localVertices[j].x, yj = localVertices[j].y;
		if (((yi > Y) != (yj > Y)) &&
			(X < (xj - xi) * (Y - yi) / (yj - yi) + xi)) {
			hit = !hit;
		}
		j = i;
	}
	return hit;
}

void Polygon::draw(Graphics2D g2d) {
	/*
g2d.translate(x, y);
if (localVertices.length == 0) return;
Path2D.decimal path = new Path2D.decimal();
path.moveTo(localVertices[0][0], localVertices[0][1]);
for (int i = 1; i < localVertices.length; i++) {
	path.lineTo(localVertices[i][0], localVertices[i][1]);
}
path.closePath();
g2d.draw(path);
g2d.translate(-x, -y);
*/
}

