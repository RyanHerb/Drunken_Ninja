#include "tree.hpp"

// Generates a random tree with n vertices;
Tree::Tree(int n):Graph(1) {
    root = (*getNodes().begin());
    for (int i = 1; i < n; i++) {
        addNode();
        int neighboor = rand()%i;
        addEdge(i, neighboor);
    }
}

list<Node*> Tree::getLeaves() {
    list<Node*> leaves;
    list<Node*> nodes = getNodes();
    list<Node*>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for (; currentNode != lend; ++currentNode) {
        if ((*currentNode)->degree() == 1 && ((*currentNode) != root))
            leaves.push_back((*currentNode));
    }
    return leaves;
}

list<Node*> Tree::getCover() {
    Tree *dup(this);
    list<Node*> cover;
    list<Node*> leaves = dup->getLeaves();
    while (leaves.size() != 0) {
        list<Node*>::const_iterator currentNode (leaves.begin()), lend(leaves.end());
        for (; currentNode != lend; ++currentNode) {
            Node *currentLeaf = (*currentNode);
            Node *leafParent = currentLeaf->getNeighbor(0);
            if (leafParent) {
                cover.push_back(leafParent);
                dup->removeEdges(leafParent->getId());
            }
        }
        leaves = dup->getLeaves();
    }
    return cover;
}
