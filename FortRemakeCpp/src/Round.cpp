#include "Round.h"
using namespace std;

Round::Round(decimal X, decimal Y, decimal R, bool owned) :Shape(X, Y, owned), r(R) { ; }


bool Round::hitTestPoint(decimal X, decimal Y) {
	if (X - x > r || Y - y > r || x - X > r || y - Y > r) {
		return false;
	}
	decimal dx = x - X;
	decimal dy = y - Y;
	return dx * dx + dy * dy <= r * r;
}

void Round::draw(Graphics2D* g2d) {
	g2d->drawOval((int)(x - r), (int)(y - r), (int)(r * 2), (int)(r * 2));
}

