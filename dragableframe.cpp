#include "dragableframe.h"

DragableFrame::DragableFrame()
{
}

void DragableFrame::mousePressEvent(QMouseEvent *event)
{
    if (circle)
    {
        painter.LoadPixels(image.getPixelsArr());
        painter.CreateCircleUsingRadius(event->pos(), radius);
        setPixmap(image.toQPixmap(1));
    }

    else if (pentagramm)
    {
        painter.LoadPixels(image.getPixelsArr());
        painter.CreatePentagramm(event->pos(), radius);
        setPixmap(image.toQPixmap(1));
    }

    else if (square)
    {
        QPoint point(event->pos().x() + a, event->pos().y() + a);
        painter.LoadPixels(image.getPixelsArr());
        painter.CreateSquare(event->pos(), point);
        setPixmap(image.toQPixmap(1));
    }

    else if (RecSwap)
        SwapLeftPoint = event->pos();

    else if (CirSwap)
    {
        QPoint left_pnt(event->pos().x() - radius, event->pos().y() - radius);
        QPoint right_pnt(event->pos().x() + radius, event->pos().y() + radius);

        if (SwapCirVariant == 1)
            painter.CreateSwapCirFormasDiagonally(left_pnt, right_pnt);
        else
            painter.CreateSwapCirFormasByCircle(left_pnt, right_pnt);

        setPixmap(image.toQPixmap(1));
    }



    else if (rotate)
        RotateLeftPoint = event->pos();

    else if (event->button() == Qt::LeftButton)
    {
        access = true;
        startPoint = event->globalPos();
    }
}

void DragableFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (access) {
        move(pos() + event -> globalPos() - startPoint);
        startPoint = event->globalPos();
    }
}

void DragableFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (rotate)
    {
        Rotate rt;
        rt.LoadSize(image.getWidth(), image.getHeight());
        rt.LoadPixels(image.getPixelsArr());

        switch (degree)
        {
            case 1:
                rt.RotateOn90Part(RotateLeftPoint, event->pos());
                break;
            case 2:
                rt.RotateOn180Part(RotateLeftPoint, event->pos());
                break;
            case 3:
                rt.RotateOn270Part(RotateLeftPoint, event->pos());
                break;
        }
        setPixmap(image.toQPixmap(1));
    }

    else if (RecSwap)
    {
        if (SwapRecVariant == 1)
            painter.CreateSwapFormsDiagonally(SwapLeftPoint, event->pos());
        else
            painter.CreateSwapFormsByCircle(SwapLeftPoint, event->pos());
        setPixmap(image.toQPixmap(1));
    }

    else if (event->button() == Qt::LeftButton)
        access = false;
}

Image* DragableFrame::getImg()
{
    return &image;
}

Painter* DragableFrame::getPnt()
{
    return &painter;
}

void DragableFrame::activateDoingRecSwap(int NewSwapVariant)
{
    disconnectOptions();
    SwapRecVariant = NewSwapVariant;
    RecSwap = true;
}

void DragableFrame::activateDoingCirSwap(int NewSwapVariant, int new_radius)
{
    disconnectOptions();
    radius = new_radius;
    SwapCirVariant = NewSwapVariant;
    CirSwap = true;
}

void DragableFrame::activateDoingSquare(int line_size)
{
    disconnectOptions();
    a = line_size;
    square = true;
}

void DragableFrame::activateDoingCircle(int value)
{
    disconnectOptions();
    radius = value;
    circle = true;
}

void DragableFrame::activateDoingPentagramm(int r)
{
    disconnectOptions();
    pentagramm = true;
    radius = r;
}

void DragableFrame::disconnectOptions()
{
    square = false;
    circle = false;
    rotate = false;
    RecSwap = false;
    CirSwap = false;
    pentagramm = false;
}

void DragableFrame::activateDoingRotate(int new_degree)
{
    disconnectOptions();
    degree = new_degree;
    rotate = true;
}
