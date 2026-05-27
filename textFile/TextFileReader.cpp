#include "TextFileReader.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

using namespace std;

vector<FormatRowFile> TextFileReader::readFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file for reading");
    }

    vector<FormatRowFile> data;
    string row;
    while (getline(file, row)) {
        data.push_back(FormatRowFile(row));
    }

    return data;
}

vector<FormatRowFile> TextFileReader::readDirectory(const string& directory, const string& mask) {
    if (!filesystem::exists(directory)) {
        throw runtime_error("Directory does not exist");
    }

    if (!filesystem::is_directory(directory)) {
        throw runtime_error("Path is not a directory");
    }

    vector<FormatRowFile> data;

    for (const filesystem::directory_entry& entry : filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            string fileName = entry.path().filename().string();
            if (matchesMask(fileName, mask)) {
                vector<FormatRowFile> fileData = readFile(entry.path().string());
                data.insert(data.end(), fileData.begin(), fileData.end());
            }
        }
    }

    return data;
}

bool TextFileReader::matchesMask(const string& fileName, const string& mask) {
    if (mask.size() > 2 && mask[0] == '*' && mask[1] == '.') {
        string extension = mask.substr(1);
        return fileName.size() >= extension.size()
            && fileName.substr(fileName.size() - extension.size()) == extension;
    }

    return fileName == mask;
}
