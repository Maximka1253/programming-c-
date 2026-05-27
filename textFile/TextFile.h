#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include "FormatRowFile.h"

#include <cstddef>
#include <string>
#include <vector>

template <class T>
class TextFile {
private:
    std::string filePath;
    bool isReadOnly;
    std::vector<T> data;

    bool containsRawRow(const std::string& row) const;
    void ensureWritable() const;

public:
    TextFile();
    TextFile(const char* path, bool readOnly = false);
    TextFile(const std::string& path, bool readOnly = false);
    TextFile(const char* directory, const char* mask);
    TextFile(const std::string& directory, const std::string& mask);
    TextFile(const std::string& path, const std::vector<T>& rows, bool readOnly = false);

    std::string getFilePath() const;
    bool getIsReadOnly() const;
    size_t getRowCount() const;
    const T& getRow(size_t index) const;

    void appendFile(const TextFile& other);
    void sortDataByColumn(size_t columnIndex, bool ascending = true);
    double sumAllNumbers() const;
    void saveToFile(const std::string& path) const;

    static TextFile createWithUniqueLines(const std::vector<TextFile>& files);
    static TextFile createWithCommonLines(const std::vector<TextFile>& files);

    TextFile& operator+=(const TextFile& other);
    TextFile operator+(const TextFile& other) const;
    TextFile& operator-=(const TextFile& other);
    TextFile operator-(const TextFile& other) const;
};

#endif
