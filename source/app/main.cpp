#include <iostream>
#include <time.h>
#include "../model/src/node.hpp"
#include "../model/src/graph.hpp"
#include "../model/src/tree.hpp"
#include "../model/src/graphutils.hpp"
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
    if (argc > 1) {
        if (string (argv[1]).compare("-h") == 0) {
            cout << "Usage: " << argv[0] << " [filename]" << endl;
            cout << "use -h for help" << endl;
            return 0;
        } else {
            filename = argv[1];
        }
    }

    Graph *graph = GraphUtils::load(filename);
    if (graph) {
        cout << "Loaded: " << endl << *graph << endl;
        vector<Node*> nodes = graph->getCoverGlouton();
        cout << "Cover size : " << nodes.size()<<endl;
        cout << "Calculated cover: " << nodes << endl;
        delete graph;
    }
}
