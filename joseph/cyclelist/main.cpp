#include <iostream>
#include "cyclelist.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "Russian");
    LineList<int> list;
    
    cout << "Начало: " << list << endl;
    
    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();
    list.insertAfter(ptr, 15);
    list.insertFirst(7);
    
    cout << "Циклический список: " << list << endl;
    

    cout << "Демонстрация цикла: ";
    LineListElem<int>* it = list.getStart();
    for (int i = 0; i < 6; i++) {
        cout << it->getData() << " ";
        it = it->getNext();
    }
    cout << endl;

    return 0;
}