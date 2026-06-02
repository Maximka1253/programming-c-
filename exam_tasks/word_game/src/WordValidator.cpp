#include "WordValidator.h"
#include "BoardGraph.h"
#include "RussianText.h"

using namespace std;

// Берем букву с учетом новой клетки.
static string getLetterForCheck(
    const Board& board,
    const Position& pos,
    const Position& addedPosition,
    const string& addedLetter
) {
    if (pos.equals(addedPosition)) {
        return addedLetter;
    }

    if (board.isEmpty(pos)) {
        return "";
    }

    return board.getLetter(pos);
}

// DFS ищет слово по соседним клеткам.
static bool depthFirstSearch(
    const Board& board,
    const BoardGraph& graph,
    const vector<string>& wordLetters,
    int currentVertex,
    const Position& addedPosition,
    const string& addedLetter,
    int index,
    bool used[Board::SIZE * Board::SIZE],
    bool containsAddedPosition
) {
    if (used[currentVertex]) {
        return false;
    }

    Position current = graph.getPosition(currentVertex);
    string currentLetter = getLetterForCheck(board, current, addedPosition, addedLetter);
    if (currentLetter != wordLetters[index]) {
        return false;
    }

    bool nowContainsAddedPosition = containsAddedPosition || current.equals(addedPosition);
    used[currentVertex] = true;

    if (index == static_cast<int>(wordLetters.size()) - 1) {
        used[currentVertex] = false;
        return nowContainsAddedPosition;
    }

    const vector<int>& neighbours = graph.getNeighbours(currentVertex);

    for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
        if (depthFirstSearch(
            board,
            graph,
            wordLetters,
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
    const vector<string>& wordLetters,
    const Position& addedPosition,
    const string& addedLetter
) {
    BoardGraph graph;
    bool used[Board::SIZE * Board::SIZE] = {};

    for (int vertex = 0; vertex < graph.getVertexCount(); vertex++) {
        if (depthFirstSearch(
            board,
            graph,
            wordLetters,
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

// Проверяем, можно ли построить слово, добавив одну новую букву на доску.
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
    string addedLetter = RussianText::normalizeRussianWord(move.addedLetter);

    if (!RussianText::isSingleRussianLetter(move.addedLetter)) {
        errorMessage = "Новая буква должна быть русской буквой.";
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

    if (!RussianText::containsOnlyRussianLetters(move.word)) {
        errorMessage = "Слово должно содержать только русские буквы.";
        return false;
    }

    vector<string> wordLetters = RussianText::splitRussianLetters(word);
    if (wordLetters.empty()) {
        errorMessage = "Слово должно содержать русские буквы.";
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

    if (static_cast<int>(wordLetters.size()) > Board::SIZE * Board::SIZE) {
        errorMessage = "Слово слишком длинное для поля 5x5.";
        return false;
    }

    if (!canBuildWordAutomatically(board, wordLetters, move.addedPosition, addedLetter)) {
        errorMessage = "Слово нельзя составить по соседним клеткам с новой буквой.";
        return false;
    }

    return true;
}
