#include "graph.hpp"
#include "node.hpp"
#include <algorithm>

using namespace std;

Graph::Graph() : counter(0){}

Graph::Graph(int n) : counter(0) {
    for (int i = 0; i < n; ++i) {
        addNode();
    }
}

Graph::Graph(int n, int p) : counter(0) {
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
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    n1->addNeighbor(this->nodes[b]);
    n2->addNeighbor(this->nodes[a]);
    edges.push_back(new Edge(n1, n2));
}

bool Graph::hasEdge(int a, int b) {
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];

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
    Node *n1 = this->nodes[a];
    Node *n2 = this->nodes[b];
    Edge *e = new Edge(n1,n2);
    vector<Edge*>::iterator it (edges.begin()), lend(edges.end());
    while(it != lend && !(**it == *e))
        ++it;
    if (it != lend) {
        n1->removeNeighbor(this->nodes[b]);
        n2->removeNeighbor(this->nodes[a]);
        edges.erase(it);
    }
}

void Graph::removeEdges(int a){
    Node * n = nodes[a];
    for (Node* node : n->getNeighbors()) {
        removeEdge(a, node->getId());
    }
}

Node* Graph::getRandomNode() {
    int select = rand() % counter;
    return nodes[select];
}

Edge* Graph::getRandomEdge(){
    int select = rand() % edges.size();
    return edges[select];
}

void Graph::removeNode(int id) {
    removeEdges(id);
    nodes.erase(id);
}

void Graph::removeNode(Node *n) {
    removeNode(n->getId());
}

list<Node*> Graph::getCover() {
    Graph *localGraph(this);
    list<Node*> cover;

    while (localGraph->edges.size() > 0) {
        Edge *edge = localGraph->getRandomEdge();
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

list<Node*> Graph::getCoverGlouton() {
    Graph *localGraph(this);
    list<Node*> cover;

    while (localGraph->edges.size() > 0) {
        Node *current = localGraph->getHigherDegreeNode();
        cover.push_front(current);
        localGraph->removeNode(current);
    }
    delete localGraph;
    return cover;
}

list<Node*> Graph::getNodes() const {
    list<Node*> list;
    for (pair<int,Node*> pair : nodes) {
        list.push_back(pair.second);
    }
    return list;
}
