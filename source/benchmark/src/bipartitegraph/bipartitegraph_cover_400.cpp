#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/bipartitegraph.hpp"

class BipartiteGraph400 : public ::hayai::Fixture {

public:
    BipartiteGraph *graph;

    virtual void SetUp() {
        this->graph = new BipartiteGraph(400, 70);
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(BipartiteGraph400, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(BipartiteGraph400, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(BipartiteGraph400, getCoverDFS, 10, 10, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_INSTANCE(BipartiteGraph400, getCover, ())
BENCHMARK_P_INSTANCE(BipartiteGraph400, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(BipartiteGraph400, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(BipartiteGraph400, getCoverMinisat, ())
