#ifndef IGRAPH_HPP
#define IGRAPH_HPP

#include "graph.hpp"
#include "node.hpp"
#include "edge.hpp"

class Tree;
class IGraph {

public:
    virtual Node* addNode() = 0;
    virtual Node* addNode(int id) = 0;
    virtual Node* getNode(int id) = 0;
    virtual void removeNode(Node *n) = 0;
    virtual void removeNode(int id) = 0;

    // Adds an edge between node A and node B
    virtual void addEdge(int a, int b) = 0;

    // Returns true if an edge exists between node A and node B
    virtual bool hasEdge(int a, int b) = 0;

    // Removes the edge between node A and node B
    virtual void removeEdge(int a, int b) = 0;

    // Removes all the edges of the node A
    virtual void removeEdges(int a) = 0;

    // Returns the a const list of Graph's Nodes;
    virtual vector<Node*> getNodes() const = 0;

    virtual Node* getRandomNode() = 0;
    virtual Edge* getRandomEdge() = 0;
    virtual Edge* getEdge(int a, int b) = 0;
    virtual vector<Node*> getCoverGlouton() = 0;

    virtual vector<Edge*> getEdges() const = 0;
    // Default cover
    virtual vector<Node*> getCover() = 0;
    virtual vector<Node*> getCoverDFS() = 0;
    virtual Tree* DepthFirstSearch() = 0;
    virtual int nbEdges() = 0;
    virtual int nbNodes() = 0;

    virtual int kernelize(int K, vector<int> * cover) = 0;
    virtual Node* getHighestDegreeNode() = 0;

    //virtual void coverToMinisat(string) = 0;
    virtual vector<Node*> minisatToCover(string) = 0;
    virtual string getType() = 0;

    // FIXME Ne marche pas avec un graphe dont on a supprimé des sommets
    virtual IGraph* edgeComplementGraph() = 0;
    // Moins rapide mais marche quel que soit le graphe
    virtual IGraph* edgeComplementGraph2() = 0;
    //virtual vector<int> getIndependentSet(int size) = 0;
    //virtual vector<int> getClique(int size) = 0;
};

// To print a Graph
inline ostream& operator<<(ostream &os, const IGraph &graph) {
    for (Node *node : graph.getNodes()) {
        os << *node << endl;
    }
    return os;
}

#endif // IGRAPH_HPP

