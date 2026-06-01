#ifndef CELL_H
#define CELL_H

class Cell {
private:
    char letter;
    bool empty;

public:
    Cell();

    bool isEmpty() const;
    char getLetter() const;
    void setLetter(char ch);
    void clear();
};

#endif
