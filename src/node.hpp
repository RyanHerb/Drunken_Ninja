#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>

using namespace std;

class Node {

private:
    int id;
    list<Node*> neighbors;

public:
    Node();
    Node(int id);
    Node(int id, list<Node*>);
    int getId() const;
    list<Node*> getNeighbors() const;

    // retourne le nieme voisin
    Node* getNeighbor(int n);
    int degree() const;
    void addNeighbor(Node*);
    void removeNeighbor(Node*);
    //bool equals(Node);
};

// To print a Node
inline ostream& operator<<(ostream &os, const Node &node) {
    os << node.getId() << " : ";
    list<Node *> neighbors = node.getNeighbors();
    list<Node *>::const_iterator currentNode (neighbors.begin()), lend(neighbors.end());
    for (; currentNode != lend; ++currentNode) {
        os << (*currentNode)->getId() << " ";
    }
    return os;
}

// To print a list<Node*>
inline ostream& operator<<(ostream &os, const list<Node*> &nodes){
    list<Node*>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for (; currentNode != lend; ++currentNode) {
        os << (*currentNode)->getId() << " ";
    }
    os << endl;
    return os;
}

//bool operator==(const Node &node1, const Node &node2);

#endif // NODE_H
