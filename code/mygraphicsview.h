#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    void wheelEvent(QWheelEvent* = nullptr);
};

#endif // MYGRAPHICSVIEW_H
