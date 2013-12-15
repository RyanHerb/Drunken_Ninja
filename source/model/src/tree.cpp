#include "tree.hpp"

// Generates a random tree with n vertices;
Tree::Tree(int n):Graph(1) {
    for(int i=0 ; i<n ; i++){
        addNode();
    }

    if (n > 2){
        int degrees[n];
        fill_n(degrees, n, 0);
        list<int> randomWord;

        for (int i=0 ; i<n-2 ; i++) {
            int node = rand()%n;
            randomWord.push_back(node);
            ++degrees[node];
        }

        list<int>leafs;
        for (int i=0 ; i<n ; i++) {
            if (degrees[i]==0) {
                leafs.push_back(i);
            }
        }
        while(!leafs.empty()){
            int father = randomWord.front();
            randomWord.pop_front();
            int son = leafs.front();
            leafs.pop_front();
            addEdge(father, son);

            if(--degrees[father] == 0){
                list<int>::iterator it = leafs.begin();
                while(it != leafs.end() && *it < father) {
                    ++it;
                }
                leafs.insert(it,father);
            }
        }
    }
    else if (n==2){
        addEdge(0,1);
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
