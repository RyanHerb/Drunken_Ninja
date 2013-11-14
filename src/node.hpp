#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>

#ifndef NODE_H
#define NODE_H


class Node: public std::list<Node> {

  private:
    int id;

  public:
    Node();
    Node(int id, std::list<Node>);
    Node(int id);
    int getId();
    bool equals(Node);
};


bool operator==(const Node& node1, const Node& node2);

#endif // NODE_H
