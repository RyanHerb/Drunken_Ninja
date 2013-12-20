#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/tree.hpp"

class Tree400 : public ::hayai::Fixture {

public:
    Tree *tree;

    virtual void SetUp() {
        this->tree = new Tree(400);
    }

    virtual void TearDown() {
        delete this->tree;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(Tree400, getCover, 10, 100, ()) {
    tree->getCover();
}

BENCHMARK_P_F(Tree400, getCoverGreedy, 10, 100, ()) {
    tree->getCoverGreedy();
}

BENCHMARK_P_F(Tree400, getCoverDFS, 10, 100, ()) {
    tree->getCoverDFS();
}

BENCHMARK_P_INSTANCE(Tree400, getCover, ())
BENCHMARK_P_INSTANCE(Tree400, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(Tree400, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(Tree200, getCoverMinisat, ())
