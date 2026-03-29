#pragma once
#include "Round.h"
#include "Utils.h"
#include "HitsDrop.h"
class Game;

class Ball :public Round {       //玉基类（请使用new创建）
protected:
    Game* game;

public:
    int side;
    int type;
    int cnt = 0;
    int jump_flg = 0;
    int speed = 1;
    int on_side;
    int hp = 10;
    int max_hp = 10;
    int rot;
    decimal drop_y = 0;
    decimal xs = 0;
    decimal ys = 0;
    decimal cos_rot;
    decimal sin_rot;
    //TODO：因为玉的角度都是整数，所以可以尝试做一个0-359度的正余弦值表

    Ball(Game* game, decimal X, decimal Y, int R, int S, int TYPE);

    virtual void kill() override;
    virtual void fakeKill() override;

    virtual KillAction step() override;
    virtual KillAction stepEx(); //如果基础行动判定通过则进行的额外行为,返回是否需要kill。

    void land();

    bool ground();

    bool jump();

    virtual void hurt(bool is_crash);

    void snipe();

    void turn(int degree);
};