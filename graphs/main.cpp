#include <iostream>

#include "dijkstra.h"
#include "graph.h"

using namespace std;

void runBfsTask(const char* file_name);
void printWay(const Way& way);

// Создает небольшой взвешенный граф и проверяет алгоритм Дейкстры.
void runDijkstraExample() {
    Graph graph;

    Node n1("1");
    Node n2("2");
    Node n3("3");
    Node n4("4");
    Node n5("5");
    Node n6("6");
    Node n7("7");
    Node n8("8");
    Node n9("9");

    graph.addNode(&n1);
    graph.addNode(&n2);
    graph.addNode(&n3);
    graph.addNode(&n4);
    graph.addNode(&n5);
    graph.addNode(&n6);
    graph.addNode(&n7);
    graph.addNode(&n8);
    graph.addNode(&n9);

    graph.addDirectedEdge(&n1, &n2, 10);
    graph.addDirectedEdge(&n1, &n3, 6);
    graph.addDirectedEdge(&n1, &n4, 8);
    graph.addDirectedEdge(&n2, &n4, 5);
    graph.addDirectedEdge(&n2, &n7, 11);
    graph.addDirectedEdge(&n3, &n5, 3);
    graph.addDirectedEdge(&n4, &n3, 2);
    graph.addDirectedEdge(&n4, &n5, 5);
    graph.addDirectedEdge(&n4, &n6, 7);
    graph.addDirectedEdge(&n4, &n7, 12);
    graph.addDirectedEdge(&n5, &n6, 9);
    graph.addDirectedEdge(&n5, &n9, 12);
    graph.addDirectedEdge(&n6, &n8, 8);
    graph.addDirectedEdge(&n6, &n9, 10);
    graph.addDirectedEdge(&n7, &n6, 4);
    graph.addDirectedEdge(&n7, &n8, 6);
    graph.addDirectedEdge(&n8, &n9, 5);

    Dijkstra dijkstra;
    Way way = dijkstra.shortestWay(&n1, &n9);

    cout << "Проверка алгоритма Дейкстры" << endl;
    printWay(way);
}

int main() {
    const char* test_file = "testgraph.txt";
    const char* main_file = "1000.csv";

    runBfsTask(test_file);
    runBfsTask(main_file);

    cout << endl;
    runDijkstraExample();

    return 0;
}
