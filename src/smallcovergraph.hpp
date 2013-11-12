#ifndef SMALLCOVERGRAPH_HPP
#define SMALLCOVERGRAPH_HPP

#include "graph.hpp"

class SmallCoverGraph : public Graph
{
public:
    SmallCoverGraph(int n, int p, int coverSize);
};

#endif // SMALLCOVERGRAPH_HPP