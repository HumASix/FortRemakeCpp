#pragma once

#include "Shape.h"
#include "CompositeShape.h"

class Game;

class Base : public CompositeShape {  //车板类（不要new）
private:
    bool tobasare_flg = false;
    decimal wrk = 0;
    decimal xx;
    decimal yy;
    decimal old_x;
    decimal old_y;

protected:
    Game* game;

public:
    int axl = 1;
    int side;
    decimal xs = 0;
    decimal ys = 0;
    decimal base_move_x = 0;
    decimal base_move_y = 0;

    Base(Game* game, decimal X, decimal Y, int S);

    void kill();

    virtual void step() override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;
};