#include "HitsDrop.h"
#include "Game.h"

HitsDrop::HitsDrop(Game* game, decimal X, decimal Y, HitsContainer* S) :Round(X, Y, 15.5F), game(game){
	xySync();
	id = game->addElement(this);
	parent = S;
	S->addShape(this);
}

void HitsDrop::kill() {
	//此处需要改
	//parent->removeShape(this);
}

KillAction HitsDrop::step() {
	return KillAction::KILL;
}

void HitsDrop::hitsDropInit(Round* user) {
	user->r = 15.5F;
}

KillAction HitsDrop::hitsDropStep(Round* user) {
	return KillAction::KILL;
}