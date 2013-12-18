#include <iostream>
#include <time.h>

#include "../model/src/node.hpp"
#include "../model/src/graph.hpp"
#include "../model/src/tree.hpp"
#include "../model/src/graphutils.hpp"
#include "../model/src/bipartitegraph.hpp"
#include "../model/src/smallcovergraph.hpp"
#include "config.h"

using namespace std;

void test();
void handleGraphGeneration(char *argv[]);
void handleAlgorithmSelection(char *argv[]);

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));

    if (argc > 1) {
        if (string (argv[1]).compare("-h") == 0) {
            cout << "Usage: " << argv[0] << " [filename] [options]" << endl << endl;
            cout << "Options:" << endl;
            cout << "-t <arg> \tType of the input graph. Can be any of the following types:" << endl;
            cout << "         \t[graph | tree | bipartitegraph | smallcovergraph]." << endl;
            return 0;
        } else if (string (argv[1]).compare("--generate") == 0) {
            handleGraphGeneration(argv);
        } else {
            handleAlgorithmSelection(argv);
        }
    }
    //test();
    return 0;
}

void handleGraphGeneration(char *argv[]) {
    string type = argv[2];
    IGraph *graph = NULL;
    if (type.compare("tree") == 0) {
        graph = new Tree(atoi(argv[3]));
    } else if (type.compare("graph") == 0) {
        graph = new Graph(atoi(argv[3]), atoi(argv[4]));
    } else if (type.compare("bipartitegraph") == 0) {
        graph = new BipartiteGraph(atoi(argv[3]), atoi(argv[4]));
    } else if (type.compare("smallcover") == 0) {
        graph = new SmallCoverGraph(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }

    if (graph) {
        GraphUtils::write(graph, type);
        cout << "Successfully generated " << type << endl;
    } else {
        cerr << "Error: incorrect parameters. Use the -h option for more information." << endl;
    }
}

void handleAlgorithmSelection(char *argv[]) {
    string input = argv[1];
    string type = argv[3];
    IGraph *g = GraphUtils::load(input);
    vector<Node*> cover;

    IGraph *graph;
    if (type.compare("graph") == 0) {
        graph = new Graph(g);
    } else if (type.compare("tree") == 0) {
        graph = new Tree(g);
    } else if (type.compare("bipartitegraph") == 0) {
        graph = new BipartiteGraph(g);
    } else if (type.compare("smallcovergraph") == 0) {
        graph = new SmallCoverGraph(g);
    }

    if (string (argv[4]).compare("--getcover") == 0) {
        cover = graph->getCover();
    } else if (string (argv[4]).compare("--getcover-greedy") == 0) {
        cover = graph->getCoverGreedy();
    } else if (string (argv[4]).compare("--getcover-dfs") == 0) {
        cover = graph->getCoverDFS();
    } else if (string (argv[4]).compare("--getcover-minisat") == 0) {
        cover = graph->getKCoverWithMinisat(atoi(argv[5]));
    } else if (type.compare("smallcovergraph") == 0) {
        if (string (argv[4]).compare("--getcover-k") == 0) {
            cover = ((SmallCoverGraph*)graph)->getCoverK(atoi(argv[5]));
        } else if (string (argv[4]).compare("--getcover-fpt") == 0) {
            cover = ((SmallCoverGraph*)graph)->getCoverFPT(atoi(argv[5]));
        }
    }

    if (cover.size() > 0) {
        cout << "Cover size: " << cover.size() << endl;
        cout << "Cover: " << cover << endl;
    } else {
        cout << "Could not find a cover with the specified configuration." << endl;
    }
}

void test() {
    Graph *graph = GraphUtils::load(DEFAULT_INPUT);
    if (graph) {
        vector<Node*> cover;
        if (type.compare("tree") == 0) cover = ((Tree*)graph)->getCover();
        else cover = graph->getKCover(13);
        cout << "Cover size : " << cover.size()<<endl;
        cout << "Calculated cover: " << cover << endl;
        delete graph;
        //return 0;
    } else {
        cout << "Error loading file. Check your specified path." << endl;
    }

    /*Graph *g = GraphUtils::load(filename);
    if(g) {
        cout << "Graph loaded:" << endl;
        cout << "Applying ministat convertion:" << endl;
        g->coverToMinisat("g.cnf");
        string cmd = "minisat " + string(DEFAULT_DIRECTORY);
        cmd += "g.cnf "; cmd += string(DEFAULT_DIRECTORY); cmd += "g_res";
        system(cmd.c_str());
        vector<Node*> cover = g->minisatToCover("g_res");

        for(Node* n : cover) {
            cout << n->getId() << " ";
        }
        cout << endl;
        delete g;
    }

    Graph *g = new Graph(4, 100);
    for(Node* n : g->getNodes()) {
        cout << n->getId() << ":";
        for(Node* neighbour : n->getNeighbours()) {
            cout << " " << neighbour->getId();
        }
        cout << endl;
    }*/

    Graph *g = GraphUtils::load(filename);

    if(g) {
        vector<Node*> cover;
        cover = g->getKCoverWithMinisat(2);

        cout << "cover: ";
        for(Node* n : cover) {
            cout << n->getId() << " ";
        }
        cout << endl;
        cout << "Size: " << cover.size() << endl;
        delete g;
    }
}



void testRemi1(){
    Node* A = new Node(1);
    Node* B = new Node(2);
    Node* C = new Node(3);

    Edge * e1 = new Edge(A,B);
    Edge * e2 = new Edge(B,A);

    if (*e1 == *e2)
        cout << "c'est bon"<<endl;
    else
        cout << "c'est pas bon"<<endl;
}

void testRemi2(){
    Graph*g = new Graph(3);
    g->addEdge(1,2);
    g->addEdge(0,1);
    g->addEdge(2,0);

    for (int i = 0; i < 10 ; i++){
        Edge* e= g->getRandomEdge();
        cout << *e << endl;
    }
}


void test() {
    list<Node*> nodeList;
    for (int i = 0; i < 10; ++i) {
        Node *n = new Node(i);
        cout << n->getId() << endl;
        nodeList.push_back(n);
    }
}
