#include "node.hpp"
#include <iterator>

Node::Node() {}

Node::Node(int id): id(id), neighbors(list<Node *>()){}

Node::Node(int id, list<Node *> neighbours) : id(id), neighbors(neighbours){}




int Node::getId() const{
    return id;
}

list<Node *> Node::getNeighbors() const{
    return neighbors;
}

Node * Node::getNeighbor(int n){
    list<Node*>::iterator result;
    if(neighbors.size() > n){
        result = neighbors.begin();
        for (int i=0 ; i<n ; i++)
            result++;
    }
    return *result;
}

void Node::addNeighbor(Node * n){
    neighbors.push_back(n);
}

void Node::removeNeighbor(Node * neighbor){
    neighbors.remove(neighbor);
}

int Node::degre() const{
    return neighbors.size();
}

/*bool Node::equals(Node n) {
    return (this->id == n.id);
}*/

bool operator<(Node& node1, Node& node2) {
    return(node1.getId() < node2.getId());
}

bool operator<=(Node& node1, Node& node2) {
    return(node1 < node2 || node1.getId() == node2.getId());
}


bool operator>(Node& node1, Node& node2) {
    return(node2.getId() < node1.getId());
}

bool operator==(Node& node1, Node& node2) {
    return(node1.getId() == node2.getId());
}
