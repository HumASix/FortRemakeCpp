#pragma once
#include "Shape.h"
class Round :public Shape {   //‘≤–Œ¿‡
public:
	decimal r;

	Round(decimal X, decimal Y, decimal R, bool owned = false);

	virtual ~Round() = default;

	virtual bool hitTestPoint(decimal X, decimal Y) override;

	virtual void draw(Graphics2D* g2d) override;
};
