#include "node.hpp"

Node::Node(int label, std::list<Node> neighbours)
  : label(label), list<Node>(neighbours) { this->id = this->counter++; }

Node::Node(int label) : label(label), list<Node>() { this->id = this->counter++; }

int Node::getLabel() {
  return label;
}

bool Node::equals(Node n) {
    return (this->id == n.id);
}

bool operator<(Node& node1, Node& node2) {
    return(node1.getLabel() < node2.getLabel());
}

bool operator<=(Node& node1, Node& node2) {
    return(node1 < node2 || node1.getLabel() == node2.getLabel());
}


bool operator>(Node& node1, Node& node2) {
    return(node2.getLabel() < node1.getLabel());
}

bool operator==(Node& node1, Node& node2) {
    return(node1.getLabel() == node2.getLabel());
}
