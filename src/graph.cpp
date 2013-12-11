#include "graph.hpp"
#include "node.hpp"
#include <algorithm>

using namespace std;

Graph::Graph(){}


Graph::Graph(Graph *g){
    vector<Node *> srcNodes = g->getNodes();
    for (int i = 0; i < srcNodes.size(); ++i) {
        addNode(srcNodes[i]->getId());
    }
    vector<Edge *> srcEdges = g->getEdges();
    for (int i = srcEdges.size()-1; i >= 0; --i) {
        addEdge(srcEdges[i]->first()->getId(), srcEdges[i]->second()->getId());
    }
}

Graph::Graph(int n){
    for (int i = 0; i < n; ++i) {
        addNode();
    }
}

Graph::Graph(int n, int p){
    p = p%101;
    for (int i = 0; i < n; ++i) {
        addNode();
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}

Node* Graph::addNode() {
    Node *n = new Node(counter);
    this->nodes.insert(make_pair(counter, n));
    ++counter;
    return n;
}

Node * Graph::addNode(int id){
    Node *n = new Node(id);
    this->nodes.insert(make_pair(id, n));
    ++counter;
    return n;
}

void Graph::addEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    n1->addNeighbour(this->nodes[b]);
    n2->addNeighbour(this->nodes[a]);
    Edge* e= new Edge(n1,n2);
    edges.insert(make_pair(e->hash(),e));
}

bool Graph::hasEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];

    Node *from = n1;
    Node *to = n2;
    if (n1->getNeighbours().size() > n2->getNeighbours().size()) {
        from = n2;
        to = n1;
    }

    for (Node *neighbour : from->getNeighbours()) {
        if (neighbour->getId() == to->getId())
            return true;
    }
    return false;
}

void Graph::removeEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    Edge *e = new Edge(n1,n2);
    unordered_map<int,Edge*>::iterator it= edges.find(e->hash());
    if (it != edges.cend()) {
        n1->removeNeighbour(this->nodes[b]);
        n2->removeNeighbour(this->nodes[a]);
        edges.erase(it);
    }
}

void Graph::removeEdges(int a){
    Node *n = nodes[a];
    for (Node *node : n->getNeighbours()) {
        removeEdge(a, node->getId());
    }
}

Node* Graph::getRandomNode() {
    int select = rand()%nodes.size();
    map<int,Node*>::iterator it = nodes.begin();
    advance(it, select);
    return it->second;
}

Edge* Graph::getRandomEdge(){
    int select = rand()%nbEdges();
    unordered_map<int,Edge*>::iterator it = edges.begin();
    advance(it, select);
    return it->second;
}

void Graph::removeNode(int id) {
    removeEdges(id);
    nodes.erase(id);
}

void Graph::removeNode(Node *n) {
    removeNode(n->getId());
}


vector<Node*> Graph::getCover() {
    Graph *localGraph(this);
    vector<Node*> cover;

    while (localGraph->edges.size() > 0) {
        Edge *edge = localGraph->getRandomEdge();
        cover.push_back(edge->first());
        cover.push_back(edge->second());
        localGraph->removeNode(edge->first());
        localGraph->removeNode(edge->second());
    }
    //TODO
    // delete localGraph; ?
    return cover;
}

Node* Graph::getHigherDegreeNode(){
    // TODO optimiser, surement avec un tableau trié
    // mis à jour à chaque ajout/retrait d'arete
    Node *selectedNode;
    int higherDegree = -1;
    for (pair<int,Node*> pair : nodes) {
        Node *node = pair.second;
        if (higherDegree < node->degree()) {
            higherDegree = node->degree();
            selectedNode = node;
        }
    }
    return selectedNode;
}


vector<Node*> Graph::getCoverGlouton() {
    Graph *localGraph(this);
    vector<Node*> cover;
    while (localGraph->edges.size() > 0) {
        Node *current = localGraph->getHigherDegreeNode();
        cover.push_back(current);
        localGraph->removeNode(current);
    }
    //TODO
    //delete localGraph; ?
    return cover;
}


vector<Node*> Graph::getNodes() const {
    vector<Node*> dup;
    for (pair<int,Node*> pair : nodes) {
        dup.push_back(pair.second);
    }
    return dup;
}

vector<int> getKCoverRec(Graph *localGraph,int K, vector<int>cover ){

    if(localGraph->nbEdges() > 0){
        if(localGraph->nbEdges() >= K*localGraph->getNodes().size()){
            delete localGraph;
            cover.clear();
            return cover;
        }
        else{
            Edge *e = localGraph->getRandomEdge();
            cout << "arete selectionnee : " << *e << endl;
            Graph* localGraph1 = new Graph(localGraph);
            vector<int> cover1(cover);
            Graph* localGraph2 = new Graph(localGraph);
            delete localGraph;
            vector<int> cover2(cover);
            cover1.push_back(e->first()->getId());
            localGraph1->removeNode(e->first()->getId());
            cover2.push_back(e->second()->getId());
            localGraph2->removeNode(e->second()->getId());
            cover1 = getKCoverRec(localGraph1,K-1, cover1);
            cover2 = getKCoverRec(localGraph2,K-1, cover2);
            if (cover2.size() == 0)
                cover2 = cover1;
            if (cover1.size() == 0)
                cover1 = cover2;
            return cover1.size()>cover2.size() ? cover2 : cover1;
        }
    }
    else{
        return cover;
        delete localGraph;
    }
}

vector<Node*> Graph::getKCover(int K){
    Graph *localGraph = new Graph(this);
    vector<int> cover;
    vector<Node*>result;
    map<int, Node*>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for (; currentNode != lend; ++currentNode) {
        if((*currentNode).second->degree() > K){
            cover.push_back((currentNode->second)->getId());
            localGraph->removeNode(currentNode->second);
        }
    }

    int Kprime = K - cover.size();
    cout << "Kprime :" << Kprime <<endl;
    if(localGraph->nbEdges() > Kprime*K){
        cout << "nbEdges : " << localGraph->nbEdges() << endl << "Kprime*K : " << Kprime*K <<endl;
        return result;
    }
    else{
        cover = getKCoverRec(localGraph, Kprime, cover);
        vector<int>::const_iterator currentNode (cover.begin()), lend(cover.end());
        for (; currentNode != lend; ++currentNode) {
            result.push_back(nodes[*currentNode]);
        }
        return result;
    }
}

int Graph::nbEdges(){
    return edges.size();
}


//TODO change to vector
vector<Edge*> Graph::getEdges() const {
    unordered_map<int, Edge*>::const_iterator currentEdge (edges.begin()), lend(edges.end());
    vector<Edge*> vec;
    for (; currentEdge != lend; ++currentEdge) {
        vec.push_back((*currentEdge).second);
    }
    return vec;
}
