#include "Game.h"
using namespace std;
using namespace chrono;
Game::Game() {
	for (int i = 0;i < 2;i++) {
		wall[i] = HitsContainer();   //墙体
		unit[i] = HitsContainer2Region();   //单位
		shield[i] =  HitsContainer() ; //屏障
		atk[i] = HitsContainer4Region();    //攻击
		fort[i] = HitsContainerContainer() ;   //要塞主体
		team[i] = HitsContainerContainer();   //队伍
		heal[i] = HitsContainer();   //治疗
		repair[i] = HitsContainer(); //修复
		jump_u[i] = HitsContainer(); //近突
		jump_f[i] = HitsContainer(); //远突
		snipe[i] = HitsContainer(); //狙击
		turn_ccw[i] = HitsContainer(); //顺时针
		turn_cw[i] = HitsContainer(); //逆时针
	}

}

Game::~Game() {
}

int Game::pskeyIndexOf(char c) {
	if (c >= 'a' && c <= 'z') return c - 87;
	else if (c >= '0' && c <= '9') return c - 48;
	else if (c >= 'A' && c <= 'Z') return c - 29;
	else return -1;
}

Result Game::run(const string& code1, const string& code2,Graphics2D* g2d ) {
	for (int i = 0; i <= 1; i++) {
		fort[i] << &wall[i] << &unit[i];
	}
	for (int i = 0; i <= 1; i++) {
		team[i] << &wall[i] << &unit[i] << &shield[i] << &atk[i];
	}
	if (g2d != nullptr) {
		canDraw = g2d->tryToOccupyBy(this);
	}
	bases[0] = new Base(this, 240, 532, 0);
	bases[1] = new Base(this, 1680, 532, 1);
	const string* codes[2] = { &code1,&code2 };
	if (!main_setup(codes)) {
		return Result(-1, 0, 0, 0.f);
	}

	 
	unsigned timePerTick = Settings::maxTps > 0 ? (unsigned)(1e9 / Settings::maxTps) : 0;
	auto lastTime = steady_clock::now();
	auto startTime = lastTime;

	 while (time < Settings::maxFrame && !end) {
		 auto now = steady_clock::now();
		 if (timePerTick == 0 || duration_cast<nanoseconds>( now - lastTime).count() >= timePerTick) {
			 lastTime = now;
			 time++;
			 base_move();    //要塞车移动
			 judge();    //判断对局是否应该结束
			 update();   //调用所有元素step()方法
			 if (canDraw && g2d->isOpen()) {
				 g2d->handleEvents();
				 g2d->clear();
				 vector<Shape*>& storeContainer = alternate ? elements1 : elements2;//此时一轮更新结束，存储容器存储了所有有效的对象
				 for (Shape* element : storeContainer) {
					 element->draw(g2d);
				 }
				 g2d->update();
			 }
		 }
	 }
	 lastTime = steady_clock::now();
	 double realTime = duration_cast<nanoseconds>(lastTime - startTime).count() / 1e9;
	 cout << endl << "结束了，用时（秒）：" << realTime;
 /*
	 long endTime = System.nanoTime();
	 int status = -1;
	 int winnerHp = 0;
	 System.out.println("1P血量: " + hp[0] + ", 2P血量: " + hp[1]);
	 if (hp0_flg[0] > 0 || hp0_flg[1] > 0) {
		 if (hp0_flg[0] == 0) {
			 status = 1;
			 winnerHp = hp[0];
		 }
		 else if (hp0_flg[1] == 0) {
			 status = 2;
			 winnerHp = hp[1];
		 }
		 else {
			 status = 0;
		 }
	 }
	 else {
		 status = -1;
	 }
	 */
	 //return new Result(status, winnerHp, time, (endTime - startTime) / 1000000000.F);
	if (g2d != nullptr) {
		g2d->release(this);
	}
	return Result(0, 0, 0, 0);
}

bool Game::main_setup(const string** codes) {      //初始布局
	int i = 0;
	while (i <= 1) {
		string wrkStr = regex_replace(*codes[i], regex("[^a-zA-Z0-9]"), "");
		if (wrkStr.length() % 6 != 0 || wrkStr.empty()) {
			return false;
		}
		Xyrt xyrt = to_xyrt(wrkStr, 0);
		if (xyrt.x < 52 || xyrt.x > 328 || xyrt.y < 58 || xyrt.y > 334) {
			return false;
		}

		//Utils.universalSeed = Utils.universalSeed * (xyr[0] % 168 + 48) * (xyr[1] % 168 + 48);
		int baseSeed = (xyrt.x % 168 + 48) * (xyrt.y % 168 + 48);
		seeder[i].setSeed(baseSeed);
		xyrt.x -= 190;
		xyrt.y -= 400;
		/*
		if (xyrt.type==1) {
			cores[i] = new BossCore(this, i == 1 ? -xyr[0] : xyr[0], xyr[1], i);
		}
		else if (xyrt.type == 2) {
			cores[i] = new BossCore2(this, i == 1 ? -xyr[0] : xyr[0], xyr[1], i);
		}
		else {
		*/
		cores[i] = new Core(this, i == 1 ? -xyrt.x : xyrt.x, xyrt.y, i);
		//}
		core_x[i] = cores[i]->x;
		core_y[i] = cores[i]->y;
		int wrkSeed;
		int j = 6;
		int wrkType;
		while (j < wrkStr.length()) {
			xyrt = to_xyrt(wrkStr, j);
			if (xyrt.x < 16 || xyrt.x > 364 || xyrt.y < 20 || xyrt.y > 369 || xyrt.r > 360) {
				return false;
			}
			//wrkSeed = baseSeed * (xyr[0] % 185 + 30) * (xyr[1] % 185 + 30);
			if (i == 1) {
				xyrt.x = (380 - xyrt.x) + 1490;
				xyrt.r = 180 - xyrt.r;
			}
			else {
				xyrt.x += 50;
			}
			xyrt.r = (xyrt.r % 360 + 360) % 360;
			xyrt.y += 132;
			if (xyrt.type < 1 || xyrt.type > 60) {
				return false;
			}
			unit_make(xyrt.x, xyrt.y, xyrt.r, xyrt.type, i);
			/*
			if (wrkType == 13) {
				ShotgunBall unit = (ShotgunBall)elements.get(ID - 1);
				unit.setSeed(wrkSeed);
			}
			else if (wrkType == 23) {
				HenBall unit = (HenBall)elements.get(ID - 1);
				unit.setSeed(wrkSeed);
			}
			*/
			j += 6;
		}
		//kekkaiFields[i] = new KekkaiField(this, i);   //界玉初始化
		i++;
	}
	return true;
}

void Game::base_move() {    //车板移动
	dokkan_flg[0] = false;
	dokkan_flg[1] = false;
	norikomi_flg = false;
	saihai_cnt[0]--;
	saihai_cnt[1]--;
	int j = 0;
	while (j <= 1) {
		if (hp0_flg[j] > 0) {
			j++;
			continue;
		}
		core_x[j] = cores[j]->x;
		core_y[j] = cores[j]->y;
		/*
		for (Shape* s : unit[j].getShapes()) {
			if (s instanceof TargetBall) {
				core_x[j] = s.x;
				core_y[j] = s.y;
				break;
			}
		}
		*/
		j++;
	}
	if (hp0_flg[0] == 0 && hp0_flg[1] == 0 && bases[1]->x - bases[1]->xs - (bases[0]->x + bases[0]->xs) <= 380) {
		norikomi_flg = true;
		cout << "要塞相撞，时间:" << time;
		j = 0;
		while (j <= 1) {
			bool nie_flg = false;
			/*
			for (Shape* s : unit[j].getShapes()) {
				if (s instanceof NieBall nie) {
					nie.alarm = 6;
					nie_flg = true;
					break;
				}
			}
			*/
			if (nie_flg) {
				j++;
				continue;
			}
			int wrkInt = floor(bases[(1 - j)]->xs * 5) + 1;
			wrkInt = max(wrkInt, 0);
			hp[j] -= wrkInt;
			dokkan_flg[j] = true;
			j++;
		}
		decimal wrk = bases[0]->xs;
		bases[0]->xs = -bases[1]->xs;
		if (bases[0]->xs > -1)  bases[0]->xs = -1;
		bases[1]->xs = -wrk;
		if (bases[1]->xs > -1)  bases[1]->xs = -1;
		bases[0]->ys = (-bases[0]->xs) * 2;
		bases[1]->ys = (-bases[1]->xs) * 2;
	}
	return;
}

void Game::judge() {    //裁决爆炸
	int i = 0;
	while (i <= 1) {
		if (hp0_flg[i] == 0 && hp[i] < 1) {
			hp0_flg[i] = 1;
			dokkan_flg[i] = true;
		}
		if (hp0_flg[i] > 0) {
			hp0_flg[i]++;
			dokkan_flg[i] = true;
			if (hp0_flg[i] == 3) {
				bases[i]->kill();
				//cores[i].kill();
			}
			if (hp0_flg[i] > 120) {
				//wrk = 0;
				hp[0] = max(0, hp[0]);
				hp[1] = max(0, hp[1]);
				end = true;
				break;
			}
		}
		i++;
	}
}

void Game::update() {  //单位更新
	alternate = !alternate;
	vector<Shape*>& wrkContainer = alternate ? elements2 : elements1;
	vector<Shape*>& storeContainer = alternate ? elements1 : elements2;
	if (wrkContainer.empty()) return;
	storeContainer.clear();
	wrkContainer.reserve(2 * wrkContainer.size());//！！！需要提前给遍历容器扩容，不然遍历中添加元素导致自动扩容时，迭代器会失效报错
	unsigned idUntilExclude = ID;//本轮遍历截止ID（不含）
	for (auto it = wrkContainer.begin();it != wrkContainer.end();it++) {
		1;
		if ((*it)->id >= idUntilExclude) {
			storeContainer.insert(storeContainer.end(), it, wrkContainer.end());
			break;
		}
		if ((*it)->lifeCyclePhase < 0) {//已经进入销毁阶段的对象不做step
			if ((*it)->parent == nullptr) {//如果已与容器取消绑定，就可以释放内存了
				delete (*it);
			}
		}
		else {
			switch ((*it)->step())
			{
			case KillAction::NONE: {
				//不需要kill，存储为更新后有效元素
				storeContainer.push_back(*it);
				break;
			}
			case KillAction::FAKEKILL: {
				//假kill，暂不存储为更新后有效元素，但插入到工作容器末尾，并修改ID，待本轮遍历结束后整体插入
				Shape* toBeErased = *it;
				toBeErased->fakeKill();
				toBeErased->lifeCyclePhase = 1;
				toBeErased->id = addElement(toBeErased);
				break;
			}
			case KillAction::KILL: {
				//真kill，进入销毁阶段
				(*it)->kill();
				(*it)->lifeCyclePhase = -1;
			}
			default:
				break;
			}
		}
	}
}

Xyrt Game::to_xyrt(const string& str, unsigned offset) {    //5位61进制转x y r数组
	int rxy = 0;
	rxy += pskeyIndexOf(str.at(offset + 1)) * 13845841;
	rxy += pskeyIndexOf(str.at(offset + 2)) * 226981;
	rxy += pskeyIndexOf(str.at(offset + 3)) * 3721;
	rxy += pskeyIndexOf(str.at(offset + 4)) * 61;
	rxy += pskeyIndexOf(str.at(offset + 5));
	int y = rxy % 1000;
	rxy /= 1000;
	int x = rxy % 1000;
	rxy /= 1000;
	return Xyrt(x, y, rxy, pskeyIndexOf(str.at(offset)));
}

unsigned Game::addElement(Shape* s) {      //增加新元素，返回id值
	//要增加到当前用于遍历的容器里，然后遍历结束后整体移动，不然顺序乱了
	vector<Shape*>& wrkContainer = alternate ? elements2 : elements1;
	wrkContainer.push_back(s);
	return ID++;
}

/**
 * @param X x
 * @param Y y
 * @param R 角度
 * @param TYPE 种类 (1-60 间整数)
 * @param S 所属方 (0 或 1)
 */
void Game::unit_make(float X, float Y, int R, int TYPE, int S) {   //创建单位
	int wrk = 0;
	Shape* created;
	switch (TYPE) {
		/*
		case 1: new BowBall(this, X, Y, R, S, TYPE);break;
		case 2: new GunBall(this, X, Y, R, S, TYPE);break;
		case 3: new SwordBall(this, X, Y, R, S, TYPE);break;
		case 4: new TateBall(this, X, Y, R, S, TYPE);break;
		case 5: new BombBall(this, X, Y, R, S, TYPE);break;
		case 6: new MagicBall(this, X, Y, R, S, TYPE);break;
		case 7: new DokyuBall(this, X, Y, R, S, TYPE);break;
		case 8: new YariBall(this, X, Y, R, S, TYPE);break;
		case 9: new CannonBall(this, X, Y, R, S, TYPE);break;
		case 10: new NagiBall(this, X, Y, R, S, TYPE);break;
		case 11: new HaneBall(this, X, Y, R, S, TYPE);break;
		case 12: new RetsuBall(this, X, Y, R, S, TYPE);break;
		case 13: new ShotgunBall(this, X, Y, R, S, TYPE);break;
		case 14: new SniperBall(this, X, Y, R, S, TYPE);break;
		case 15: new UkiBall(this, X, Y, R, S, TYPE);break;
		case 16: new GuideBall(this, X, Y, R, S, TYPE);break;
		case 17: new RepairBall(this, X, Y, R, S, TYPE);break;
		case 18: new HealBall(this, X, Y, R, S, TYPE);break;
		case 19: new KabeBall(this, X, Y, R, S, TYPE);break;
		case 20: new TobiBall(this, X, Y, R, S, TYPE);break;
		case 21: new SenBall(this, X, Y, R, S, TYPE);break;
		case 22: new MinigunBall(this, X, Y, R, S, TYPE);break;
		case 23: new HenBall(this, X, Y, R, S, TYPE);break;
		case 24: new KekkaiBall(this, X, Y, R, S, TYPE);break;
		case 25: new Wood(this, X, Y, S, TYPE); wrk = 1; break;
		case 26: new Stone(this, X, Y, S, TYPE); wrk = 1; break;
		case 27: new Paper(this, X, Y, S, TYPE); wrk = 1; break;
		case 28: new Iron(this, X, Y, S, TYPE); wrk = 1; break;
		case 29: new Jet(this, X, Y, S, TYPE); wrk = 1; break;
		case 30: new Turbo(this, X, Y, S, TYPE); wrk = 1; break;
		case 31: new BoneBall(this, X, Y, R, S, TYPE);break;
		case 32: new GekiBall(this, X, Y, R, S, TYPE);break;
		case 33: new TonBall(this, X, Y, R, S, TYPE);break;
		case 34: new HolyBall(this, X, Y, R, S, TYPE);break;
		case 35: new NinBall(this, X, Y, R, S, TYPE);break;
		case 36: new SyouBall(this, X, Y, R, S, TYPE);break;
		case 37: new HanaBall(this, X, Y, R, S, TYPE);break;
		case 38: new HanBall(this, X, Y, R, S, TYPE);break;
		case 39: new PushBall(this, X, Y, R, S, TYPE);break;
		case 40: new GeiBall(this, X, Y, R, S, TYPE);break;
		case 41: new NieBall(this, X, Y, R, S, TYPE);break;
		case 42: new TargetBall(this, X, Y, R, S, TYPE);break;
		case 43: new TuiBall(this, X, Y, R, S, TYPE);break;
		case 44: new BoxBall(this, X, Y, R, S, TYPE);break;
		case 45: new DarkBall(this, X, Y, R, S, TYPE);break;
		case 46: new HeriBall(this, X, Y, R, S, TYPE);break;
		case 47: new SaiBall(this, X, Y, R, S, TYPE);break;
		case 48: new KnightBall(this, X, Y, R, S, TYPE);break;
		case 49: new KakuBall(this, X, Y, R, S, TYPE);break;
		case 50: new ShaBall(this, X, Y, R, S, TYPE);break;
		case 51: new StarBall(this, X, Y, R, S, TYPE);break;
		case 52: new ConBall(this, X, Y, R, S, TYPE);break;
		case 53: new KanBall(this, X, Y, R, S, TYPE);break;
		case 54: new SearchBall(this, X, Y, R, S, TYPE);break;
		case 55: new Near(this, X, Y, S, TYPE); wrk = 1; break;
		case 56: new Far(this, X, Y, S, TYPE); wrk = 1; break;
		case 57: new Wide(this, X, Y, S, TYPE); wrk = 1; break;
		case 58: new Narrow(this, X, Y, S, TYPE); wrk = 1; break;
		case 59: new Snipe(this, X, Y, S, TYPE); wrk = 1; break;
		case 60: new Elevator(this, X, Y, S, TYPE); wrk = 1; break;
		*/
	default: {created = new Ball(this, X, Y, R, S, TYPE);break;}
	}
		switch (wrk) {
		case 0: {
			Ball* unit = (Ball*)created;
			if (unit->side != 0) {
				unit->cnt = -((380 - ((int)unit->x - 1490)) % unit->speed);
			}
			else {
				unit->cnt = -((int)(unit->x - 50) % unit->speed);
			}
			break;
		}
		case 1: break;
		default: break;
	}
}
