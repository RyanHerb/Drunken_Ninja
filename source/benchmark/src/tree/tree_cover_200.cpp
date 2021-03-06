#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/tree.hpp"

class Tree200 : public ::hayai::Fixture {

public:
    Tree *tree;

    virtual void SetUp() {
        this->tree = new Tree(200);
        //tree->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->tree;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(Tree200, getCover, 10, 10, ()) {
    tree->getCover();
}

BENCHMARK_P_F(Tree200, getCoverGreedy, 10, 10, ()) {
    tree->getCoverGreedy();
}

BENCHMARK_P_F(Tree200, getCoverDFS, 10, 10, ()) {
    tree->getCoverDFS();
}

BENCHMARK_P_F(Tree200, getCoverMinisat, 10, 10, ()) {
    tree->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(Tree200, getCover, ())
BENCHMARK_P_INSTANCE(Tree200, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(Tree200, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(Tree200, getCoverMinisat, ())
