#ifndef DRAGABLEFRAM_H
#define DRAGABLEFRAM_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QSizeGrip>
#include <QGraphicsItem>
#include <QWidget>
#include "image.h"
#include "painter.h"
#include "rotate.h"

class DragableFrame : public QLabel
{
public:
    DragableFrame();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void activateDoingRecSwap(int NewSwapVariant);
    void activateDoingCirSwap(int NewSwapVariant, int new_radius);
    void activateDoingRotate(int new_degree);
    void activateDoingSquare(int line_size);
    void activateDoingCircle(int value);
    void activateDoingPentagramm(int r);
    void disconnectOptions();
    Image* getImg();
    Painter* getPnt();

private:
    int a;
    int radius;
    int degree;
    Image image;
    Painter painter;
    QPoint RotateLeftPoint;
    QPoint SwapLeftPoint;
    QPoint SquareStartPos;
    QPoint startPoint;
    QPoint CirSwapCenter;
    int SwapRecVariant;
    int SwapCirVariant;
    bool access = false;
    bool square = false;
    bool circle = false;
    bool rotate = false;
    bool pentagramm = true;
    bool RecSwap = false;
    bool CirSwap = false;
};
#endif // DRAGABLEFRAM_H
