#include "dfs.h"

bool DFS::connected(Node* begin, Node* end) {
    visited.clear();
    return connectedRecursive(begin, end);
}

bool DFS::connectedRecursive(Node* begin, Node* end) {
    if (begin == nullptr || end == nullptr) {
        return false;
    }

    if (begin == end) {
        return true;
    }

    visited.insert(begin);

    for (auto it = begin->nb_begin(); it != begin->nb_end(); ++it) {
        Node* neighbour = it->first;

        if (visited.find(neighbour) == visited.end() &&
            connectedRecursive(neighbour, end)) {
            return true;
        }
    }

    return false;
}