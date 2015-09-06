#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>

namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinDialog(int playTime, int bestTime, int playCount, int winCount, QWidget *parent = 0);
    ~WinDialog();
    void resetData(int playTime, int bestTime, int playCount, int winCount);
signals:
    void exieGame();
    void againGame();
private slots:
    void on_againButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
