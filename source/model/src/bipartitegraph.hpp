#ifndef BIPARTITEGRAPH_HPP
#define BIPARTITEGRAPH_HPP

#include "graph.hpp"
#include <queue>

class BipartiteGraph : public Graph {

private:
    //contient une couverture qui peut ne pas etre optimale
    vector<Node*> leftPartition;
    vector<Node*> rightPartition;
    //pour un acces à la partition d'un Node en O(1)
    vector<int> partition;

    void BFSforInitialisation(Node * root, Graph * dup);
    vector<Edge *> DFSforAugmentingPathRec(Node * current, Node * previous, vector<Edge*> * matching, vector<bool> * visited, vector<bool> * marked);
    vector<Edge *> getAugmentedMatching(vector<Edge *> *matching, vector<Edge *> *path);

public:
    BipartiteGraph(int n, int p);
    BipartiteGraph(IGraph * g);
    vector<Node*>getSolution();
    vector<Node*>getLeftPartition();
    vector<Node*>getRightPartition();
    void initialisePartitions();
    vector<Edge *> getMaximumMatching();
    vector<Node*> getCover();
    string getType();
};

#endif // BIPARTITEGRAPH_HPP
