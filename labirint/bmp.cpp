#include "bmp.h"

#include "maze.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <stdexcept>

using namespace std;

// Возвращает ширину изображения в пикселях.
int BmpImage::width() const {
    return imageWidth;
}

// Возвращает высоту изображения в пикселях.
int BmpImage::height() const {
    return imageHeight;
}

// Проверяет, что координаты не выходят за границы картинки.
bool BmpImage::isInside(int x, int y) const {
    return x >= 0 && y >= 0 && x < imageWidth && y < imageHeight;
}

bool BmpImage::isInside(Point point) const {
    return isInside(point.x, point.y);
}

Pixel BmpImage::getPixel(int x, int y) const {
    return pixels[pixelIndex(x, y)];
}

Pixel BmpImage::getPixel(Point point) const {
    return getPixel(point.x, point.y);
}

void BmpImage::setPixel(int x, int y, Pixel color) {
    mutablePixel(x, y) = color;
}

void BmpImage::setPixel(Point point, Pixel color) {
    setPixel(point.x, point.y, color);
}

// Переводит координаты пикселя в индекс внутри одномерного массива.
size_t BmpImage::pixelIndex(int x, int y) const {
    if (!isInside(x, y)) {
        throw out_of_range("Pixel coordinates are outside the image");
    }
    return static_cast<size_t>(y) * imageWidth + x;
}

Pixel& BmpImage::mutablePixel(int x, int y) {
    return pixels[pixelIndex(x, y)];
}

// BMP хранит числа от младшего байта к старшему.
uint16_t BmpReader::readU16(const vector<uint8_t>& data, size_t pos) {
    return static_cast<uint16_t>(data[pos] | (data[pos + 1] << 8));
}

uint32_t BmpReader::readU32(const vector<uint8_t>& data, size_t pos) {
    return static_cast<uint32_t>(data[pos] | (data[pos + 1] << 8) |
                                 (data[pos + 2] << 16) | (data[pos + 3] << 24));
}

int32_t BmpReader::readI32(const vector<uint8_t>& data, size_t pos) {
    return static_cast<int32_t>(readU32(data, pos));
}

// Читает весь файл в массив байтов.
vector<uint8_t> BmpReader::readFileBytes(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        throw runtime_error("Cannot open input file: " + filename);
    }

    return {
        istreambuf_iterator<char>(in),
        istreambuf_iterator<char>()
    };
}

// Строка BMP выравнивается по 4 байтам.
size_t BmpReader::rowSizeFor24BitBmp(int width) {
    return ((static_cast<size_t>(width) * 3 + 3) / 4) * 4;
}

BmpImage BmpReader::readFromFile(const string& filename) const {
    const vector<uint8_t> fileData = readFileBytes(filename);

    // Проверяем, что это обычный BMP-файл.
    if (fileData.size() < 54 || fileData[0] != 'B' || fileData[1] != 'M') {
        throw runtime_error("Input file is not a BMP image");
    }

    // Достаём основные поля заголовка BMP.
    const uint32_t pixelOffset = readU32(fileData, 10);
    const uint32_t dibSize = readU32(fileData, 14);
    const int newWidth = readI32(fileData, 18);
    const int rawHeight = readI32(fileData, 22);
    const uint16_t planes = readU16(fileData, 26);
    const uint16_t bitsPerPixel = readU16(fileData, 28);
    const uint32_t compression = readU32(fileData, 30);

    // Программа поддерживает только несжатый 24-битный BMP.
    if (dibSize < 40 || planes != 1 ||
        bitsPerPixel != BmpImage::supportedBitsPerPixel ||
        compression != 0) {
        throw runtime_error("Only uncompressed 24-bit Windows BMP files are supported");
    }
    if (newWidth <= 0 || rawHeight == 0) {
        throw runtime_error("Unsupported BMP dimensions");
    }

    BmpImage image;
    image.imageWidth = newWidth;
    // Отрицательная высота означает, что строки уже идут сверху вниз.
    image.imageHeight = abs(rawHeight);
    image.bottomUp = rawHeight > 0;

    const size_t rowSize = rowSizeFor24BitBmp(image.imageWidth);
    const size_t expectedSize = static_cast<size_t>(pixelOffset) + rowSize * image.imageHeight;
    if (fileData.size() < expectedSize) {
        throw runtime_error("BMP file is truncated");
    }

    image.header.assign(fileData.begin(), fileData.begin() + pixelOffset);
    image.pixels.resize(static_cast<size_t>(image.imageWidth) * image.imageHeight);

    // Копируем пиксели в обычную систему координат: x вправо, y вниз.
    for (int y = 0; y < image.imageHeight; ++y) {
        const int bmpY = image.bottomUp ? (image.imageHeight - 1 - y) : y;
        const size_t rowStart = static_cast<size_t>(pixelOffset) + rowSize * bmpY;
        for (int x = 0; x < image.imageWidth; ++x) {
            const size_t src = rowStart + static_cast<size_t>(x) * 3;
            image.setPixel(x, y, {
                fileData[src],
                fileData[src + 1],
                fileData[src + 2]
            });
        }
    }

    return image;
}

// Такая же формула выравнивания строки нужна при записи.
size_t BmpWriter::rowSizeFor24BitBmp(int width) {
    return ((static_cast<size_t>(width) * 3 + 3) / 4) * 4;
}

void BmpWriter::writeToFile(const BmpImage& image, const string& filename) const {
    ofstream out(filename, ios::binary);
    if (!out) {
        throw runtime_error("Cannot open output file: " + filename);
    }

    const size_t rowSize = rowSizeFor24BitBmp(image.imageWidth);
    vector<uint8_t> row(rowSize, 0);

    // Заголовок сохраняем из исходного файла, меняем только пиксели.
    out.write(reinterpret_cast<const char*>(image.header.data()),
              static_cast<streamsize>(image.header.size()));

    // Записываем строки в том же порядке, в каком они были в исходном BMP.
    for (int rowY = 0; rowY < image.imageHeight; ++rowY) {
        const int y = image.bottomUp ? (image.imageHeight - 1 - rowY) : rowY;
        fill(row.begin(), row.end(), 0);
        for (int x = 0; x < image.imageWidth; ++x) {
            const Pixel currentPixel = image.getPixel(x, y);
            const size_t dst = static_cast<size_t>(x) * 3;
            row[dst] = currentPixel.b;
            row[dst + 1] = currentPixel.g;
            row[dst + 2] = currentPixel.r;
        }
        out.write(reinterpret_cast<const char*>(row.data()),
                  static_cast<streamsize>(row.size()));
    }
}
