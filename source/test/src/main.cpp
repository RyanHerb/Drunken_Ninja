#include <iostream>
#include <time.h>
#include "main.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));
    rlutil::setColor(7);
    cout << "Executing unit tests" << endl << endl;

    testNodeAddNeighbour();
    testNodeGetNeighbour();
    testNodeRemoveNeighbour();
    testNodeDegree();

    cout << endl << "Finished executing tests" << endl;
}

void testNodeAddNeighbour() {
    cout << "node.addNeighbour:" << endl;
    Node *parent = new Node();
    parent->addNeighbour(new Node());
    parent->addNeighbour(new Node());
    assertEquals(parent->getNeighbours().size(), 2);
    cout << endl;
}

void testNodeGetNeighbour() {
    cout << "node.getNeighbour:" << endl;
    Node *parent = new Node();
    Node *child1 = new Node();
    Node *child2 = new Node();
    parent->addNeighbour(child1);
    parent->addNeighbour(child2);
    assertTrue(parent->getNeighbour(0) == child1);
    assertTrue(parent->getNeighbour(1) == child2);
    assertTrue(parent->getNeighbour(2) == NULL);
    assertTrue(parent->getNeighbour(-1) == NULL);
    cout << endl;
}

void testNodeRemoveNeighbour() {
    cout << "node.removeNeighbour:" << endl;
    Node *parent = new Node();
    Node *child1 = new Node();
    Node *child2 = new Node();
    parent->addNeighbour(child1);
    parent->addNeighbour(child2);
    parent->removeNeighbour(child1);
    assertEquals(parent->degree(), 1);
    cout << endl;
}

void testNodeDegree() {
    cout << "node.degree:" << endl;
    Node *parent = new Node();
    parent->addNeighbour(new Node());
    parent->addNeighbour(new Node());
    assertEquals(parent->degree(), 2);
    cout << endl;
}

void testTreeGen(){
    Tree t(6); // Random tree with 6 vertices;
    cout << t;
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
    /*Graph *graph = GraphUtils::load(filename);
    if (graph) {
        cout << "Loaded: " << endl << *graph << endl;
        vector<Node*> nodes = (graph)->getCoverFPT2(2);
        cout << "Minimal cover: " << nodes << endl;
        cout <<"size : " << nodes.size()<<endl;
        delete graph;
    }*/
    Tree t(6); // Random tree with 6 vertices;
    cout << t;
    vector<Node*> nodes = t.getCover();
    cout << "Minimal cover :" << nodes << endl;
}

