#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
typedef float decimal;
constexpr decimal TORAD = 0.017453292519943295F;
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
	short x;
	short y;
	short r;
	short type;
};