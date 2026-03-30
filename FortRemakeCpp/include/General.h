#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <regex>
#include <chrono>
#include <ctime>

typedef float decimal;
constexpr decimal TORAD = 0.017453292519943295F;
constexpr decimal TODEG = 57.29577951308232088F;
class Shape;
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
enum KillAction {//Game的step后执行的kill动作
	NONE,
	FAKEKILL,
	KILL
};
/*
class General {
public:
	const static std::list<Shape*> empty_list;
	const static std::list<Shape*>::iterator nullIt;
};
*/