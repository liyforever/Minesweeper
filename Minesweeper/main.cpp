#include <QApplication>
#include <QCoreApplication>
#include <QTextCodec>
#include <QTime>
#include <QPixmap>
#include <iostream>
#include <QColorDialog>
#include <QDebug>
#include "resultdialog.h"
#include "mainwindow.h"
#include "optiondialog.h"
#include "gamemap.h"
#include "windialog.h"
#include "resultdialog.h"
#include "timelabel.h"

using namespace std;
int main(int argc, char *argv[])
{
    //QCoreApplication app(argc, argv);//
    QApplication app(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //qDebug() << sizeof(QPixmap) << sizeof(QStringList);
    //GameMap myMap(8,8,10);
    //myMap.ShowMap();
    MainWindow/*TimeLabel*/ mainWin;///(50,40,40,20);//(50,40,40,20);
    mainWin.show();
    //ResultDialog resultWidget(50,40,40,20);// = new ResultWidget;
    //resultWidget.show();
    //qDebug() << QColorDialog::getColor() << endl;
    return app.exec();
}
