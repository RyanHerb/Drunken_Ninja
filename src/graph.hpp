#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"


class Graph {

private:
    std::list<Node> graphNodes;

public:
    Graph();
    Graph(int n); // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
    Graph(int n, int p);// Generates a graph with n vertices, labeled from 0 to n-1, propbality p (from 0 to 100) to have an edge between to vertices
    void addNode(int label);
    void addEdge(int a, int b);//add an adge between node A and node B
};

#endif // GRAPH_H
