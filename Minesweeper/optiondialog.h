#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();
private slots:
    void on_okButton_clicked();

signals:
    void changeSize(int row,int column, int mine);
private:
    Ui::OptionDialog *ui;
    enum gameLayout {
        SIMPLES_Y = 9,
        SIMPLES_X = 9,
        SIMPLES_MINE = 10,
        MIDDLE_Y = 16,
        MIDDLE_X = 16,
        MIDDLE_MINE = 40,
        EXPERT_Y = 16,
        EXPERT_X = 30,
        EXPERT_MINE = 99
    };
};

#endif // OPTIONDIALOG_H
