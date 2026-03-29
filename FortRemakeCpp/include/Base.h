#pragma once

#include "Shape.h"
#include "RoundedRect.h"
#include "Round.h"
#include "General.h"

class Game;

class Base : public Shape {  //车板类(使用new创建）（此类由Game负责Kill）
private:
    bool tobasare_flg = false;
    decimal wrk = 0;
    decimal xx;
    decimal yy;
    decimal old_x;
    decimal old_y;
    bool died = false;

protected:
    Game* const game;

public:
    int axl = 1;
    int side;
    decimal xs = 0;
    decimal ys = 0;
    decimal base_move_x = 0;
    decimal base_move_y = 0;

    Base(Game* game, decimal X, decimal Y, int S);

    virtual void kill();

    bool isDied();

    virtual KillAction step() override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;

    virtual void draw(Graphics2D* g2d) override;
};