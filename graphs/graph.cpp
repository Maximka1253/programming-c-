#include "graph.h"

#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

Node::Node(const string& aname) : name(aname) {}

const string& Node::getName() const {
    return name;
}

void Node::addNeighbour(Node* neighbour, int weight) {
    neighbours[neighbour] = weight;
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

Node::node_iterator Node::nb_begin() const {
    return neighbours.begin();
}

Node::node_iterator Node::nb_end() const {
    return neighbours.end();
}

Graph::Graph(const char* file_name) {
    ifstream input(file_name);

    if (!input.is_open()) {
        return;
    }

    string source_header;
    string target_header;

    if (!(input >> source_header >> target_header)) {
        return;
    }

    map<string, Node*> nodes_by_name;
    string source;
    string target;

    // Каждое имя вершины должно соответствовать одному объекту Node.
    while (input >> source >> target) {
        if (nodes_by_name.find(source) == nodes_by_name.end()) {
            Node* node = new Node(source);
            nodes_by_name[source] = node;
            owned_nodes.push_back(node);
            addNode(node);
        }

        if (nodes_by_name.find(target) == nodes_by_name.end()) {
            Node* node = new Node(target);
            nodes_by_name[target] = node;
            owned_nodes.push_back(node);
            addNode(node);
        }

        // В файле указаны смежные вершины, поэтому добавляем неориентированное ребро.
        addEdge(nodes_by_name[source], nodes_by_name[target], 1);
    }
}

Graph::~Graph() {
    for (Node* node : owned_nodes) {
        delete node;
    }

    owned_nodes.clear();
    nodes.clear();
}

void Graph::addNode(Node* node) {
    if (node == nullptr) {
        return;
    }

    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    if (node == nullptr) {
        return;
    }

    nodes.erase(node);

    // Удаляем все ребра, которые вели к этой вершине.
    for (Node* current : nodes) {
        current->removeNeighbour(node);
    }

    auto owned_it = find(owned_nodes.begin(), owned_nodes.end(), node);
    if (owned_it != owned_nodes.end()) {
        owned_nodes.erase(owned_it);
        delete node;
    }
}

void Graph::addDirectedEdge(Node* begin, Node* end, int weight) {
    if (begin == nullptr || end == nullptr) {
        return;
    }

    if (nodes.find(begin) == nodes.end()) {
        return;
    }

    if (nodes.find(end) == nodes.end()) {
        return;
    }

    begin->addNeighbour(end, weight);
}

void Graph::addEdge(Node* begin, Node* end, int weight) {
    if (begin == nullptr || end == nullptr) {
        return;
    }

    if (nodes.find(begin) == nodes.end()) {
        return;
    }

    if (nodes.find(end) == nodes.end()) {
        return;
    }

    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (begin == nullptr || end == nullptr) {
        return;
    }

    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

Node* Graph::findNode(const string& name) const {
    for (Node* node : nodes) {
        if (node->getName() == name) {
            return node;
        }
    }

    return nullptr;
}

Graph::node_iterator Graph::begin() const {
    return nodes.begin();
}

Graph::node_iterator Graph::end() const {
    return nodes.end();
}