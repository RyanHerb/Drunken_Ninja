#include <iostream>
#include <time.h>
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
}
