#include <iostream>
#include "linelist.h"

using namespace std;

long long josephus_list(long long n, long long k) {
    LineList<long long> list;

    // заполняем список 1..n
    for (long long i = n; i >= 1; --i)
        list.insertFirst(i);

    auto current = list.getStart();

    // если один элемент
    if (!current) return -1;

    while (true) {
        // проверка: остался один элемент
        if (current == list.getStart() && current->getNext() == nullptr)
            return current->getData();

        // двигаемся на k-1 шагов
        for (long long i = 1; i < k - 1; ++i) {
            if (!current->getNext())
                current = list.getStart();
            else
                current = current->getNext();
        }

        // если next = nullptr → удаляем первый
        if (!current->getNext()) {
            list.deleteFirst();
            current = list.getStart();
        } else {
            list.deleteAfter(current);

            // переход дальше
            if (!current->getNext())
                current = list.getStart();
            else
                current = current->getNext();
        }
    }
}

int main() {
    long long n, k;
    cout << "Введите n и k: ";
    cin >> n >> k;
    if (n <= 0 || k <= 0) return 1;

    clock_t start = clock();


    long long result = josephus_list(n, k);

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    cout << result << endl;
    cout << "Время: " << duration << "сек" << endl;

    return 0;
}