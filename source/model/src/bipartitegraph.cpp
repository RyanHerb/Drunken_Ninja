#include "bipartitegraph.hpp"

BipartiteGraph::BipartiteGraph(IGraph * g) : Graph(g){
    initialisePartitions();
}

BipartiteGraph::BipartiteGraph(int n) : Graph(n){}

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

void BipartiteGraph::resetPartitions(){
    rightPartition = vector<Node*>();
    initialisePartitions();
}

void BipartiteGraph::initialisePartitions(){
    if((rightPartition.size() != 0) || (nbNodes() == 0))
        return;
    Graph dup(this);
    rightPartition = vector<Node*>();
    leftPartition = vector<Node*>();
    partition = vector<int>(nbNodes(), 0);

    Edge *edge;
    while((edge = dup.getRandomEdge()) != 0){
        BFSforInitialisation(edge->first(), &dup);
    }

    Node *node;
    while((node = dup.getRandomNode()) != 0){
        rightPartition.push_back(getNode(node->getId()));
        dup.removeNode(node);
    }

    for(Node * n : leftPartition)
        partition[n->getId()] = 1;
}

vector<Node*> BipartiteGraph::getSolution() {
    return getLeftPartition();
}

vector<Node*> BipartiteGraph::succ(Node * n){
    if (n == s)
        return leftPartition;
    if (n == t)
        return vector<Node*>();
    if (partition[n->getId()] == 1)
        return n->getNeighbours();
    return vector<Node*>(1, t);
}


vector<Node *> BipartiteGraph::pred(Node * n){
    if (n == s)
        return vector<Node*>();
    if (n == t)
        return rightPartition;
    if (partition[n->getId()] == 0)
        return n->getNeighbours();
    return vector<Node*>(1, s);
}

bool BipartiteGraph::FordFulkerson(vector<NodeColor> * colorVector) {
    //initialise tmpFlux adn father
    map<Edge*, int> tmpFlux;
    for( Edge * e : getEdges()){
        tmpFlux.insert(make_pair(e, 0));
    }
    vector<int> father = vector<int>(nbNodes(), -1);
    *colorVector = vector<NodeColor>();
    for(int i = 0; i < nbNodes(); ++i){
        colorVector->push_back(NodeColor::white);
    }
    colorVector->at(s->getId()) = NodeColor::grey; //color of s

    //initialise queue
    queue<Node *> calls;
    calls.push(s);
    while((colorVector->at(t->getId()) == NodeColor::white) && !calls.empty()){
        Node * v = calls.front();
        calls.pop();
        for (Node * w : succ(v)){
            Edge * vw = getEdge(v->getId(), w->getId());
            if ((colorVector->at(w->getId()) == NodeColor::white) && (flux.at(vw) == 0)) {
                colorVector->at(w->getId()) = NodeColor::grey;
                tmpFlux.at(vw) = 1;
                father[w->getId()] = v->getId();
                calls.push(w);
            }
        }
        for (Node * u : pred(v)){
            Edge * uv = getEdge(u->getId(), v->getId());
            if((colorVector->at(u->getId()) == NodeColor::white) && (flux.at(uv) == 1)){
                colorVector->at(u->getId()) = NodeColor::grey;
                tmpFlux.at(uv) = 0;
                father[u->getId()] = v->getId();
                calls.push(u);
            }
        }
        colorVector->at(v->getId()) = NodeColor::black;
    }
    if(colorVector->at(t->getId()) == NodeColor::grey){
        Node * v = t;
        Node * u = getNode(father[v->getId()]);
        Edge * uv = getEdge(u->getId(), v->getId());
        flux.at(uv) = tmpFlux.at(uv);
        while(u->getId() != s->getId()){
            v = u;
            u = getNode(father[v->getId()]);
            Edge * uv = getEdge(u->getId(), v->getId());
            flux.at(uv) = tmpFlux.at(uv);
        }
        return true;
    }
    return false;
}

void BipartiteGraph::initialiseFlux() {
    for( Edge * e : getEdges()){
        flux.insert(make_pair(e, 0));
    }
}

void BipartiteGraph::setST(Node * s, Node * t) {
    this->s = s;
    this->t = t;
}

vector<Node*> BipartiteGraph::getCover(){

    //initialise orientedGraph dups
    BipartiteGraph dup(this);
    dup.initialisePartitions();
    s = dup.addNode();
    for(Node * n : leftPartition)
        dup.addEdge(s->getId(),n->getId());
    t = dup.addNode();
    for(Node * n : rightPartition)
        dup.addEdge(n->getId(),t->getId());
    dup.setST(s, t);

    //initialise dup flux
    dup.initialiseFlux();
    vector<NodeColor> colorVector;

    //repeat Ford Fulkerson algorithme until found maximum matching.
    while(dup.FordFulkerson(&colorVector));

    vector<Node *> cover;
    for(Node * n : leftPartition)
        if(colorVector[n->getId()] == NodeColor::white)
            cover.push_back(n);
    for(Node * n : rightPartition)
        if(colorVector[n->getId()] == NodeColor::black)
            cover.push_back(n);

    return cover;

}


vector<Node*> BipartiteGraph::getLeftPartition() {
    initialisePartitions();
    return leftPartition;
}

vector<Node*> BipartiteGraph::getRightPartition() {
    initialisePartitions();
    return rightPartition;
}



string BipartiteGraph::getType() {
    return "bipartitegraph";
}
