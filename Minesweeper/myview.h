#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "gamemap.h"

class BoxItem;
class QGraphicsLineItem;
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(int y, int x, int mineNum, QWidget *parent = 0);
    ~MyView();
    void resetGame();
    void againGame();
    void changeViewSize(int y, int x, int mineNum);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void changeMap(int y, int x, int index);
    void showAllMine();
signals:
    void victory();
    void gameOver();
    void beginGame();
    void updateMine(bool addOrSub);
private:
    void initView();
    void initScene();
    void createBox();
    void createGameMap();
    void drawLine();
public slots:
private:
    enum GameLayout {
        DEFAULT_X = 30,
        DEFAULT_Y = 16,
        MAX_Y = 24,
        MAX_X = 30,
        DEFAULT_MINE = 99,
        BOX_SIZE = 40,
        DEFAULT_Y_OFFSET = 60
    };
    enum MouseEvent{
        LEFT_CLICK,
        RIGHT_CLICK,
        DOUBLE__CLICK
    };
    int viewCy;
    int viewCx;
    int m_mineNum;
    int countOkBox;
    int currentOkBox;
    bool updateTimeLabel;
    GameMap *gameMap;
    BoxItem *boxMap[MAX_Y][MAX_X];
    QGraphicsLineItem *yLineGroup[MAX_X];
};

#endif // MYVIEW_H
