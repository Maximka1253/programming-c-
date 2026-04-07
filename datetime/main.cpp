#include "datatime.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    DateTime dt1(2026, 4, 5, 12, 30, 0);
    DateTime dt2(2025, 1, 1);

    cout << "dt1: " << dt1 << "\n";
    cout << "dt2: " << dt2 << "\n";

    DateTime dt3(2021, 2, 12, 23, 54, 32);
    DateTime dt4(2024, 9, 22, 21, 24, 52);
    DateTime dt5(2023, 7, 2, 13, 42, 12);

    cout << "dt3: " << dt3 << "\n";
    cout << "dt4: " << dt4 << "\n";
    cout << "dt5: " << dt5 << "\n";

    // ввод с клавиатуры
    cout << "Введите дату: ";
    cin >> dt1;
    cout << " Вы ввели: " << dt1 << "\n";

    // арифметика
    cout << "(dt1 + 100): " << (dt1 + 100) << "\n";
    cout << "(dt1 - 30):  " << (dt1 - 30)  << "\n";
    cout << "Разница: "     << (dt1 - dt2) << " дней\n";

    // сравнение
    cout << "dt1 > dt2:  " << (dt1 >  dt2) << "\n";
    cout << "dt1 < dt2:  " << (dt1 <  dt2) << "\n";
    cout << "dt1 == dt2: " << (dt1 == dt2) << "\n";

    // сортировка
    DateTime arr[] = {
        DateTime(2023, 6, 15),
        DateTime(2021, 12, 21),
        DateTime(2025, 1, 1),
        DateTime(2022, 3, 10),
        DateTime(2024, 7, 4)
    };
    int n = 5;
    return 0;
}