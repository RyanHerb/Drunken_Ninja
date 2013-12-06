#include "bipartiteGraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p) {
    // tire au hasard la taille d'une partie, entre 1 et n-1
    int cut = (rand()%(n-1)) +1;

    // ajoute les noeuds
    for (int  i = 0; i < n; ++i) {
        addNode();
    }

    // ajoute des aretes entre les noeuds de parties différentes
    for (int i = 0; i < cut; i++) {
        for (int j = cut; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}
