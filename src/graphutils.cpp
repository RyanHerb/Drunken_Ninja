#include "graphutils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Graph* GraphUtils::load(string filename) {
    cout << "Loading file: " << filename << endl;
    ifstream file(filename);
    if (file) {
        string line;
        getline(file, line);
        Graph *graph = new Graph(stoi(line));
        while (getline(file, line)) {
            vector<string> tokens = split(line, ':');
            if (tokens.size() == 2) {
                int from = stoi(tokens[0]);
                string adj = tokens[1];
                string nodes = adj.substr(1, adj.length());
                for (string node : split(nodes, ' ')) {
                    int to = stoi(node);
                    if (!graph->hasEdge(from, to))
                        graph->addEdge(from, to);
                }
            }
        }

        return graph;
    } else {
        cout << "Error reading file" << endl;
        return NULL;
    }
}

vector<string>& GraphUtils::split(string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> GraphUtils::split(string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
