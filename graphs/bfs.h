#pragma once

#include "graph.h"

#include <set>

class BFS {
public:
    bool connected(Node* begin, Node* end);
    std::set<Node*> component(Node* begin);
};