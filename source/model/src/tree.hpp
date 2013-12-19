#ifndef TREE_H
#define TREE_H

#include "graph.hpp"
#include <iostream>
#include <vector>

class Tree : public Graph {

public:
    Tree();
    Tree(int n); // Generates a random tree with n vertices, labeled from 0 to n-1;
    Tree(IGraph *g);
    vector<Node*> getCover();
    vector<Node*> getLeaves();
    string getType();
};

#endif // TREE_H

