#include "directededge.hpp"

DirectedEdge::DirectedEdge(Node * from, Node * to) : Edge(from, to){}

int DirectedEdge::hash()const {
    int id1, id2;
    id1 = n1->getId();
    id2 = n2->getId();
    return (id1+id2) * (id1 + id2 + 1)/2 + id2;
}
