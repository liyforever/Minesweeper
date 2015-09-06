#include <QPixmap>
#include <QPainter>
#include "timelabel.h"

TimeLabel::TimeLabel(QWidget *parent) :
    QLabel(parent)
{
    setMaximumSize(70, 30);
    setMinimumSize(70, 30);
    setText(tr("0000"));
    setStyleSheet("background-color:rgb(0,255,100)");
}

