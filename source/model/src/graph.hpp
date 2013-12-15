#ifndef GRAPH_H
#define GRAPH_H

#include "edge.hpp"
#include "node.hpp"
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {

protected:
    int counter;
    map<int, Node*> nodes;
    unordered_map<int, Edge*> edges;

public:
    Graph();
    Graph(Graph*g);
    // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
    Graph(int n);

    // Generates a graph with n vertices, labeled from 0 to n-1,
    // with a propbality p for having an edge between two vertices
    Graph(int n, int p);

    ~Graph();

    Node* addNode();
    Node* addNode(int id);
    Node* getNode(int id);
    void removeNode(Node *n);
    void removeNode(int id);

    // Adds an edge between node A and node B
    void addEdge(int a, int b);

    // Returns true if an edge exists between node A and node B
    bool hasEdge(int a, int b);

    // Removes the edge between node A and node B
    void removeEdge(int a, int b);

    // Removes all the edges of the node A
    void removeEdges(int a);

    // Returns the a const list of Graph's Nodes;
    vector<Node*> getNodes() const;

    Node* getRandomNode();
    Edge* getRandomEdge();
    vector<Node*> getCoverGlouton();

    vector<Edge*> getEdges() const;
    // Default cover
    vector<Node*> getCover();
    vector<Node*> getKCover(int K);
    int nbEdges();
    int nbNodes();

    int Kernelisation(int K, vector<int> * cover);
    Node* getHighestDegreeNode();
};

// To print a Graph
inline ostream& operator<<(ostream &os, const Graph &graph) {
    for (Node *node : graph.getNodes()) {
        os << *node << endl;
    }
    return os;
}

#endif // GRAPH_H
