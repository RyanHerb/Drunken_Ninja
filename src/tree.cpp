#include "tree.hpp"

// Generates a random tree with n vertices;
Tree::Tree(int n):Graph(1){
    for (int i=1 ; i<n ; i++){
        addNode(i);
        addEdge(i, rand()%i);
    }
}
