#include "moon.h"
#include <ctime>
#include <iostream>

using namespace std;

DateTime readDateFromInput() {
    DateTime dateTime;

    cout << "Введите дату: ГОД МЕСЯЦ ДЕНЬ ЧАС МИНУТА СЕКУНДА" << endl;

    while (!(cin >> dateTime)) {
        cout << "Ошибка ввода! Попробуйте снова." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return dateTime;
}

void printDateTime(const DateTime& dateTime, bool exists) {
    if (!exists) {
        cout << "нет";
        return;
    }

    cout << dateTime;
}

void printMoonResult(const MoonResult& result) {
    if (!result.fileOpened) {
        cout << "Не удалось открыть файл с данными для года "
             << result.date.getYear() << endl;
        return;
    }

    cout << endl;
    cout << "Дата: " << result.date << endl;
    cout << "Восход Луны: ";
    printDateTime(result.rise, result.hasRise);
    cout << endl;
    cout << "Кульминация Луны: ";
    printDateTime(result.culmination, result.hasCulmination);
    cout << endl;
    cout << "Заход Луны: ";
    printDateTime(result.set, result.hasSet);
    cout << endl;
}

int main() {
    clock_t startTime = clock();

    DateTime dateTime = readDateFromInput();
    Moon moon(dateTime);
    MoonResult result = moon.calculate();
    printMoonResult(result);

    clock_t endTime = clock();
    double executionTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << endl;
    cout << "Время выполнения: " << executionTime << " сек" << endl;

    return 0;
}