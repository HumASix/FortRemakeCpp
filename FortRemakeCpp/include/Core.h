#pragma once
#include "Shape.h"
#include "Poly.h"
#include "Round.h"

class Game;
class Core : public Shape {      //核心类（此类由Game负责Kill）

protected:
    Game* const game;

public:
    int side;
    decimal unit_x;
    decimal unit_y;
    //bool dmg_flg = false;

    Core(Game* game, decimal X, decimal Y, int S);

    virtual void kill();

    virtual KillAction step() override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;

    virtual void draw(Graphics2D* g2d) override;
};