#ifndef FORMAT_ROW_FILE_H
#define FORMAT_ROW_FILE_H

#include <cstddef>
#include <string>
#include <vector>

class FormatRowFile {
private:
    std::string rawRow;
    std::vector<std::string> parsedFields;

    // Разбивает строку на поля.
    void parseRow();
    // Проверяет, является ли поле числом.
    bool stringToDouble(const std::string& text, double& number) const;

public:
    FormatRowFile();
    FormatRowFile(const char* row);
    FormatRowFile(const std::string& row);

    std::string getRawRow() const;
    std::string getFieldValue(size_t index) const;
    std::vector<std::string> getFields() const;
    std::vector<double> getNumbers() const;
    bool hasField(size_t index) const;
    bool tryGetNumber(size_t index, double& number) const;
};

#endif
