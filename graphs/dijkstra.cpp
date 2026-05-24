#include "dijkstra.h"

#include <algorithm>

class PriorityQueue {
    std::vector<MarkedNode> nodes;

public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);

    bool empty() const;
};

MarkedNode::MarkedNode(Node* anode, int amark, Node* aprev)
    : node(anode), mark(amark), prev(aprev) {}

MarkedNode PriorityQueue::pop() {
    // В конце вектора лежит вершина с минимальной текущей меткой.
    MarkedNode mn = nodes.back();
    nodes.pop_back();
    return mn;
}

void PriorityQueue::push(Node* node, int mark, Node* prev) {
    auto it = nodes.begin();
    MarkedNode mn(node, mark, prev);

    // Храним вершины так, чтобы pop() доставал минимальную метку.
    while (it != nodes.end() && mark < it->mark) {
        ++it;
    }

    if (it == nodes.end()) {
        nodes.push_back(mn);
    } else {
        nodes.insert(it, mn);
    }
}

bool PriorityQueue::empty() const {
    return nodes.empty();
}

Way Dijkstra::shortestWay(Node* begin, Node* end) {
    if (begin == nullptr || end == nullptr) {
        return Way();
    }

    PriorityQueue nodes;
    nodes.push(begin, 0, nullptr);

    std::map<Node*, MarkedNode> visited;

    while (!nodes.empty()) {
        MarkedNode current = nodes.pop();

        // Если вершина уже обработана, ее кратчайшее расстояние известно.
        if (visited.find(current.node) != visited.end()) {
            continue;
        }

        visited[current.node] = current;

        if (current.node == end) {
            return buildWay(visited, begin, end);
        }

        for (auto it = current.node->nb_begin();
             it != current.node->nb_end(); ++it) {
            Node* neighbour = it->first;
            int weight = it->second;

            // Алгоритм Дейкстры работает только с неотрицательными весами.
            if (weight < 0) {
                return Way();
            }

            // Добавляем новый возможный путь до соседней вершины.
            int new_distance = current.mark + weight;

            if (visited.find(neighbour) == visited.end()) {
                nodes.push(neighbour, new_distance, current.node);
            }
        }
    }

    return Way();
}

Way Dijkstra::buildWay(const std::map<Node*, MarkedNode>& visited, Node* begin, Node* current) {
    Way way;
    way.length = visited.at(current).mark;

    // Восстанавливаем путь от конца к началу по ссылкам prev.
    while (current != nullptr) {
        way.nodes.push_back(current);

        if (current == begin) {
            break;
        }

        current = visited.at(current).prev;
    }

    std::reverse(way.nodes.begin(), way.nodes.end());
    return way;
}