#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

const int DEFAULT_CAPACITY = 10;

class ArrayException {};

class Array
{
    // Указатель на массив в динамической памяти
    int* ptr;
    // Текущий размер
    int size;
    // Вместимость
    int capacity;

    // Закрытая функция увеличения предельного размера
    void increaseCapacity(int newCapacity);

public:
    explicit Array(int startCapacity = DEFAULT_CAPACITY);

    // Деструктор
    ~Array();

    // Конструктор копирования
    Array(const Array& arr);

    // Оператор присваивания
    Array& operator =(const Array& arr);

    // Оператор индексации (чтение и запись)
    int& operator [](int index);

    // Оператор индексации (только чтение)
    int operator [](int index) const;

    void insert(int elem, int index);

    void insert(int elem);

    void remove(int index);

    int getSize() const;

    friend ostream& operator <<(ostream& out, const Array& arr);
};


#endif
