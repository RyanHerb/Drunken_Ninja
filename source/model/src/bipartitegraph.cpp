#include "bipartitegraph.hpp"

BipartiteGraph::BipartiteGraph(int n, int p) {
    // tire au hasard la taille d'une partie, entre 1 et n-1
    int cut = (rand()%(n-1)) +1;

    // ajoute les noeuds
    for (int  i = 0; i < n; ++i) {
       if ((i<cut && cut <= n/2) || (i>=cut && cut >= n/2))
           solution.push_back(addNode());
       else
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

vector<Node*> BipartiteGraph::getSolution(){
    return solution;
}

string BipartiteGraph::getType() {
    return "bipartitegraph";
}
