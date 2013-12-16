#include <iostream>
#include <time.h>
<<<<<<< HEAD:src/main.cpp
#include "node.hpp"
#include "graph.hpp"
#include "tree.hpp"
#include "graphutils.hpp"
#include "minisatconverter.hpp"
#include "config.h"

using namespace std;

=======
#include "../model/src/node.hpp"
#include "../model/src/graph.hpp"
#include "../model/src/tree.hpp"
#include "../model/src/graphutils.hpp"
#include "../model/src/bipartitegraph.hpp"
#include "../model/src/smallcovergraph.hpp"

using namespace std;

#ifdef _WIN32
const string DEFAULT_INPUT = "../data/graph1.txt";
#else
const string DEFAULT_INPUT = "../../data/graph1.txt";
#endif //_WIN32

>>>>>>> 22004bbf77731195ff6c5c1daeec817c3aaf5619:source/app/main.cpp
int main(int argc, char *argv[]) {
    srand((unsigned)time(0));

    string filename = DEFAULT_INPUT;
    string type = "graph";
    if (argc > 1) {
        if (string (argv[1]).compare("-h") == 0) {
            cout << "Usage: " << argv[0] << " [filename] [options]" << endl << endl;
            cout << "Options:" << endl;
            cout << "-t <arg> \tType of the input graph. Can be any of the following types:" << endl;
            cout << "         \t[graph | tree | smallcovergraph | bipartitegraph]." << endl;
            return 0;
        } else {
            filename = argv[1];
        }
        if (argc == 4) {
            if (string (argv[2]).compare("-t") == 0) {
                type = argv[3];
            }
        }
    }

    Graph *graph = GraphUtils::load(filename);
    if (graph) {
        vector<Node*> cover;
        if (type.compare("tree") == 0) cover = ((Tree*)graph)->getCover();
        else cover = graph->getCover();
        cout << "Cover size : " << cover.size()<<endl;
        cout << "Calculated cover: " << cover << endl;
        delete graph;
        return 0;
    } else {
        cout << "Error loading file. Check your specified path." << endl;
    }

    Graph *g = GraphUtils::load(filename);
    if(graph) {
        cout << "Graph loaded:" << endl;
        cout << "Applying ministat convertion:" << endl;
        coverToMinisat(g, "g.cnf");
        string cmd = "minisat " + string(DEFAULT_DIRECTORY);
        cmd += "g.cnf "; cmd += string(DEFAULT_DIRECTORY); cmd += "g_res";
        system(cmd.c_str());
        vector<Node*> cover = minisatToCover("g_res");

        for(Node* n : cover) {
            cout << n->getId() << " ";
            cout << endl;
        }
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
