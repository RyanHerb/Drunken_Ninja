#include "bipartitegraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p) {
    // tire au hasard la taille d'une partie, entre 1 et n-1
    int cut = (rand()%(n-1)) +1;

    // ajoute les noeuds
    for (int  i = 0; i < n; ++i) {
       if ((i<cut && cut <= n/2) || (i>=cut && cut >= n/2))
           leftPartition.push_back(addNode());
       else
           rightPartition.push_back(addNode());
    }

    // ajoute des aretes entre les noeuds de parties différentes
    for (int i = 0; i < cut; i++) {
        for (int j = cut; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}

void BipartiteGraph::BFS(Node * root){
    queue<Node*> calls[2];
    vector<Node*> tmpPartitions[2];
    vector<bool> visited(nbNodes(), false);

    int i = 0;
    calls[i].push(root);
    while (!calls[i].empty()){
        while (!calls[i].empty()){
            Node * current = calls[i].front();
            calls[i].pop();
            tmpPartitions[i].push_back(current);
            for (Node * v : current->getNeighbours()){
                if (!visited[v->getId()]){
                    calls[1-i].push(v);
                    visited[v->getId()] = true;
                }
            }
        }
        i = 1 - i;
    }

    if (tmpPartitions[i].size() > tmpPartitions[1-i].size())
        i = 1 - i;
    for (Node * n : tmpPartitions[i])
        leftPartition.push_back(n);
    i = 1 - i;
    for (Node * n : tmpPartitions[i])
        rightPartition.push_back(n);
    return;
}



bool BipartiteGraph::initialisePartitions(){
    if((rightPartition.size() != 0) || (nbNodes() == 0))
        return true;
    Graph dup(this);

    Edge * edge;
    while((edge = dup.getRandomEdge()) != 0){
        BFS(edge->first());
    }

    Node * node;
    while((node = dup.getRandomNode()) != 0){
        rightPartition.push_back(getNode(node->getId()));
        dup.removeNode(node);
    }
    return true;
}

vector<Node*> BipartiteGraph::getSolution() {
    initialisePartitions();
    return leftPartition;
}

vector<Node*> BipartiteGraph::getLeftPartition() {
    initialisePartitions();
    return leftPartition;
}

vector<Node*> BipartiteGraph::getRightPartition() {
    initialisePartitions();
    return rightPartition;
}
