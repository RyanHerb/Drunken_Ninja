#ifndef BIPARTITEGRAPH_HPP
#define BIPARTITEGRAPH_HPP

#include <queue>
#include "graph.hpp"

enum NodeColor {
    grey,
    white,
    black
};

class BipartiteGraph : public Graph {

private:
    //contient une couverture qui peut ne pas etre optimale
    vector<Node*> leftPartition;
    vector<Node*> rightPartition;
    //pour un acces à la partition d'un Node en O(1)
    vector<int> partition;
    map<Edge *, int> flux;
    void initialiseFlux();
    void BFSforInitialisation(Node * root, Graph * dup);
    bool FordFulkerson(vector<NodeColor> * colorVector);
    vector<Node *> succ(Node * n);
    vector<Node *> pred(Node * n);
    Node * s, * t;
    void setST(Node * s, Node * t);
public:
    BipartiteGraph(int n, int p);
    BipartiteGraph(IGraph * g);
    BipartiteGraph(int n);
    NodeColor color(Node * node);
    vector<Node*>getSolution();
    vector<Node*>getLeftPartition();
    vector<Node*>getRightPartition();
    void resetPartitions();
    void initialisePartitions();
    vector<Node*> getCover();
    string getType();
};

#endif // BIPARTITEGRAPH_HPP
