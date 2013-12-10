#include <iostream>
#include <time.h>
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"

using namespace std;

const string DEFAULT_INPUT = "../Drunken_Ninja/data/tree1.txt";

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
    if (graph) {
        cout << "Loaded: " << endl << *graph << endl;
        vector<Node*> nodes = ((Tree*)graph)->getCover();
        cout << "Minimal cover: " << nodes << endl;
    }
}

/**
 * @brief Tests the identity of an edge when referenced
 *        by any permutation of two nodes.
 */
void testEdgeIdentity() {
    Node *a = new Node(1);
    Node *b = new Node(2);

    Edge *e1 = new Edge(a, b);
    Edge *e2 = new Edge(b, a);

    if (*e1 == *e2)
        cout << "Test successful" << endl;
    else
        cout << "Test failed" << endl;
}

void test3() {
    srand((unsigned)time(0));
    Graph *g = new Graph(3);
    g->addEdge(1, 2);
    g->addEdge(0, 1);
    g->addEdge(2, 0);
    cout << *g << endl;
    g->removeEdge(2, 0);
    cout << *g << endl;
    g->removeEdge(2, 0);
    cout << *g << endl;
}

void test4() {
    srand((unsigned)time(0));
    Tree t(6); // Random tree with 6 vertices;
    cout << t;
    vector<Node*> nodes = t.getCover();
    cout << "Minimal cover :" << nodes << endl;
}

