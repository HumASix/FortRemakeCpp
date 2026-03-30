#include "HitsContainer2Region.h"
using namespace std;

HitsContainer2Region::HitsContainer2Region() :HitsContainer() {
	left = vector<Shape*>();
	right = vector<Shape*>();
	common = vector<Shape*>();
}

void HitsContainer2Region::resign(decimal m) {
    mid = m;
    common.clear();
    left.clear();
    right.clear();
    alternate = !alternate;
    vector<Shape*>& wrkContainer = alternate ? shapes2 : shapes1;
    vector<Shape*>& storeContainer = alternate ? shapes1 : shapes2;
    storeContainer.clear();
    for (auto it = wrkContainer.begin();it != wrkContainer.end();it++) {
        auto wrk = *it;
        if (wrk->lifeCyclePhase < 0 || wrk->parent != this) {
            if (wrk->parent == this) wrk->parent = nullptr;
        }
        else {
            if (dynamic_cast<Ball*>(wrk)) {
                if (wrk->x < mid + 42) {
                    left.push_back(wrk);
                }
                if (wrk->x > mid - 42) {
                    right.push_back(wrk);
                }
            }
            else {
                common.push_back(wrk);
            }
            storeContainer.push_back(wrk);
        }
    }
}

bool HitsContainer2Region::hitTestPoint(decimal X, decimal Y) {
    for (Shape* s : common) {
        if (safeHitTestPointCall(s, X, Y)) return true;
    }
    if (X <= mid) {
        for (Shape* s : left) {
            if (safeHitTestPointCall(s, X, Y)) return true;
        }
    }
    else {
        for (Shape* s : right) {
            if (safeHitTestPointCall(s, X, Y)) return true;
        }
    }
    return false;
}