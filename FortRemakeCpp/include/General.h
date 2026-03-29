#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <regex>
#include <chrono>
#include <ctime>

typedef float decimal;
constexpr decimal TORAD = 0.017453292519943295F;
constexpr decimal TODEG = 57.29577951308232088F;
struct Point {
	decimal x;
	decimal y;
};
struct Result {
	int status;
	int winnerHP;
	int framePassed;
	decimal time;
};
struct Xyrt {
	int x;
	int y;
	int r;
	int type;
};
enum KillAction {
	NONE,
	FAKEKILL,
	KILL
};