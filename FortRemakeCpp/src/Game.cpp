#include "Game.h"
using namespace std;
Game::Game() {
	
}

short Game::pskeyIndexOf(char c) {
	if (c >= 'a' && c <= 'z') return c - 87;
	else if (c >= '0' && c <= '9') return c - 48;
	else if (c >= 'A' && c <= 'Z') return c - 29;
	else return -1;
}

Result Game::run(const string& code1, const string& code2) {
	/*
	for (int i = 0; i <= 1; i++) {
		fort[i].addShape(wall[i]);
		fort[i].addShape(unit[i]);
	}
	for (int i = 0; i <= 1; i++) {
		team[i].addShape(wall[i]);
		team[i].addShape(unit[i]);
		team[i].addShape(shield[i]);
		team[i].addShape(atk[i]);
	}

	bases = new Base[]{ new Base(this, 240, 532, 0), new Base(this, 1680, 532, 1) };

	if (!main_setup(new String[]{ code1, code2 })) {
		return new Result(-1, 0, 0, 0.f);
	}
	/*稍后处理
	if (ENABLE_VISUALIZATION) {
		java.awt.EventQueue.invokeLater(() -> {
			window = new GameWindow(1920, 960, 60).setList(new ArrayList<>(elements.values()));
			window.setVisible(true);
		});
	}

	 */
	 /*
	 long timePerTick = Settings.LOGIC_TPS > 0 ? 1000000000L / Settings.LOGIC_TPS : 0;
	 long lastTime = System.nanoTime();
	 long startTime = lastTime;

	 while (time < Settings.max_run_time && !end) {
		 long now = System.nanoTime();
		 if (timePerTick == 0 || now - lastTime >= timePerTick) {
			 lastTime = now;
			 time++;
			 base_move();    //要塞车移动
			 judge();    //判断对局是否应该结束
			 update();   //调用所有元素step()方法
			 /*稍后处理
			 if (ENABLE_VISUALIZATION && window != null) {
				 window.setList(new ArrayList<>(elements.values()));
				 window.requestRender();
			 }

			  *//*
		 }
	 }
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
	return Result(0, 0, 0, 0);
}

bool Game::main_setup(const string* codes) {      //初始布局
	/*
	i = 0;
	while (i <= 1) {
		code[i] = code[i].replaceAll("[^a-zA-Z0-9]", "");
		if (code[i].length() % 6 != 0) {
			return false;
		}
		int[] xyr = to_xyr(code[i].substring(1, 6));
		if (xyr[0] < 52 || xyr[0] > 328 || xyr[1] < 58 || xyr[1] > 334) {
			return false;
		}

		Utils.universalSeed = Utils.universalSeed * (xyr[0] % 168 + 48) * (xyr[1] % 168 + 48);
		int baseSeed = (xyr[0] % 168 + 48) * (xyr[1] % 168 + 48);
		seeder[i].setSeed(baseSeed);
		xyr[0] -= 190;
		xyr[1] -= 400;
		if (code[i].startsWith("1")) {
			cores[i] = new BossCore(this, i == 1 ? -xyr[0] : xyr[0], xyr[1], i);
		}
		else if (code[i].startsWith("2")) {
			cores[i] = new BossCore2(this, i == 1 ? -xyr[0] : xyr[0], xyr[1], i);
		}
		else {
			cores[i] = new Core(this, i == 1 ? -xyr[0] : xyr[0], xyr[1], i);
		}
		core_x[i] = cores[i].x;
		core_y[i] = cores[i].y;
		int wrkSeed;
		j = 6;
		int wrkType;
		while (j < code[i].length()) {
			xyr = to_xyr(code[i].substring(j + 1, j + 6));
			if (xyr[0] < 16 || xyr[0] > 364 || xyr[1] < 20 || xyr[1] > 369 || xyr[2] > 360) {
				return false;
			}
			wrkSeed = baseSeed * (xyr[0] % 185 + 30) * (xyr[1] % 185 + 30);
			if (i == 1) {
				xyr[0] = (380 - xyr[0]) + 1490;
				xyr[2] = 180 - xyr[2];
			}
			else {
				xyr[0] += 50;
			}
			xyr[2] = (xyr[2] % 360 + 360) % 360;
			xyr[1] += 132;
			wrkType = pskey.indexOf(code[i].charAt(j));
			if (wrkType < 1 || wrkType > 60) {
				return false;
			}
			unit_make(xyr[0], xyr[1], xyr[2], wrkType, i);
			if (wrkType == 13) {
				ShotgunBall unit = (ShotgunBall)elements.get(ID - 1);
				unit.setSeed(wrkSeed);
			}
			else if (wrkType == 23) {
				HenBall unit = (HenBall)elements.get(ID - 1);
				unit.setSeed(wrkSeed);
			}
			j += 6;
		}
		kekkaiFields[i] = new KekkaiField(this, i);   //界玉初始化
		i++;
	}
	*/
	return true;
}

void Game::base_move() {    //车板移动
	/*
	dokkan_flg[0] = false;
	dokkan_flg[1] = false;
	norikomi_flg = false;
	saihai_cnt[0]--;
	saihai_cnt[1]--;
	j = 0;
	while (j <= 1) {
		if (hp0_flg[j] > 0) {
			j++;
			continue;
		}
		core_x[j] = cores[j].x;
		core_y[j] = cores[j].y;
		for (Shape s : unit[j].getShapes()) {
			if (s instanceof TargetBall) {
				core_x[j] = s.x;
				core_y[j] = s.y;
				break;
			}
		}
		j++;
	}
	if (hp0_flg[0] == 0 && hp0_flg[1] == 0 && bases[1].x - bases[1].xs - (bases[0].x + bases[0].xs) <= 380) {
		norikomi_flg = true;
		System.out.println("要塞相撞，时间: " + time);
		j = 0;
		while (j <= 1) {
			boolean nie_flg = false;
			for (Shape s : unit[j].getShapes()) {
				if (s instanceof NieBall nie) {
					nie.alarm = 6;
					nie_flg = true;
					break;
				}
			}
			if (nie_flg) {
				j++;
				continue;
			}
			wrk = (float)(Math.floor(bases[(1 - j)].xs * 5) + 1);
			wrk = Math.round(wrk);
			if (wrk < 0) {
				wrk = 0;
			}
			hp[j] -= (int)wrk;
			dokkan_flg[j] = true;
			j++;
		}
		wrk = bases[0].xs;
		bases[0].xs = -bases[1].xs;
		if (bases[0].xs > -1) { bases[0].xs = -1; }
		bases[1].xs = -wrk;
		if (bases[1].xs > -1) { bases[1].xs = -1; }
		bases[0].ys = (-bases[0].xs) * 2;
		bases[1].ys = (-bases[1].xs) * 2;
	}
	*/
	return;
}

void Game::judge() {    //裁决爆炸
	i = 0;
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
				wrk = 0;
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
	/*
	List<Integer> keys = new ArrayList<>(elements.keySet());

	for (Integer key : keys) {
		if (!elements.containsKey(key)) {
			continue;
		}
		elements.get(key).step();
	}
	*/
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
	elements.emplace(ID, s);
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
		default: new Ball(this, X, Y, R, S, TYPE);break;
		}
		switch (wrk) {
		case 0: {
			Ball unit = (Ball)elements.get(ID - 1);
			if (unit.side != 0) {
				unit.cnt = (int)(-(380 - (unit.x - 1490)) % unit.speed);
			}
			else {
				unit.cnt = (int)(-(unit.x - 50) % unit.speed);
			}
			break;
		}
		case 1: break;
		default: break;
		*/
	}
}
