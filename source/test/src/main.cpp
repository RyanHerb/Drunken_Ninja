#include <iostream>
#include <time.h>
#include "main.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));
    rlutil::setColor(7);
    cout << "Executing unit tests" << endl << endl;

    // Node tests
    testNodeAddNeighbour();
    testNodeGetNeighbour();
    testNodeRemoveNeighbour();
    testNodeDegree();

    // Edge tests
    testEdgeIdentity();

    // Graph tests
    testGraphAddEdge();
    testGraphHasEdge();
    testGraphRemoveEdge();
    testGraphGetHighestDegreeNode();

    // BipartiteGraph tests
    testBipartiteGraphInitialisePartitions();

    // Tree tests
    testTreeCover();

    cout << endl << "Finished executing tests" << endl;
}

/****************************************/
/************** Node tests **************/
/****************************************/

/**
 * @brief Tests that adding a neighbour to a node
 *        correctly updates its neighbours collection.
 */
void testNodeAddNeighbour() {
    cout << "node.addNeighbour:" << endl;
    Node *parent = new Node();
    parent->addNeighbour(new Node());
    parent->addNeighbour(new Node());
    assertEquals(parent->getNeighbours().size(), 2);
    cout << endl;
}

/**
 * @brief Tests that a node's neighbours can be correctly
 *        retrieved by their insertion order.
 */
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

/**
 * @brief Tests that removing a node's neighbour
 *        correctly updates its degree.
 */
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

/**
 * @brief Tests that a node's degree is equal to
 *        the sum of its neighbours.
 */
void testNodeDegree() {
    cout << "node.degree:" << endl;
    Node *parent = new Node();
    parent->addNeighbour(new Node());
    parent->addNeighbour(new Node());
    assertEquals(parent->degree(), 2);
    cout << endl;
}

/****************************************/
/************** Edge tests **************/
/****************************************/

/**
 * @brief Tests the identity of an edge when referenced
 *        by both permutations of its underlying nodes.
 */
void testEdgeIdentity() {
    cout << "edge.identity:" << endl;
    Node *a = new Node(1);
    Node *b = new Node(2);

    Edge *e1 = new Edge(a, b);
    Edge *e2 = new Edge(b, a);

    assertTrue(*e1 == *e2);
    cout << endl;
}

/****************************************/
/************* Graph tests **************/
/****************************************/

/**
 * @brief Tests that adding edges between a graph's nodes
 *        correctly updates its edges collection.
 */
void testGraphAddEdge() {
    cout << "graph.addEdge:" << endl;
    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    g->addEdge(2, 0);
    assertEquals(g->getEdges().size(), 3);
    cout << endl;
}

/**
 * @brief Tests that Graph::hasEdge(int,int) correctly
 *        indicates whether an edge exists between two nodes.
 */
void testGraphHasEdge() {
    cout << "graph.hasEdge:" << endl;
    Graph *g = new Graph(2);
    g->addEdge(0, 1);
    assertTrue(g->hasEdge(0, 1));
    assertTrue(!g->hasEdge(0, 2));
    cout << endl;
}

/**
 * @brief Tests that removing an edge from a graph
 *        correctly updates its state.
 */
void testGraphRemoveEdge() {
    cout << "graph.removeEdge:" << endl;
    Graph *g = new Graph(2);
    g->addEdge(0, 1);
    g->removeEdge(0, 1);
    assertTrue(!g->hasEdge(0, 1));
    cout << endl;
}

/**
 * @brief Tests that Graph::getHighestDegreeNode() returns
 *        the node with the highest degree in the calling graph.
 */
void testGraphGetHighestDegreeNode() {
    cout << "graph.getHighestDegreeNode:" << endl;
    Graph *g = new Graph(4);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    g->addEdge(2, 0);
    g->addEdge(0, 3);
    Node *node = g->getHighestDegreeNode();
    assertEquals(node->getId(), 0);
    assertEquals(node->degree(), 3);
    cout << endl;
}

/**
 * @brief Tests that BipartiteGraph::InitialisePartitions()
 *        initialise correctly left and right partitions.
 */
void testBipartiteGraphInitialisePartitions() {
    cout << "bipartiteGraph.initialisePartitions:" << endl;
    Graph * g = new Graph(4);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    BipartiteGraph * bg = new BipartiteGraph(g);
    bg->initialisePartitions();
    assertEquals(bg->getLeftPartition()[0]->getId(), 0);
    assertEquals(bg->getRightPartition().size(), 3);
    cout << endl;
}

/****************************************/
/************** Tree tests **************/
/****************************************/

/**
 * @brief Tests that Tree::getCover() returns
 *        a minimal cover.
 */
void testTreeCover() {
    cout << "tree.getCover:" << endl;
#ifdef _WIN32
    string input = "../data/tree1.txt";
#else
    string input = "../../data/tree1.txt";
#endif // _WIN32

    Graph *graph = GraphUtils::load(input);
    if (graph) {
        Tree *t = new Tree(graph);
        vector<Node*> nodes = t->getCover();
        assertEquals(nodes.size(), 2);
        assertTrue(nodes.at(0)->getId() == 1);
        assertTrue(nodes.at(1)->getId() == 4);
        delete graph;
        delete t;
    }
    cout << endl;
}
