#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

class Node {
    std::string name;
    // Соседи вершины и веса ребер до них.
    std::map<Node*, int> neighbours;

public:
    explicit Node(const std::string& aname);

    const std::string& getName() const;

    void addNeighbour(Node* neighbour, int weight);
    void removeNeighbour(Node* neighbour);

    using node_iterator = std::map<Node*, int>::const_iterator;

    node_iterator nb_begin() const;
    node_iterator nb_end() const;
};

class Graph {
    // Все вершины графа.
    std::set<Node*> nodes;
    // Вершины, созданные внутри графа при чтении из файла.
    std::vector<Node*> owned_nodes;

public:
    using node_iterator = std::set<Node*>::const_iterator;

    Graph() = default;
    explicit Graph(const char* file_name);
    ~Graph();

    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    void addNode(Node* node);
    void removeNode(Node* node);

    void addDirectedEdge(Node* begin, Node* end, int weight);
    void addEdge(Node* begin, Node* end, int weight);
    void removeEdge(Node* begin, Node* end);

    Node* findNode(const std::string& name) const;

    node_iterator begin() const;
    node_iterator end() const;
};