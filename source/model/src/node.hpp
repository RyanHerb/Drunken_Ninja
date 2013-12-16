#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

class Node {

private:
    int id;
    vector<Node*> neighbours;

public:
    Node();
    Node(int id);
    Node(int id, vector<Node*>);
    int getId() const;
    vector<Node*> getNeighbours() const;

    // Returns the nth neighbour
    Node* getNeighbour(int n);
    int degree() const;
    void addNeighbour(Node*);
    void removeNeighbour(Node*);
    //bool equals(Node);
};

// To print a Node
inline ostream& operator<<(ostream &os, const Node &node) {
    os << node.getId() << " : ";
    for (Node *neighbour : node.getNeighbours()) {
        os << (neighbour)->getId() << " ";
    }
    return os;
}



// To print a list<Node*>
inline ostream& operator<<(ostream &os, const vector<Node*> &nodes){
    for (Node *node : nodes) {
        os << node->getId() << " ";
    }
    os << endl;
    return os;
}

inline bool operator==(const Node &node1, const Node &node2){
    return node1.getId() == node2.getId();
}

inline bool operator > (const Node &node1, const Node &node2){
    return node1.degree() > node2.degree();
}

inline bool operator >= (const Node &node1, const Node &node2){
    return node1.degree() >= node2.degree();
}

inline bool operator < (const Node &node1, const Node &node2){
    return node1.degree() < node2.degree();
}

inline bool operator <= (const Node &node1, const Node &node2){
    return node1.degree() <= node2.degree();
}

#endif // NODE_H
