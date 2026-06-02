#include "Game.h"
#include "BoardGraph.h"
#include "RussianText.h"
#include <iostream>
#include <unordered_set>

using namespace std;

static int readInt(const string& message) {
    int value;

    while (true) {
        cout << message;
        if (cin >> value) {
            return value;
        }

        cout << "Ошибка ввода. Нужно ввести число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Чтение одного слова.
static string readWord(const string& message) {
    string value;
    cout << message;
    cin >> value;
    return value;
}

// Чтение позиции в виде двух чисел: строки и столбца.
static Position readPosition(const string& message) {
    int row;
    int col;

    while (true) {
        cout << message;
        if (cin >> row >> col) {
            return Position(row, col);
        }

        cout << "Ошибка ввода. Нужно ввести два числа.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

Game::Game() {
    currentPlayer = 0;
    passesInRow = 0;
    moveNumber = 1;
}

// Инициализация игры: загрузка словаря, ввод игроков и стартового слова.
bool Game::init() {
    cout << "Консольная игра \"Слова\"\n\n";

    // Загружаем словарь и открываем лог.
    if (!dictionary.loadFromFile("dictionary.txt")) {
        cout << "Не найден файл dictionary.txt. Добавьте файл словаря рядом с программой и запустите снова.\n";
        return false;
    }

    if (!logger.open("logs/log.txt")) {
        cout << "Не удалось открыть logs/log.txt для записи.\n";
        return false;
    }

    int playerCount = 0;
    while (playerCount < 2 || playerCount > 4) {
        playerCount = readInt("Введите количество игроков (2-4): ");
        if (playerCount < 2 || playerCount > 4) {
            cout << "Количество игроков должно быть от 2 до 4.\n";
        }
    }

    players.clear();
    for (int i = 0; i < playerCount; i++) {
        string name = readWord("Введите имя игрока: ");
        players.push_back(Player(name));
    }

    string startWord;
    bool startWordOk = false;

    // Вводим корректное стартовое слово.
    while (!startWordOk) {
        string enteredStartWord = readWord("Введите стартовое слово из 5 букв: ");
        startWord = dictionary.normalize(enteredStartWord);

        if (!RussianText::containsOnlyRussianLetters(enteredStartWord)) {
            cout << "Стартовое слово должно содержать только русские буквы.\n";
        } else if (RussianText::getRussianLetterCount(startWord) != Board::SIZE) {
            cout << "Стартовое слово должно содержать ровно 5 букв.\n";
        } else if (!dictionary.contains(enteredStartWord)) {
            cout << "Стартового слова нет в dictionary.txt.\n";
        } else {
            startWordOk = board.initStartWord(startWord);
        }
    }

    usedWords.clear();
    usedWords.push_back(startWord);

    currentPlayer = 0;
    passesInRow = 0;
    moveNumber = 1;

    logger.logStart(players, startWord);
    cout << "Игра началась. Координаты клеток вводятся числами от 0 до 4.\n";

    return true;
}

void Game::play() {
    // Основной игровой цикл.
    while (!isGameOver()) {
        Player& player = players[currentPlayer];
        bool moveAccepted = false;

        while (!moveAccepted && !isGameOver()) {
            board.print();
            cout << "\nХод игрока: " << player.getName() << "\n";
            cout << "Очки: " << player.getScore() << "\n";

            Move move = inputMove();
            string errorMessage = "";

            // Проверяем ход и применяем его.
            if (validator.validateMove(board, move, dictionary, usedWords, errorMessage)) {
                if (move.pass) {
                    passesInRow++;
                    cout << "Ход пропущен.\n";
                    logger.logMove(moveNumber, player, move, "Пропуск хода. Пропусков подряд: " + to_string(passesInRow));
                    moveNumber++;
                } else {
                    string word = dictionary.normalize(move.word);
                    string letter = RussianText::normalizeRussianWord(move.addedLetter);
                    int points = RussianText::getRussianLetterCount(word);

                    board.setLetter(move.addedPosition, letter);
                    player.addScore(points);
                    usedWords.push_back(word);
                    passesInRow = 0;

                    cout << "Ход принят. Начислено очков: " << points << "\n";
                    logger.logMove(moveNumber, player, move, "Ход принят. Начислено очков: " + to_string(points));
                    moveNumber++;
                }

                moveAccepted = true;
            } else {
                cout << "Ошибка хода: " << errorMessage << "\n";
                cout << "Попробуйте ввести ход еще раз.\n";
                logger.logMove(moveNumber, player, move, "Ошибка: " + errorMessage);
            }
        }

        if (moveAccepted && !isGameOver()) {
            nextPlayer();
        }
    }

    board.print();
    printResults();

    string result = getWinnerText();
    cout << result << "\n";
    logger.logEnd(players, result);
}

Move Game::inputMove() {
    // Ввод одного хода игрока.
    Move move;

    string command;
    while (true) {
        command = readWord("Введите букву или pass для пропуска хода: ");

        if (command == "pass") {
            move.pass = true;
            return move;
        }

        if (RussianText::isSingleRussianLetter(command)) {
            move.pass = false;
            move.addedLetter = RussianText::normalizeRussianWord(command);
            break;
        }

        cout << "Ошибка ввода. Нужно ввести одну русскую букву или pass.\n";
    }

    move.addedPosition = readPosition("Введите строку и столбец новой буквы: ");
    move.word = readWord("Введите составленное слово: ");

    return move;
}

void Game::nextPlayer() {
    currentPlayer++;

    if (currentPlayer >= static_cast<int>(players.size())) {
        currentPlayer = 0;
    }
}

// Рекурсивная функция для проверки, можно ли построить слово, добавив одну новую букву.
static bool depthFirstSearch(
    const Board& board,
    const BoardGraph& graph,
    const vector<string>& letters,
    int currentVertex,
    int index,
    bool used[Board::SIZE * Board::SIZE],
    bool usedNewCell
) {
    if (used[currentVertex]) {
        return false;
    }

    Position pos = graph.getPosition(currentVertex);
    bool currentIsNewCell = false;

    if (board.isEmpty(pos)) {
        if (usedNewCell || !board.hasFilledNeighbour(pos)) {
            return false;
        }

        currentIsNewCell = true;
    } else if (board.getLetter(pos) != letters[index]) {
        return false;
    }

    bool nowUsedNewCell = usedNewCell || currentIsNewCell;
    used[currentVertex] = true;

    if (index == static_cast<int>(letters.size()) - 1) {
        used[currentVertex] = false;
        return nowUsedNewCell;
    }

    const vector<int>& neighbours = graph.getNeighbours(currentVertex);
    for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
        if (depthFirstSearch(
            board,
            graph,
            letters,
            neighbours[i],
            index + 1,
            used,
            nowUsedNewCell
        )) {
            used[currentVertex] = false;
            return true;
        }
    }

    used[currentVertex] = false;
    return false;
}

// Проверяем, можно ли построить слово, добавив одну новую букву на доску.
static bool canBuildWordAutomatically(const Board& board, const vector<string>& letters) {
    BoardGraph graph;
    bool used[Board::SIZE * Board::SIZE] = {};

    for (int vertex = 0; vertex < graph.getVertexCount(); vertex++) {
        if (depthFirstSearch(board, graph, letters, vertex, 0, used, false)) {
            return true;
        }
    }

    return false;
}

// Проверка, есть ли у игроков возможный ход. Если нет, то игра заканчивается.
bool Game::hasPossibleMove() const {
    if (board.isFull()) {
        return false;
    }

    int filledCells = 0;
    for (int row = 0; row < Board::SIZE; row++) {
        for (int col = 0; col < Board::SIZE; col++) {
            if (!board.isEmpty(Position(row, col))) {
                filledCells++;
            }
        }
    }

    unordered_set<string> usedWordSet;
    for (int i = 0; i < static_cast<int>(usedWords.size()); i++) {
        usedWordSet.insert(dictionary.normalize(usedWords[i]));
    }

    const vector<string>& words = dictionary.getWords();
    int maxWordLength = filledCells + 1;

    for (int w = 0; w < static_cast<int>(words.size()); w++) {
        string word = dictionary.normalize(words[w]);
        vector<string> letters = RussianText::splitRussianLetters(word);

        if (
            word.empty()
            || static_cast<int>(letters.size()) > maxWordLength
            || usedWordSet.find(word) != usedWordSet.end()
        ) {
            continue;
        }

        if (canBuildWordAutomatically(board, letters)) {
            return true;
        }
    }

    return false;
}

bool Game::isGameOver() const {
    int maxPasses = static_cast<int>(players.size()) * 3;
    return board.isFull() || passesInRow >= maxPasses || !hasPossibleMove();
}

void Game::printResults() const {
    cout << "\nИтоги игры:\n";

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        cout << players[i].getName() << ": " << players[i].getScore() << " очков\n";
    }
}
// Определение победителя и формирование текста результата.
string Game::getWinnerText() const {
    if (players.empty()) {
        return "Нет игроков.";
    }

    if (passesInRow >= static_cast<int>(players.size()) * 3) {
        return "Ничья: игроки сделали три круга пропусков подряд.";
    }

    // Ищем лучший счет.
    int bestScore = players[0].getScore();
    for (int i = 1; i < static_cast<int>(players.size()); i++) {
        if (players[i].getScore() > bestScore) {
            bestScore = players[i].getScore();
        }
    }

    int winnersCount = 0;
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        if (players[i].getScore() == bestScore) {
            winnersCount++;
        }
    }

    if (winnersCount > 1) {
        string result = "Ничья по очкам между игроками: ";
        bool first = true;

        for (int i = 0; i < static_cast<int>(players.size()); i++) {
            if (players[i].getScore() == bestScore) {
                if (!first) {
                    result += ", ";
                }

                result += players[i].getName();
                first = false;
            }
        }

        result += ". Счет: " + to_string(bestScore);
        return result;
    }

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        if (players[i].getScore() == bestScore) {
            return "Победитель: " + players[i].getName() + ". Счет: " + to_string(bestScore);
        }
    }

    return "Победитель не определен.";
}
