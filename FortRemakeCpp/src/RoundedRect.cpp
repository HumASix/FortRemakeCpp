#include "RoundedRect.h"
using namespace std;

RoundedRect::RoundedRect(decimal X, decimal Y, decimal startX, decimal startY, decimal W, decimal H, decimal R, bool owned) :Shape(X, Y, owned), width(W), height(H), start_x(startX), start_y(startY), radius(R) {

}

bool RoundedRect::hitTestPoint(decimal X, decimal Y) {   //µãÅö×²
	X = X - x - start_x;
	Y = Y - y - start_y;
	if (X >= 0 && X <= width && Y >= 0 && Y <= height) {
		decimal halfW = width * .5F;
		decimal halfH = height * .5F;
		X = abs(X - halfW) - halfW + radius;
		Y = abs(Y - halfH) - halfH + radius;
		return (X + Y <= radius || X * X + Y * Y <= radius * radius);
	}
	else {
		return false;
	}
}

void RoundedRect::draw(Graphics2D* g2d) {   //»æÖÆ
	decimal ltX = x + start_x;
	decimal ltY = y + start_y;
	decimal locRadius = radius;
	g2d->drawLine(ltX + locRadius, ltY, ltX + width - locRadius, ltY);
	g2d->drawLine(ltX + locRadius, ltY + height, ltX + width - locRadius, ltY + height);
	g2d->drawLine(ltX, ltY + locRadius, ltX, ltY + height - locRadius);
	g2d->drawLine(ltX + width, ltY + locRadius, ltX + width, ltY + height - locRadius);
	g2d->drawArc(ltX + locRadius, ltY + locRadius, locRadius, 225 * TORAD, 90 * TORAD);
	g2d->drawArc(ltX + width - locRadius, ltY + locRadius, locRadius, 315 * TORAD, 90 * TORAD);
	g2d->drawArc(ltX + locRadius, ltY + height - locRadius, locRadius, 135 * TORAD, 90 * TORAD);
	g2d->drawArc(ltX + width - locRadius, ltY + height - locRadius, locRadius, 45 * TORAD, 90 * TORAD);
}
