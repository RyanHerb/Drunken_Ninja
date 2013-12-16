#include "tree.hpp"

Tree::Tree(){}

Tree::Tree(IGraph *g): Graph(g){}

// Generates a random tree with n vertices
Tree::Tree(int n):Graph(1) {
    for(int i=1 ; i<n ; i++){
        addNode();
    }

    if (n > 2){
        vector<int> degrees(n,0);
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
        while(!randomWord.empty()){
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
        if(leafs.size() == 2){
            int father = leafs.front();
            leafs.pop_front();
            int son = leafs.front();
            addEdge(father, son);
        }
    }
    else if (n==2){
        addEdge(0,1);
    }
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
    vector<int> cover;
    vector<Node*> leaves = dup.getLeaves();
    while (leaves.size() != 0) {
        for (Node *leaf : leaves) {
            Node *leafParent = leaf->getNeighbour(0);
            if (leafParent) {
                cover.push_back(leafParent->getId());
                dup.removeEdges(leafParent->getId());
            }
        }
        leaves = dup.getLeaves();
    }
    vector<Node*> result;
    for (int id : cover) {
        result.push_back(this->getNode(id));
    }
    return result;
}

string Tree::getType() {
    return "tree";
}
