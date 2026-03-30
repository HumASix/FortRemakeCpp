#pragma once
#include "General.h"
#include "HitsContainer.h"

class HitsContainerContainer:public HitsContainer {
private:
	std::vector<HitsContainer*> childContainers;
public:
	HitsContainerContainer();
	virtual ~HitsContainerContainer() = default;
	virtual bool hitTestPoint(decimal X, decimal Y);
	virtual HitsContainerContainer& operator<<(HitsContainer* s);
	//是否需要加一个整体清理的函数？
};