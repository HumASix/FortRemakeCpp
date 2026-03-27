#include "Rect.h"
using namespace std;

Rect::Rect(decimal X, decimal Y, decimal startX, decimal startY, decimal W, decimal H, bool owned) :Shape(X, Y, owned), width(W), height(H), start_x(startX), start_y(startY) {

}

bool Rect::hitTestPoint(decimal X, decimal Y) {   //µãÅö×²
	X -= start_x;
	Y -= start_y;
	return X >= x && X <= x + width && Y >= y && Y <= y + height;
}

void Rect::draw(Graphics2D* g2d) {   //»æÖÆ
	g2d->drawRect((int)(x + start_x), (int)(y + start_y), (int)(x + start_x + width), (int)(y + start_y + height));
}
