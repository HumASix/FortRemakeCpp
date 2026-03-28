#include "Core.h"
#include "Game.h"
using namespace std;

Core::Core(Game* game, decimal X, decimal Y, short S) :Shape(X, Y), game(game), unit_x(X), unit_y(Y), side(S) {
	id = game->addElement(this);
	game->wall[side] << this;
}

void Core::kill() {
	game->cores[side] = nullptr;
	game->elements.erase(id);
	game->wall[side].removeShape(this);
	delete this;
}

void Core::step() {     //ÕÕ°áÔ­°æÂß¼­
	moveTo(game->bases[side]->x + unit_x, game->bases[side]->y + unit_y);
	if (game->atk[1 - side].hitTestPoint(x - 40, y - 40) ||
		game->atk[1 - side].hitTestPoint(x + 40, y - 40) ||
		game->atk[1 - side].hitTestPoint(x - 40, y + 40) ||
		game->atk[1 - side].hitTestPoint(x + 40, y + 40) ||
		game->atk[1 - side].hitTestPoint(x - 20, y - 20) ||
		game->atk[1 - side].hitTestPoint(x, y - 20) ||
		game->atk[1 - side].hitTestPoint(x + 20, y - 20) ||
		game->atk[1 - side].hitTestPoint(x - 20, y + 20) ||
		game->atk[1 - side].hitTestPoint(x, y + 20) ||
		game->atk[1 - side].hitTestPoint(x + 20, y + 20) ||
		game->atk[1 - side].hitTestPoint(x - 20, y) ||
		game->atk[1 - side].hitTestPoint(x + 20, y) ||
		game->atk[1 - side].hitTestPoint(x, y)) {
		//dmg_flg = true;
		game->hp[side]--;
	}
	if (game->hp[side] < 100 && game->repair[side].hitTestPoint(x, y)) {
		game->hp[side]++;
	}
	//dmg_flg = false;
}

bool Core::hitTestPoint(decimal X, decimal Y) {
	X -= x;
	Y -= y;
	if (X < -53.5F || X > 53.5F || Y < -53.5F || Y > 53.5F) {
		return false;
	}
	X = abs(X);
	Y = abs(Y);
	if (Y - X <= 9.221316F && Y - X >= -9.221316F && X < 40) return true;
	if (X * X + Y * Y <= 1122.25F) return true;
	X -= 40;
	Y -= 40;
	return X * X + Y * Y <= 182.25F;
}

void Core::draw(Graphics2D* g2d) {
	vector<Point> vxy1 = { {-27.63934F,-36.86066F},{-36.86066F,-27.63934F},{27.63934F,36.86066F},{36.86066F,27.63934F} };
	vector<Point> vxy2 = { {-27.63934F,36.86066F},{-36.86066F,27.63934F},{27.63934F,-36.86066F},{36.86066F,-27.63934F} };
	Round(x - 40, y - 40, 13.5F).draw(g2d);
	Round(x - 40, y + 40, 13.5F).draw(g2d);
	Round(x + 40, y - 40, 13.5F).draw(g2d);
	Round(x + 40, y + 40, 13.5F).draw(g2d);
	Round(x, y, 33.5F).draw(g2d);
	Poly(x, y, vector<Point>({ {-27.63934F,-36.86066F},{-36.86066F,-27.63934F},{27.63934F,36.86066F},{36.86066F,27.63934F} })).draw(g2d);
	Poly(x, y, vector<Point>({ {-27.63934F,36.86066F},{-36.86066F,27.63934F},{27.63934F,-36.86066F},{36.86066F,-27.63934F} })).draw(g2d);
}