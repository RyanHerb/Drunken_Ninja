#include "edge.hpp"


Edge::Edge(){}
Edge::Edge(Node*a, Node*b):n1(a), n2(b){}

Edge::~Edge() {}

Node* Edge::first() {
    return n1;
}
Node* Edge::second() {
    return n2;
}

const Node* Edge::first() const {
    return n1;
}
const Node* Edge::second() const {
    return n2;
}

int Edge::hash()const {
    int id1, id2;
    if (n2->getId() > n1->getId()){
        id1 = n2->getId();
        id2 = n1->getId();
    } else {
        id2 = n2->getId();
        id1 = n1->getId();
    }
    return (id1+id2) * (id1 + id2 + 1)/2 + id2;
}

