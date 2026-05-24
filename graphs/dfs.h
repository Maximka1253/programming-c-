#pragma once

#include "graph.h"

#include <set>

class DFS {
    std::set<Node*> visited;

    bool connectedRecursive(Node* begin, Node* end);

public:
    bool connected(Node* begin, Node* end);
};