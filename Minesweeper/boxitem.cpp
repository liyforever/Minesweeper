#include <QPainter>
#include <QDebug>
#include "boxitem.h"

BoxItem::BoxItem()
{
    path_.reserve(BOX_STATECOUNT);
    path_ << QString(":/Images/box.jpg") << QString(":/Images/1.jpg")
         << QString(":/Images/2.jpg") << QString(":/Images/3.jpg")
         << QString(":/Images/4.jpg") << QString(":/Images/5.png")
         << QString(":/Images/6.png") << QString(":/Images/question.png")
         << QString(":/Images/flag.png") << QString(":/Images/empty.png")
         << QString(":/Images/mine.png");
    pixmap_.load(path_.at(BOX_DEFAULT));
}

QRectF BoxItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                  40 + penWidth, 40 + penWidth);
}

void BoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch (boxState) {
    case BOX_DEFAULT:
        pixmap_.load(path_.at(BOX_DEFAULT));
        break;
    case BOX_1:
        pixmap_.load(path_.at(BOX_1));
        break;
    case BOX_2:
        pixmap_.load(path_.at(BOX_2));
        break;
    case BOX_3:
        pixmap_.load(path_.at(BOX_3));
        break;
    case BOX_4:
        pixmap_.load(path_.at(BOX_4));
        break;
    case BOX_5:
        pixmap_.load(path_.at(BOX_5));
        break;
    case BOX_6:
        pixmap_.load(path_.at(BOX_6));
        break;
    case BOX_QUESTION:
        pixmap_.load(path_.at(BOX_QUESTION));
        break;
    case BOX_FLAG:
        pixmap_.load(path_.at(BOX_FLAG));
        break;
    case BOX_EMPTY:
        pixmap_.load(path_.at(BOX_EMPTY));
        break;
    case BOX_MINE:
        pixmap_.load(path_.at(BOX_MINE));
        break;
    default:
        break;
    }
    painter->drawPixmap(0, 0, pixmap_);
    return;
}

void BoxItem::changBoxState(int state)
{
    boxState_ = state;
    update();
}
