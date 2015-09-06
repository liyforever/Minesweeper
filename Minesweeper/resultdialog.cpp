#include <QDate>
#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(int playTime,int bestTime,int playCount,int winCount,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateLabel->setText(tr("日期:%1/%2/%3").arg(date.year()).arg(date.month()).arg(date.day()));
    resetData(playTime, bestTime, playCount, winCount);
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::resetData(int playTime, int bestTime, int playCount, int winCount)
{
    ui->playTimeLabel->setText(tr("时间:%1 秒").arg(playTime));
    ui->bestTimeLabel->setText(tr("最佳时间:%1 秒").arg(bestTime));
    ui->countPlayLabel->setText(tr("已玩游戏:%1").arg(playCount));
    ui->countWinLabel->setText(tr("已胜游戏:%1").arg(winCount));
    ui->gameInfoLabel->setText(tr("百分比:%1%").arg(winCount*100/playCount));
}


void ResultDialog::on_resetGameButton_clicked()
{
    this->hide();
    emit resetGame();
}

void ResultDialog::on_exitButton_clicked()
{
    emit exieGame();
}

void ResultDialog::on_againButton_clicked()
{
    this->hide();
    emit againGame();
}
