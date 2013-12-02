#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"
#include <map>

using namespace std;

class Graph {

private:
  int counter;
  map<int, Node> graphNodes;

public:
  Graph();

  // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
  Graph(int n); 

  // Generates a graph with n vertices, labeled from 0 to n-1, propbality p (from 0 to 100) to have an edge between to vertices
  Graph(int n, int p);

  int addNode();

  //add an adge between node A and node B
  void addEdge(int a, int b);

  //return format :
  //nbNodes
  //nodeID : neighboursID
  //nodeID : neighboursID
  //...
  String toString();
};

#endif // GRAPH_H
