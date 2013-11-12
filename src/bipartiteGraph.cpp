#include "bipartiteGraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p)
{
    int cut = (rand()%(n-1)) +1;
    for (int i=0 ; i<n ; i++){
        addNode(i);
    }
    for(int i=0 ; i<cut ; i++)
        for(int j=cut ; j<n ; j++){
            if (rand()%101 <= p)
                addEdge(i,j);
        }
}
