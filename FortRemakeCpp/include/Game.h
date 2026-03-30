#pragma once
#include "General.h"
#include "Shape.h"
#include "CompositeShape.h"
#include "Base.h"
#include "Core.h"
#include "Settings.h"
#include "Utils.h"
#include "Ball.h"
#include "HitsContainer.h"
#include "HitsContainer2Region.h"
#include "HitsContainer4Region.h"
#include "HitsContainerContainer.h"

class Game {
private:
    bool alternate = true;//当true时，2被遍历，1作存储，否则1被遍历，2做存储
    bool end = false;
    bool canDraw = false;
    //static GameWindow window;
    bool main_setup(const std::string** codes);
    void base_move();
    void judge();
    void update();
    static Xyrt to_xyrt(const std::string& str, unsigned offset);

public:
    bool norikomi_flg = false;    //是否发生对撞
    unsigned ID = 0;   //待分配的ID，只会一直增长
    int hp[2] = { 100, 100 };    //要塞血量
    int hp0_flg[2] = { 0, 0 };   //要塞爆炸标记
    bool dokkan_flg[2] = { false, false };    //受到撞击标记，有贽玉不会变成true
    int saihai_cnt[2] = { 0, 0 };        //采玉效果剩余时间
    int saihai_rot[2] = { 0, 0 };        //采玉效果角度
    int dead_last[2] = { 0, 0 };         //上一个死亡的单位种类
    decimal core_x[2] = { 0, 0 };
    decimal core_y[2] = { 0, 0 };
    unsigned time = 0;     //计时器
    Utils seeder[2] = {Utils(),Utils()};
    Base* bases[2] = { nullptr,nullptr };     //双方车板（要不要用指针形式存储？）
    Core* cores[2] = { nullptr,nullptr };    //双方老家
    std::vector<Shape*> elements1 = std::vector<Shape*>();   //所有需要参与循环的部件1
    std::vector<Shape*> elements2 = std::vector<Shape*>();   //所有需要参与循环的部件1
    HitsContainer wall[2];   //墙体
    HitsContainer2Region unit[2];   //单位
    HitsContainer shield[2]; //屏障
    HitsContainer4Region atk[2];    //攻击
    HitsContainerContainer fort[2];   //要塞主体
    HitsContainerContainer team[2];   //队伍
    HitsContainer heal[2];   //治疗
    HitsContainer repair[2]; //修复
    HitsContainer jump_u[2]; //近突
    HitsContainer jump_f[2]; //远突
    HitsContainer snipe[2]; //狙击
    HitsContainer turn_ccw[2]; //顺时针
    HitsContainer turn_cw[2]; //逆时针
    //public LinkedList<Integer>[] kekkaiIds = new LinkedList[]{ new LinkedList<Integer>(), new LinkedList<Integer>() };
    //public KekkaiField[] kekkaiFields = new KekkaiField[]{ null, null };
    Game();
    ~Game();
    static int pskeyIndexOf(char c);//密码表
    Result run(const std::string& code1, const std::string& code2, Graphics2D* g2d = nullptr);
    unsigned addElement(Shape* s);//增加新元素，返回id值
    void unit_make(decimal X, decimal Y, int R, int TYPE, int S);
    //unsigned putToLast(unsigned id);
};
