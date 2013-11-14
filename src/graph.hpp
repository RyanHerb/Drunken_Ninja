#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"


class Graph {

private:
  int counter = 0;
  std::map<int, Node> graphNodes;

public:
  Graph();

  // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
  Graph(int n); 

  // Generates a graph with n vertices, labeled from 0 to n-1, propbality p (from 0 to 100) to have an edge between to vertices
  Graph(int n, int p);

  void addNode();

  //add an adge between node A and node B
  void addEdge(int a, int b);
};

#endif // GRAPH_H
