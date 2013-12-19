#ifndef DIRECTEDEDGE_HPP
#define DIRECTEDEDGE_HPP
#include "edge.hpp"

class DirectedEdge : public Edge
{

public:
    DirectedEdge(Node * from, Node * to);
    int hash() const;
};

#endif // DIRECTEDEDGE_HPP
