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
};

inline bool operator==(const Edge& e1, const Edge& e2){
    return (*(e1.first()) == *(e2.first()) && *(e1.second()) == *(e2.second()))
            || (*(e1.first()) == *(e2.second()) && *(e1.second()) == *(e2.first()));
}

inline ostream& operator<<(ostream &os, const Edge &e) {
    os << "from "<< e.first() <<" to " << e.second() << endl;
    return os;
}

#endif // EDGE_H
