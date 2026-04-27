#include "4_in_a_row.h"
#include <iostream>
#include <limits>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Field field(true); // Начинает красный
    
    while (!field.isOver()) {
        field.print();
        cout << "Ходит "
             << (field.isRedTurnNow() ? "красный" : "жёлтый")
             << " игрок, введите номер столбца (1-7): ";
        
        int column;
        
        // Цикл ввода данных
        while (true) {
            if (cin >> column && column >= 1 && column <= 7) {
                break; // Успешный ввод корректного числа
            } else {
                cout << "Ошибка! Введите целое число от 1 до 7: ";
                cin.clear(); // Сброс состояния потока
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка мусора из буфера
            }
        }
        
        // Проверка на случай, выбора полностью заполненного столбеца
        if (!field.makeTurn(column)) {
            cout << "-> Этот столбец уже заполнен! Выберите другой.\n\n";
        }
    }
    
    field.print(); // Показываем итоговое поле
    field.printResult();
    
    return 0;
}