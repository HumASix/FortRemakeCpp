#pragma once
#include "General.h"
#include "CompositeShape.h"
#include "Round.h"
class Game;


class HitsBombMult :public Round {   //爆炸判定
private:
    int side;
    decimal mult;

protected:
    Game* game;

public:
    HitsBombMult(Game* game, decimal X, decimal Y,int S,decimal mult);

    HitsBombMult(Game* game, decimal X, decimal Y, int S);

    virtual KillAction step() override;

    virtual void kill() override;

    static KillAction hitsBombStep(Round* user);//对象自己当本类对象用（每帧动作)

    static void hitsBombInit(Round* user);//对象自己当本类对象用（初始化:改大小）

    static KillAction hitsBombStep(Round* user, decimal mult);//对象自己当本类对象用（每帧动作)

    static void hitsBombInit(Round* user, decimal mult);//对象自己当本类对象用（初始化:改大小）
};