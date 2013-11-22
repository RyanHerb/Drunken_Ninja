#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"
#include <map>

using namespace std;

class Graph {

private:
    int counter;
    map<int, Node *> graphNodes;

public:
  Graph();

  // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
  Graph(int n); 

  // Generates a graph with n vertices, labeled from 0 to n-1, propbality p (from 0 to 100) to have an edge between to vertices
  Graph(int n, int p);

  int addNode();

  //add an edge between node A and node B
  void addEdge(int a, int b);

  //remove the edge between node A and node B
  void removeEdge(int a, int b);

  //remove all the edge of the node A
  void removeAllEdges(int a);

  //return the a const list of Graph's Nodes;
  list<Node *> getNodes() const;
};

//To print a Graph
inline ostream& operator<<(ostream& os, const Graph & graph)
{
    list<Node *> nodes = graph.getNodes();
    list<Node *>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for(;currentNode!=lend;++currentNode)os << *(*currentNode) << endl;
    return os;
}

#endif // GRAPH_H
