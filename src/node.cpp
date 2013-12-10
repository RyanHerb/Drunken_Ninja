#include "node.hpp"
#include <iterator>
#include <algorithm>

Node::Node() {}

Node::Node(int id): id(id), neighbors(vector<Node*>()){}

Node::Node(int id, vector<Node*> neighbours) : id(id), neighbors(neighbours){}


int Node::getId() const {
    return id;
}

vector<Node*> Node::getNeighbours() const {
    return neighbors;
}

Node* Node::getNeighbour(int n) {
    if (n < neighbors.size()) {
        return neighbors.at(n);
    }
    return NULL;
}

void Node::addNeighbour(Node *n) {
    neighbors.push_back(n);
}

void Node::removeNeighbour(Node *neighbor) {
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), neighbor), neighbors.end());
}

int Node::degree() const {
    return neighbors.size();
}

/*bool Node::equals(Node n) {
    return (this->id == n.id);
}*/

bool operator<(Node &node1, Node &node2) {
    return (node1.getId() < node2.getId());
}

bool operator<=(Node &node1, Node &node2) {
    return (node1 < node2 || node1.getId() == node2.getId());
}

bool operator>(Node &node1, Node &node2) {
    return (node2.getId() < node1.getId());
}

bool operator==(Node &node1, Node &node2) {
    return (node1.getId() == node2.getId());
}
