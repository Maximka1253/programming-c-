#include "FormatRowFile.h"

#include <cstdlib>
#include <stdexcept>

FormatRowFile::FormatRowFile() {
    rawRow = "";
}

FormatRowFile::FormatRowFile(const char* row) {
    if (row == nullptr) {
        rawRow = "";
    } else {
        rawRow = row;
    }

    parseRow();
}

FormatRowFile::FormatRowFile(const std::string& row) {
    rawRow = row;
    parseRow();
}
// Разбирает строку на поля, разделенные пробелами или табуляциями.
void FormatRowFile::parseRow() {
    parsedFields.clear();

    std::string field = "";
    for (size_t i = 0; i < rawRow.size(); i++) {
        char symbol = rawRow[i];

        // Пробелы и табуляции разделяют поля.
        if (symbol == ' ' || symbol == '\t') {
            if (!field.empty()) {
                parsedFields.push_back(field);
                field = "";
            }
        } else {
            field += symbol;
        }
    }

    if (!field.empty()) {
        parsedFields.push_back(field);
    }
}

std::string FormatRowFile::getRawRow() const {
    return rawRow;
}

std::string FormatRowFile::getFieldValue(size_t index) const {
    if (index >= parsedFields.size()) {
        throw std::out_of_range("Column index is out of range");
    }

    return parsedFields[index];
}

std::vector<std::string> FormatRowFile::getFields() const {
    return parsedFields;
}

std::vector<double> FormatRowFile::getNumbers() const {
    std::vector<double> numbers;

    // Берем только поля, которые можно преобразовать в число.
    for (size_t i = 0; i < parsedFields.size(); i++) {
        double number = 0.0;
        if (stringToDouble(parsedFields[i], number)) {
            numbers.push_back(number);
        }
    }

    return numbers;
}

bool FormatRowFile::hasField(size_t index) const {
    return index < parsedFields.size();
}

bool FormatRowFile::tryGetNumber(size_t index, double& number) const {
    if (!hasField(index)) {
        throw std::out_of_range("Column index is out of range");
    }

    return stringToDouble(parsedFields[index], number);
}

bool FormatRowFile::stringToDouble(const std::string& text, double& number) const {
    if (text.empty()) {
        return false;
    }

    char* endPointer = nullptr;
    number = std::strtod(text.c_str(), &endPointer);

    // Вся строка должна быть числом без лишних символов.
    return endPointer != text.c_str() && *endPointer == '\0';
}
