#include "WordValidator.h"
#include "BoardGraph.h"
#include <cctype>

using namespace std;

// Проверка латинской буквы.
static bool isLatinLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Берем букву с учетом новой клетки.
static char getLetterForCheck(
    const Board& board,
    const Position& pos,
    const Position& addedPosition,
    char addedLetter
) {
    if (pos.equals(addedPosition)) {
        return addedLetter;
    }

    if (board.isEmpty(pos)) {
        return ' ';
    }

    return board.getLetter(pos);
}

// DFS ищет слово по соседним клеткам.
static bool depthFirstSearch(
    const Board& board,
    const BoardGraph& graph,
    const string& word,
    int currentVertex,
    const Position& addedPosition,
    char addedLetter,
    int index,
    bool used[Board::SIZE * Board::SIZE],
    bool containsAddedPosition
) {
    if (used[currentVertex]) {
        return false;
    }

    Position current = graph.getPosition(currentVertex);
    char currentLetter = getLetterForCheck(board, current, addedPosition, addedLetter);
    if (currentLetter != word[index]) {
        return false;
    }

    bool nowContainsAddedPosition = containsAddedPosition || current.equals(addedPosition);
    used[currentVertex] = true;

    if (index == static_cast<int>(word.length()) - 1) {
        used[currentVertex] = false;
        return nowContainsAddedPosition;
    }

    const vector<int>& neighbours = graph.getNeighbours(currentVertex);

    for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
        if (depthFirstSearch(
            board,
            graph,
            word,
            neighbours[i],
            addedPosition,
            addedLetter,
            index + 1,
            used,
            nowContainsAddedPosition
        )) {
            used[currentVertex] = false;
            return true;
        }
    }

    used[currentVertex] = false;
    return false;
}

// Пробуем начать слово из каждой клетки.
static bool canBuildWordAutomatically(
    const Board& board,
    const string& word,
    const Position& addedPosition,
    char addedLetter
) {
    BoardGraph graph;
    bool used[Board::SIZE * Board::SIZE] = {};

    for (int vertex = 0; vertex < graph.getVertexCount(); vertex++) {
        if (depthFirstSearch(
            board,
            graph,
            word,
            vertex,
            addedPosition,
            addedLetter,
            0,
            used,
            false
        )) {
            return true;
        }
    }

    return false;
}

bool WordValidator::validateMove(
    const Board& board,
    const Move& move,
    const Dictionary& dictionary,
    const vector<string>& usedWords,
    string& errorMessage
) const {
    if (move.pass) {
        return true;
    }

    // Проверяем правила хода по порядку.
    string word = dictionary.normalize(move.word);
    char addedLetter = static_cast<char>(tolower(static_cast<unsigned char>(move.addedLetter)));

    if (!isLatinLetter(move.addedLetter)) {
        errorMessage = "Новая буква должна быть латинской буквой.";
        return false;
    }

    if (!board.isInside(move.addedPosition)) {
        errorMessage = "Координаты новой буквы находятся вне поля.";
        return false;
    }

    if (!board.isEmpty(move.addedPosition)) {
        errorMessage = "Выбранная клетка уже занята.";
        return false;
    }

    if (!board.hasFilledNeighbour(move.addedPosition)) {
        errorMessage = "Новая буква должна стоять рядом с уже заполненной клеткой.";
        return false;
    }

    if (word.empty()) {
        errorMessage = "Слово не должно быть пустым.";
        return false;
    }

    if (!dictionary.contains(word)) {
        errorMessage = "Такого слова нет в dictionary.txt.";
        return false;
    }

    for (int i = 0; i < static_cast<int>(usedWords.size()); i++) {
        if (dictionary.normalize(usedWords[i]) == word) {
            errorMessage = "Это слово уже использовалось.";
            return false;
        }
    }

    if (word.length() > Board::SIZE * Board::SIZE) {
        errorMessage = "Слово слишком длинное для поля 5x5.";
        return false;
    }

    if (!canBuildWordAutomatically(board, word, move.addedPosition, addedLetter)) {
        errorMessage = "Слово нельзя составить по соседним клеткам с новой буквой.";
        return false;
    }

    return true;
}
