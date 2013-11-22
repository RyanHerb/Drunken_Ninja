#include "tree.hpp"

// Generates a random tree with n vertices;
Tree::Tree(int n):Graph(1){
    root = (*getNodes().begin());
    for (int i=1 ; i<n ; i++){
        addNode();
        addEdge(i, rand()%i);
    }
}

list<Node *> Tree::getLeaves(){
    list<Node *> leaves;
    list<Node *> nodes = getNodes();
    list<Node *>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for(;currentNode!=lend;++currentNode){
        if((*currentNode)->degre() == 1 && ((*currentNode) != root))
            leaves.push_back((*currentNode));
    }
    return leaves;
}
