#include "atk/Bullet.h"
#include "Game.h"

Bullet::Bullet(Game* game, decimal X, decimal Y, int S):Round(X,Y,15.5F),game(game),side(S) {
    id = game->addElement(this);
    game->atk[side] << this;
}

void Bullet::kill() {
    return;
}
void Bullet::fakeKill() {
    HitsDrop::hitsDropInit(this);
    return;
}
KillAction Bullet::fakeKillStep() {
    return HitsDrop::hitsDropStep(this);
}
KillAction Bullet::step() {
    if (lifeCyclePhase > 0) {
        return fakeKillStep();
    }
    else {
        if (y > 570) {
            KillAction wrk = hit_ground();
            if (wrk != KillAction::NONE) return wrk;
        }
        if (game->team[1 - side].hitTestPoint(x, y) || gei_flg == 2) {
            KillAction wrk = hit();
            if (wrk != KillAction::NONE) return wrk;
        }
        move();
    }
    return KillAction::NONE;
}

KillAction Bullet::hit_ground() {    //撞击地面
    return KillAction::KILL;
}

Bullet& Bullet::move() {      //移动
    x = x + xs;
    y = y + ys;
    xySync();
    ys = ys + gravity;
    return *this;
}

KillAction Bullet::hit() {   //被摧毁
    return KillAction::FAKEKILL;
}

Bullet& Bullet::setVec(decimal vx, decimal vy) {     //设置运动向量
    xs = vx;
    ys = vy;
    return *this;
}

Bullet& Bullet::setVecMult(decimal vx, decimal vy, decimal mult) {     //设置运动向量
    xs = vx * mult;
    ys = vy * mult;
    power = mult;
    return *this;
}

Bullet& Bullet::setVecR(int r, decimal speed) {      //设置运动向量，极坐标版
    setVec(Utils::cos(r) * speed, Utils::sin(r) * speed);
    power = speed;
    return *this;
}

Bullet& Bullet::setGravity(decimal g) {    //设置重力
    gravity = g;
    return *this;
}

Bullet& Bullet::setPower(decimal P) {      //设置运动向量，极坐标版
    power = P;
    return *this;
}

void Bullet::reflect(int from_rot) {
    betray();
    xs = Utils::cos(from_rot) * power;
    ys = Utils::sin(from_rot) * power;
}

void Bullet::betray() {
    game->atk[1 - side] << this;
}