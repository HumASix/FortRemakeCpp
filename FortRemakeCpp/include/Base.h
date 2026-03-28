#pragma once

#include "Shape.h"
#include "RoundedRect.h"
#include "Round.h"

class Game;

class Base : public Shape {  //车板类(使用new创建）
private:
    bool tobasare_flg = false;
    decimal wrk = 0;
    decimal xx;
    decimal yy;
    decimal old_x;
    decimal old_y;

protected:
    Game* const game;

public:
    int axl = 1;
    short side;
    decimal xs = 0;
    decimal ys = 0;
    decimal base_move_x = 0;
    decimal base_move_y = 0;

    Base(Game* game, decimal X, decimal Y, short S);

    void kill();

    virtual void step() override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;

    virtual void draw(Graphics2D* g2d) override;
};