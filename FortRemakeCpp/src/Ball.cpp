#include "Ball.h"
#include "Game.h"
using namespace std;
Ball::Ball(Game* game, decimal X, decimal Y, int R, int S, int TYPE) :Round(X, Y, 23.25F), game(game), side(S), on_side(S), rot(R), type(TYPE) {
	xySync();
	cos_rot = Utils::cos(R);
	sin_rot = Utils::sin(R);
	id = game->addElement(this);
	game->unit[side].addShape(this);
}

void Ball::kill() {
	game->unit[side].removeShape(this);
}

void Ball::fakeKill() {
	HitsDrop::hitDropInit(this);
}

KillAction Ball::step() {     //照搬原版unit_func()
	if (fakeKillCnt >= 0) {
		return HitsDrop::hitsDropStep(this);
	}
	if (jump_flg != 1) {
		if (jump_flg != 2) {
			land();
		}
		else {
			if (ground()) return KillAction::KILL;
		}
	}
	else {
		if (jump()) return KillAction::KILL;
	}
	if (game->saihai_cnt[side] > 0) {
		if (jump_flg == 0 && side != on_side || jump_flg == 2) {
			jump_flg = 1;
			xs = Utils::cos(game->saihai_rot[side]) * 4;
			ys = -2 + Utils::sin(game->saihai_rot[side]) * 4;
			if (ys > -2) {
				ys = -2;
			}
		}
	}
	if (jump_flg == 0 && game->jump_u[side].hitTestPoint(x, y)) {
		jump_flg = 1;
		xs = 4 - 8 * on_side;
		ys = -8;
		on_side = 1 - on_side;
	}
	else if (jump_flg == 0 && game->jump_f[side].hitTestPoint(x, y)) {
		jump_flg = 1;
		xs = 15 - 30 * on_side;
		ys = -4;
		on_side = 1 - on_side;
	}
	else if (game->snipe[side].hitTestPoint(x, y + 16)) {
		snipe();
	}
	else if (game->turn_ccw[side].hitTestPoint(x, y + 16)) {
		turn(-2);
	}
	else if (game->turn_cw[side].hitTestPoint(x, y + 16)) {
		turn(2);
	}
	if (game->atk[1 - side].hitTestPoint(x - 8, y - 8) || game->atk[1 - side].hitTestPoint(x + 8, y - 8) || game->atk[1 - side].hitTestPoint(x - 8, y + 8) || game->atk[1 - side].hitTestPoint(x + 8, y + 8) || jump_flg == 0 && game->dokkan_flg[on_side]) {
		hurt(game->dokkan_flg[on_side]);     //从又臭又长的switch()改为调用自己的hurt方法
		hp--;
	}
	if (hp <= 0 || game->hp0_flg[on_side] > 0 && jump_flg == 0) {
		//TODO:new HitsDrop(this.x, this.y, game->unit[side]);
		game->dead_last[side] = type;
		return KillAction::FAKEKILL;
	}

	if (hp < max_hp) {
		if (game->heal[side].hitTestPoint(x, y)) {
			hp++;
		}
	}
	return stepEx();
}

KillAction Ball::stepEx() {
	return KillAction::NONE;
}  

void Ball::land() {      //正常
	if (jump_flg == 0 && !(side == on_side) && game->hp0_flg[on_side] > 0) {
		jump_flg = 1;
		xs = Utils::random(game->seeder[side]) * 7 - 3;
		ys = Utils::random(game->seeder[side]) * 4 - 10;
		on_side = 1 - on_side;
	}
	cnt++;
	Base* wrkBase = game->bases[on_side];
	if (!wrkBase->isDied()) {
		move(wrkBase->base_move_x, wrkBase->base_move_y);
	}
	ys = ys + 1;
	drop_y = y + ys;
	if (drop_y >= 566) {
		drop_y = 566;
		jump_flg = 2;
	}
	else {
		while (game->wall[on_side].hitTestPoint(x, drop_y + 15)) {
			jump_flg = 0;
			drop_y -= 1;
			ys = 0;
		}
	}
	y = drop_y;
	ySync();
}

bool Ball::ground() {    //地面
	cnt++;
	if (game->wall[1 - side].hitTestPoint(x, y)) {
		game->dead_last[side] = type;
		return true;
	}
	return false;
}

bool Ball::jump() {      //突击中
	ys += 0.32F;
	x = x + xs;
	y = y + ys;
	xySync();
	if (y >= 566) {
		y = 566;
		xs = 0;
		jump_flg = 2;
	}
	else if (game->wall[on_side].hitTestPoint(x, y + 15)) {
		jump_flg = 0;
	}
	else if (game->wall[on_side].hitTestPoint(x + (xs < 0 ? -16 : 16), y)) {
		xs = 0;
	}
	if (x < 0 || x > 1920) {
		return true;
	}
	return false;
}

void Ball::hurt(bool is_crash) {  }   //受伤

void Ball::snipe() {
	int wrk_target = round((atan2(game->core_y[1 - side] - y, game->core_x[1 - side] - x)) * TODEG);
	if (rot - 180 > wrk_target) {
		wrk_target = wrk_target + 360;
	}
	else if (rot + 180 < wrk_target) {
		wrk_target = wrk_target - 360;
	}
	if (rot > wrk_target) {
		--rot;
		cos_rot = Utils::cos(rot);
		sin_rot = Utils::sin(rot);
	}
	else if (rot < wrk_target) {
		++rot;
		cos_rot = Utils::cos(rot);
		sin_rot = Utils::sin(rot);
	}
	if (rot > 360) {
		rot = rot - 360;
	}
	else if (rot < 0) {
		rot = rot + 360;
	}
}

void Ball::turn(int degree) {
	rot = rot + (on_side == 0 ? 1 : -1) * degree;
	cos_rot = Utils::cos(rot);
	sin_rot = Utils::sin(rot);
	if (rot > 360) {
		rot = rot - 360;
	}
	else if (rot < 0) {
		rot = rot + 360;
	}
}
