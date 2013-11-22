#include <iostream>
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"

using namespace std;
/*
int main() {
    list<Node *> nodeList;
    for(int i = 0; i < 10; ++i) {
        Node * n = new Node(i);
        cout << n->getId() << '\n';
        nodeList.push_back(n);
    }

    cout << nodeList.front()->getId() << '\n';

}
*/
int main(){
    Tree t(10); // random tree with 6 vertices;
    list<Node *> nodes = t.getLeaves();
    cout << t;
    cout << endl << "leaves : ";
    list<Node *>::const_iterator currentNode (nodes.begin()), lend(nodes.end());
    for(;currentNode!=lend;++currentNode)cout << (*currentNode)->getId() << " ";
}

