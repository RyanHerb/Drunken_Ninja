#ifndef MAIN_H
#define MAIN_H

#include "rlutil.h"
#include "node.hpp"
#include "graph.hpp"
#include "bipartitegraph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"

// Node unit tests
void testNodeAddNeighbour();
void testNodeGetNeighbour();
void testNodeRemoveNeighbour();
void testNodeDegree();

// Edge unit tests
void testEdgeIdentity();

// Graph unit tests
void testGraphAddEdge();
void testGraphHasEdge();
void testGraphRemoveEdge();
void testGraphGetHighestDegreeNode();
void testGraphCover();

// BipartiteGraph unit tests
void testBipartiteGraphInitialisePartitions();

// Tree unit tests
void testTreeCover();


void assertValidCover(IGraph *graph, vector<Node*> cover) {
    IGraph *g = new Graph(graph);
    for (Node *node : cover) {
        g->removeNode(node);
    }
    if (g->nbEdges() == 0) {
        rlutil::setColor(2);
        cout << "OK" << endl;
        rlutil::setColor(7);
    } else {
        rlutil::setColor(12);
        cout << "FAILED :  The provided cover is not a valid solution." << endl;
        rlutil::setColor(7);
    }
    delete g;
}

void assertEquals(int result, int expected) {
    if (result == expected) {
        rlutil::setColor(2);
        cout << "OK" << endl;
        rlutil::setColor(7);
    } else {
        rlutil::setColor(12);
        cout << "FAILED :  Unexpected result: " << result
             << ", the expected result was: " << expected << endl;
        rlutil::setColor(7);
    }
}

void assertTrue(bool result) {
    if (result) {
        rlutil::setColor(2);
        cout << "OK" << endl;
        rlutil::setColor(7);
    } else {
        rlutil::setColor(12);
        cout << "FAILED :  Condition not verified" << endl;
        rlutil::setColor(7);
    }
}
#endif // MAIN_H
