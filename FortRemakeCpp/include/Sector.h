#pragma once
#include "General.h"
#include "Shape.h"
class Sector :public Shape {     //扇形类（不能超过半圆）

private:
	decimal cosHalfAngle;

public:
	decimal r;
	decimal dirX;
	decimal dirY;
	decimal dir;
	decimal a;

	Sector(decimal X, decimal Y, decimal R, decimal angle, decimal direction);

	virtual boolean hitTestPoint(decimal X, decimal Y) override; 

	void update();

	virtual void draw(Graphics2D g2d) override;
};