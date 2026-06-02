#ifndef CELL_H
#define CELL_H

#include <string>

using std::string;

class Cell {
private:
    string letter;
    bool empty;

public:
    Cell();

    bool isEmpty() const;
    string getLetter() const;
    void setLetter(const string& value);
    void clear();
};

#endif
