#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/smallcovergraph.hpp"

class SmallCoverGraph400 : public ::hayai::Fixture {

public:
    SmallCoverGraph *graph;

    virtual void SetUp() {
        this->graph = new SmallCoverGraph(400, 70, 12);
    }

    virtual void TearDown() {
        delete this->graph;
    }
};

// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(SmallCoverGraph400, getCover, 10, 10, ()) {
    graph->getCover();
}

BENCHMARK_P_F(SmallCoverGraph400, getCoverGreedy, 10, 10, ()) {
    graph->getCoverGreedy();
}

BENCHMARK_P_F(SmallCoverGraph400, getCoverDFS, 10, 10, ()) {
    graph->getCoverDFS();
}

BENCHMARK_P_F(SmallCoverGraph400, getCoverFPT, 10, 10, (int k)) {
    graph->getCoverFPT(k);
}

BENCHMARK_P_F(SmallCoverGraph400, getCoverK, 10, 10, (int k)) {
    graph->getCoverK(k);
}

BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCover, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverGreedy, ())
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverDFS, ())
//BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverMinisat, ())

BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverFPT, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverFPT, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverFPT, (13))

BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverK, (11))
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverK, (12))
BENCHMARK_P_INSTANCE(SmallCoverGraph400, getCoverK, (13))
