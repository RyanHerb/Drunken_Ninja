#include <iostream>
#include <time.h>
#include "main.hpp"

using namespace std;

//const string DEFAULT_INPUT = "../Drunken_Ninja/data/tree1.txt";

int main(int argc, char *argv[]) {

    srand((unsigned)time(0));
    cout << "Executing unit tests" << endl;
    testTreeGene();

    cout << "Finished executing tests" << endl;

    /*string filename = DEFAULT_INPUT;

    Graph *graph = GraphUtils::load(filename);
    if (graph) {
        cout << "Loaded: " << endl << *graph << endl;
        vector<Node*> nodes = (graph)->getCoverFPT2(2);
        cout << "Minimal cover: " << nodes << endl;
        cout <<"size : " << nodes.size()<<endl;
        delete graph;
    }*/
}

void assertEquals(int result, int expected) {
    if (result != expected) {
        cout << "FAILED :" << "\tUnexpected result: " << result
             << ", the expected result was: " << expected << endl;
    } else {
        cout << "OK" << endl;
    }
}

void testTreeGene(){
    Tree t(6); // Random tree with 6 vertices;
    cout << t;
}

void testNodeAddNeighbour() {
    Node *parent = new Node();
    parent->addNeighbour(new Node());
    parent->addNeighbour(new Node());
    assertEquals(parent->degree(), 2);
}


void testRemi2(){
    Graph *g = new Graph(3);
    g->addEdge(1,2);
    g->addEdge(0,1);
    g->addEdge(2,0);

    for (int i = 0; i < 10 ; i++){
        Edge* e= g->getRandomEdge();
        cout << *e << endl;
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
    Tree t(6); // Random tree with 6 vertices;
    cout << t;
    vector<Node*> nodes = t.getCover();
    cout << "Minimal cover :" << nodes << endl;
}

