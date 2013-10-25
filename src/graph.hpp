#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"


class Graph {

private:
    std::list<Node> graphNodes;

public:
    Graph();
    Graph(int n); // Generates a graph with n vertices, but no edges;

    void addNode(int n); // add n vertices to the graph
    void addNode(); // add 1 vertex to the graph

};

#endif // GRAPH_H
