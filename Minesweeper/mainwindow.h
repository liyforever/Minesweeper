#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myview.h"

class TimeLabel;
class QAction;
class QLabel;
class QTimer;
class ResultDialog;
class WinDialog;
class OptionDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();
public slots:
    void showResult();
    void showOpition();
    void showWin();
    void gameBegin();
    void updateGameTime();
    void resetGame();
    void againGame();
    void changeSize(int row,int column, int mine);
    void updateMineLabel(bool addOrSub);
    //void setData(int cx = hightCx, int cy = hightCy, int tdNum = hightThunder);
signals:
protected:
    void closeEvent(QCloseEvent *event);
private:
    void createActions();
    void createMenus();
    void createLabel(int y, int x);
    void setLabelSize(int y, int x);
    void createCentralView();
    void createGameTime();
    void createResultDialog();
    void createWinDialog();
    void initGameData();
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
    QMenu *gameMenu;
    QMenu *helpMenu;
    QAction *newGameAction;
    QAction *infoAction;
    QAction *optionAction;
    QAction *changFaceAction;
    QAction *exitAction;
    QAction *seeHelpAction;
    QAction *aboutGameAction;
    QAction *clientGameAction;
    QLabel *timeLabel;
    QLabel *mineLabel;
    QTimer *gameTimer;
    int clientCx, clientCy;
    int currentPlayTime;
    int currentMineNum;
    int mineNum;
    MyView *gameView;
    ResultDialog *resultDialog;
    WinDialog *winDialog;
    OptionDialog *optionDialog;
    int playTime;
    int bestTime;
    int playCount;
    int winCount;
private:

public slots:

};

#endif // MAINWINDOW_H
