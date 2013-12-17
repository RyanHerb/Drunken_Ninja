#include "bipartitegraph.hpp"

BipartiteGraph::BipartiteGraph(IGraph * g) : Graph(g){
    initialisePartitions();
}

BipartiteGraph::BipartiteGraph(int n, int p) {
    // tire au hasard la taille d'une partie, entre 1 et n-1
    int cut = (rand()%(n-1)) +1;

    // ajoute les noeuds
    for (int  i = 0; i < n; ++i) {
       if ((i<cut && cut <= n/2) || (i>=cut && cut >= n/2)){
           leftPartition.push_back(addNode());
           partition.push_back(1);
       }
       else{
           rightPartition.push_back(addNode());
           partition.push_back(0);
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

void BipartiteGraph::BFSforInitialisation(Node * root, Graph *dup){
    queue<Node*> calls[2];
    vector<Node*> tmpPartitions[2];
    vector<bool> visited(nbNodes(), false);

    int i = 0;
    calls[i].push(root);
    while (!calls[i].empty()){
        while (!calls[i].empty()){
            Node *current = calls[i].front();
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
    for (Node *n : tmpPartitions[i])
        leftPartition.push_back(getNode(n->getId()));
    i = 1 - i;
    for (Node  *n : tmpPartitions[i])
        rightPartition.push_back(getNode(n->getId()));
    return;
}

void BipartiteGraph::initialisePartitions(){
    if((rightPartition.size() != 0) || (nbNodes() == 0))
        return;
    Graph dup(this);

    Edge *edge;
    while((edge = dup.getRandomEdge()) != 0){
        BFSforInitialisation(edge->first(), &dup);
    }

    Node *node;
    while((node = dup.getRandomNode()) != 0){
        rightPartition.push_back(getNode(node->getId()));
        dup.removeNode(node);
    }

    partition = vector<int>(nbNodes(), 0);
    for(Node * n : leftPartition)
        partition[n->getId()] = 1;
}

vector<Edge *> BipartiteGraph::DFSforAugmentingPathRec(Node * current, Node * previous, vector<Edge*> * matching, vector<int> * visited, vector<int> * marked) {

    if ((marked->at(current->getId()) == 0) && (partition[current->getId()] == 0)){

        return vector<Edge *>(1,getEdge(current->getId(),previous->getId()));
    }

    for (Node * v : current->getNeighbours()){
        if (visited->at(v->getId()) == 0){
            visited->at(v->getId()) = 1;

            vector<Edge *> resultat = DFSforAugmentingPathRec(v, current, matching, visited, marked);
            if (resultat.size() != 0) {
                if(previous != 0)
                    resultat.push_back(getEdge(current->getId(),previous->getId()));
                return resultat;
            }
        }
    }
    return vector<Edge *>();
}
vector<Edge *> BipartiteGraph::getAugmentedMatching(vector<Edge *> *matching, vector<Edge *> *path, vector<int> * marked) {
    //TODO baisser la complexyté de cette fonction
    vector<Edge *> result;
    *marked = vector<int>(nbNodes(), 0);
    int i = 0;
    for(Edge * edge : *path) {
        if((i%2) == 0) {
            result.push_back(edge);
            marked->at(edge->first()->getId()) = 1;
            marked->at(edge->second()->getId()) = 1;
        }
        ++i;
    }
    for(Edge * edge : *matching) {
        //TODO surtout ici
        bool valideEdge = true;
        for(Edge * pedge : *path) {
            if (edge == pedge)
                valideEdge = false;
        }
        if (valideEdge){
            result.push_back(edge);
            marked->at(edge->first()->getId()) = 1;
            marked->at(edge->second()->getId()) = 1;
        }
    }
    return result;
}

vector<Edge*> BipartiteGraph::getMaximumMatching() {
    vector<Edge*> matching;
    vector<int> visited(nbNodes(), 0);
    vector<int> marked(nbNodes(), 0);
    vector<Edge *> path;
    for(Node * n : leftPartition) {
        visited = vector<int>(nbNodes(), 0);
        path = DFSforAugmentingPathRec(n, 0, &matching, &visited, &marked);
        matching = getAugmentedMatching(&matching, &path, &marked);
    }
    return matching;
}

vector<Node*> BipartiteGraph::getSolution() {
    return getLeftPartition();
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
