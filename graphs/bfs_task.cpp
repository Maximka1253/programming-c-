#include "bfs.h"
#include "disconnected_graphs.h"
#include "dijkstra.h"
#include "graph.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Выводит найденный кратчайший путь.
void printWay(const Way& way) {
    if (way.length == -1) {
        cout << "Путь не найден" << endl;
        return;
    }

    cout << "Кратчайший путь: ";

    for (size_t i = 0; i < way.nodes.size(); ++i) {
        cout << way.nodes[i]->getName();

        if (i + 1 < way.nodes.size()) {
            cout << " -> ";
        }
    }

    cout << endl;
    cout << "Длина пути: " << way.length << endl;
}

// Проверяет связность двух вершин через BFS и записывает результат.
void writeBfsCheck(const Graph& graph, BFS& bfs, const string& source, const string& target, ostream& output) {
    Node* begin = graph.findNode(source);
    Node* end = graph.findNode(target);

    if (begin == nullptr || end == nullptr) {
        output << source << ' ' << target << " NO" << endl;
        return;
    }

    output << source << ' ' << target << ' ';
    output << (bfs.connected(begin, end) ? "YES" : "NO") << endl;
}

string fileBaseName(const char* file_name) {
    string base_name(file_name);
    size_t slash_pos = base_name.find_last_of("/\\");

    if (slash_pos != string::npos) {
        base_name = base_name.substr(slash_pos + 1);
    }

    size_t dot_pos = base_name.find_last_of('.');

    if (dot_pos != string::npos) {
        base_name = base_name.substr(0, dot_pos);
    }

    return base_name;
}

string componentPrefix(const char* file_name) {
    return fileBaseName(file_name) + "_component";
}

void runBfsTask(const char* file_name) {
    Graph graph(file_name);
    BFS bfs;
    ofstream bfs_output(fileBaseName(file_name) + "_bfs_result.txt");

    bfs_output << "Source Target Connected" << endl;
    writeBfsCheck(graph, bfs, "0", "48", bfs_output);
    writeBfsCheck(graph, bfs, "0", "29", bfs_output);

    DisconnectedGraphs components(file_name);
    int component_count = components.writeToFiles(componentPrefix(file_name));

    cout << "Компоненты в " << file_name << ": " << component_count << endl;
}
