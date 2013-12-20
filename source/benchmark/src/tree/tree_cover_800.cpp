#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/tree.hpp"

class Tree800 : public ::hayai::Fixture {

public:
    Tree *tree;

    virtual void SetUp() {
        this->tree = new Tree(800);
    }

    virtual void TearDown() {
        delete this->tree;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(Tree800, getCover, 10, 10, ()) {
    tree->getCover();
}

BENCHMARK_P_F(Tree800, getCoverGreedy, 10, 10, ()) {
    tree->getCoverGreedy();
}

BENCHMARK_P_F(Tree800, getCoverDFS, 10, 10, ()) {
    tree->getCoverDFS();
}

BENCHMARK_P_INSTANCE(Tree800, getCover, ())
BENCHMARK_P_INSTANCE(Tree800, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(Tree800, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(Tree200, getCoverMinisat, ())
