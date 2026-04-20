#ifndef CYCLELIST_H
#define CYCLELIST_H

#include <exception>
#include <iostream>

using namespace std;

class LineListException : public exception {
public:
    const char* what() const throw() { return "LineList Error"; }
};

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

template <class T> class LineList {
    LineListElem<T>* start;
    LineListElem<T>* tail;

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
        if (!start) {
            start = new LineListElem<T>(data, 0);
            tail = start;
            tail->next = start; // Закольцовывание
        } else {
            LineListElem<T>* second = start;
            start = new LineListElem<T>(data, second);
            tail->next = start; // Поддержание цикла
        }
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
            if (start == tail) {
                delete start;
                start = 0;
                tail = 0;
            } else {
                LineListElem<T>* temp = start->next;
                delete start;
                start = temp;
                tail->next = start; // Поддержание цикла
            }
        } else throw LineListException();
    }

    void deleteAfter(LineListElem<T>* ptr) {
        if (ptr && start) {
            LineListElem<T>* temp = ptr->next;
            if (temp == start) {
                deleteFirst();
            } else {
                ptr->next = temp->next;
                if (temp == tail) tail = ptr;
                delete temp;
            }
        } else throw LineListException();
    }

    template <class U> friend ostream& operator <<(ostream& out, LineList<U>& list);
};

// Оператор вывода для циклического списка
template <class T> ostream& operator <<(ostream& out, LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) {
        out << "EMPTY ";
    } else {
        LineListElem<T>* first = ptr;
        do {
            out << ptr->getData() << " ";
            ptr = ptr->getNext();
        } while (ptr != first);
    }
    return out;
}

#endif