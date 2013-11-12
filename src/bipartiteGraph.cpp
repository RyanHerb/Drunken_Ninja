#include "bipartiteGraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p)
{
    for (int i=0 ; i<n ; i++){
        addNode(i);
    }
}
