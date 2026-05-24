#pragma once

#include "bfs.h"
#include "graph.h"

#include <set>
#include <string>

class DisconnectedGraphs {
    Graph graph;
    BFS bfs;

    static void writeComponent(const std::set<Node*>& component, int component_number, const std::string& file_prefix);

public:
    explicit DisconnectedGraphs(const char* file_name);

    int writeToFiles(const std::string& file_prefix);
};