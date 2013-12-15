#ifndef GRAPHUTILS_HPP
#define GRAPHUTILS_HPP
#include <string>
#include <vector>
#include "graph.hpp"

using namespace std;

class GraphUtils {

public:
    static Graph* load(string filename);

private:
    static vector<string>& split(string &s, char delim, vector<string> &elems);
    static vector<string> split(string &s, char delim);
};

#endif // GRAPHUTILS_HPP
