#include "datatime.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    DateTime dt1(2026, 4, 5, 12, 30, 0);
    DateTime dt2(2025, 1, 1);

    cout << "dt1: " << dt1 << "\n";
    cout << "dt2: " << dt2 << "\n";

    istringstream ss1("2021-12-21T07:54:34");
    istringstream ss2("2024-02-29");
    istringstream ss3("07:54:34");

    DateTime dt3, dt4, dt5;
    ss1 >> dt3;
    ss2 >> dt4;
    ss3 >> dt5;

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