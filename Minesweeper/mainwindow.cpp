#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include <QLabel>
#include <QVector>
#include <QPainter>
#include <QTimer>
#include <QDataStream>
#include <QFile>
#include "mainwindow.h"
#include "resultdialog.h"
#include "optiondialog.h"
#include "windialog.h"


MainWindow::MainWindow()
{
    createCentralView();
    createActions();
    createMenus();
    createLabel(DEFAULT_Y, DEFAULT_X);
    createGameTime();
    initGameData();
    createResultDialog();
    createWinDialog();
    setWindowIcon(QIcon(":/Images/Icon.jpeg"));
    setWindowTitle(tr("扫雷"));
    setMinimumSize(DEFAULT_X * BOX_SIZE,DEFAULT_Y * BOX_SIZE + DEFAULT_Y_OFFSET);
    setMaximumSize(DEFAULT_X * BOX_SIZE,DEFAULT_Y * BOX_SIZE + DEFAULT_Y_OFFSET);
    mineNum = DEFAULT_MINE;
    optionDialog = NULL;
}

void MainWindow::showResult()
{
    qDebug()<<currentPlayTime << "\n"
           << bestTime << "\n"
           << playCount << "\n"
           << winCount << "\n";
    ++playCount;
    resultDialog->resetData(currentPlayTime,bestTime,playCount,winCount);
    resultDialog->exec();
    gameTimer->stop();
}

void MainWindow::showOpition()
{
    if(optionDialog == NULL)
    {
        optionDialog = new OptionDialog(this);
        connect(optionDialog,SIGNAL(changeSize(int,int,int)),this,SLOT(changeSize(int,int,int)));
    }
    optionDialog->exec();
}

void MainWindow::showWin()
{
    if(currentPlayTime<bestTime)
        bestTime = currentPlayTime;
    ++winCount;
    ++playCount;
    winDialog->resetData(currentPlayTime,bestTime,playCount,winCount);
    currentPlayTime = 0;
    winDialog->exec();
    gameTimer->stop();
}

void MainWindow::gameBegin()
{
    gameTimer->start(1000);
}

void MainWindow::updateGameTime()
{
    ++currentPlayTime;
    timeLabel->setNum(currentPlayTime);
}

void MainWindow::resetGame()
{
    gameView->resetGame();
    currentPlayTime = 0;
    mineLabel->setNum(mineNum);
    timeLabel->setNum(0);
}

void MainWindow::againGame()
{
    gameView->againGame();
    currentPlayTime = 0;
    mineLabel->setNum(mineNum);
    timeLabel->setNum(0);
}

void MainWindow::changeSize(int row, int column, int mine)
{
    qDebug()<<"row"<<row<<"column"<<column
           <<"mine"<<mine ;
    clientCx = column;
    clientCy = row;
    mineNum = mine;
    currentMineNum = mine;
    currentPlayTime = 0;
    qDebug()<<"dddddddddddddddddddddddddddddddddddddddddddd\n";
    qDebug()<<"myXXX" << clientCx << "myYY" << clientCy << "clientCx" << clientCx * BOX_SIZE
           << "clientyCy" << clientCy * BOX_SIZE + DEFAULT_Y_OFFSET
           <<"\n";
    mineLabel->setNum(mineNum);
    timeLabel->setNum(0);
    gameView->changeViewSize(row, column, mine);
    setMinimumSize(clientCx * BOX_SIZE,clientCy * BOX_SIZE + DEFAULT_Y_OFFSET);
    setMaximumSize(clientCx * BOX_SIZE,clientCy * BOX_SIZE + DEFAULT_Y_OFFSET);
    setLabelSize(clientCy, clientCx);
}

void MainWindow::updateMineLabel(bool addOrSub)
{
    qDebug()<< "updateMineLabel";
    if(addOrSub)
    {
        ++currentMineNum;
        mineLabel->setNum(currentMineNum);
    } else {
        --currentMineNum;
        mineLabel->setNum(currentMineNum);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QFile file("MineSweeper.dat");
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);
    out << bestTime << playCount << winCount;
    QMainWindow::closeEvent(event);
}

void MainWindow::createActions()
{
    newGameAction = new QAction(tr("新游戏(&N)"), this);
    connect(newGameAction,SIGNAL(triggered()),this,SLOT(againGame()));

    infoAction = new QAction(tr("统计信息(&S)"), this);;

    optionAction = new QAction(tr("选项(&O)"), this);
    connect(optionAction,SIGNAL(triggered()),this,SLOT(showOpition()));

    changFaceAction = new QAction(tr("更改外观(&A)"), this);

    exitAction = new QAction(tr("退出(&X)"), this);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    seeHelpAction = new QAction(tr("查看帮助(&O)"), this);

    aboutGameAction = new QAction(tr("关于扫雷(&A)"), this);

    clientGameAction = new QAction(tr("连接获取更多游戏(&M)"), this);
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("游戏(&G)"));
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(infoAction);
    gameMenu->addAction(optionAction);
    gameMenu->addAction(changFaceAction);
    gameMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(seeHelpAction);
    helpMenu->addAction(aboutGameAction);
    helpMenu->addAction(clientGameAction);
}

void MainWindow::createLabel(int y,int x)
{
    currentPlayTime = 0;
    timeLabel = new QLabel(this);
    timeLabel->setNum(currentPlayTime);


    currentMineNum = DEFAULT_MINE;
    mineLabel = new QLabel(this);
    mineLabel->setNum(currentMineNum);
    setLabelSize(y, x);
}

void MainWindow::setLabelSize(int y, int x)
{
    timeLabel->setGeometry(20,y * BOX_SIZE + 20,30,30);
    timeLabel->setStyleSheet("background:rgba(100,225,100");
    mineLabel->setGeometry((x-1)*BOX_SIZE,y * BOX_SIZE + 20,30,30);
}

void MainWindow::createCentralView()
{
    gameView = new MyView(DEFAULT_Y,DEFAULT_X,DEFAULT_MINE,this);
    connect(gameView,SIGNAL(gameOver()),this,SLOT(showResult()));
    connect(gameView,SIGNAL(victory()),this,SLOT(showWin()));
    connect(gameView,SIGNAL(beginGame()),this,SLOT(gameBegin()));
    connect(gameView,SIGNAL(updateMine(bool)),this,SLOT(updateMineLabel(bool)));
    setCentralWidget(gameView);
}

void MainWindow::createGameTime()
{
    gameTimer = new QTimer(this);
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(updateGameTime()));
}

void MainWindow::createResultDialog()
{
    resultDialog = new ResultDialog(50,40,40,20,this);
    resultDialog->hide();
    connect(resultDialog,SIGNAL(resetGame()),this,SLOT(resetGame()));
    connect(resultDialog,SIGNAL(exieGame()),this,SLOT(close()));
    connect(resultDialog,SIGNAL(againGame()),this,SLOT(againGame()));
}

void MainWindow::createWinDialog()
{
    winDialog = new WinDialog(50,40,40,20,this);
    resultDialog->hide();
    connect(winDialog,SIGNAL(exieGame()),this,SLOT(close()));
    connect(winDialog,SIGNAL(againGame()),this,SLOT(againGame()));
}

void MainWindow::initGameData()
{
    QFile file("MineSweeper.dat");
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);
    in >> bestTime >> playCount >> winCount;
    if(!bestTime)
        bestTime = 10000;
}
