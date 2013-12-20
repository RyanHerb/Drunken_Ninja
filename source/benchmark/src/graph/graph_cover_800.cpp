#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/graph.hpp"

class Graph800 : public ::hayai::Fixture {

public:
    Graph *graph;

    virtual void SetUp() {
        this->graph = new Graph(800, 70);
        //graph->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(Graph800, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(Graph800, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(Graph800, getCoverDFS, 2, 2, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(Graph800, getCoverMinisat, 10, 10, ()) {
    graph->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(Graph800, getCover, ())
BENCHMARK_P_INSTANCE(Graph800, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(Graph800, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(Graph800, getCoverMinisat, ())
