#pragma once

#include "graph.h"

#include <map>
#include <vector>

struct MarkedNode {
    Node* node;
    int mark;
    Node* prev;

    MarkedNode(Node* anode = nullptr, int amark = 0, Node* aprev = nullptr);
};

struct Way {
    std::vector<Node*> nodes;
    int length = -1;
};

class Dijkstra {
public:
    Way shortestWay(Node* begin, Node* end);

private:
    static Way buildWay(const std::map<Node*, MarkedNode>& visited, Node* begin, Node* current);
};