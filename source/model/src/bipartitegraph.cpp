#include "bipartitegraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p) {
    // tire au hasard la taille d'une partie, entre 1 et n-1
    int cut = (rand()%(n-1)) +1;

    // ajoute les noeuds
    for (int  i = 0; i < n; ++i) {
       if ((i<cut && cut <= n/2) || (i>=cut && cut >= n/2)){
           leftPartition.push_back(addNode());
           partition.push_back(0);
       }
       else{
           rightPartition.push_back(addNode());
           partition.push_back(1);
       }
    }

    // ajoute des aretes entre les noeuds de parties différentes
    for (int i = 0; i < cut; i++) {
        for (int j = cut; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}

BipartiteGraph::BipartiteGraph(Graph * g) : Graph(g){
}

void BipartiteGraph::BFSforInitialisation(Node * root, Graph *dup){
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
            dup->removeNode(current->getId());
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

vector<Edge *> BipartiteGraph::DFSforAugmentingPathRec(Node * current, Node * previous, vector<Edge*> * matching, vector<bool> * visited, vector<bool> * marked) {

    if (!marked->at(current->getId()) && (partition[current->getId()] == 1)){

        return vector<Edge *>(/*getEdge(current->getId(),previous->getId())*/);
    }

    for (Node * v : current->getNeighbours()){
        if (!visited->at(v->getId())){
            visited->at(v->getId()) = true;
            DFSforAugmentingPathRec(v, current, matching, visited, marked);
        }
    }
}

vector<Edge *> BipartiteGraph::DFSforAugmentingPath(Node * root, vector<Edge*> * matching, vector<bool> * marked){
    vector<bool> visited(nbNodes(), false);
    return DFSforAugmentingPathRec(root, 0, matching, &visited, marked);

}


vector<Edge*> BipartiteGraph::getAugmentedMatching(vector<Edge*> * matching){
    vector<Edge*> result;

    return result;
}

vector<Edge*> BipartiteGraph::getMaximumMatching() {
    Edge * edge;
    vector<Edge*> matching;
    getAugmentedMatching(&matching);
    vector<Edge*> result;
    return result;
}


void BipartiteGraph::initialisePartitions(){
    if((rightPartition.size() != 0) || (nbNodes() == 0))
        return;
    Graph dup(this);

    Edge * edge;
    while((edge = dup.getRandomEdge()) != 0){
        BFSforInitialisation(edge->first(), &dup);
    }

    Node * node;
    while((node = dup.getRandomNode()) != 0){
        rightPartition.push_back(getNode(node->getId()));
        dup.removeNode(node);
    }

    partition = vector<int>(nbNodes(), 0);
    for(Node * n : leftPartition)
        partition[n->getId()] = 1;
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

vector<Node*> BipartiteGraph::getCover(){
    vector<Node*> result;
    return result;
}

string BipartiteGraph::getType() {
    return "bipartitegraph";
}
