#pragma once
#include "General.h"
#include "Shape.h"

class HitsContainer {
protected:
	bool alternate = true;//当true时，2被遍历，1作存储，否则1被遍历，2做存储
	bool safeHitTestPointCall(Shape* s, decimal X, decimal Y);
public:
	std::vector<Shape*>shapes1;
	std::vector<Shape*>shapes2;
	HitsContainer();
	virtual ~HitsContainer() = default;
	virtual bool hitTestPoint(decimal X, decimal Y);
	virtual HitsContainer& addShape(Shape* s);
	virtual HitsContainer& operator<<(Shape* s);
	//是否需要加一个整体清理的函数？
};