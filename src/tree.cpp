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

Tree::Tree(Tree * t):Graph(t) {

}

vector<Node*> Tree::getLeaves() {
    vector<Node*> leaves;
    for (Node *node : getNodes()) {
        if (node->degree() == 1 && (node != root))
            leaves.push_back(node);
    }
    return leaves;
}

vector<Node*> Tree::getCover() {

    Tree dup(this);
    vector<Node*> cover;
    vector<Node*> leaves = dup.getLeaves();
    while (leaves.size() != 0) {
        for (Node *leaf : leaves) {
            Node *leafParent = leaf->getNeighbour(0);
            if (leafParent) {
                cover.push_back(leafParent);
                dup.removeEdges(leafParent->getId());
            }
        }
        leaves = dup.getLeaves();
    }
    return cover;
}
