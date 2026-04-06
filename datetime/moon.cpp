#include "datatime.h"
#include <iostream>
#include <fstream>
#include <filesystem>


using namespace std;

void openMoonFile(int year) {
    if (year < 1998 || year > 2023) {
        cerr << "Данные за " << year << " год отсутствуют." << endl;
        return;
    }
    string filePath = "moon/moon" + std::to_string(year) + ".dat";
    ifstream file(filePath);
    if (!file.is_open()) {
    cerr << "Не удалось открыть файл: " << filePath << endl;
        return;
    }
    file.close();
}