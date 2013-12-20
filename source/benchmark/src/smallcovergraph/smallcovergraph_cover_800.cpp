#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/smallcovergraph.hpp"

class SmallCoverGraph800 : public ::hayai::Fixture {

public:
    SmallCoverGraph *graph;

    virtual void SetUp() {
        this->graph = new SmallCoverGraph(800, 70, 12);
    }

    virtual void TearDown() {
        delete this->graph;
    }
};

// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(SmallCoverGraph800, getCover, 10, 100, ()) {
    graph->getCover();
}

BENCHMARK_P_F(SmallCoverGraph800, getCoverGreedy, 10, 100, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(SmallCoverGraph800, getCoverDFS, 10, 100, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(SmallCoverGraph800, getCoverFPT, 10, 100, (int k)) {
    graph->getCoverFPT(k);
}

BENCHMARK_P_F(SmallCoverGraph800, getCoverK, 10, 100, (int k)) {
    graph->getCoverK(k);
}

BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCover, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverMinisat, ())

BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverFPT, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverFPT, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverFPT, (13))

BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverK, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverK, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph800, getCoverK, (13))
