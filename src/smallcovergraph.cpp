#include "smallcovergraph.hpp"

SmallCoverGraph::SmallCoverGraph(int n, int p, int coverSize)
{
    for (int i=0 ; i<n ; i++) {
        addNode();
    }
    for (int i=0 ; i<coverSize ; i++)
        for (int j=i+1 ; j<n ; j++){
            if (rand()%101 <= p)
                addEdge(i,j);
        }
}
