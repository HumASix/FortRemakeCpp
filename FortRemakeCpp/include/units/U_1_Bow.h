#pragma once
#include "General.h"
#include "Ball.h"
#include "atk/Bullet.h"
class Game;

class U_1_Bow :public Ball {     //¹­Óñ
public:
    U_1_Bow(Game* game, decimal X, decimal Y, int R, int S, int TYPE);

    virtual KillAction stepEx() override;
};