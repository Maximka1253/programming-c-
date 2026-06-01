#ifndef BOARD_GRAPH_H
#define BOARD_GRAPH_H

#include <vector>
#include "Board.h"
#include "Position.h"

using std::vector;

class BoardGraph {
private:
    vector<vector<int>> adjacency;

    bool isInside(const Position& pos) const;

public:
    BoardGraph();

    void build();
    int getVertexNumber(const Position& pos) const;
    Position getPosition(int vertex) const;
    const vector<int>& getNeighbours(int vertex) const;
    int getVertexCount() const;
};

#endif
