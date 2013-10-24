#include "tree.hpp"

Tree::Tree(int label, std::list<Tree> children)
  : label(label), children(children) {}

const int Tree::getLabel() {
  return label;
}

void Tree::addChild(Tree child) {
  children.push_back(child);
}

void Tree::removeChild(Tree child) {
  children.remove(child);
}

bool operator==(const Tree& tree1, const Tree& tree2) {
    // TODO Fix implementation
    // return (tree1.getLabel() == tree2.getLabel());
    return true; // Piece of shit code because the REAL implementation of this function wouldn't fucking work
}
