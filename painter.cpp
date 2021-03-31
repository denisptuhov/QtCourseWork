#include "painter.h"

Painter::Painter()
{

}

void Painter::LoadPixels(PIXEL **new_pixels)
{
    pixels = new_pixels;
}

void Painter::LoadSize(int new_width, int new_height)
{
    width = new_width;
    height = new_height;
}

void Painter::CreateSquare(QPoint start_point, QPoint current_point)
{
    int x1 = start_point.x(),
        y1 = start_point.y(),
        x2 = current_point.x(),
        y2 = current_point.y();
    double k = static_cast<double>(y2 - y1) / static_cast<double>(x2 - x1);
    double b = static_cast<double>(y1) - k * x1;
    double k2 = -k;
    double b2 =  static_cast<double>(y1) - k2 * x2;

    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
    {
        if (fill && i > y1 && i < y2
                && j > x1 && j < x2)
            drawPixel(i, j, fill_color);

        if ((abs(i - j * k - b) < thickness || abs(i - j * k2 - b2) < thickness)
                && i >= y1 && i <= y2
                && j >= x1 && j <= x2)
            drawPixel(i, j, CurrentLineColor);

        if ((abs(i - y1) < thickness || abs(i - y2) < thickness) && j > x1 && j < x2)
            drawPixel(i, j, CurrentLineColor);

        if ((abs(j - x1) < thickness || abs(j - x2) < thickness) &&
            i > y1 - thickness && i < y2 + thickness)
            drawPixel(i, j, CurrentLineColor);
    }
}

void Painter::CreateCircleUsingRadius(QPoint center, int radius)
{
    int x = center.x(),
        y = center.y();
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
    {
        if (fill && (j - x)*(j - x) + (i - y)*(i - y) - radius * radius < 0)
            drawPixel(i, j, fill_color);

        if (abs((j - x)*(j - x) + (i - y)*(i - y) - radius * radius) <= radius * thickness)
            drawPixel(i, j, CurrentLineColor);
    }
}

void Painter::CreateCircleUsingSquare(QPoint left, QPoint right)
{
    int a = right.x() - left.x();
    int radius = a / 2;
    QPoint center(left.x() + radius, left.y() + radius);
    CreateCircleUsingRadius(center, radius);
}

void Painter::CreatePentagramm(QPoint center, int radius)
{
    CreateCircleUsingRadius(center, radius);

    QPoint* rotate_points = new QPoint[5];
    rotate_points[0] = {center.x(), center.y() - radius};
    rotate_points[1] = GetRotatePoints(rotate_points[0], center, 1.2697);
    rotate_points[2] = GetRotatePoints(rotate_points[0], center, 2.5264);
    rotate_points[3] = GetRotatePoints(rotate_points[0], center, 3.7830);
    rotate_points[4] = GetRotatePoints(rotate_points[0], center, 5.0265);

    DrawLine(rotate_points[0].x(), rotate_points[0].y(),
             rotate_points[2].x(), rotate_points[2].y());
    DrawLine(rotate_points[0].x(), rotate_points[0].y(),
             rotate_points[3].x(), rotate_points[3].y());
    DrawLine(rotate_points[2].x(), rotate_points[2].y(),
             rotate_points[4].x(), rotate_points[4].y());
    DrawLine(rotate_points[1].x(), rotate_points[1].y(),
             rotate_points[3].x(), rotate_points[3].y());
    DrawLine(rotate_points[4].x(), rotate_points[4].y(),
             rotate_points[1].x(), rotate_points[1].y() - 1);

    delete [] rotate_points;
}

QPoint Painter::GetRotatePoints(QPoint current_point, QPoint center, double a)
{
    int x1 = current_point.x(),
        y1 = current_point.y();

    x1 -= center.x();
    y1 -= center.y();

    int xnew = static_cast<int>(x1 * cos(a) - y1 * sin(a));
    int ynew = static_cast<int>(x1 * sin(a) + y1 * cos(a));

    x1 = xnew + center.x();
    y1 = ynew + center.y();
    return QPoint(x1, y1);

}

void Painter::DrawLine(int x1, int y1, int x2, int y2)
{
    const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;
        int error = deltaX - deltaY;

        if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height)
            drawPixel(y2, x2, CurrentLineColor);

        while(x1 != x2 || y1 != y2)
        {
            if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
                drawPixel(y1, x1, CurrentLineColor);

            const int error2 = error * 2;

            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
}

void Painter::UpdateColor(QColor new_color)
{
    CurrentLineColor = new_color;
}

void Painter::UpdateFillColor(QColor new_color)
{
    fill = true;
    fill_color = new_color;
}

void Painter::UpdateThickness(int new_thickness)
{
    thickness = new_thickness;
}

void Painter::disconnectFill()
{
    fill = false;
}

void Painter::drawPixel(int x, int y, QColor currentLineColor)
{
    pixels[x][y].r = static_cast<unsigned char>(currentLineColor.red());
    pixels[x][y].g = static_cast<unsigned char>(currentLineColor.green());
    pixels[x][y].b = static_cast<unsigned char>(currentLineColor.blue());
}

void Painter::CreateRgb(int n_color, int n)
{
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
    {
        if (!n_color)
            pixels[i][j].r = static_cast<unsigned char>(n);
        else if (n_color == 1)
            pixels[i][j].g = static_cast<unsigned char>(n);
        else
            pixels[i][j].b = static_cast<unsigned char>(n);
    }

}

void Painter::CreateBW()
{
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
    {
        unsigned char n = static_cast<unsigned char>((pixels[i][j].r + pixels[i][j].b + pixels[i][j].g) / 3);
        pixels[i][j] = {n, n, n};
    }
}

void Painter::CreateCollage(int n, int m)
{
    int PartWidth = width / m;
    int PartHeight = height / n;

    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
        pixels[i / n][j / m] = pixels[i][j];

    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
        if (j > PartWidth || i > PartHeight)
            pixels[i][j] = pixels[i % PartHeight][j % PartWidth];

    DrawCollageLines(PartWidth, PartHeight);
}

void Painter::DrawCollageLines(int PartWidth, int PartHeight)
{
    int cnt = PartHeight;
    while (cnt <= height - height % PartHeight)
    {
        for (int j = 0; j < width; j++)
        {
            pixels[cnt][j] = {0, 0, 0};
            pixels[cnt - 1][j] = {0, 0, 0};
            pixels[cnt + 1][j] = {0, 0, 0};
        }
        cnt += PartHeight;
    }

    cnt = PartWidth;
    while (cnt <= width - width % PartWidth)
    {
        for (int i = 0; i < height; i++)
        {
            pixels[i][cnt + 1] = {0, 0, 0};
            pixels[i][cnt - 1] = {0, 0, 0};
            pixels[i][cnt] = {0, 0, 0};
        }
        cnt += PartWidth;
    }
}

void Painter::CreateSwapFormsDiagonally(QPoint left, QPoint right)
{
    int x1 = left.x(),
        x2 = right.x(),
        y1 = left.y(),
        y2 = right.y(),
        w = x2 - x1,
        h = y2 - y1;

    for (int i = y1; i < y1 + h / 2; i++) for (int j = x1; j < x1 + w / 2; j++)
        SwapPixels(&(pixels[i][j]), &(pixels[i + h / 2][j + w / 2]));


    for (int i = y1; i < y1 + h / 2; i++) for (int j = x1 + w / 2; j < x2; j++) 
        SwapPixels(&(pixels[i][j]), &(pixels[i + h / 2][j - w / 2]));

}

void Painter::CreateSwapCirFormasDiagonally(QPoint left, QPoint right)
{
    int x1 = left.x(),
        x2 = right.x(),
        y1 = left.y(),
        a = x2 - x1,
        radius = a / 2,
        x_center = x1 + a / 2,
        y_center = y1 + a / 2;
    QPoint delta;

    if (!(x_center >= radius && x_center <= width - 1 - radius &&
        y_center >= radius && y_center <= height - 1 - radius))
        return;

    for (int i = y1; i < y1 + a / 2; i++) for (int j = x1; j <= x2; j++)
        if ((i - y_center) * (i - y_center) + (j - x_center) * (j - x_center) - radius * radius < 0)
        {
            delta = {x_center - j, y_center - i};
            SwapPixels(&(pixels[i][j]), &(pixels[i + 2*delta.y()][j + 2*delta.x()]));
        }

    for (int j = x1; j < (x1 + x2) / 2; j++)
        SwapPixels(&(pixels[y1 + a / 2][j]), &(pixels[y1 + a / 2][x2 - (j - x1)]));
}

void Painter::CreateSwapCirFormasByCircle(QPoint left, QPoint right)
{
    int x1 = left.x(),
        x2 = right.x(),
        y1 = left.y(),
        y2 = right.y(),
        a = x2 - x1,
        radius = a / 2,
        x_center = x1 + a / 2,
        y_center = y1 + a / 2;
    QPoint delta;

    for (int i = y1; i < y2; i++) for (int j = x1; j < x1  + a / 2; j++)
        if ((i - y_center) * (i - y_center) + (j - x_center) * (j - x_center) - radius * radius < 0)
            SwapPixels(&(pixels[i][j]), &(pixels[i][x2 - (j - x1)]));

    for (int i = y1; i < y1 + a / 2; i++) for (int j = x1; j < x1 + a / 2; j++)
        if ((i - y_center) * (i - y_center) + (j - x_center) * (j - x_center) - radius * radius < 0)
        {
            delta = {x_center - j, y_center - i};
            SwapPixels(&(pixels[i][j]), &(pixels[i + 2*delta.y()][j + 2*delta.x()]));
        }
}

void Painter::CreateSwapFormsByCircle(QPoint left, QPoint right)
{
    int x1 = left.x(),
        x2 = right.x(),
        y1 = left.y(),
        y2 = right.y(),
        w = x2 - x1,
        h = y2 - y1;

    for (int i = y1; i < y2; i++) for (int j = x1; j < x1 + w / 2; j++)
        SwapPixels(&(pixels[i][j]), &(pixels[i][j + w / 2]));

    for (int i = y1; i < y1 + h / 2; i++) for (int j = x1; j < x1 + w / 2; j++)
        SwapPixels(&(pixels[i][j]), &(pixels[i + h / 2][j + w / 2]));
}

void Painter::SwapPixels(PIXEL *a, PIXEL *b)
{
    PIXEL tmp = *a;
    *a = *b;
    *b = tmp;
}
