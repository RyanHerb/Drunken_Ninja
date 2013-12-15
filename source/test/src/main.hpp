#ifndef MAIN_H
#define MAIN_H

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

// Tree unit tests
void testTreeGen();


void assertEquals(int result, int expected) {
    if (result == expected) {
        cout << "OK" << endl;
    } else {
        cout << "FAILED :\tUnexpected result: " << result
             << ", the expected result was: " << expected << endl;
    }
}

void assertTrue(bool result) {
    if (result) {
        cout << "OK" << endl;
    } else {
        cout << "FAILED :\tCondition not verified" << endl;
    }
}
#endif // MAIN_H
