#ifndef TREE_H
#define TREE_H

#include "graph.hpp"
#include <iostream>

class Tree : public Graph {

private:
    Node *root;

public:
    Tree(int n); // Generates a random tree with n vertices, labeled from 0 to n-1;
    list<Node*> getLeaves();
    list<Node*> getCover();
};

#endif // TREE_H

