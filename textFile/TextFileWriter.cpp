#include "TextFileWriter.h"

#include <fstream>
#include <stdexcept>

using namespace std;

void TextFileWriter::saveToFile(const string& path, const vector<FormatRowFile>& data) {
    ofstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file for writing");
    }

    for (size_t i = 0; i < data.size(); i++) {
        file << data[i].getRawRow();
        if (i + 1 < data.size()) {
            file << '\n';
        }
    }
}
