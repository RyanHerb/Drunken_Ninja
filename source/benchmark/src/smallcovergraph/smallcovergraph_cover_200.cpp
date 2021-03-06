#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/smallcovergraph.hpp"

class SmallCoverGraph200 : public ::hayai::Fixture {

public:
    SmallCoverGraph *graph;

    virtual void SetUp() {
        this->graph = new SmallCoverGraph(200, 70, 12);
        //graph->coverToMinisat("g.cnf");
    }

    virtual void TearDown() {
        delete this->graph;
    }
};

// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(SmallCoverGraph200, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(SmallCoverGraph200, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(SmallCoverGraph200, getCoverDFS, 10, 10, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(SmallCoverGraph200, getCoverFPT, 10, 10, (int k)) {
    graph->getCoverFPT(k);
}

BENCHMARK_P_F(SmallCoverGraph200, getCoverK, 10, 10, (int k)) {
    graph->getCoverK(k);
}

BENCHMARK_P_F(SmallCoverGraph200, getCoverMinisat, 10, 10, ()) {
    graph->minisatToCover("g_res");
}

BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCover, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverMinisat, ())

BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverFPT, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverFPT, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverFPT, (13))

BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverK, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverK, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph200, getCoverK, (13))
