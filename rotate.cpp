#include "rotate.h"

Rotate::Rotate()
{
}

void Rotate::LoadPixels(PIXEL** new_pixels)
{
    pixels = new_pixels;
}

void Rotate::LoadSize(int new_width, int new_height)
{
    width = new_width;
    height = new_height;
}

void Rotate::RotateOn180Full()
{
    RotateOn90Full();
    RotateOn90Full();
}

void Rotate::RotateOn90Full()
{
     PIXEL** PixelsAfterRotate = new PIXEL*[width];
     for (int i = 0; i < width; i++)
         PixelsAfterRotate[i] = new PIXEL[height];

     for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
         PixelsAfterRotate[j][i] = pixels[height - 1 - i][j];

     long tmp = width;
     width = height;
     height = tmp;

     for (int i = 0; i < height; i++) for (int j = 0; j < width; j++)
         pixels[i][j] = PixelsAfterRotate[i][j];
}

void Rotate::RotateOn270Full()
{
    RotateOn90Full();
    RotateOn90Full();
    RotateOn90Full();
}

void Rotate::RotateOn90Part(QPoint start_point, QPoint current_point)
{
    int w = current_point.x() - start_point.x(),
        h = current_point.y() - start_point.y(),
        x1 = start_point.x(),
        y1 = start_point.y(),
        x2 = current_point.x(),
        y2 = current_point.y();

    if (x1 > width || x2 > width || y1 > height || y2 > height || x1 > x2 || y1 > y2)
        return;
    int max = h;
    if (h < w) max = w;

    PIXEL** buf_tmp = new PIXEL* [max];
    for (int i = 0; i <= max; i++)
        buf_tmp[i] = new PIXEL[max];

    for (int i = y1; i < y2; i++) for (int j = x1; j < x2; j++){
        buf_tmp[i - y1][j - x1] = pixels[i][j];
        pixels[i][j] = {255, 255, 255};
    }
    int len, x_left, y_left, x_right, y_right;
    if (h < w)
    {
        len = (w - h) / 2;
        x_left = x1 + len;
        y_left = y1 - len;
        x_right = x2 - len;
        y_right = y2 + len;
    }
    else
    {
        len = (h - w) / 2;
        x_left = x1 - len;
        y_left = y1 + len;
        x_right = x2 + len;
        y_right = y2 - len;
    }

    for (int i = y_left; i < y_right; i++) for (int j = x_left; j < x_right; j++)
    {
        int n = h - (j - x_left);
        int m = i - y_left;
        if (i >= 0 && j >= 0 && i < height && j < width &&
            n > 0 && n < h && m > 0 && m < w)
            pixels[i][j] = buf_tmp[n][m];
    }
}

void Rotate::RotateOn180Part(QPoint start_point, QPoint current_point)
{
    int w = current_point.x() - start_point.x(),
        h = current_point.y() - start_point.y(),
        x1 = start_point.x(),
        y1 = start_point.y(),
        x2 = current_point.x(),
        y2 = current_point.y();

    int max = h;
    if (h < w) max = w;

    PIXEL** buf_tmp = new PIXEL* [max];
    for (int i = 0; i <= max; i++)
        buf_tmp[i] = new PIXEL[max];

    for (int i = y1; i <= y2; i++) for (int j = x1; j <= x2; j++)
        buf_tmp[i - y1][j - x1] = pixels[i][j];

    for (int i = y1; i <= y2; i++) for (int j = x1; j <= x2; j++)
        if ((i >= 0) && (j >= 0) && (i < height) && (j < width))
            pixels[i][j] = buf_tmp[h - (i - y1)][w - (j - x1)];
}

void Rotate::RotateOn270Part(QPoint start_point, QPoint current_point)
{
    RotateOn180Part(start_point, current_point);
    RotateOn90Part(start_point, current_point);
}
