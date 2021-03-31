#ifndef ROTATE_H
#define ROTATE_H

#include <image.h>

class Rotate
{
public:
    Rotate();
    void LoadPixels(PIXEL** new_pixels);
    void LoadSize(int new_width, int new_height);
    void RotateOn180Full();
    void RotateOn90Full();
    void RotateOn270Full();
    void RotateOn90Part(QPoint start_point, QPoint current_point);
    void RotateOn180Part(QPoint start_point, QPoint current_point);
    void RotateOn270Part(QPoint start_point, QPoint current_point);

private:
    int width;
    int height;
    PIXEL** pixels;
};

#endif // ROTATE_H
