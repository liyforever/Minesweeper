#ifndef BOXITEM_H
#define BOXITEM_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QVector>

class BoxItem : public QGraphicsObject
{
public:
    BoxItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
public slots:
    void changBoxState(int state);
private:
    enum {BOX_DEFAULT, BOX_1, BOX_2, BOX_3, BOX_4,
          BOX_5, BOX_6, BOX_QUESTION, BOX_FLAG,
          BOX_EMPTY, BOX_MINE,BOX_STATECOUNT};
    QVector<QString> path_;
    QPixmap pixmap_;
    int boxState_;
};


#endif // BOXITEM_H
