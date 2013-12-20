#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/graph.hpp"

class Graph200 : public ::hayai::Fixture {

public:
    Graph *graph;

    virtual void SetUp() {
        this->graph = new Graph(200, 70);
        //graph->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(Graph200, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(Graph200, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(Graph200, getCoverDFS, 10, 10, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(Graph200, getCoverMinisat, 10, 10, ()) {
    graph->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(Graph200, getCover, ())
BENCHMARK_P_INSTANCE(Graph200, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(Graph200, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(Graph200, getCoverMinisat, ())
