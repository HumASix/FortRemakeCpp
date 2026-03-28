#pragma once
#include "Shape.h"
#include "Poly.h"
#include "Round.h"

class Game;
class Core : public Shape {      //ºËÐÄÀà

protected:
    Game* const game;

public:
    short side;
    decimal unit_x;
    decimal unit_y;
    //bool dmg_flg = false;

    Core(Game* game, decimal X, decimal Y, short S);

    void kill();

    virtual void step() override;

    virtual bool hitTestPoint(decimal X, decimal Y) override;

    virtual void draw(Graphics2D* g2d) override;
};