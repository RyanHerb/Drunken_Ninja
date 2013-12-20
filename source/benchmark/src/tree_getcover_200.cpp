#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "hayai/hayai.hpp"
#include "../../model/src/tree.hpp"

class TreeGetCover200 : public ::hayai::Fixture {

public:
    Tree *tree;

    virtual void SetUp() {
        this->tree = new Tree(200);
    }

    virtual void TearDown() {
        delete this->tree;
    }
};


// Parameters: fixture, method, runs, iterations, arguments
BENCHMARK_P_F(TreeGetCover200, getCover, 10, 100, ())
{
    tree->getCover();
}

BENCHMARK_P_INSTANCE(TreeGetCover200, getCover, ())
