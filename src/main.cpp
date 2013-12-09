#include <iostream>
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"

using namespace std;

const string DEFAULT_INPUT = "../../Drunken_Ninja/data/tree1.txt";

int main(int argc, char *argv[]) {
    string filename = DEFAULT_INPUT;
    if (argc > 1) {
        if (string (argv[1]).compare("-h") == 0) {
            cout << "Usage: " << argv[0] << " [filename]" << endl;
            cout << "use -h for help" << endl;
            return 0;
        } else {
            filename = argv[1];
        }
    }
    Graph *graph = GraphUtils::load(filename);
    cout << "Loaded: " << endl;
    cout << *graph << endl;

    list<Node*> nodes = ((Tree*)graph)->getCover();
    cout << "Couverture min : " << nodes;

}

void test() {
    list<Node*> nodeList;
    for (int i = 0; i < 10; ++i) {
        Node *n = new Node(i);
        cout << n->getId() << endl;
        nodeList.push_back(n);
    }

    cout << nodeList.front()->getId() << endl;

/*

    Node* n1 = new Node();
    Node* n2 = new Node();

    pair<Node*, Node*>p1(n1, n2);
    pair<Node*, Node*>p2(n1, n2);

    if (p1 == p2)
        cout << "c'est bon\n";
    else
        cout << "c'est pas bon\n";


            srand((unsigned)time(0));
            for (int i=0 ; i< 200 ; i++)
                cout << rand()%101 << "\n";
            Tree t(6); // random tree with 6 vertices;
            cout << t;
            list<Node *> nodes = t.getCover();
            cout << "couverture min :" << nodes <<"\n";

            return 0;*/
}
