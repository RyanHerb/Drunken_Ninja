#include "smallcovergraph.hpp"

SmallCoverGraph::SmallCoverGraph(IGraph *g) : Graph(g) {}

SmallCoverGraph::SmallCoverGraph(int n, int p, int coverSize) {
    for (int i = 0; i < n; i++) {
        solution.push_back(addNode());
    }
    for (int i = 0; i < coverSize; i++) {
        for (int j = i+1; j < n; j++) {
            if (rand()%101 <= p)
                addEdge(i, j);
        }
    }
}

vector<Node*> SmallCoverGraph::getSolution(){
    return solution;
}

vector<int> getCoverFPT2Rec(Graph *localGraph, int k, vector<int>cover) {
    if (localGraph->nbEdges() > 0) {
        if (localGraph->nbEdges() >= k * localGraph->nbNodes()) {
            delete localGraph;
            cover.clear();
            return cover;
        } else {
            Node *node = localGraph->getHighestDegreeNode();
            Graph *localGraph1 = new Graph(localGraph);
            Graph *localGraph2 = new Graph(localGraph);
            vector<int> neighboursId;
            int nodeId = node->getId();
            for (Node *n : node->getNeighbours()) {
                neighboursId.push_back(n->getId());
            }
            delete localGraph;
            vector<int> cover1(cover);
            vector<int> cover2(cover);
            cover1.push_back(nodeId);
            localGraph1->removeNode(nodeId);
            for (int neighbId : neighboursId) {
                cover2.push_back(neighbId);
                localGraph2->removeNode(neighbId);
            }
            cover1 = getCoverFPT2Rec(localGraph1, k-1, cover1);
            cover2 = getCoverFPT2Rec(localGraph2, k-neighboursId.size(), cover2);
            if (cover2.size() == 0)
                cover2 = cover1;
            if (cover1.size() == 0)
                cover1 = cover2;
            return cover1.size() > cover2.size() ? cover2 : cover1;
        }
    } else {
        delete localGraph;
        return cover;
    }
}

vector<Node *> SmallCoverGraph::getCover(int k) {
    Graph *localGraph = new Graph(this);
    vector<int> cover;
    vector<Node*> result;

    int Kprime = localGraph->kernelize(k, &cover);
    if (localGraph->nbEdges() > Kprime * localGraph->nbNodes()) {
        cout << "nbEdges : " << localGraph->nbEdges() << endl << "Kprime*k : " << Kprime*k <<endl;
        delete localGraph;
        return result;
    } else {
        cover = getCoverFPT2Rec(localGraph, Kprime, cover);
        for (int nodeId : cover) {
            result.push_back(nodes[nodeId]);
        }
        return result;
    }
}

string SmallCoverGraph::getType() {
    return "smallcovergraph";
}
