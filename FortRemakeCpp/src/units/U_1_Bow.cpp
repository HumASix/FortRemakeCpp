#include "units/U_1_Bow.h"
#include "Game.h"
U_1_Bow::U_1_Bow(Game* game, decimal X, decimal Y, int R, int S, int TYPE) :Ball(game, X, Y, R, S, TYPE) {
	speed = 30;
}

KillAction U_1_Bow::stepEx() {
	if (cnt == speed + 6) {
		cnt = 0;
		(*(new Bullet(game, x, y, side))).setVecMult(cos_rot, sin_rot, 15).setGravity(0.32F);
	}
	return KillAction::NONE;
}
