#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "graphutils.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif // _WIN32

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

void GraphUtils::write(IGraph *g, string type) {
    ofstream output;
    string filename = generateFileName(type);
    output.open(filename);

    if (output.is_open()) {
        output << g->nbNodes() << endl;
        for (Node *node : g->getNodes()) {
            output << node->getId() << ":";
            for (Node *n : node->getNeighbours()) {
                output << " " << n->getId();
            }
            output << endl;
        }
    } else {
        cout << "Error: could not open specified file." << endl;
    }
}

string GraphUtils::generateFileName(string type) {
    stringstream ss;
    ss << DEFAULT_OUTPUT_DIRECTORY << type << "-";

#ifdef _WIN32
    SYSTEMTIME st;
    GetSystemTime(&st);
    ss << st.wYear << st.wMonth << st.wDay << '-' ;
    ss << st.wHour << st.wMinute << st.wSecond << '-' << st.wMilliseconds;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    ss << tv.tv_sec << "-" << tv.tv_usec;
#endif // _WIN32

    ss << ".txt";
    return ss.str();
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
