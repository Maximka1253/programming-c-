#include "datatime.h"
#include <iostream>

using namespace std;

int main() {
    DateTime dt1(2026, 4, 7, 14, 30, 0);
    DateTime dt2(2025, 1, 1);

    cout << "dt1 = " << dt1 << endl;
    cout << "dt2 = " << dt2 << endl << endl;

    cout << "День недели для dt1: " << dt1.getWeekDayName() << endl;
    cout << "День недели для dt2: " << dt2.getWeekDayName() << endl << endl;

    cout << "dt1 + 10 дней = " << (dt1 + 10) << endl;
    cout << "dt1 - 5 дней  = " << (dt1 - 5) << endl;
    cout << "Разница между dt1 и dt2 = " << (dt1 - dt2) << " дней" << endl << endl;

    cout << "dt1 > dt2: " << (dt1 > dt2) << endl;
    cout << "dt1 < dt2: " << (dt1 < dt2) << endl;
    cout << "dt1 == dt2: " << (dt1 == dt2) << endl << endl;

    DateTime userDate;

    cout << "Введите дату в формате: ГОД МЕСЯЦ ДЕНЬ ЧАС МИНУТА СЕКУНДА(2026 4 7 12 12 12)" << endl;
    cout << "> ";

    if (cin >> userDate) {
        cout << "Вы ввели: " << userDate << endl;
        cout << "День недели: " << userDate.getWeekDayName() << endl;
    } else {
        cout << "Ошибка! Такой даты не существует или формат ввода неверный." << endl;
    }
}