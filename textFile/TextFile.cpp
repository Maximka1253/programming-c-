#include "TextFile.h"
#include "TextFileReader.h"
#include "TextFileWriter.h"

#include <algorithm>
#include <set>
#include <stdexcept>

using namespace std;

template <class T>
TextFile<T>::TextFile() {
    filePath = "";
    isReadOnly = false;
}

template <class T>
TextFile<T>::TextFile(const char* path, bool readOnly) {
    if (path == nullptr) {
        throw invalid_argument("File path is null");
    }

    filePath = path;
    isReadOnly = readOnly;
    data = TextFileReader::readFile(filePath);
}

template <class T>
TextFile<T>::TextFile(const string& path, bool readOnly) {
    filePath = path;
    isReadOnly = readOnly;
    data = TextFileReader::readFile(filePath);
}

template <class T>
TextFile<T>::TextFile(const char* directory, const char* mask) {
    if (directory == nullptr || mask == nullptr) {
        throw invalid_argument("Directory or mask is null");
    }

    filePath = directory;
    isReadOnly = false;

    data = TextFileReader::readDirectory(directory, mask);
}

template <class T>
TextFile<T>::TextFile(const string& directory, const string& mask) {
    filePath = directory;
    isReadOnly = false;

    data = TextFileReader::readDirectory(directory, mask);
}

template <class T>
TextFile<T>::TextFile(const string& path, const vector<T>& rows, bool readOnly) {
    filePath = path;
    isReadOnly = readOnly;
    data = rows;
}

template <class T>
string TextFile<T>::getFilePath() const {
    return filePath;
}

template <class T>
bool TextFile<T>::getIsReadOnly() const {
    return isReadOnly;
}

template <class T>
size_t TextFile<T>::getRowCount() const {
    return data.size();
}

template <class T>
const T& TextFile<T>::getRow(size_t index) const {
    if (index >= data.size()) {
        throw out_of_range("Row index is out of range");
    }

    return data[index];
}

template <class T>
void TextFile<T>::appendFile(const TextFile& other) {
    ensureWritable();
    data.insert(data.end(), other.data.begin(), other.data.end());
}

template <class T>
void TextFile<T>::sortDataByColumn(size_t columnIndex, bool ascending) {
    ensureWritable();

    typename vector<T>::iterator begin = data.begin();

    // Если первая строка не число, считаем ее заголовком.
    if (!data.empty()) {
        try {
            double number = 0.0;
            if (!data[0].tryGetNumber(columnIndex, number)) {
                begin++;
            }
        } catch (const out_of_range&) {
            throw;
        }
    }

    sort(begin, data.end(), [columnIndex, ascending](const T& first, const T& second) {
        string firstValue = first.getFieldValue(columnIndex);
        string secondValue = second.getFieldValue(columnIndex);

        // Числа сравниваем как числа, остальные поля как строки.
        double firstNumber = 0.0;
        double secondNumber = 0.0;
        bool firstIsNumber = first.tryGetNumber(columnIndex, firstNumber);
        bool secondIsNumber = second.tryGetNumber(columnIndex, secondNumber);

        if (firstIsNumber && secondIsNumber) {
            if (ascending) {
                return firstNumber < secondNumber;
            }

            return firstNumber > secondNumber;
        }

        if (ascending) {
            return firstValue < secondValue;
        }

        return firstValue > secondValue;
    });
}

template <class T>
double TextFile<T>::sumAllNumbers() const {
    double sum = 0.0;

    for (const T& row : data) {
        vector<double> numbers = row.getNumbers();
        for (double number : numbers) {
            sum += number;
        }
    }

    return sum;
}

template <class T>
void TextFile<T>::saveToFile(const string& path) const {
    ensureWritable();
    TextFileWriter::saveToFile(path, data);
}

template <class T>
TextFile<T> TextFile<T>::createWithUniqueLines(const vector<TextFile>& files) {
    TextFile result;
    set<string> addedRows;

    // Добавляем каждую строку только один раз.
    for (size_t i = 0; i < files.size(); i++) {
        for (size_t j = 0; j < files[i].data.size(); j++) {
            string row = files[i].data[j].getRawRow();
            if (addedRows.count(row) == 0) {
                result.data.push_back(files[i].data[j]);
                addedRows.insert(row);
            }
        }
    }

    return result;
}

template <class T>
TextFile<T> TextFile<T>::createWithCommonLines(const vector<TextFile>& files) {
    TextFile result;

    if (files.empty()) {
        return result;
    }

    set<string> addedRows;

    // Оставляем строки, которые есть во всех файлах.
    for (size_t i = 0; i < files[0].data.size(); i++) {
        string row = files[0].data[i].getRawRow();
        bool isCommon = true;

        for (size_t fileIndex = 1; fileIndex < files.size(); fileIndex++) {
            if (!files[fileIndex].containsRawRow(row)) {
                isCommon = false;
                break;
            }
        }

        if (isCommon && addedRows.count(row) == 0) {
            result.data.push_back(files[0].data[i]);
            addedRows.insert(row);
        }
    }

    return result;
}

template <class T>
TextFile<T>& TextFile<T>::operator+=(const TextFile& other) {
    ensureWritable();

    // Объединяем без повторов.
    for (size_t i = 0; i < other.data.size(); i++) {
        if (!containsRawRow(other.data[i].getRawRow())) {
            data.push_back(other.data[i]);
        }
    }

    return *this;
}

template <class T>
TextFile<T> TextFile<T>::operator+(const TextFile& other) const {
    TextFile result = *this;
    result += other;
    return result;
}

template <class T>
TextFile<T>& TextFile<T>::operator-=(const TextFile& other) {
    ensureWritable();

    vector<T> newData;

    // Удаляем строки, которые есть во втором файле.
    for (size_t i = 0; i < data.size(); i++) {
        if (!other.containsRawRow(data[i].getRawRow())) {
            newData.push_back(data[i]);
        }
    }

    data = newData;
    return *this;
}

template <class T>
TextFile<T> TextFile<T>::operator-(const TextFile& other) const {
    TextFile result = *this;
    result -= other;
    return result;
}

template <class T>
bool TextFile<T>::containsRawRow(const string& row) const {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].getRawRow() == row) {
            return true;
        }
    }

    return false;
}

template <class T>
void TextFile<T>::ensureWritable() const {
    if (isReadOnly) {
        throw runtime_error("TextFile is read-only");
    }
}

template class TextFile<FormatRowFile>;
