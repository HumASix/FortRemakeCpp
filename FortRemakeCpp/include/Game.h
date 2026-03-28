#pragma once
#include "General.h"
#include "Shape.h"
#include "CompositeShape.h"
#include "Base.h"
#include "Core.h"
#include "Settings.h"

class Game {
private:
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
    short hp[2] = { 100, 100 };    //要塞血量
    short hp0_flg[2] = { 0, 0 };   //要塞爆炸标记
    bool dokkan_flg[2] = { false, false };    //受到撞击标记，有贽玉不会变成true
    int saihai_cnt[2] = { 0, 0 };        //采玉效果剩余时间
    short saihai_rot[2] = { 0, 0 };        //采玉效果角度
    short dead_last[2] = { 0, 0 };         //上一个死亡的单位种类
    decimal core_x[2] = { 0, 0 };
    decimal core_y[2] = { 0, 0 };
    unsigned time = 0;     //计时器
    //public Utils[] seeder = { new Utils(),new Utils() };
    Base* bases[2] = { nullptr,nullptr };     //双方车板（要不要用指针形式存储？）
    Core* cores[2] = { nullptr,nullptr };    //双方老家
    std::map<unsigned, Shape*> elements = std::map<unsigned, Shape*>();   //所有需要参与循环的部件
    CompositeShape wall[2] = { CompositeShape(0,0), CompositeShape(0,0) };   //墙体
    CompositeShape unit[2] = { CompositeShape(0,0), CompositeShape(0,0) };   //单位
    CompositeShape shield[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //屏障
    CompositeShape atk[2] = { CompositeShape(0,0), CompositeShape(0,0) };    //攻击
    CompositeShape fort[2] = { CompositeShape(0,0), CompositeShape(0,0) };   //要塞主体
    CompositeShape team[2] = { CompositeShape(0,0), CompositeShape(0,0) };   //队伍
    CompositeShape heal[2] = { CompositeShape(0,0), CompositeShape(0,0) };   //治疗
    CompositeShape repair[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //修复
    CompositeShape jump_u[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //近突
    CompositeShape jump_f[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //远突
    CompositeShape snipe[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //狙击
    CompositeShape turn_ccw[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //顺时针
    CompositeShape turn_cw[2] = { CompositeShape(0,0), CompositeShape(0,0) }; //逆时针
    //public LinkedList<Integer>[] kekkaiIds = new LinkedList[]{ new LinkedList<Integer>(), new LinkedList<Integer>() };
    //public KekkaiField[] kekkaiFields = new KekkaiField[]{ null, null };
    Game();
    ~Game();
    static short pskeyIndexOf(char c);//密码表
    Result run(const std::string& code1, const std::string& code2, Graphics2D* g2d = nullptr);
    unsigned addElement(Shape* s);//增加新元素，返回id值
    void unit_make(decimal X, decimal Y, int R, int TYPE, int S);
};
