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
    n1->addNeighbour(this->nodes[b]);
    n2->addNeighbour(this->nodes[a]);
    edges.push_back(new Edge(n1, n2));
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
    vector<Edge*>::iterator it (edges.begin()), lend(edges.end());
    while(it != lend && !(**it == *e))
        ++it;
    if (it != lend) {
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

vector<Node*> Graph::getCoverGlouton() {
    Graph *localGraph(this);
    vector<Node*> cover;

    while (localGraph->edges.size() > 0) {
        Node *current = localGraph->getHigherDegreeNode();
        cover.push_back(current);
        localGraph->removeNode(current);
    }
    delete localGraph;
    return cover;
}

vector<Node*> Graph::getNodes() const {
    vector<Node*> dup;
    for (pair<int,Node*> pair : nodes) {
        dup.push_back(pair.second);
    }
    return dup;
}
