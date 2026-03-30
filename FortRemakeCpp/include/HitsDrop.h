#pragma once
#include "General.h"
#include "HitsContainer.h"
#include "Round.h"
class Game;

class HitsDrop :public Round {   //基础攻击判定（黑线）
//private:
    //此处需要改

protected:
    Game* game;

public:
    HitsDrop(Game* game, decimal X, decimal Y, HitsContainer* S);

    virtual KillAction step() override;

    virtual void kill() override;

    static KillAction hitsDropStep(Round* user);//对象自己当本类对象用（每帧动作)

    static void hitsDropInit(Round* user);//对象自己当本类对象用（初始化:改大小）
};