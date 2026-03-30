#pragma once
#include "General.h"
#include "HitsContainer.h"
#include "Ball.h"
#include "atk/Bullet.h"

class HitsContainer4Region :public HitsContainer {
private:
	decimal mid = 0.F;
public:
	std::vector<Shape*> left;
	std::vector<Shape*> right;
	std::vector<Shape*> leftTop;
	std::vector<Shape*> rightTop;
	std::vector<Shape*> common;
	HitsContainer4Region();
	virtual ~HitsContainer4Region() = default;
	void resign(decimal m);
	bool hitTestPoint(decimal X, decimal Y);
};