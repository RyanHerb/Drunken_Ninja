#include "graph.hpp"
#include "node.hpp"
#include <algorithm>

using namespace std;

Graph::Graph(){}

Graph::Graph(int n){
    for (int i = 0; i < n; ++i) {
        addNode();
    }
}

Graph::Graph(int n, int p) {
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
    pair<Node*,Node*> p(n1,n2);
    edges.push_back(p);
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
    pair<Node*,Node*> p1(n1,n2);
    pair<Node*,Node*> p2(n2,n1);
    vector<pair<Node*, Node*> >::iterator it1;
    vector<pair<Node*, Node*> >::iterator it2;
    it1 = find(edges.begin(), edges.end(),p1);
    it2 = find(edges.begin(), edges.end(),p2);
    if ((it1->first == n1 && it1->second == n2) || (it2->first == n2 && it2->second == n1)) {
        n1->removeNeighbor(this->graphNodes[b]);
        n2->removeNeighbor(this->graphNodes[a]);
        if (it1->first == n1 && it1->second == n2)
            edges.erase(it1);
        else
            edges.erase(it2);
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


pair<Node*,Node*> Graph::getRandomEdge(){
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
        pair<Node*, Node*> edge = localGraph->getRandomEdge();
        cover.push_front(edge.first);
        cover.push_front(edge.second);
        localGraph->removeNode(edge.first);
        localGraph->removeNode(edge.second);
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
