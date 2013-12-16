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

    if (type.compare("graph") == 0) {
        // Graph algorithms
        Graph *graph = new Graph(g);
        vector<Node*> cover;

        if (string (argv[4]).compare("--getcover") == 0) {
            cover = graph->getCover();
        } else if (string (argv[4]).compare("--getcover-greedy") == 0) {
            cover = graph->getCoverGreedy();
        } else if (string (argv[4]).compare("--getcover-dfs") == 0) {
            cover = graph->getCoverDFS();
        }

        if (cover.size() > 0) {
            cout << "Cover size: " << cover.size() << endl;
            cout << "Cover: " << cover << endl;
        } else {
            cout << "Could not find a cover with the specified configuration." << endl;
        }

    } else if (type.compare("tree") == 0) {

    } else if (type.compare("bipartitegraph") == 0) {

    } else if (type.compare("smallcovergraph") == 0) {

    }
}

void test() {
    Graph *graph = GraphUtils::load(DEFAULT_INPUT);
    if (graph) {
        vector<Node*> cover = graph->getCover();
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

    }*/
}
