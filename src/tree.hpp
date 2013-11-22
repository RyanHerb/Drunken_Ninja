#ifndef TREE_H
#define TREE_H

#include "graph.hpp"
#include <iostream>

class Tree : public Graph {

public:
    Tree(int n); // Generates a random tree with n vertices, labeled from 0 to n-1;
};

/*ostream& operator<<(ostream& os, const Tree & tree)
{
    return os;
}
*/

#endif // TREE_H

