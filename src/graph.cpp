#include "graph.hpp"
#include "node.hpp"

Graph::Graph(){}

Graph::Graph(int n){
    for (int i=0 ; i<n ; i++){
        addNode();
    }
}

Graph::Graph(int n, int p){
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

void Graph::addNode(){
   Node* n = new Node(1);
   graphNodes.push_back(n);
}

void Graph::addEdge(int a, int b){

}
