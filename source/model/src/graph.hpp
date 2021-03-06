#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include "igraph.hpp"
#include "edge.hpp"
#include "node.hpp"

#include "../app/config.h" //contains useful variables

using namespace std;

class Graph : public IGraph {

protected:
    int counter;
    map<int, Node*> nodes;
    unordered_map<int, Edge*> edges;

public:
    Graph();
    Graph(IGraph *g);
    // Generates a graph with n vertices, labeled from 0 to n-1, but no edges;
    Graph(int n);

    // Generates a graph with n vertices, labeled from 0 to n-1,
    // with a propbality p for having an edge between two vertices
    Graph(int n, int p);
    vector<int> shuffle();
    ~Graph();

    Node* addNode();
    Node* addNode(int id);
    Node* getNode(int id);
    void removeNode(Node *n);
    void removeNode(int id);
    void addEdge(int a, int b);
    bool hasEdge(int a, int b);
    void removeEdge(int a, int b);
    void removeEdges(int a);
    vector<Node*> getNodes() const;
    Node* getRandomNode();
    Edge* getRandomEdge();
    Edge* getEdge(int a, int b);
    vector<Node*> getCoverGreedy();
    vector<Edge*> getEdges() const;
    vector<Node*> getCover();
    int nbEdges();
    int nbNodes();

    int kernelize(int k, vector<int> *cover);
    Node* getHighestDegreeNode();

    // Does not work on graphs from which a node was removed
    Graph* edgeComplementGraph();
    // Less efficient but works on any type of graph
    Graph* edgeComplementGraph2();

    void coverToMinisat(string);
    vector<Node*> minisatToCover(string);
    string getType();

    vector<int> getIndependentSet(int);
    vector<Node*> getCoverDFS();
    Tree* depthFirstSearch();
    vector<Node*> getKCoverWithMinisat(int);
    vector<int> getClique(int);
    vector<int> getIsomorphicSubgraph(Graph*);
    void discardIsolatedNodes();
};

vector<int> getSatCover(unordered_map<int, int>, unordered_map<int, int>);

#endif // GRAPH_H
