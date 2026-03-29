#pragma once
#include "General.h"
#include "CompositeShape.h"
#include "Round.h"
class Game;

class HitsDrop :public Round {   //基础攻击判定（黑线）
private:
    CompositeShape* const parent;

protected:
    Game* game;

public:
    HitsDrop(Game* game, decimal X, decimal Y, CompositeShape* S);

    virtual KillAction step();

    static KillAction hitsDropStep(Round* user);//对象自己当本类对象用（每帧动作)

    static void hitDropInit(Round* user);//对象自己当本类对象用（初始化:改大小）
};