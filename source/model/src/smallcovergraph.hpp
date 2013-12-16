#ifndef SMALLCOVERGRAPH_HPP
#define SMALLCOVERGRAPH_HPP

#include "graph.hpp"

class SmallCoverGraph : public Graph
{
private:
    vector<Node*> solution;
public:
    SmallCoverGraph(int n, int p, int coverSize);
    SmallCoverGraph(IGraph *g);
    vector<Node*>getCoverK(int k);
    vector<Node*>getCoverFPT(int k);
    vector<Node*>getSolution();
    string getType();
};

#endif // SMALLCOVERGRAPH_HPP
