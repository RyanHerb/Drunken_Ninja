#ifndef MINISATCONVERTER_HPP
#define MINISATCONVERTER_HPP

#include <iostream>
#include <fstream>

#include "graph.hpp"
#include "node.hpp"

void coverToMinisat(Graph*, std::string);
vector<Node*> minisatToCover(std::string);

#endif // MINISATCONVERTER_HPP
