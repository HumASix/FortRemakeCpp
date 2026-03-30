#pragma once
#include "General.h"
#include "HitsContainer.h"
#include "Ball.h"

class HitsContainer2Region :public HitsContainer {
private:
	decimal mid = 0.F;
public:
	std::vector<Shape*> left;
	std::vector<Shape*> right;
	std::vector<Shape*> common;
	HitsContainer2Region();
	virtual ~HitsContainer2Region() = default;
	void resign(decimal m);
	bool hitTestPoint(decimal X, decimal Y);
};