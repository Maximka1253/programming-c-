#include "4_in_a_row.h"
#include <iostream>

using namespace std;

// Конструктор
Field::Field(bool isRedFirst) {
    clear(isRedFirst);
}

// Очистка поля
void Field::clear(bool isRedFirst) {
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

// Выполнение хода
bool Field::makeTurn(int column) {
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;
    
    int i = column - 1;
    
    // Поиск первой свободной ячейки снизу вверх
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
        if (cells[i][j] == EMPTY) {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }
    }
    return false; // Если столбец полностью заполнен
}

// Проверка победителя
const int DIR_NUMBER = 4;
const int di[] = {1, 0, 1, 1};
const int dj[] = {0, 1, -1, 1};
const int WIN_LENGTH = 4;

void Field::checkWinner() {
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;
            for (int dir = 0; dir < DIR_NUMBER; dir++) {
                int length = 1;   
                int iline = i, jline = j;
                
                while (length < WIN_LENGTH) {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;
                    if (cells[iline][jline] != start)
                        break;
                    length++;
                }
                if (length == WIN_LENGTH) {
                    winner = start;
                    return;
                }
            }
        }
    }
}

// Проверка, выиграл ли конкретный цвет
bool Field::isWon(bool red) const {
    Cell target = red ? RED : YELLOW;
    return winner == target;
}

// Игра окончена
bool Field::isOver() const {
    if (winner != EMPTY) return true;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;
    return true;
}

Cell Field::getCell(int i, int j) const {
    return cells[i][j];
}

// Сейчас ход красных?
bool Field::isRedTurnNow() const {
    return isRedTurn;
}

// Печать поля
void Field::print() const {
    cout << " 1 2 3 4 5 6 7\n";
    for (int j = 0; j < FIELD_HEIGHT; j++) {
        cout << "|";
        for (int i = 0; i < FIELD_WIDTH; i++) {
            char c;
            switch (cells[i][j]) {
                case RED:    c = 'R'; break;
                case YELLOW: c = 'Y'; break;
                default:     c = ' '; break;
            }
            cout << c << "|";
        }
        cout << "\n";
    }
    cout << "---------------\n";
}

// Печать результата игры
void Field::printResult() const {
    if (winner == RED)
        cout << "Победил красный игрок!\n";
    else if (winner == YELLOW)
        cout << "Победил жёлтый игрок!\n";
    else
        cout << "Ничья!\n";
}