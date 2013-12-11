#ifndef EDGE_H
#define EDGE_H

#include "node.hpp"

class Edge
{
private:
    Node* n1;
    Node* n2;
public:
    Edge();
    Edge(Node*, Node*);
    Node* first();
    Node* second();
    const Node* first()const;
    const Node* second()const;
    int hash()const;
};

inline bool operator==(const Edge& e1, const Edge& e2){
    return e1.hash() == e2.hash();
}

inline ostream& operator<<(ostream &os, const Edge &e) {
    os << "from "<< *(e.first()) <<" to " << *(e.second()) << endl;
    return os;
}



#endif // EDGE_H
