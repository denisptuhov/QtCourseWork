#ifndef CIRCLEANDSQUARE_H
#define CIRCLEANDSQUARE_H

#include "image.h"

class Painter
{
public:
    Painter();
    void LoadPixels(PIXEL** new_pixels);
    void LoadSize(int new_width, int new_height);
    void CreateSquare(QPoint start_point, QPoint current_point);
    void CreateCircleUsingRadius(QPoint center, int radius);
    void CreateCircleUsingSquare(QPoint left, QPoint right);
    void CreatePentagramm(QPoint center, int radius);
    void DrawLine(int x1, int y1, int x2, int y2);
    void UpdateColor(QColor new_color);
    void UpdateFillColor(QColor new_color);
    void UpdateThickness(int new_thickness);
    void disconnectFill();
    void drawPixel(int x, int y, QColor cur_color);
    void CreateRgb(int n_color, int n);
    void CreateBW();
    void CreateCollage(int n, int m);
    void DrawCollageLines(int PartWidth, int PartHeight);
    void CreateSwapFormsDiagonally(QPoint left, QPoint right);
    void CreateSwapCirFormasDiagonally(QPoint left, QPoint right);
    void CreateSwapCirFormasByCircle(QPoint left, QPoint right);
    void CreateSwapFormsByCircle(QPoint left, QPoint right);
    void SwapPixels(PIXEL* a, PIXEL* b);
    QPoint GetRotatePoints(QPoint current_point, QPoint center, double a);

private:
    PIXEL** pixels;
    int width;
    int height;

    bool fill = false;
    QColor fill_color;
    QColor CurrentLineColor = Qt::black;
    int thickness = 1;
};

#endif // CIRCLEANDSQUARE_H
