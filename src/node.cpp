#include "node.hpp"

Node::Node(int id, std::list<Node> neighbours)
  : id(id), list<Node>(neighbours) {}

Node::Node(int id) : id(id), list<Node>() {}

int Node::getId() {
  return id;
}

bool Node::equals(Node n) {
    return (this->id == n.id);
}

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
