#include "Sector.h"

Sector::Sector(decimal X, decimal Y, decimal R, decimal angle, decimal direction) :Shape(X, Y), r(R) {
	a = angle * TORAD;
	dir = direction * TORAD;
	update();
}

boolean Sector::hitTestPoint(decimal X, decimal Y) {
	if (X - x > r || Y - y > r || x - X > r || y - Y > r) {
		return false;
	}
	decimal dx = X - x, dy = Y - y;
	decimal dist2 = dx * dx + dy * dy;
	if (dist2 > r * r)
		return false;
	decimal dot = dx * dirX + dy * dirY;
	decimal cos2 = cosHalfAngle * cosHalfAngle;
	return dot > 0 && dot * dot >= dist2 * cos2;
}

void Sector::update() {  //扇形范围变化时（如薙玉剑气）更新数据
	dirX = cos(dir);
	dirY = sin(dir);
	cosHalfAngle = cos(a * 0.5f);
}

void Sector::draw(Graphics2D g2d) {
	/*
	decimal wrk = 0.017453292519943295F;
	int startAngle = (int)(-(dir + a / 2) / wrk);
	int arcAngle = (int)(a / wrk);
	g2d.drawArc((int)(x - r), (int)(y - r), (int)(r * 2), (int)(r * 2), startAngle, arcAngle);
	g2d.drawLine((int)x, (int)y, (int)(x + r * Math.cos(dir + a / 2)), (int)(y + r * Math.sin(dir + a / 2)));
	g2d.drawLine((int)x, (int)y, (int)(x + r * Math.cos(dir - a / 2)), (int)(y + r * Math.sin(dir - a / 2)));
	*/
}
