#pragma once
#include "General.h"

class Utils {     //工具类

private:
    int seed = 0;
    const static decimal trigonometricLookup[450];
public:
    Utils() = default;
    ~Utils() = default;
    static int universalSeed;
    static int randFunc;//0～2依次为三个随机选项
    void setSeed(int S);
    static decimal sin(int x);

    static decimal cos(int x);

    static decimal cosF(decimal RDeg);

    static decimal sinF(decimal RDeg);

    static decimal random(Utils& src);
};