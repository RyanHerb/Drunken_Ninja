#ifndef BIPARTITEGRAPH_HPP
#define BIPARTITEGRAPH_HPP

class BipartiteGraph : public Graph
{
private :
    std::list<Node> partA;
    std::list<Node> partB;

public:
    BipartiteGraph(int n, int p);
};

#endif // BIPARTITEGRAPH_HPP
