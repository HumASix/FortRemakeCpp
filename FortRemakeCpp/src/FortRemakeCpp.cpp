// FortRemakeCpp.cpp: 定义应用程序的入口点。
//

#include "FortRemakeCpp.h"

using namespace std;

int main()
{
    srand(time(NULL));
	cout << "Hello CMake." << endl;


    Graphics2D win(1440, 650, "面向对象绘图窗口");
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
    game->run("000u7C1mKWf81kO8sn1l6WwQ1mKNn91ljkmI1lk7xs1lj5iL1oLMAb11AsIj1ljk511liXRf1liYnI", "000Vz51laDpR1laFzb1laIgl1laKWd1laN6m1laQAw1laScT1mtiR81mY7Kx1p0uGw1p0agv1lK9hU1lKdjO1lKh5k1lKlE11lKryF", &win);
	return 0;
}
