#include "Rect.h"

Rect::Rect(float X, float Y, float startX, float startY, float W, float H) :Shape(X, Y), width(W), height(H), start_x(startX), start_y(startY) {

}

bool Rect::hitTestPoint(float X, float Y) {   //µãÅö×²
	X -= start_x;
	Y -= start_y;
	return X >= x && X <= x + width && Y >= y && Y <= y + height;
}

void Rect::draw(Graphics2D* g2d) {   //»æÖÆ
	g2d->drawRect((int)(x + start_x), (int)(y + start_y), (int)width, (int)height);
}
