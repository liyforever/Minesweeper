#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(int playTime, int bestTime, int playCount, int winCount, QWidget *parent = 0);
    ~ResultDialog();
    void resetData(int playTime, int bestTime, int playCount, int winCount);
signals:
    void resetGame();
    void exieGame();
    void againGame();
private slots:
    void on_resetGameButton_clicked();

    void on_exitButton_clicked();

    void on_againButton_clicked();

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_H
