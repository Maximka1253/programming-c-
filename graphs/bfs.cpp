#include "bfs.h"

#include <queue>
#include <set>

bool BFS::connected(Node* begin, Node* end) {
    if (begin == nullptr || end == nullptr) {
        return false;
    }

    // Очередь хранит вершины, которые еще нужно обработать.
    std::queue<Node*> to_visit;
    std::set<Node*> visited;

    to_visit.push(begin);
    visited.insert(begin);

    while (!to_visit.empty()) {
        Node* current = to_visit.front();
        to_visit.pop();

        if (current == end) {
            return true;
        }

        for (auto it = current->nb_begin(); it != current->nb_end(); ++it) {
            Node* neighbour = it->first;

            // insert возвращает true, если вершина еще не была посещена.
            if (visited.insert(neighbour).second) {
                to_visit.push(neighbour);
            }
        }
    }

    return false;
}

std::set<Node*> BFS::component(Node* begin) {
    std::set<Node*> visited;

    if (begin == nullptr) {
        return visited;
    }

    std::queue<Node*> to_visit;

    to_visit.push(begin);
    visited.insert(begin);

    while (!to_visit.empty()) {
        Node* current = to_visit.front();
        to_visit.pop();

        for (auto it = current->nb_begin(); it != current->nb_end(); ++it) {
            Node* neighbour = it->first;

            // Все достижимые вершины попадут в одну компоненту связности.
            if (visited.insert(neighbour).second) {
                to_visit.push(neighbour);
            }
        }
    }

    return visited;
}