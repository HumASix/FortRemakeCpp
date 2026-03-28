#include "Base.h"
#include "Game.h"

//TODO：车板可以像要塞壁一样优化碰撞，同时也不再需要子图形（最终版本）
Base::Base(Game* game, decimal X, decimal Y, short S) :Shape(X, Y), game(game) {
	side = S;
	xx = X;
	yy = Y;
	old_x = X;
	old_y = Y;
	id = game->addElement(this);
	game->wall[side] << this;
}

void Base::kill() {
	game->elements.erase(id);
	game->wall[side].removeShape(this);
}

void Base::step() {     //照搬原版逻辑
	xs = xs + (decimal)axl / 1000;
	if (game->hp0_flg[side] >= 3) {
		xs = 0;
	}
	ys += 0.05F;
	xx += (xs - 2 * xs * side);
	yy += ys;
	if (yy > 532) {
		yy = 532;
		ys *= -0.5F;
	}
	moveTo(round(xx), round(yy));
	base_move_x = x - old_x;
	base_move_y = y - old_y;
	old_x = x;
	old_y = y;
	tobasare_flg = false;
	if (x < 190) {
		wrk = round((-xs) * 5) + 1;
		xx = 191;
		xs = (-xs) / 2;
		tobasare_flg = true;
	}
	else if (x > 1730) {
		wrk = round((-xs) * 5) + 1;
		xx = 1729;
		xs = (-xs) / 2;
		tobasare_flg = true;
	}
	if (tobasare_flg && game->hp0_flg[side] == 0) {
		std::cout << ("hit wall") << std::endl;
		boolean nie_flg = false;
		/*
		for (Shape s : Main.unit[side].getShapes()) {
			if (s instanceof NieBall nie) {
				nie.alarm = 6;
				nie_flg = true;
				break;
			}
		}
		*/
		if (!nie_flg) {
			game->dokkan_flg[side] = true;
			wrk = round(wrk);
			if (wrk < 0) {
				wrk = 0;
			}
			game->hp[side] -= (int)wrk;
			//game->cores[side].dmg_flg = true;
		}
	}
}

bool Base::hitTestPoint(decimal X, decimal Y) {
	decimal dx = X - x;
	decimal dy = Y - y;
	if (dx < -191.5F || dx > 191.5F || dy < -15.5F || dy > 51.5F) {
		return false;
	}
	if (dy > -4.F) {
		if (dy > 17.F) {
			if (dy > 27.5F) {
				dx = abs(dx) - 108.7F;
				dy -= 20;
				return dx * dx + dy * dy <= 992.25F;
			}
			dy -= 17.F;
			dy *= 1.095238095238F;
		}
		else {
			return true;
		}
	}
	else {
		dy += 4.F;
	}
	if (dx > -180.F) {
		if (dx > 180.F) {
			dx -= 180.F;
		}
		else {
			return true;
		}
	}
	else {
		dx += 180.F;
	}
	return dx * dx + dy * dy <= 132.25F;
}

void Base::draw(Graphics2D* g2d) {
	RoundedRect(x, y, -191.5F, -15.5F, 383, 43, 11.5F).draw(g2d);
	Round(x - 108.7F, y + 20.F, 31.5F).draw(g2d);
	Round(x + 108.7F, y + 20.F, 31.5F).draw(g2d);
}