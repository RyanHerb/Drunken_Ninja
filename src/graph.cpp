#include "graph.hpp"
#include "node.hpp"
#include <algorithm>

using namespace std;

Graph::Graph(){}


Graph::Graph(Graph *g){
    //TODO un graph peut avoir des ID plus grand que son nombre de sommets car on supprime des sommets
    cout << "creation graph"<<endl;
    for (int i = 0; i < g->getNodes().size(); ++i) {
        addNode();
    }
    cout << "creation 2"<<endl;
    list<Edge *>gEdges = g->getEdges();
    list<Edge *>::const_iterator currentEdge (gEdges.begin()), lend(gEdges.end());
    cout << "creation 2.5"<<endl;
    for(;currentEdge!=lend;++currentEdge){
        Node *n1 = (*currentEdge)->first();
        Node *n2 = (*currentEdge)->second();
        cout << "creation 2.6"<<endl;

        //ça pose problème ici
        addEdge(n1->getId(), n2->getId());
        cout << "creation 2.7"<<endl;
    }
    cout << "creation 3"<<endl;
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

void Graph::addEdge(int a, int b) {
    Node *n1 = this->graphNodes[a];
    Node *n2 = this->graphNodes[b];
    n1->addNeighbor(this->graphNodes[b]);
    n2->addNeighbor(this->graphNodes[a]);
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
        n1->removeNeighbor(this->graphNodes[b]);
        n2->removeNeighbor(this->graphNodes[a]);
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
    int select = rand() % counter;
    return nodes[select];
}

Edge* Graph::getRandomEdge(){
    int select = rand()%nbEdge;
   unordered_map<int,Edge*>::iterator it = edges.begin();
    advance(it, select);
    return it->second;
    //TODO pourquoi ça marche pour les nodes mais pas pour les edges ?
    //return edges[select];
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

void getKCoverRec(Graph *localGraph,int K, list<int>cover ){

    cout << "K : " << K <<endl;
    cout << "localgraph"<<endl;
    cout << *localGraph <<endl;
    cout <<"\n\n"<<endl;

    if(localGraph->nbEdges() > 0){
        if(localGraph->nbEdges() >= K*localGraph->getNodes().size()){
            delete localGraph;
            cover.clear();
        }
        else{
            cout << "else entrée"<<endl;
            Edge *e = localGraph->getRandomEdge();
            cout << "else 1"<<endl;
            Graph* localGraph1 = new Graph(localGraph);
            cout << "else 2"<<endl;
            list<int> cover1(cover);
            cout << "else 3"<<endl;
            Graph* localGraph2 = new Graph(localGraph);
            delete localGraph;
            cout << "else 4"<<endl;
            list<int> cover2(cover);
            cout << "else 5"<<endl;
            cover1.push_back(e->first()->getId());
            cout << "else 6"<<endl;
            localGraph1->removeNode(e->first()->getId());
            cout << "else 7"<<endl;
            cover2.push_back(e->second()->getId());
            cout << "else 8"<<endl;
            localGraph2->removeNode(e->second()->getId());
            cout << "else 9"<<endl;
            getKCoverRec(localGraph1,K-1, cover1);
            getKCoverRec(localGraph2,K-1, cover2);
            cover.splice(cover.end(), cover1);
            cover.splice(cover.end(), cover2);
            cout << "else sortie"<<endl;   
        }
    }
}

list<Node*> Graph::getKCover(int K){
    Graph *localGraph = new Graph(this);
    list<int> cover;
    list<Node*>result;
    map<int, Node*>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    for (; currentNode != lend; ++currentNode) {
        if((*currentNode).second->degree() > K){
            cover.push_back((currentNode->second)->getId());
            localGraph->removeNode(currentNode->second);
        }
    }

    K = K - cover.size();
    cout << "K :" << K <<endl;
    if(localGraph->nbEdges() > K*K){
        return result;
    }
    else{
        getKCoverRec(localGraph, K, cover);
        list<int>::const_iterator currentNode (cover.begin()), lend(cover.end());
        for (; currentNode != lend; ++currentNode) {
            result.push_back(graphNodes[*currentNode]);
        }
        return result;
    }
}

int Graph::nbEdges(){
    return nbEdge;
}


//TODO change to vector
list<Edge*> Graph::getEdges() const {
    map<int, Edge*>::const_iterator currentEdge (edges.begin()), lend(edges.end());
    list<Edge*> list;
    for (; currentEdge != lend; ++currentEdge) {
        list.push_back((*currentEdge).second);
    }
    return list;
}
