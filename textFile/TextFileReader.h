#ifndef TEXT_FILE_READER_H
#define TEXT_FILE_READER_H

#include "FormatRowFile.h"

#include <string>
#include <vector>

class TextFileReader {
private:
    static bool matchesMask(const std::string& fileName, const std::string& mask);

public:
    static std::vector<FormatRowFile> readFile(const std::string& path);
    static std::vector<FormatRowFile> readDirectory(const std::string& directory, const std::string& mask);
};

#endif
