#ifndef BMP_H
#define BMP_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct Point;

struct Pixel {
    // BMP хранит цвета в порядке BGR: синий, зелёный, красный.
    std::uint8_t b = 0;
    std::uint8_t g = 0;
    std::uint8_t r = 0;
};

// Хранит пиксели изображения и служебные данные BMP.
class BmpImage {
public:
    int width() const;
    int height() const;
    bool isInside(int x, int y) const;
    bool isInside(Point point) const;

    Pixel getPixel(int x, int y) const;
    Pixel getPixel(Point point) const;
    void setPixel(int x, int y, Pixel color);
    void setPixel(Point point, Pixel color);

private:
    friend class BmpReader;
    friend class BmpWriter;

    static constexpr std::uint16_t supportedBitsPerPixel = 24;

    std::size_t pixelIndex(int x, int y) const;
    Pixel& mutablePixel(int x, int y);

    int imageWidth = 0;
    int imageHeight = 0;
    bool bottomUp = true;
    // Заголовок BMP сохраняем, чтобы при записи не менять его, а только пиксели.
    std::vector<std::uint8_t> header;
    std::vector<Pixel> pixels;
};

// Читает BMP-файл в объект изображения.
class BmpReader {
public:
    BmpImage readFromFile(const std::string& filename) const;

private:
    static std::uint16_t readU16(const std::vector<std::uint8_t>& data, std::size_t pos);
    static std::uint32_t readU32(const std::vector<std::uint8_t>& data, std::size_t pos);
    static std::int32_t readI32(const std::vector<std::uint8_t>& data, std::size_t pos);
    static std::vector<std::uint8_t> readFileBytes(const std::string& filename);
    static std::size_t rowSizeFor24BitBmp(int width);
};

// Записывает изображение в BMP-файл.
class BmpWriter {
public:
    void writeToFile(const BmpImage& image, const std::string& filename) const;

private:
    static std::size_t rowSizeFor24BitBmp(int width);
};

#endif
