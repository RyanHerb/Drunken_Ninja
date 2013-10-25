#include <iostream>
#include "node.hpp"

using namespace std;

int main() {
    std::list<Node>* nodeList = new std::list<Node>();
    for(int i = 0; i < 10; ++i) {
        Node n(i);
        cout << n.getLabel() << '\n';
        nodeList->push_back(n);
    }

    cout << nodeList->front().getLabel() << '\n';

}
