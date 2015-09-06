#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <cstdlib>
#include <QBitArray>
#include <bitset>
#include <vector>
#include <queue>
using namespace std;

struct Point
{
    Point(int _y=0, int _x=0)
        : y(_y), x(_x)
    {}
    Point(const Point& pp)
        : y(pp.y), x(pp.x)
    {}
    int y;
    int x;
};

//第0位是否有雷,第1位是否可以被点击，第2位标志是否有旗子，第3位标志是否是问号
struct Node{
    int sum;
    bitset<6> info;
    Node():sum(0)
    {}
};

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(int _y, int _x, int _mineNum, QObject *parent = 0);
    void ShowMap();
    void Test(int y, int x,int clickInfo);
    void showMine();
    void resetGameMap();
    void changeGameMapSize(int _row, int _column, int _mineNum);
    void againGameMap();
signals:
    void changeBox(int y, int x, int mineNum);
    void gameover();
    void updateMine(bool addOrSub);
public slots:
private:
    //第0位是否有雷,第1位是否接受左键点击，第2位标志是否有旗子，第3位标志是否是问号,第4位是否接受右键点击
    enum TestBit {
        TEST_MINE,
        TEST_ACCEPT_LCLICK,
        TEST_FLAG,
        TEST_QUESTION,
        TEST_ACCEPT_RCLICK,
        TEST_RESET
    };
    enum MouseEvent{
        LEFT_CLICK,
        RIGHT_CLICK,
        DOUBLE__CLICK
    };
    enum BoxInfo {
        BOX_DEFAULT,
        BOX_1,
        BOX_2,
        BOX_3,
        BOX_4,
        BOX_5,
        BOX_6,
        BOX_QUESTION,
        BOX_FLAG,
        BOX_EMPTY,
        BOX_MINE,
        BOX_STATECOUNT
    };
    enum MapSize{
        MAX_Y = 24,
        MAX_X = 30
    };
    enum MineInfo {
        SUB_MINE,
        ADD_MINE
    };

    void initGameMap();
    int testAround(int y, int x, int testInfo);
    bool TestRange(int y, int x);
    void leftClick(int y, int x);
    void rightClick(int y, int x);
    void doubleClick(int y, int x);
    Point Transform(int y, int x, int direction);
private:
    int gameMapY_;
    int gameMapX_;
    int mineNum_;
    Node map_[MAX_Y][MAX_X];
};

#endif // GAMEMAP_H
