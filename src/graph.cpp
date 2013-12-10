#include "graph.hpp"
#include "node.hpp"
#include <algorithm>

using namespace std;

Graph::Graph() : counter(0), nbEdge(0){}

Graph::Graph(int n) : counter(0), nbEdge(0) {
    for (int i = 0; i < n; ++i) {
        addNode();
    }
}

Graph::Graph(int n, int p) : counter(0), nbEdge(0) {
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
    this->graphNodes.insert(make_pair(counter, n));
    ++counter;
    return n;
}

void Graph::addEdge(int a, int b) {
    Node *n1 = this->graphNodes[a];
    Node *n2 = this->graphNodes[b];
    n1->addNeighbor(this->graphNodes[b]);
    n2->addNeighbor(this->graphNodes[a]);
    Edge* e= new Edge(n1,n2);
    edges.push_back(e);
    ++nbEdge;
}

bool Graph::hasEdge(int a, int b) {
    Node *n1 = this->graphNodes[a];
    Node *n2 = this->graphNodes[b];

    Node *from = n1;
    Node *to = n2;
    if (n1->getNeighbors().size() > n2->getNeighbors().size()) {
        from = n2;
        to = n1;
    }

    for (Node *neighbour : from->getNeighbors()) {
        if (neighbour->getId() == to->getId())
            return true;
    }
    return false;
}

void Graph::removeEdge(int a, int b) {
    Node *n1 = this->graphNodes[a];
    Node *n2 = this->graphNodes[b];
    Edge *e = new Edge(n1,n2);
    vector<Edge*>::iterator it (edges.begin()), lend(edges.end());
    while(it != lend && !(**it == *e))
        ++it;
    if (it != lend) {
        n1->removeNeighbor(this->graphNodes[b]);
        n2->removeNeighbor(this->graphNodes[a]);
        edges.erase(it);
        --nbEdge;
    }
}

void Graph::removeEdges(int a){
    Node * n = graphNodes[a];
    list<Node *> neighbors = n->getNeighbors();
    list<Node *>::const_iterator currentNeighbor (neighbors.begin()), lend(neighbors.end());
    for(;currentNeighbor!=lend;++currentNeighbor){
        Node * cNeighbor = (*currentNeighbor);
        removeEdge(a,cNeighbor->getId());
    }
}

Node* Graph::getRandomNode() {
    int select = rand()%counter;
    return graphNodes[select];
}


Edge* Graph::getRandomEdge(){
    int select = rand()%nbEdge;
    return edges[select];
}

void Graph::removeNode(int id) {
    removeEdges(id);
    graphNodes.erase(id);
}

void Graph::removeNode(Node *n) {
    removeNode(n->getId());
}

list<Node*> Graph::getCover() {
    Graph *localGraph(this);
    list<Node*> cover;

    while (localGraph->nbEdge > 0) {
        Edge* edge = localGraph->getRandomEdge();
        cover.push_front(edge->first());
        cover.push_front(edge->second());
        localGraph->removeNode(edge->first());
        localGraph->removeNode(edge->second());
    }
    delete localGraph;
    return cover;
}

Node* Graph::getHigherDegreeNode(){
    // TODO optimiser, surement avec un tableau trié
    // mis à jour à chaque ajout/retrait d'arete
    Node *selectedNode;
    int higherDegree = 0;
    map<int, Node*>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    for (; currentNode != lend; ++currentNode) {
        if (higherDegree < (*currentNode).second->degree()) {
            selectedNode = (*currentNode).second;
            higherDegree = selectedNode->degree();
        }
    }
    return selectedNode;
}

list<Node*> Graph::getCoverGlouton() {
    Graph *localGraph(this);
    list<Node*> cover;

    while (localGraph->nbEdge > 0) {
        Node *current = localGraph->getHigherDegreeNode();
        cover.push_front(current);
        localGraph->removeNode(current);
    }
    delete localGraph;
    return cover;
}

list<Node*> Graph::getNodes() const {
    map<int, Node*>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    list<Node*> list;
    for (; currentNode != lend; ++currentNode) {
        list.push_back((*currentNode).second);
    }
    return list;
}
