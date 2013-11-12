#ifndef TREE_H
#define TREE_H

#include "graph.hpp"

class Tree : public Graph {

public:
    Tree(int n); // Generates a random tree with n vertices, labeled from 0 to n-1;
};


#endif // TREE_H

