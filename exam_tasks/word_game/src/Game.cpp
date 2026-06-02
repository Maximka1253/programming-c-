#include "Game.h"
#include "RussianText.h"
#include <iostream>

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

static string readWord(const string& message) {
    string value;
    cout << message;
    cin >> value;
    return value;
}

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
}

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
                    logger.logMove(player, move, "Пропуск хода. Пропусков подряд: " + to_string(passesInRow));
                } else {
                    string word = dictionary.normalize(move.word);
                    string letter = RussianText::normalizeRussianWord(move.addedLetter);
                    int points = RussianText::getRussianLetterCount(word);

                    board.setLetter(move.addedPosition, letter);
                    player.addScore(points);
                    usedWords.push_back(word);
                    passesInRow = 0;

                    cout << "Ход принят. Начислено очков: " << points << "\n";
                    logger.logMove(player, move, "Ход принят. Начислено очков: " + to_string(points));
                }

                moveAccepted = true;
            } else {
                cout << "Ошибка хода: " << errorMessage << "\n";
                cout << "Попробуйте ввести ход еще раз.\n";
                logger.logMove(player, move, "Ошибка: " + errorMessage);
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


bool Game::isWordUsed(const string& word) const {
    string normalizedWord = dictionary.normalize(word);

    for (int i = 0; i < static_cast<int>(usedWords.size()); i++) {
        if (dictionary.normalize(usedWords[i]) == normalizedWord) {
            return true;
        }
    }

    return false;
}

bool Game::hasPossibleMove() const {
    if (board.isFull()) {
        return false;
    }

    const vector<string>& words = dictionary.getWords();

    for (int row = 0; row < Board::SIZE; row++) {
        for (int col = 0; col < Board::SIZE; col++) {
            Position pos(row, col);

            if (!board.isEmpty(pos) || !board.hasFilledNeighbour(pos)) {
                continue;
            }

            for (int w = 0; w < static_cast<int>(words.size()); w++) {
                string word = dictionary.normalize(words[w]);

                if (word.empty() || isWordUsed(word)) {
                    continue;
                }

                vector<string> checkedLetters;
                vector<string> letters = RussianText::splitRussianLetters(word);

                for (int i = 0; i < static_cast<int>(letters.size()); i++) {
                    bool alreadyChecked = false;

                    for (int j = 0; j < static_cast<int>(checkedLetters.size()); j++) {
                        if (checkedLetters[j] == letters[i]) {
                            alreadyChecked = true;
                        }
                    }

                    if (alreadyChecked) {
                        continue;
                    }

                    checkedLetters.push_back(letters[i]);

                    Move move;
                    move.pass = false;
                    move.addedLetter = letters[i];
                    move.addedPosition = pos;
                    move.word = word;

                    string errorMessage;
                    if (validator.validateMove(board, move, dictionary, usedWords, errorMessage)) {
                        return true;
                    }
                }
            }
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
