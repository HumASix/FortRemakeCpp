#include "HitsContainer.h"
using namespace std;

HitsContainer::HitsContainer() {
	shapes1 = vector<Shape*>();
	shapes2 = vector<Shape*>();
}

bool HitsContainer::hitTestPoint(decimal X, decimal Y) {
	vector<Shape*>& wrkContainer = alternate ? shapes2 : shapes1;
	vector<Shape*>& storeContainer = alternate ? shapes1 : shapes2;
	storeContainer.clear();
	for (auto it = wrkContainer.begin();it != wrkContainer.end();it++) {
		auto wrk = *it;
		if (wrk->lifeCyclePhase < 0 || wrk->parent != this) {
			if (wrk->parent == this) wrk->parent = nullptr;
		}
		else
		{
			if (wrk->hitTestPoint(X, Y)) {
				storeContainer.insert(storeContainer.end(), it, wrkContainer.end());
				alternate = !alternate;
				return true;
			}
			else {
				storeContainer.push_back(wrk);
			}
		}
	}
	alternate = !alternate;
	return false;
}
HitsContainer& HitsContainer::addShape(Shape* s){
	s->parent = this;
	if (alternate) shapes2.push_back(s);
	else shapes1.push_back(s);
	return *this;
}

HitsContainer& HitsContainer::operator<<(Shape* s) {
	s->parent = this;
	if (alternate) shapes2.push_back(s);
	else shapes1.push_back(s);
	return *this;
}

bool HitsContainer::safeHitTestPointCall(Shape* s,decimal X,decimal Y) {
	if (s->lifeCyclePhase < 0 || s->parent != this) {
		if (s->parent == this) s->parent = nullptr;
		return false;
	}
	else if (s->hitTestPoint(X, Y)) return true;
	else return false;
}