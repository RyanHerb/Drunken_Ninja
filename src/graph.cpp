#include "graph.hpp"
#include "node.hpp"

using namespace std;

Graph::Graph(){this->counter = 0;}

Graph::Graph(int n){
    Graph();
    for (int i=0 ; i<n ; i++){
        addNode();
    }
}

Graph::Graph(int n, int p){
    Graph();
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
    Node n(counter);
    this->graphNodes.insert(make_pair(counter, n));
    return counter++;
}

void Graph::addEdge(int a, int b){
    Node n1 = this->graphNodes[a];
    Node n2 = this->graphNodes[b];
    n1.push_back(this->graphNodes[b]);
    n2.push_back(this->graphNodes[a]);
}
