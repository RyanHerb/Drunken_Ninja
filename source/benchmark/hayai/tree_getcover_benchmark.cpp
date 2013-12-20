#include "hayai.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "../../model/src/tree.hpp"


class TreeGetCover : public ::hayai::Fixture {

public:
    Tree *tree;

    virtual void SetUp() {
        this->tree = new Tree(20);
    }

    virtual void TearDown() {
        delete this->tree;
    }
};


BENCHMARK_P_F(TreeGetCover, getCover, 10, 100, ())
{
    tree->getCover();
}

BENCHMARK_P_INSTANCE(TreeGetCover, getCover, ());
BENCHMARK_P_INSTANCE(TreeGetCover, getCover, ());
BENCHMARK_P_INSTANCE(TreeGetCover, getCover, ());
