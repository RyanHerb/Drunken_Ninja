#include "graph.hpp"
#include "node.hpp"

using namespace std;

Graph::Graph():counter(0),nbEdge(0){}

Graph::Graph(int n):counter(0),nbEdge(0){
    for (int i=0 ; i<n ; i++){
        addNode();
    }
}

Graph::Graph(int n, int p):counter(0),nbEdge(0){
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



Node* Graph::addNode(){
    Node * n = new Node(counter);
    this->graphNodes.insert(make_pair(counter, n));
    counter++;
    return n;
}

void Graph::addEdge(int a, int b){
    Node * n1 = this->graphNodes[a];
    Node * n2 = this->graphNodes[b];
    n1->addNeighbor(this->graphNodes[b]);
    n2->addNeighbor(this->graphNodes[a]);
    nbEdge++;
}

void Graph::removeEdge(int a, int b){
    //TODO verifier que l'arete existe
    Node * n1 = this->graphNodes[a];
    Node * n2 = this->graphNodes[b];
    n1->removeNeighbor(this->graphNodes[b]);
    n2->removeNeighbor(this->graphNodes[a]);
    nbEdge--;
}

void Graph::removeAllEdges(int a){
    Node * n = graphNodes[a];
    list<Node *> neighbors = n->getNeighbors();
    list<Node *>::const_iterator currentNeighbor (neighbors.begin()), lend(neighbors.end());
    for(;currentNeighbor!=lend;++currentNeighbor){
        Node * cNeighbor = (*currentNeighbor);
        cNeighbor->removeNeighbor(n);
        n->removeNeighbor(cNeighbor);
        nbEdge--;
    }
}

Node* Graph::getRandomNode(){
    int select = rand()%counter;
    return graphNodes[select];
}


pair<Node*,Node*> *Graph::getRandomEdge(){
    //TODO Marche pas (aretes comptées deux fois)
    int select = rand()%nbEdge;
    map<int, Node *>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    for(;currentNode!=lend;++currentNode){
        if(select < (*currentNode).second->degre()){
            Node* A = (*currentNode).second;
            Node* B = A->getNeighbor(select);
            return new pair<Node*, Node*>(A,B);
        }
        else{
            select -= (*currentNode).second->degre();
        }
    }
}

void Graph::removeNode(Node* n){
    removeAllEdges(n->getId());
    graphNodes.erase(n->getId());
}


list<Node *> Graph::getCover(){
    Graph * localGraph(this);
    list<Node *> cover;

    while (localGraph->nbEdge>0){
        pair<Node*, Node*>* edge = localGraph->getRandomEdge();
        cover.push_front(edge->first);
        cover.push_front(edge->second);
        localGraph->removeNode(edge->first);
        localGraph->removeNode(edge->second);
    }
    delete localGraph;
    return cover;
}

Node * Graph::getHigherDegreeNode(){
    //TODO optimiser, surement avec un tableau trié mis à jour à chaque ajout/retrait d'arete
    Node* selectedNode;
    int higherDegree = 0;
    map<int, Node *>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    for(;currentNode!=lend;++currentNode){
        if(higherDegree < (*currentNode).second->degre()){
            selectedNode = (*currentNode).second;
            higherDegree = selectedNode->degre();
        }
    }
    return selectedNode;
}

list<Node *> Graph::getCoverGlouton(){
    Graph * localGraph(this);
    list<Node *> cover;

    while (localGraph->nbEdge>0){
        Node * current = localGraph->getHigherDegreeNode();
        cover.push_front(current);
        localGraph->removeNode(current);
    }
    delete localGraph;
    return cover;
}



list<Node *> Graph::getNodes() const{
    map<int, Node *>::const_iterator currentNode (graphNodes.begin()), lend(graphNodes.end());
    list<Node *> list;
    for(;currentNode!=lend;++currentNode)list.push_back((*currentNode).second);
    return list;
}
