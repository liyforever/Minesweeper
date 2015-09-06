#include <QDate>
#include "windialog.h"
#include "ui_windialog.h"


WinDialog::WinDialog(int playTime,int bestTime,int playCount,int winCount,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateLabel->setText(tr("日期:%1/%2/%3").arg(date.year()).arg(date.month()).arg(date.day()));
    resetData(playTime, bestTime, playCount, winCount);
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::resetData(int playTime, int bestTime, int playCount, int winCount)
{
    ui->playTimeLabel->setText(tr("时间:%1 秒").arg(playTime));
    ui->bestTimeLabel->setText(tr("最佳时间:%1 秒").arg(bestTime));
    ui->countPlayLabel->setText(tr("已玩游戏:%1").arg(playCount));
    ui->countWinLabel->setText(tr("已胜游戏:%1").arg(winCount));
    ui->gameInfoLabel->setText(tr("百分比:%1%").arg(winCount*100/playCount));
}

void WinDialog::on_againButton_clicked()
{
    this->hide();
    emit againGame();
}

void WinDialog::on_exitButton_clicked()
{
    emit exieGame();
}
