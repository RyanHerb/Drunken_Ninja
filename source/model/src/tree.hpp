#ifndef TREE_H
#define TREE_H

#include "graph.hpp"
#include <iostream>
#include <vector>

class Tree : public Graph {

private:
    Node *root;

public:
    Tree(int n); // Generates a random tree with n vertices, labeled from 0 to n-1;
    Tree(Graph *g);
    Tree(Tree * t);
    vector<Node*> getLeaves();
    vector<Node*> getCover();
    string getType();
};

#endif // TREE_H

