#ifndef BIPARTITEGRAPH_HPP
#define BIPARTITEGRAPH_HPP

#include "graph.hpp"
#include <queue>

class BipartiteGraph : public Graph {

private:
    //contient une couverture qui peut ne pas etre optimale
    vector<Node*> leftPartition;
    vector<Node*> rightPartition;
    void BFS(Node * root);
public:
    BipartiteGraph(int n, int p);
    vector<Node*>getSolution();
    vector<Node*>getLeftPartition();
    vector<Node*>getRightPartition();
    bool initialisePartitions();
};

#endif // BIPARTITEGRAPH_HPP
