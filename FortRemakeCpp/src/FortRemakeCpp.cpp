// FortRemakeCpp.cpp: 定义应用程序的入口点。
//

#include "FortRemakeCpp.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
    Graphics2D win(800, 600, "面向对象绘图窗口");
    vector<Shape*> s;
    s.push_back(new Round(100, 200, 50));
    s.push_back(new Rect(200, 200, 111, 222, 333, 444));
    s.push_back(new Poly(222, 222, vector<Point>({ Point(11, 22), Point(-22,-11), Point(33,66) })));
    s.push_back(new Sector(400, 200, 66, 40, 70));
    while (win.isOpen()) {
        win.handleEvents();
        //测试绘图
        // ======================
        // 你的游戏逻辑
        // ======================
        // update();
        // checkCollision();

        win.clear();
        for (Shape* shape : s) {
            shape->draw(&win);
        }
        win.update();
        // win.drawPolygon( ... );
    }
	return 0;
}
