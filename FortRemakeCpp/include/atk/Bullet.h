#pragma once
#include "General.h"
#include "Round.h"
#include "HitsDrop.h"

class Game;
class Bullet :public Round {     //×Óµ¯»ùÀà
protected:
    Game* const game;
    virtual KillAction fakeKillStep();

public:
    int side;
    int gei_flg = 1;
    decimal xs = 0;
    decimal ys = 0;
    decimal gravity = 0;
    decimal power = 0;

    Bullet(Game* game, decimal X, decimal Y, int S);
    virtual ~Bullet() = default;

    virtual KillAction step() override;

    virtual void kill() override;

    virtual void fakeKill() override;

    KillAction hit_ground();

    Bullet& move();

    KillAction hit();

    Bullet& setVec(decimal vx, decimal vy);

    Bullet& setVecMult(decimal vx, decimal vy, decimal mult);

    Bullet& setVecR(int r, decimal speed);

    Bullet& setGravity(decimal g);

    Bullet& setPower(decimal P);

    virtual void reflect(int from_rot);

    void betray();
};