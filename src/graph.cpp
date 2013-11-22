#include "graph.hpp"
#include "node.hpp"

using namespace std;

Graph::Graph():counter(0){}

Graph::Graph(int n):counter(0){
    for (int i=0 ; i<n ; i++){
        addNode();
    }
}

Graph::Graph(int n, int p):counter(0){
    p = p%101;
    for (int i=0 ; i<n ; i++){
        addNode();
    }

    for (int i=0 ; i<n-1 ; i++){
        for (int j=i+1 ; j < n ; j++){
            if (rand()%101 <= p)
                addEdge(i,j);
        }
    }
}

int Graph::addNode(){
    Node * n = new Node(counter);
    this->graphNodes.insert(make_pair(counter, n));
    return counter++;
}

void Graph::addEdge(int a, int b){
    Node * n1 = this->graphNodes[a];
    Node * n2 = this->graphNodes[b];
    n1->addNeighbor(this->graphNodes[b]);
    n2->addNeighbor(this->graphNodes[a]);
}

void Graph::removeEdge(int a, int b){
    Node * n1 = this->graphNodes[a];
    Node * n2 = this->graphNodes[b];
    n1->removeNeighbor(this->graphNodes[b]);
    n2->removeNeighbor(this->graphNodes[a]);
}

void Graph::removeAllEdges(int a){
    Node * n = graphNodes[a];
    list<Node *> neighbors = n->getNeighbors();
    list<Node *>::const_iterator currentNeighbor (neighbors.begin()), lend(neighbors.end());
    for(;currentNeighbor!=lend;++currentNeighbor){
        Node * cNeighbor = (*currentNeighbor);
        cNeighbor->removeNeighbor(n);
        n->removeNeighbor(cNeighbor);
    }
}

/*Node * Graph::getNode(int node) const{
    return graphNodes[node];
}*/

list<Node *> Graph::getNodes() const{
    map<int, Node *>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    list<Node *> list;
    for(;currentNode!=lend;++currentNode)list.push_back((*currentNode).second);
    return list;
}
