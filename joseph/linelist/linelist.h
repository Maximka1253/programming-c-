#ifndef LINELIST_H
#define LINELIST_H

#include <exception>
#include <iostream>

using namespace std;

// Класс исключения
class LineListException : public exception {
public:
    const char* what() const throw() { return "LineList Error"; }
};

// Шаблон элемента списка
template <class T> class LineListElem {
    T data;
    LineListElem<T>* next;
public:
    LineListElem(const T& adata, LineListElem<T>* anext) {
        data = adata;
        next = anext;
    }
    const T& getData() const { return data; }
    LineListElem<T>* getNext() { return next; }

    template <class U> friend class LineList;
};

// Шаблон списка
template <class T> class LineList {
    LineListElem<T>* start;
    LineListElem<T>* tail;

    // Запрет копирования
    LineList(const LineList& list); 
    LineList& operator =(const LineList& list);

public:
    LineList() { 
        start = 0;
        tail = 0;
    }

    ~LineList() {
        while (start) deleteFirst();
    }

    LineListElem<T>* getStart() { return start; }

    void insertFirst(const T& data) {
        LineListElem<T>* second = start;
        start = new LineListElem<T>(data, second);
        if (!tail) tail = start;
    }

    void insertAfter(LineListElem<T>* ptr, const T& data) {
        if (ptr) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = new LineListElem<T>(data, temp);
            if (ptr == tail) tail = ptr->next;
        } else throw LineListException();
    }

    void deleteFirst() {
        if (start) {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
            if (!start) tail = 0;
        } else throw LineListException();
    }

    void deleteAfter(LineListElem<T>* ptr) {
        if (ptr && ptr->next) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = ptr->next->next;
            if (temp == tail) tail = ptr;
            delete temp;
        } else throw LineListException();
    }

    template <class U> friend ostream& operator <<(ostream& out, LineList<U>& list);
};

// Оператор вывода
template <class T> ostream& operator <<(ostream& out, LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) out << "EMPTY ";
    else while (ptr) {
        out << ptr->getData() << ' ';
        ptr = ptr->getNext();
    }
    return out;
}

#endif