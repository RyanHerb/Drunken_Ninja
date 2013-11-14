#include "graph.hpp"
#include "node.hpp"

using namespace std;

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

int Graph::addNode(){
    Node n(counter);
    graphNodes.insert(make_pair(counter, n));
    return counter++;
}

void Graph::addEdge(int a, int b){
  Node n1, n2
  n1 = graphNodes.find(a);
  n2 = graphNodes.find(b);

  n1.push_back(n2);
  n2.push_back(n1);
}
