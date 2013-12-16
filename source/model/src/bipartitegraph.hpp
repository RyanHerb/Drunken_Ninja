#ifndef BIPARTITEGRAPH_HPP
#define BIPARTITEGRAPH_HPP

#include "graph.hpp"

class BipartiteGraph : public Graph {

private:
    //contient une couverture qui peut ne pas etre optimale
    vector<Node*> solution;
public:
    BipartiteGraph(int n, int p);
    vector<Node*> getSolution();
    string getType();
};

#endif // BIPARTITEGRAPH_HPP
