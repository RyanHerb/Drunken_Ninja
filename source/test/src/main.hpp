#ifndef MAIN_H
#define MAIN_H

#include "rlutil.h"
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"


void assertEquals(int result, int expected);
void assertTrue(bool result);

// Node unit tests
void testNodeAddNeighbour();
void testNodeGetNeighbour();
void testNodeRemoveNeighbour();
void testNodeDegree();

// Edge unit tests
void testEdgeIdentity();


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
