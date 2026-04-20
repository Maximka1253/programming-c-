#include <iostream>

using namespace std;

long long josephus(long long n, long long k) {
    long long res = 0;
    for (long long i = 1; i <= n; ++i) {
        res = (res + k) % i;
    }
    return res + 1;
}

int main() {
    long long n = 0;
    long long k = 0;

    cout << "Введите n и k: ";
    if (!(cin >> n >> k)) {
        return 1;
    }

    if (n <= 0 || k <= 0) {
        return 1;
    }

    clock_t start = clock();

    long long result = josephus(n, k);

    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    cout << result << endl;
    cout << "Время: " << duration << "сек" << endl;

    return 0;
}