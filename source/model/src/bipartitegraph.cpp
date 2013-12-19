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

void BipartiteGraph::addDirectedEdge(int a, int b) {
    map<int, Node*>::iterator it = nodes.find(a);
    if (it != nodes.end()) {
        it = nodes.find(b);
        if (it != nodes.end()) {
            Node *n1 = this->nodes[a];
            Node *n2 = this->nodes[b];
            n1->addNeighbour(this->nodes[b]);
            n2->addNeighbour(this->nodes[a]);
            Edge* e= new DirectedEdge(n1,n2);
            edges.insert(make_pair(e->hash(),e));
        } else {
            cerr << "Node " << b << " does not exist" << endl;
        }
    } else {
        cout << "Node " << a << " does not exist" << endl;
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
/*
vector<Edge *> BipartiteGraph::DFSforAugmentingPathRec(Node * current, Node * previous, vector<Edge*> * matching, vector<int> * visited, vector<int> * marked) {

    if ((marked->at(current->getId()) == 0) && (partition[current->getId()] == 0))
        return vector<Edge *>(1,getEdge(current->getId(),previous->getId()));
    vector<Edge *> resultat;
    if((marked->at(current->getId()) == 1) &&  (partition[current->getId()] == 0)){
        for(Edge * e : *matching) {
            if(e->first() == current){
                resultat = DFSforAugmentingPathRec(e->second(), current, matching, visited, marked);
            }
            else if(e->second() == current)
                resultat = DFSforAugmentingPathRec(e->first(), current, matching, visited, marked);
        }

    }
    else{
        for (Node * v : current->getNeighbours()){
            if (visited->at(v->getId()) == 0){
                visited->at(v->getId()) = 1;
                resultat = DFSforAugmentingPathRec(v, current, matching, visited, marked);
                if (resultat.size() != 0) {
                    if(previous != 0)
                        resultat.push_back(getEdge(current->getId(),previous->getId()));
                    return resultat;
                }
            }
        }
    }
    if (resultat.size() != 0) {
        if(previous != 0)
            resultat.push_back(getEdge(current->getId(),previous->getId()));
        return resultat;
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
    marked = vector<int>(nbNodes(), 0);
    vector<Edge *> path;
    for(Node * n : leftPartition) {
        visited = vector<int>(nbNodes(), 0);
        path = DFSforAugmentingPathRec(n, 0, &matching, &visited, &marked);
        matching = getAugmentedMatching(&matching, &path, &marked);
    }
    return matching;
}
*/
vector<Node*> BipartiteGraph::getSolution() {
    return getLeftPartition();
}

NodeColor BipartiteGraph::color(Node * node){
    return colorVector[node->getId()];
}

vector<Node*> BipartiteGraph::getCover(){
    //initialise colorVector
    colorVector = vector<NodeColor>();
    for(Node * node : getNodes())
        colorVector.push_back(NodeColor::white);

    //initialise orientedGraph dup
    BipartiteGraph dup(nbNodes());
    for(Edge * e : getEdges()){
        if(partition[e->first()->getId()] == 1)
            dup.addDirectedEdge(e->first()->getId(), e->second()->getId());
        else
            dup.addDirectedEdge(e->second()->getId(), e->first()->getId());
    }
    dup.resetPartitions();
    cout << "left : " << leftPartition << endl << "right : " << rightPartition << endl;
    Node * s = dup.addNode();
    for(Node * n : leftPartition)
        dup.addDirectedEdge(s->getId(),n->getId());
    Node * t = dup.addNode();
    for(Node * n : rightPartition)
        dup.addDirectedEdge(n->getId(),t->getId());

    cout << "vla le dup :" << endl << dup <<endl;
    //initialise queue
    queue<int> waitingQueue();

}


vector<Node*> BipartiteGraph::getLeftPartition() {
    initialisePartitions();
    return leftPartition;
}

vector<Node*> BipartiteGraph::getRightPartition() {
    initialisePartitions();
    return rightPartition;
}

/*
vector<Node*> BipartiteGraph::getCover(){
    BipartiteGraph dup(this);
    vector<Node*> result;
    vector<Edge *> mMatching = getMaximumMatching();
    for (Node * node : dup.getNodes()) {
        if (marked.at(node->getId()) == 0) {
            for(Node * neig : node->getNeighbours()) {
                if (marked.at(neig->getId()) == 1) {
                    result.push_back(getNode(neig->getId()));
                    for(Node * neig2 : neig->getNeighbours()) {
                        if (marked.at(neig2->getId()))
                            dup.removeNode(neig2);
                    }
                    dup.removeNode(neig);
                }
            }
            dup.removeNode(node);
        }
    }
    Node * remainingMarkedNode;
    while((remainingMarkedNode = dup.getRandomNode()) != 0) {
        result.push_back(getNode(remainingMarkedNode->getId()));
        Node * neig;
        for( Edge * e : mMatching) {
            if (e->first()->getId() == remainingMarkedNode->getId())
                neig = dup.getNode(e->second()->getId());
            else if (e->second()->getId() == remainingMarkedNode->getId())
                neig = dup.getNode(e->first()->getId());
        }
        dup.removeNode(neig);
        dup.removeNode(remainingMarkedNode);
    }
    return result;
}
*/

string BipartiteGraph::getType() {
    return "bipartitegraph";
}
