#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/bipartitegraph.hpp"

class BipartiteGraph200 : public ::hayai::Fixture {

public:
    BipartiteGraph *graph;

    virtual void SetUp() {
        this->graph = new BipartiteGraph(200, 70);
        //graph->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(BipartiteGraph200, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(BipartiteGraph200, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(BipartiteGraph200, getCoverDFS, 10, 10, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(BipartiteGraph200, getCoverMinisat, 10, 10, ()) {
    graph->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(BipartiteGraph200, getCover, ())
BENCHMARK_P_INSTANCE(BipartiteGraph200, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(BipartiteGraph200, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(BipartiteGraph200, getCoverMinisat, ())
