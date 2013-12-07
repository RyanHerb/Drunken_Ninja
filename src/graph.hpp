#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"
#include <map>

using namespace std;

class Graph {

private:
    int counter;
    int nbEdge;
    map<int, Node*> graphNodes;

public:
    Graph();

    // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
    Graph(int n);

    // Generates a graph with n vertices, labeled from 0 to n-1,
    // with a propbality p for having an edge between two vertices
    Graph(int n, int p);

    Node* addNode();

    void removeNode(Node *n);

    // Adds an edge between node A and node B
    void addEdge(int a, int b);

    // Returns true if an edge exists between node A and node B
    bool hasEdge(int a, int b);

    // Removes the edge between node A and node B
    void removeEdge(int a, int b);

    // Removes all the edges of the node A
    void removeAllEdges(int a);

    // Returns the a const list of Graph's Nodes;
    list<Node*> getNodes() const;

    // Default cover
    list<Node*> getCover();

    Node* getRandomNode();
    pair<Node*,Node*> *getRandomEdge();
    list<Node*> getCoverGlouton();
    Node* getHigherDegreeNode();
};

// To print a Graph
inline ostream& operator<<(ostream &os, const Graph &graph) {
    list<Node*> nodes = graph.getNodes();
    list<Node*>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for (; currentNode != lend; ++currentNode) {
        os << *(*currentNode) << endl;
    }
    return os;
}

#endif // GRAPH_H
