#include "TextFile.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const string PATH_TO_FILES = "STARLINK";
const string FILE_MASK = "*.dat";
using TextFileFormatRow = TextFile<FormatRowFile>;

// Собирает путь к входному файлу из папки STARLINK.
string makeInputPath(const string& fileName) {
    filesystem::path nameOnly = filesystem::path(fileName).filename();
    return (filesystem::path(PATH_TO_FILES) / nameOnly).string();
}

// Сохраняет результат в директорию, из которой запущена программа.
string makeOutputPath(const string& fileName) {
    filesystem::path nameOnly = filesystem::path(fileName).filename();
    return (filesystem::current_path() / nameOnly).string();
}
// Выводит первые строки файла.
void printFirstRows(const TextFileFormatRow& file, size_t count) {
    size_t rowsToPrint = count;
    if (rowsToPrint > file.getRowCount()) {
        rowsToPrint = file.getRowCount();
    }

    for (size_t i = 0; i < rowsToPrint; i++) {
        cout << file.getRow(i).getRawRow() << endl;
    }
}

int main() {
    try {
        // Читаем настройки работы программы.
        string firstName;
        string secondName;
        int previewRowCountInput = 0;
        int sortColumnIndexInput = 0;
        bool sortAscending = false;
        string unionOutputName;
        string differenceOutputName;
        string sortedOutputName;

        cout << "Введите имя первого файла: ";
        cin >> firstName;

        cout << "Введите имя второго файла: ";
        cin >> secondName;

        cout << "Сколько первых строк вывести: ";
        cin >> previewRowCountInput;

        cout << "Введите номер колонки для сортировки: ";
        cin >> sortColumnIndexInput;

        cout << "Сортировать по возрастанию? 1 - да, 0 - нет: ";
        cin >> sortAscending;

        cout << "Введите имя файла для объединения: ";
        cin >> unionOutputName;

        cout << "Введите имя файла для разности: ";
        cin >> differenceOutputName;

        cout << "Введите имя файла для сортировки: ";
        cin >> sortedOutputName;

        string firstPath = makeInputPath(firstName);
        string secondPath = makeInputPath(secondName);
        string unionOutputPath = makeOutputPath(unionOutputName);
        string differenceOutputPath = makeOutputPath(differenceOutputName);
        string sortedOutputPath = makeOutputPath(sortedOutputName);

        if (previewRowCountInput < 0) {
            throw invalid_argument("Row count cannot be negative");
        }

        if (sortColumnIndexInput < 0) {
            throw invalid_argument("Column index cannot be negative");
        }

        size_t previewRowCount = static_cast<size_t>(previewRowCountInput);
        size_t sortColumnIndex = static_cast<size_t>(sortColumnIndexInput);

        cout << endl;

        // Загружаем выбранные файлы и все файлы из папки STARLINK.
        TextFileFormatRow firstFile(firstPath);
        TextFileFormatRow secondFile(secondPath);
        TextFileFormatRow allStarlinkFiles(PATH_TO_FILES, FILE_MASK);

        cout << "Строк в первом файле: " << firstFile.getRowCount() << endl;
        cout << "Строк во втором файле: " << secondFile.getRowCount() << endl;
        cout << "Строк во всех файлах: " << allStarlinkFiles.getRowCount() << endl;
        cout << endl;

        cout << "Первые строки первого файла:" << endl;
        printFirstRows(firstFile, previewRowCount);
        cout << endl;

        // Проверяем основные операции класса TextFile.
        TextFileFormatRow appended = firstFile;
        appended.appendFile(secondFile);
        cout << "Строк после appendFile: " << appended.getRowCount() << endl;

        TextFileFormatRow unionFile = firstFile + secondFile;
        cout << "Строк после operator+ без дублей: " << unionFile.getRowCount() << endl;

        TextFileFormatRow differenceFile = firstFile - secondFile;
        cout << "Строк после operator-: " << differenceFile.getRowCount() << endl;

        TextFileFormatRow plusEqualFile = firstFile;
        plusEqualFile += secondFile;
        cout << "Строк после operator+=: " << plusEqualFile.getRowCount() << endl;

        TextFileFormatRow minusEqualFile = firstFile;
        minusEqualFile -= secondFile;
        cout << "Строк после operator-=: " << minusEqualFile.getRowCount() << endl;
        cout << endl;

        vector<TextFileFormatRow> files = {firstFile, secondFile};

        TextFileFormatRow uniqueLines = TextFileFormatRow::createWithUniqueLines(files);
        TextFileFormatRow commonLines = TextFileFormatRow::createWithCommonLines(files);

        cout << "Строк после объединения без дублей: " << uniqueLines.getRowCount() << endl;
        cout << "Общих строк в двух файлах: " << commonLines.getRowCount() << endl;
        cout << endl;

        // Сортируем первый файл по выбранной колонке.
        TextFileFormatRow sortedByAmp = firstFile;
        sortedByAmp.sortDataByColumn(sortColumnIndex, sortAscending);

        cout << "Первый файл отсортирован по колонке " << sortColumnIndex
             << ", первые " << previewRowCount << " строк:" << endl;
        printFirstRows(sortedByAmp, previewRowCount);
        cout << endl;

        cout << "Сумма всех чисел в первом файле: " << firstFile.sumAllNumbers() << endl;
        cout << "Сумма всех чисел во втором файле: " << secondFile.sumAllNumbers() << endl;

        // Сохраняем результаты в выбранные файлы.
        unionFile.saveToFile(unionOutputPath);
        differenceFile.saveToFile(differenceOutputPath);
        sortedByAmp.saveToFile(sortedOutputPath);
        
    } catch (const exception& error) {
        cout << "Ошибка: " << error.what() << endl;
        return 1;
    }

    return 0;
}
