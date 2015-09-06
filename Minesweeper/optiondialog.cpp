#include <QRegExpValidator>
#include <QIntValidator>
#include <QDebug>
#include <QMessageBox>
#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
    ui->rowEdit->setValidator(new QIntValidator(9,24,this));//9-24

    ui->columnEdit->setValidator(new QIntValidator(9,30,this));//9-30

    ui->mineEdit->setValidator(new QIntValidator(10,688,this));//10-688
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::on_okButton_clicked()
{
    if(ui->simpleRadioButton->isChecked())
    {
        hide();
        emit changeSize(SIMPLES_Y, SIMPLES_X, SIMPLES_MINE);
        return;
    }

    if(ui->middleRadioButton->isChecked())
    {
        hide();
        emit changeSize(MIDDLE_Y, MIDDLE_X, MIDDLE_MINE);
        return;
    }

    if(ui->expertRadioButton->isChecked())
    {
        hide();
        emit changeSize(EXPERT_Y, EXPERT_X, EXPERT_MINE);
        return;
    }

    int rowNum = ui->rowEdit->text().toInt();
    if(rowNum<9) {
        QMessageBox::warning(this,tr("高度设置错误"),tr("当前高度数值小于9,请从新输入!"),QMessageBox::Yes);
        ui->rowEdit->clear();
        return;
    }
    int columnNum = ui->columnEdit->text().toInt();
    if(columnNum<9) {
        QMessageBox::warning(this,tr("宽度设置错误"),tr("当前宽度数值小于9,请从新输入!"),QMessageBox::Yes);
        ui->columnEdit->clear();
        return;
    }
    int mineNum = ui->mineEdit->text().toInt();
    if(mineNum>columnNum*rowNum-1 || mineNum<10) {
        QMessageBox::warning(this,tr("雷数错误"),tr("当前雷数大数大于最大雷数,请从新输入!"),QMessageBox::Yes);
        ui->mineEdit->clear();
        return;
    }
    emit changeSize(rowNum,columnNum,mineNum);
    hide();
}
