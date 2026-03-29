#include "HitsDrop.h"
#include "Game.h"

HitsDrop::HitsDrop(Game* game, decimal X, decimal Y, CompositeShape* S) :Round(X, Y, 15.5F), game(game), parent(S) {
	xySync();
	id = game->addElement(this);
	S->addShape(this);
}

KillAction HitsDrop::step() {
	parent->removeShape(this);
	return KillAction::KILL;
}

void HitsDrop::hitDropInit(Round* user) {
	user->r = 15.5F;
}

KillAction HitsDrop::hitsDropStep(Round* user) {
	return KillAction::KILL;
}