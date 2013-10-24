#include <iostream>
#include <cstdlib>
#include <std::list>


class Node {

  private:
    static int counter;
    int value;
    list::Node neighbours;

  public:
    Node();
    int getValue();
    list::Node getNeighbours();

}