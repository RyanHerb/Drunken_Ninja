#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>

#ifndef NODE_H
#define NODE_H


class Node: public std::list<Node> {

  private:
    static int counter;
    int id;
    int label;

  public:
    Node(int, std::list<Node>);
    Node(int);
    int getLabel();
    bool equals(Node);
};

bool operator==(const Node& node1, const Node& node2);

#endif // NODE_H
