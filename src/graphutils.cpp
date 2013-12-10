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
        cout << "Graph: " << endl;
        cout << *graph << endl;

        while (getline(file, line)) {
            vector<string> tokens = split(line, ':');
            int from = stoi(tokens[0]);

            string nodes = tokens[1].substr(1, tokens[1].length());
            for (string node : split(nodes, ' ')) {
                int to = stoi(node);
                if (!graph->hasEdge(from, to))
                    graph->addEdge(from, to);
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
