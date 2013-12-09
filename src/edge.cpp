#include "edge.hpp"


Edge::Edge(){}
Edge::Edge(Node*a, Node*b):n1(a), n2(b){}

Node* Edge::first(){
    return n1;
}
Node* Edge::second(){
    return n2;
}

const Node* Edge::first() const{
    return n1;
}
const Node* Edge::second()const{
    return n2;
}
