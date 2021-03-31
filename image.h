#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <stdio.h>
#include <cstdlib>
#include <math.h>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)


typedef struct tagBITMAPINFOHEADER{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPINFOHEADER;


struct PIXEL{
        unsigned char b;
        unsigned char g;
        unsigned char r;
};

class Image
{

public:
    Image();
    ~Image();
    int load(const char* fname);
    int save(const char* fname);
    void create();
    void SwapCoordinates();
    long int getWidth();
    long int getHeight();
    void LoadOldPixmap();
    void ShiftOldPixmaps();
    bool isNull();
    QPixmap toQPixmap(int f);
    QPixmap toOldQPixmap();
    QString info() const;
    PIXEL** getPixelsArr();

private:
    bool is_load = false;
    int max;
    PIXEL** pixels;
    BITMAPFILEHEADER  bfh;
    BITMAPINFOHEADER  bih;
    PIXEL*** OldPixmaps;
    int PixmapIndex;
    int RotateIndex;
    int* RotateArr;
};

#endif // IMAGE_H
