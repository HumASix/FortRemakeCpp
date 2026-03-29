// FortRemakeCpp.cpp: 定义应用程序的入口点。
//

#include "FortRemakeCpp.h"

using namespace std;

int main()
{
    srand(time(NULL));
	cout << "Hello CMake." << endl;


    Graphics2D win(1440, 600, "面向对象绘图窗口");
    Game* game = new Game();
    /*
    vector<Shape*> shapes;
    CompositeShape* s=new CompositeShape(100, 0);
    shapes.push_back(s);
    (*s) << s->circle(100, 200, 50)
        << s->rectangle(200, 200, 111, 222)
        << s->polygon(222, 222, vector<Point>({ Point(11, 22), Point(-22,-11), Point(33,66) }))
        << s->sector(400, 200, 66, 40, 70);
    shapes.push_back(new RoundedRect(10, 10, 0, 0, 80, 50, 10));
    shapes.push_back(new Base(game, 1920-240, 300, 0));
    shapes.push_back(new Core(game, 650, 450, 0));
    */
    game->run("000P6R222222100dYp", "000P6R100P6R", &win);
	return 0;
}
