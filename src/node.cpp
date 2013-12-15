#include "node.hpp"
#include <iterator>
#include <algorithm>

Node::Node() {}

Node::Node(int id): id(id), neighbours(vector<Node*>()){}

Node::Node(int id, vector<Node*> neighbours) : id(id), neighbours(neighbours){}


int Node::getId() const {
    return id;
}

vector<Node*> Node::getNeighbours() const {
    return neighbours;
}

Node* Node::getNeighbour(int n) {
    if (n < neighbours.size()) {
        return neighbours.at(n);
    }
    return NULL;
}

void Node::addNeighbour(Node *n) {
    neighbours.push_back(n);
}

void Node::removeNeighbour(Node *neighbor) {
    neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), neighbor), neighbours.end());
}

int Node::degree() const {
    return neighbours.size();
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
