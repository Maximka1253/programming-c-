#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

int Joseph(int n, int k) {
    // контейнер c числами от 1 до N 
    Array arr(n);
    for (int i = 1; i <= n; i++) {
        arr.insert(i);
    }

    int index = 0;
    
    // удаление элементов 
    while (arr.getSize() > 1) {
        
        index = (index + k - 1) % arr.getSize();
        arr.remove(index);
    }

    return arr[0];
}

int main() {
    int n, k;
    cout << "Введите N (количество элементов) и k (шаг): ";
    if (!(cin >> n >> k)) return 0;

    clock_t start = clock();

    int result = Joseph(n, k);

    clock_t end = clock();
    double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    cout << "Последний оставшийся элемент: " << result << endl;
    cout << "Время расчета: " << seconds << " сек." << endl;

    return 0;
}