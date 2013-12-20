#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/smallcovergraph.hpp"

class SmallcovergraphGetCoverFPT200 : public ::hayai::Fixture {

public:
    SmallCoverGraph *graph;

    virtual void SetUp() {
        this->graph = new SmallCoverGraph(200, 75, 12);
    }

    virtual void TearDown() {
        delete this->graph;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(SmallcovergraphGetCoverFPT200, getCoverFPT, 10, 100, (int k))
{
    graph->getCoverFPT(k);
}

BENCHMARK_P_INSTANCE(SmallcovergraphGetCoverFPT200, getCoverFPT, (11))
BENCHMARK_P_INSTANCE(SmallcovergraphGetCoverFPT200, getCoverFPT, (12))
BENCHMARK_P_INSTANCE(SmallcovergraphGetCoverFPT200, getCoverFPT, (13))
