#include "BoardGraph.h"

BoardGraph::BoardGraph() {
    build();
}

void BoardGraph::build() {
    // Строим граф соседства для поля 5x5.
    adjacency.clear();
    adjacency.resize(Board::SIZE * Board::SIZE);

    for (int row = 0; row < Board::SIZE; row++) {
        for (int col = 0; col < Board::SIZE; col++) {
            Position current(row, col);
            int currentVertex = getVertexNumber(current);

            Position neighbours[4] = {
                Position(row - 1, col),
                Position(row + 1, col),
                Position(row, col - 1),
                Position(row, col + 1)
            };

            for (int i = 0; i < 4; i++) {
                if (isInside(neighbours[i])) {
                    adjacency[currentVertex].push_back(getVertexNumber(neighbours[i]));
                }
            }
        }
    }
}

int BoardGraph::getVertexNumber(const Position& pos) const {
    // Перевод координат в номер вершины.
    return pos.row * Board::SIZE + pos.col;
}

Position BoardGraph::getPosition(int vertex) const {
    // Перевод номера вершины обратно в координаты.
    int row = vertex / Board::SIZE;
    int col = vertex % Board::SIZE;
    return Position(row, col);
}

const vector<int>& BoardGraph::getNeighbours(int vertex) const {
    return adjacency[vertex];
}

int BoardGraph::getVertexCount() const {
    return static_cast<int>(adjacency.size());
}

bool BoardGraph::isInside(const Position& pos) const {
    return pos.row >= 0 && pos.row < Board::SIZE && pos.col >= 0 && pos.col < Board::SIZE;
}
