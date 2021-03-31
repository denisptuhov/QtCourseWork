#include "image.h"


Image::Image()
{
    PixmapIndex = 0;
    RotateIndex = 0;
    OldPixmaps = new PIXEL**[100];
    RotateArr = new int[100];
}

Image::~Image()
{
    if (is_load)
    {
        for (int i = 1; i < PixmapIndex; i++)
            delete [] OldPixmaps[i];
        delete [] OldPixmaps;

        for (int i = 0; i < max; i++)
            delete [] pixels[i];
        delete [] pixels;
    }
}

int Image::load(const char* fname)
{
    FILE *f = fopen(fname, "r+b");
    if (!f)
        return 0;

    fread(&bfh, sizeof(bfh), 1, f);
    fread(&bih, sizeof(bih), 1, f);

    if (bfh.bfReserved1 != 0 ||
            (bih.biSize != 40 && bih.biSize != 108 && bih.biSize != 124) ||
            bih.biWidth < 1 || bih.biWidth > 10000 ||
            bih.biHeight < 1 || bih.biHeight > 10000 ||
            bih.biCompression != 0 ||
            bih.biBitCount != 24)
    {
        fclose(f);
        return -1;
    }

    is_load = true;
    size_t padding = (4 - (3 * bih.biWidth) % 4) % 4;
    max = bih.biHeight;
    if (max < bih.biWidth)
        max = bih.biWidth;
    PixmapIndex = 0;

    pixels = new PIXEL*[max];
    for (int i = 0; i < max; i++)
        pixels[i] = new PIXEL [max + 1];

    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);
    for (int i = 0; i < bih.biHeight; i++) {
        for (int j = 0; j < bih.biWidth; j++)
            fread(&pixels[bih.biHeight - 1 - i][j], 3, 1, f);
        fread(&pixels[bih.biHeight - 1 - i][bih.biWidth], padding, 1, f);
    }

    fclose(f);
    return 1;
}

int Image::save(const char *fname)
{
    FILE* f;
    f = fopen(fname, "w+b");
    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, f);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, f);

    size_t padding = (4 - (3 * bih.biWidth) % 4) % 4;
    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);
    for (int i = 0; i < bih.biHeight; i++)
    {
        for (int j = 0; j < bih.biWidth; j++)
            fwrite(&pixels[bih.biHeight - 1 - i][j], 1, 3, f);
        fwrite(&pixels[bih.biHeight - 1 - i][bih.biWidth], padding, 1, f);
    }

    fclose(f);
    return 1;
}

void Image::create()
{
    memset(&bih, 0, sizeof(bih));
    memset(&bfh, 0, sizeof(bfh));

    bih.biWidth = 1280;
    bih.biHeight = 720;
    bih.biSize = sizeof(bih);
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bfh.bfOffBits = 14 + sizeof(bih);
    bfh.bfType = 0x4d42;
    bfh.bfSize = static_cast<DWORD>(54 + bih.biHeight * bih.biWidth);
    max = 1280;
    PixmapIndex = 0;

    pixels = new PIXEL*[max];
    for (int i = 0; i < max; i++) pixels[i] = new PIXEL[max];
    is_load = true;

    for (int i = 0; i < bih.biHeight; i++) for (int j = 0; j < bih.biWidth; j++)
        pixels[i][j] = {255, 255, 255};
}


QPixmap Image::toQPixmap(int f)
{
    QPixmap pix;
    QImage* pict = new QImage(bih.biWidth, bih.biHeight, QImage::Format_RGB888);

    for (int i = 0; i < bih.biHeight; i++) for (int j = 0; j < bih.biWidth; j++)
    {
        QColor color(pixels[i][j].r, pixels[i][j].g, pixels[i][j].b);
        pict->setPixel(j, i, color.rgb());
    }
    pix.convertFromImage(*pict, nullptr);

    if (f)
        LoadOldPixmap();

    return pix;
}

void Image::LoadOldPixmap()
{
    if (PixmapIndex == 99)
    {
        ShiftOldPixmaps();
        PixmapIndex -= 1;
    }

    PixmapIndex += 1;
    OldPixmaps[PixmapIndex] = new PIXEL*[max];
    for (int i = 0; i < max; i++)
        OldPixmaps[PixmapIndex][i] = new PIXEL[max];

    for (int i = 0; i < bih.biHeight; i++) for (int j = 0; j < bih.biWidth; j++)
        OldPixmaps[PixmapIndex][i][j] = pixels[i][j];
}

void Image::ShiftOldPixmaps()
{
    for (int i = 1; i < 99; i++)
        OldPixmaps[i] = OldPixmaps[i + 1];

    for (int i = 0; i < RotateIndex; i++)
        RotateArr[RotateIndex] -= 1;
}

bool Image::isNull()
{
    return !is_load;
}

QPixmap Image::toOldQPixmap()
{
    if (PixmapIndex - 1 <= 0)
        return QPixmap("");


    PixmapIndex -= 1;
    if (PixmapIndex == RotateArr[RotateIndex - 1])
    {
        RotateArr -= 1;
        long tmp = bih.biWidth;
        bih.biWidth = bih.biHeight;
        bih.biHeight = tmp;
    }

    for (int i = 0; i < bih.biHeight; i++) for (int j = 0; j < bih.biWidth; j++)
        pixels[i][j] = OldPixmaps[PixmapIndex][i][j];

    return toQPixmap(0);
}

QString Image::info() const
{
    QString information;
    QString n = QString::number(static_cast<double>(bfh.bfSize) / 1048576, 'g', 3);
    information.sprintf("File format: .bmp\nFile resolution: %ld x %ld\n", bih.biWidth, bih.biHeight);
    information += "Size on disk: " + n + " Mb\n";
    information += "Bit count: " + QString::number(bih.biBitCount);
    return information;
}

void Image::SwapCoordinates()
{
    RotateArr[RotateIndex] = PixmapIndex;
    RotateIndex += 1;

    long tmp = bih.biHeight;
    bih.biHeight = bih.biWidth;
    bih.biWidth = tmp;
}

long Image::getWidth()
{
    return bih.biWidth;
}

long Image::getHeight()
{
    return bih.biHeight;
}

PIXEL** Image::getPixelsArr()
{
    return pixels;
}
