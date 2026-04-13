#include <iostream>
#include "array.h"
using namespace std;

int main()
{
    // Создаём массив вместимостью 4 и вставляем 4 элемента в конец
    Array arr(4);
    for (int i = 0; i < 4; i++)
        arr.insert(i + 1);
    cout << arr << endl;

    // Вставляем элементы по индексам 0, 2, 4, 6
    for (int i = 0; i < 8; i += 2)
        arr.insert(10 + i, i);
    cout << arr << endl;

    // Записываем значения по нечётным индексам
    for (int i = 1; i < arr.getSize(); i += 2)
        arr[i] = 20 + i;
    cout << arr << endl;

    // Удаляем элементы по индексам 6, 3, 0
    for (int i = 6; i >= 0; i -= 3)
        arr.remove(i);
    cout << arr << endl;


    cout << "Введите n и k: ";
    int n,k;
    cin >> n >> k;
    Array arr2(n);
    for (int i = 1; i < arr2.getSize(); i++){
        arr.insert(i);
    }
    cout << arr <<endl;


    try {
        cout << "Попытка обратиться к индексу 100:" << endl;
        int x = arr[100];
    } catch (ArrayException&) {
        cout << "Ошибка: индекс за пределами массива!" << endl;
    }

    return 0;
}
