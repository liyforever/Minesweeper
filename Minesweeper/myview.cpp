#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include "myview.h"
#include "boxitem.h"

MyView::MyView(int y, int x, int mineNum, QWidget *parent) :
    viewCy(y), viewCx(x), m_mineNum(mineNum),currentOkBox(0), countOkBox(y*x-mineNum),
    QGraphicsView(parent)
{
    createGameMap();
    updateTimeLabel = true;
    initView();
    createBox();
    drawLine();
}

MyView::~MyView()
{

}

void MyView::resetGame()
{
    updateTimeLabel = true;
    qDebug() << "MyViewResetGame";
    currentOkBox = 0;
    gameMap->resetGameMap();
}

void MyView::againGame()
{
    updateTimeLabel = true;
    currentOkBox = 0;
    gameMap->againGameMap();
}

void MyView::changeViewSize(int y, int x, int mineNum)
{
    if(y<viewCy)//如果新尺寸小于当前尺寸
    {
        for(int row=y;row!=viewCy;++row)
            for(int column=0;column!=MAX_X;++column)
                boxMap[row][column]->hide();
    } else {
        for(int row=viewCy;row!=y;++row)
            for(int column=0;column!=MAX_X;++column)
                boxMap[row][column]->show();
    }
    for(int myX=0;myX!=x;++myX) {
        yLineGroup[myX]->setLine(myX * BOX_SIZE,0,myX * BOX_SIZE ,y * BOX_SIZE);
    }
    viewCy = y;
    viewCx = x;
    m_mineNum = mineNum;
    updateTimeLabel = true;
    currentOkBox = 0;
    countOkBox = y*x-mineNum;
    gameMap->changeGameMapSize(viewCy, viewCx, m_mineNum);
}

void MyView::initView()
{
    // 使用抗锯齿渲染
    setRenderHint(QPainter::Antialiasing);
    // 设置缓存背景，这样可以加快渲染速度
    setCacheMode(CacheBackground);
    setMinimumSize(viewCx*BOX_SIZE+5, viewCy*BOX_SIZE+5);
    setMaximumSize(viewCx*BOX_SIZE+5, viewCy*BOX_SIZE+5);

    //设置场景
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, viewCx*BOX_SIZE, viewCy*BOX_SIZE);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
}

void MyView::createBox()
{
    for(int y=0; y!=viewCy; ++y)
        for(int x=0; x!=viewCx; ++x)
        {
            boxMap[y][x] = new BoxItem();
            scene()->addItem(boxMap[y][x]);
            boxMap[y][x]->setPos(x * BOX_SIZE, y * BOX_SIZE);
        }
}

void MyView::createGameMap()
{
    gameMap = new GameMap(viewCy, viewCx, m_mineNum, this);
    connect(gameMap, SIGNAL(changeBox(int,int,int)),this,SLOT(changeMap(int,int,int)));
    connect(gameMap, SIGNAL(gameover()), this, SLOT(showAllMine()));
    connect(gameMap, SIGNAL(updateMine(bool)),SIGNAL(updateMine(bool)));
}

void MyView::drawLine()
{
    for(int y=0; y!=viewCy; ++y)
        scene()->addLine(0,y * BOX_SIZE,viewCx * BOX_SIZE,y * BOX_SIZE);
    for(int x=0; x!=viewCx; ++x)
        yLineGroup[x] = scene()->addLine(x * BOX_SIZE,0,x * BOX_SIZE ,viewCy * BOX_SIZE);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    if(updateTimeLabel)
    {
        updateTimeLabel = false;
        emit beginGame();
    }
    if(event->button() == Qt::LeftButton)
        gameMap->Test(event->pos().y() / BOX_SIZE, event->pos().x() / BOX_SIZE, LEFT_CLICK);
    if(event->button() == Qt::RightButton)
        gameMap->Test(event->pos().y() / BOX_SIZE, event->pos().x() / BOX_SIZE, RIGHT_CLICK);
}

void MyView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(updateTimeLabel)
    {
        updateTimeLabel = false;
        emit beginGame();
    }
    if(event->button() == Qt::LeftButton) {
        gameMap->Test(event->pos().y() / BOX_SIZE, event->pos().x() / BOX_SIZE, DOUBLE__CLICK);
        qDebug() << "double";
    }
}


void MyView::changeMap(int y, int x, int index)
{
    if((index>=1 && index <=6) || (index == 9)) {
        ++currentOkBox;
        qDebug() << "currentOkBox:" << currentOkBox << "\n";
    }
    //qDebug() << "("<< y << "," << x <<
      //       ")" <<"index:" << index << "\n";
    boxMap[y][x]->changBoxState(index);
    if(currentOkBox == countOkBox) {
        qDebug() << "victory" << countOkBox;
        emit victory();
    }
}

void MyView::showAllMine()
{
    gameMap->showMine();
    emit gameOver();
}

