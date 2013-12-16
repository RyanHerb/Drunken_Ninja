#ifndef SMALLCOVERGRAPH_HPP
#define SMALLCOVERGRAPH_HPP

#include "graph.hpp"

class SmallCoverGraph : public Graph
{
private:
    vector<Node*> solution;
public:
    SmallCoverGraph(int n, int p, int coverSize);
    SmallCoverGraph(SmallCoverGraph *g);
    vector<Node*>getCover(int K);
    vector<Node*>getSolution();
};

#endif // SMALLCOVERGRAPH_HPP
