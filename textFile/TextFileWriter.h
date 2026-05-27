#ifndef TEXT_FILE_WRITER_H
#define TEXT_FILE_WRITER_H

#include "FormatRowFile.h"

#include <string>
#include <vector>

class TextFileWriter {
public:
    static void saveToFile(const std::string& path, const std::vector<FormatRowFile>& data);
};

#endif
