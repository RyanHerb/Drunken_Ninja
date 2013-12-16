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

    vector<Node*> getCoverGlouton();
    vector<Edge*> getEdges() const;
    vector<Node*> getCover();
    vector<Node*> getKCover(int K);
    int nbEdges();
    int nbNodes();

    int kernelize(int K, vector<int> * cover);
    Node* getHighestDegreeNode();

    // FIXME Ne marche pas avec un graphe dont on a supprimé des sommets
    IGraph* edgeComplementGraph();
    // Moins rapide mais marche quel que soit le graphe
    IGraph* edgeComplementGraph2();

    //void coverToMinisat(string);
    vector<Node*> minisatToCover(string);
    string getType();
    vector<Node*> getCoverDFS();
    Tree* DepthFirstSearch();
    vector<Node*> getKCoverWithMinisat(int);
    vector<int> getClique(int);
    vector<int> getIsomorphicSubgraph(Graph);
};

#endif // GRAPH_H
