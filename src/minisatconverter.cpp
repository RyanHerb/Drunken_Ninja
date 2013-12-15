#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>

#include "config.h"
#include "minisatconverter.hpp"

using namespace std;

void coverToMinisat(Graph *g, string outputfile) {
    ofstream myFile;
    myFile.open(DEFAULT_DIRECTORY + outputfile);

    if(myFile.is_open()) {
        int graphSize = g->getNodes().size();
        myFile << "p cnf " << graphSize << " " << graphSize << endl;

        int literals = 0;
        for(Node* node : g->getNodes()) {
            for(Node* neighbour : node->getNeighbours()) {
                myFile << node->getId()+1 << " " << neighbour->getId()+1 << " 0" << endl;
                ++literals;
            }
        }

    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
}

vector<Node*> minisatToCover(string inputFile) {
    ifstream input;
    input.open(DEFAULT_DIRECTORY + inputFile);
    vector<Node*> negativeNodes;
    vector<Node*> positiveNodes;

    if(input.is_open()) {
        string line("");
        getline(input, line);
        getline(input, line); // read second line from file
        istringstream ss(line);
        string buffer;
        while(ss >> buffer) {
            int id = stoi(buffer);
            if(id > 0) {
                positiveNodes.push_back(new Node(id-1));
            } else if(id < 0){
                id = abs(id);
                negativeNodes.push_back(new Node(id-1));
            }
        }
    } else {
        cout << "Unable to read file, exiting" << endl;
        exit(1);
    }

    return negativeNodes.size() < positiveNodes.size() ? negativeNodes : positiveNodes;
}
