#include "HitsContainer4Region.h"
using namespace std;

HitsContainer4Region::HitsContainer4Region() :HitsContainer() {
    left = vector<Shape*>();
    right = vector<Shape*>();
    leftTop = vector<Shape*>();
    rightTop = vector<Shape*>();
    common = vector<Shape*>();
}

void HitsContainer4Region::resign(decimal m) {
    //TODO:需要好好处理新产生的atk。他们现在刚产生的那一个遍历周期不会被检测到。
    mid = m;
    common.clear();
    left.clear();
    right.clear();
    leftTop.clear();
    rightTop.clear();
    vector<Shape*>& wrkContainer = alternate ? shapes2 : shapes1;
    vector<Shape*>& storeContainer = alternate ? shapes1 : shapes2;
    storeContainer.clear();
    for (auto it = wrkContainer.begin();it != wrkContainer.end();it++) {
        auto wrk = *it;
        if (wrk->lifeCyclePhase < 0 || wrk->parent != this) {
            if (wrk->parent == this) wrk->parent = nullptr;
        }
        else {
            if (dynamic_cast<Bullet*>(wrk)/*TODO:这里换成子弹或剃刀！！！*/) {
                if (wrk->y < 84) {
                    if (wrk->x < mid + 84) {
                        leftTop.push_back(wrk);
                    }
                    if (wrk->x > mid - 84) {
                        rightTop.push_back(wrk);
                    }
                }
                if (wrk->y > -84) {
                    if (wrk->x < mid + 84) {
                        left.push_back(wrk);
                    }
                    if (wrk->x > mid - 84) {
                        right.push_back(wrk);
                    }
                }
            }
            else {
                common.push_back(wrk);
            }
            storeContainer.push_back(wrk);
        }
    }
    alternate = !alternate;
}

bool HitsContainer4Region::hitTestPoint(decimal X, decimal Y) {
    for (Shape* s : common) {
        if (safeHitTestPointCall(s, X, Y)) return true;
    }
    if (Y < 0) {
        if (X <= mid) {
            for (Shape* s : leftTop) {
                if (safeHitTestPointCall(s, X, Y)) return true;
            }
            return false;
        }
        else {
            for (Shape* s : rightTop) {
                if (safeHitTestPointCall(s, X, Y)) return true;
            }
            return false;
        }
    }
    else {
        if (X <= mid) {
            for (Shape* s : left) {
                if (safeHitTestPointCall(s, X, Y)) return true;
            }
            return false;
        }
        else {
            for (Shape* s : right) {
                if (safeHitTestPointCall(s, X, Y)) return true;
            }
            return false;
        }
    }
}