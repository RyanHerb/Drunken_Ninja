#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/bipartitegraph.hpp"

class BipartiteGraph800 : public ::hayai::Fixture {

public:
    BipartiteGraph *graph;

    virtual void SetUp() {
        this->graph = new BipartiteGraph(800, 70);
        //graph->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(BipartiteGraph800, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(BipartiteGraph800, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(BipartiteGraph800, getCoverDFS, 2, 2, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(BipartiteGraph800, getCoverMinisat, 10, 10, ()) {
    graph->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(BipartiteGraph800, getCover, ())
BENCHMARK_P_INSTANCE(BipartiteGraph800, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(BipartiteGraph800, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(BipartiteGraph800, getCoverMinisat, ())
