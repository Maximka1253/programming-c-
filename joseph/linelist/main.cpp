#include <iostream>
#include "linelist.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "Russian");
    
    LineList<int> list;
    cout << "Начало: " << list << endl;
    
    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();
    list.insertAfter(ptr, 15);
    list.insertAfter(ptr->getNext(), 12);
    list.insertFirst(7);
    
    cout << "Шаг 1: " << list << endl;
    
    // Подсчет суммы элементов
    int sum = 0;
    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext()) {
        sum += it->getData();
    }
    cout << "Сумма элементов: " << sum << endl;

    return 0;
}