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

list<Node *> Tree::getCover(){
    Tree * copie(this);
    list<Node *> cover;
    list<Node *> leaves = copie->getLeaves();
    while(leaves.size() != 0){
        list<Node *>::const_iterator currentNode (leaves.begin()), lend(leaves.end());
        for(;currentNode!=lend;++currentNode){
            Node * currentLeaf = (*currentNode);
            Node * leafFather = currentLeaf->getNeighbor(0);
            if(leafFather){
                cover.push_back(leafFather);
                copie->removeAllEdges(leafFather->getId());
            }
        }
        leaves = copie->getLeaves();
    }
    return cover;
}
