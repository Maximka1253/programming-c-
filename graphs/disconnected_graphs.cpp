#include "disconnected_graphs.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <set>
#include <string>
#include <utility>

using namespace std;

namespace {

bool isNumber(const string& text) {
    if (text.empty()) {
        return false;
    }

    for (char symbol : text) {
        if (!isdigit(static_cast<unsigned char>(symbol))) {
            return false;
        }
    }

    return true;
}

bool nameLess(const string& left, const string& right) {
    bool left_is_number = isNumber(left);
    bool right_is_number = isNumber(right);

    // Числовые имена сортируем как числа: 2 должно идти раньше 10.
    if (left_is_number && right_is_number && left.size() != right.size()) {
        return left.size() < right.size();
    }

    return left < right;
}
// Сравнивает ребра по именам вершин, не учитывая направление.
struct EdgeCompare {
    bool operator()(const pair<string, string>& left, const pair<string, string>& right) const {
        if (left.first != right.first) {
            return nameLess(left.first, right.first);
        }

        return nameLess(left.second, right.second);
    }
};

}

DisconnectedGraphs::DisconnectedGraphs(const char* file_name) : graph(file_name) {}
// Записывает одну компоненту связности в файл. Нумерация компонентов начинается с 1.
void DisconnectedGraphs::writeComponent(const set<Node*>& component, int component_number, const string& file_prefix) {
    set<pair<string, string>, EdgeCompare> edges;

    for (Node* node : component) {
        for (auto it = node->nb_begin(); it != node->nb_end(); ++it) {
            Node* neighbour = it->first;

            if (component.find(neighbour) == component.end()) {
                continue;
            }

            string begin = node->getName();
            string end = neighbour->getName();

            // Для неориентированного графа ребро A-B и B-A одно и то же.
            if (nameLess(end, begin)) { 
                swap(begin, end);
            }

            edges.insert(make_pair(begin, end));
        }
    }

    string file_name = file_prefix + "_part_" + to_string(component_number) + ".txt";
    ofstream output(file_name);

    output << "Source Target\n";

    for (const auto& edge : edges) {
        output << edge.first << ' ' << edge.second << '\n';
    }
}
// Выделение компонентов связности и записывание их в файлы.
int DisconnectedGraphs::writeToFiles(const string& file_prefix) {
    set<Node*> visited;
    int component_number = 1;

    // Запуск BFS из каждой еще не посещенной вершины.
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        Node* node = *it;

        if (visited.find(node) != visited.end()) {
            continue;
        }

        set<Node*> component = bfs.component(node);

        for (Node* component_node : component) {
            visited.insert(component_node);
        }

        writeComponent(component, component_number, file_prefix);
        ++component_number;
    }

    return component_number - 1;
}