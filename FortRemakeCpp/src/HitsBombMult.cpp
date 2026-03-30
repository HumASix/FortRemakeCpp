#include "HitsBombMult.h"
#include "Game.h"



HitsBombMult::HitsBombMult(Game* game, decimal X, decimal Y, int S, decimal mult) :Round(X, Y, 30 * mult), game(game), side(S), mult(mult) {
	xySync();
	lifeCyclePhase = 1;
	id = game->addElement(this);
	game->atk[side].addShape(this);
}

HitsBombMult::HitsBombMult(Game* game, decimal X, decimal Y, int S) :Round(X, Y, 30), game(game), side(S), mult(1.F) {
	xySync();
	id = game->addElement(this);
	game->atk[side].addShape(this);
}


void HitsBombMult::kill() {
}

KillAction HitsBombMult::step() {
	switch (lifeCyclePhase) {
	case 1: {
		r = 60.F;
		break;
	}
	case 2: {
		r = 39.F;
		break;
	}
	case 3: {
		r = 12.F;
		break;
	}
	default: {
		return KillAction::KILL;
	}
	}
	r *= mult;
	lifeCyclePhase++;
	return KillAction::NONE;
}

KillAction HitsBombMult::hitsBombStep(Round* user) {
	switch (user->lifeCyclePhase) {
	case 1: {
		user->r = 60.F;
		break;
	}
	case 2: {
		user->r = 39.F;
		break;
	}
	case 3: {
		user->r = 12.F;
		break;
	}
	default: {
		return KillAction::KILL;
	}
	}
	user->lifeCyclePhase++;
	return KillAction::NONE;
}


KillAction HitsBombMult::hitsBombStep(Round* user, decimal mult) {
	switch (user->lifeCyclePhase) {
	case 1: {
		user->r = 60.F;
		break;
	}
	case 2: {
		user->r = 39.F;
		break;
	}
	case 3: {
		user->r = 12.F;
		break;
	}
	default: {
		return KillAction::KILL;
	}
	}
	user->r *= mult;
	user->lifeCyclePhase++;
	return KillAction::NONE;
}

void HitsBombMult::hitsBombInit(Round* user) {
	user->r = 15.5F;
}

void HitsBombMult::hitsBombInit(Round* user, decimal mult) {
	user->r = 15.5F * mult;
}