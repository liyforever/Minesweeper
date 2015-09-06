#include "gamemap.h"
#include <iostream>
#include <QDebug>
//第0位是否有雷,第1位是否可以被点击，第2位标志是否有旗子，第3位标志是否是问号,第4位是否接受右键点击，第5位标志那些box需要重置
GameMap::GameMap(int _y, int _x, int _mineNum_, QObject *parent) :
    gameMapY_(_y), gameMapX_(_x), mineNum_(_mineNum_), QObject(parent)
{
    initGameMap();
    //ShowMap();
}

void GameMap::initGameMap()
{
    int thunderNum=1;
    int tmpX, tmpY;
    while(thunderNum <= mineNum_) {
        tmpY = qrand()% (gameMapY_-1);
        tmpX = qrand()% (gameMapX_-1);
        if(!(map_[tmpY][tmpX].info.test(0))) {
            map_[tmpY][tmpX].info.set(0);
            ++thunderNum;
        }
    }
    for(int row=0; row!=gameMapY_; ++row) {
        for(int column = 0; column!=gameMapX_; ++column)
            if(!map_[row][column].info.test(TEST_MINE))
                map_[row][column].sum = testAround(row, column,TEST_MINE);
    }
}

void GameMap::againGameMap()
{
    resetGameMap();
    for(int row=0; row!=gameMapY_; ++row)
        for(int column=0; column!=gameMapX_; ++column)
            map_[row][column].info.reset();
    initGameMap();
}

void GameMap::ShowMap()
{    int i = 0;
     cout << "\t";
     for(int c=0; c!=gameMapX_; ++c)
         cout << c << "       ";
     for(int row=0; row!=gameMapY_; ++row) {
         for(int column = 0; column!=gameMapX_; ++column)
         {
             if((i%gameMapX_)==0) {
                 cout << endl;
                 cout << row;
             }
             cout << "(" << map_[row][column].sum << ","
                  << map_[row][column].info << ")";
             ++i;
         }
     }
     cout << endl;
}

int GameMap::testAround(int y, int x, int testInfo)
{
    int sum = 0;
    if(map_[y-1][x-1].info.test(testInfo) && TestRange(y-1,x-1))//1
        ++sum;
    if(map_[y-1][x].info.test(testInfo) && TestRange(y-1,x))//2
        ++sum;
    if(map_[y-1][x+1].info.test(testInfo) && TestRange(y-1,x+1))//3
        ++sum;
    if(map_[y][x-1].info.test(testInfo) && TestRange(y,x-1))//4
        ++sum;
    if(map_[y][x+1].info.test(testInfo) && TestRange(y,x+1))//5
        ++sum;
    if(map_[y+1][x-1].info.test(testInfo) && TestRange(y+1,x-1))//6
        ++sum;
    if(map_[y+1][x].info.test(testInfo) && TestRange(y+1,x))//7
        ++sum;
    if(map_[y+1][x+1].info.test(testInfo) && TestRange(y+1,x+1))//8
        ++sum;
    return sum;
}

bool GameMap::TestRange(int y, int x)
{
    if(y>=0 && y < gameMapY_ && x>=0 && x<gameMapX_)
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameMap::Test(int y, int x, int clickInfo)
{
    switch (clickInfo) {
    case LEFT_CLICK:
        leftClick(y, x);
        return;
    case RIGHT_CLICK:
        rightClick(y, x);
        return;
    case DOUBLE__CLICK:
        doubleClick(y, x);
    default:
        return;
    }
}

void GameMap::showMine()
{
    for(int row=0; row!=gameMapY_; ++row)
        for(int column=0; column!=gameMapX_; ++column)
            if(map_[row][column].info.test(TEST_MINE))
            {
                map_[row][column].info.set(TEST_RESET);//设置重新游戏时需要重置
                changeBox(row, column, BOX_MINE);
            }
}

void GameMap::resetGameMap()
{
    for(int row=0; row!=gameMapY_; ++row)
        for(int column=0; column!=gameMapX_; ++column)
            if(map_[row][column].info.test(TEST_RESET))
            {
                if(map_[row][column].info.test(TEST_MINE))
                {
                    map_[row][column].info.reset();
                    map_[row][column].info.set(TEST_MINE);
                } else {
                    map_[row][column].info.reset();
                }
                emit changeBox(row,column,BOX_DEFAULT);
            }
}

void GameMap::changeGameMapSize(int _row, int _column, int _mineNum)
{
    gameMapX_ = _column;
    gameMapY_ = _row;
    mineNum_ = _mineNum;
    againGameMap();
}


void GameMap::leftClick(int y, int x)
{
    //case 1如果不接受点击,忽略事件
    if(map_[y][x].info.test(TEST_ACCEPT_LCLICK))
        return;
    //case 2如果是雷,就发射gameove信号,然后返回
    if(map_[y][x].info.test(TEST_MINE)) {
        emit gameover();
        return;
    }
    //case 3 点到不是雷，周围有雷，设置改位置不可点,返回周围雷数
    if(map_[y][x].sum!=0) {
        map_[y][x].info.set(TEST_ACCEPT_LCLICK);//设置不接受左键点击
        map_[y][x].info.set(TEST_ACCEPT_RCLICK);//设置不接收右键点击
        map_[y][x].info.set(TEST_RESET);//设置重新游戏时需要重置
        emit changeBox(y, x, map_[y][x].sum);
        return;
    }
    //case 4 点到的是空格,拓扑周围
    Point tmpPoint;
    Point tp;
    queue<Point> pq;
    pq.push(Point(y,x));
    while(!pq.empty())
    {
        tmpPoint = pq.front();
        pq.pop();
        if(!map_[tmpPoint.y][tmpPoint.x].info.test(TEST_ACCEPT_LCLICK)){
            map_[tmpPoint.y][tmpPoint.x].info.set(TEST_ACCEPT_LCLICK);
            map_[tmpPoint.y][tmpPoint.x].info.set(TEST_ACCEPT_RCLICK);
            map_[tmpPoint.y][tmpPoint.x].info.set(TEST_RESET);//设置重新游戏时需要重置
            emit changeBox(tmpPoint.y, tmpPoint.x, BOX_EMPTY);
        }
        for(int direction=1; direction<=8; ++direction)
        {
            tp = Transform(tmpPoint.y,tmpPoint.x,direction);
            if(TestRange(tp.y, tp.x) && !map_[tp.y][tp.x].info.test(TEST_ACCEPT_LCLICK)) {//如果位置有效，且没点点过
                //cout << tp.y << "\t" << tp.x << endl;
                if(map_[tp.y][tp.x].sum == 0) {//如果这个位置没雷
                    //cout << tp.y << "\t" << tp.x << endl;
                    //gameMap[tp.y][tp.x].info.set(1);
                    pq.push(tp);
                } else  {//有雷
                    emit changeBox(tp.y, tp.x, map_[tp.y][tp.x].sum);
                    map_[tp.y][tp.x].info.set(TEST_ACCEPT_LCLICK);
                    map_[tp.y][tp.x].info.set(TEST_ACCEPT_RCLICK);
                    map_[tp.y][tp.x].info.set(TEST_RESET);//设置重新游戏时需要重置
                }
            }
        }
    }
}
//第0位是否有雷,第1位是否可以被点击，第2位标志是否有旗子，第3位标志是否是问号
void GameMap::rightClick(int y, int x)
{
    if((map_[y][x].info.test(TEST_ACCEPT_RCLICK)))//如果不接受右键点击就忽略
        return;
    if(map_[y][x].info.test(TEST_FLAG)) {//如果当前是旗子
        map_[y][x].info.set(TEST_FLAG,false);//取消旗子标志取消
        map_[y][x].info.set(TEST_ACCEPT_LCLICK,false);//设置该位置接受左击事件
        map_[y][x].info.set(TEST_QUESTION);//设置当前位置为问号
        map_[y][x].info.set(TEST_RESET);//设置当前位置需要重置
        emit updateMine(ADD_MINE);
        emit changeBox(y, x, BOX_QUESTION);
    } else if(map_[y][x].info.test(TEST_QUESTION)) {//如果当前是问号
        map_[y][x].info.set(3,false);//取消问号标志
        map_[y][x].info.set(TEST_RESET,false);
        emit changeBox(y, x, BOX_DEFAULT);
    } else {//如果还没被点击过
        map_[y][x].info.set(TEST_FLAG);//设置当前位置为旗子
        map_[y][x].info.set(TEST_ACCEPT_LCLICK);//设置忽略左击事件
        map_[y][x].info.set(TEST_RESET);//设置当前位置需要重置
        emit updateMine(SUB_MINE);
        emit changeBox(y, x, BOX_FLAG);
    }
}

void GameMap::doubleClick(int y, int x)
{
    qDebug() << "myDoubleClick";
    if(map_[y][x].sum != testAround(y,x,TEST_FLAG))//如果旗子数量不和雷数相等忽略双击事件
        return;
    Point p;
    for(int i=0;i<=8;++i) {//八个方向发送双击事件
        p = Transform(y,x,i);
        if(TestRange(p.y,p.x))
            Test(p.y,p.x,LEFT_CLICK);
    }
}

Point GameMap::Transform(int y, int x, int direction)
{
    switch (direction) {
    case 1:
        return Point(y-1, x-1);
    case 2:
        return Point(y-1, x);
    case 3:
        return Point(y-1, x+1);
    case 4:
        return Point(y, x-1);
    case 5:
        return Point(y, x+1);
    case 6:
        return Point(y+1, x-1);
    case 7:
        return Point(y+1, x);
    case 8:
        return Point(y+1, x+1);
    }
}
