#include "HitsContainerContainer.h"
using namespace std;

HitsContainerContainer::HitsContainerContainer():HitsContainer() {
	childContainers = vector<HitsContainer*>();
}

bool HitsContainerContainer::hitTestPoint(decimal X, decimal Y) {
	if (HitsContainer::hitTestPoint(X, Y)) return true;
	for (HitsContainer* hc : childContainers) {
		if (hc->hitTestPoint(X, Y)) return true;
	}
	return false;
}

HitsContainerContainer& HitsContainerContainer::operator<<(HitsContainer* s) {
	childContainers.push_back(s);
	return *this;
}
