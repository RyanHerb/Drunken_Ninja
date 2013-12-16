#include <iostream>
#include <time.h>
<<<<<<< HEAD:src/main.cpp
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"
#include "minisatconverter.hpp"
#include "config.h"

using namespace std;

=======
#include "../model/src/node.hpp"
#include "../model/src/graph.hpp"
#include "../model/src/tree.hpp"
#include "../model/src/graphutils.hpp"
#include "../model/src/smallcovergraph.hpp"

using namespace std;

const string DEFAULT_INPUT = "../../data/graph12.txt";

>>>>>>> 22004bbf77731195ff6c5c1daeec817c3aaf5619:source/app/main.cpp
int main(int argc, char *argv[]) {


    srand((unsigned)time(0));

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
        vector<Node*> nodes = graph->getCoverGlouton();
        cout << "Minimal cover: " << nodes << endl;
        cout <<"size : " << nodes.size()<<endl;
        delete graph;
    }

    Graph *g = GraphUtils::load(filename);
    if(graph) {
        cout << "Graph loaded:" << endl;
        cout << "Applying ministat convertion:" << endl;
        coverToMinisat(g, "g.cnf");
        string cmd = "minisat " + string(DEFAULT_DIRECTORY);
        cmd += "g.cnf "; cmd += string(DEFAULT_DIRECTORY); cmd += "g_res";
        system(cmd.c_str());
        vector<Node*> cover = minisatToCover("g_res");

        for(Node* n : cover) {
            cout << n->getId() << " ";
            cout << endl;
        }
        delete g;

    }
}

void testRemi1(){
    Node* A = new Node(1);
    Node* B = new Node(2);
    Node* C = new Node(3);

    Edge * e1 = new Edge(A,B);
    Edge * e2 = new Edge(B,A);

    if (*e1 == *e2)
        cout << "c'est bon"<<endl;
    else
        cout << "c'est pas bon"<<endl;
}

void testRemi2(){
    Graph*g = new Graph(3);
    g->addEdge(1,2);
    g->addEdge(0,1);
    g->addEdge(2,0);

    for (int i = 0; i < 10 ; i++){
        Edge* e= g->getRandomEdge();
        cout << *e << endl;
    }
}


void test() {
    list<Node*> nodeList;
    for (int i = 0; i < 10; ++i) {
        Node *n = new Node(i);
        cout << n->getId() << endl;
        nodeList.push_back(n);

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

