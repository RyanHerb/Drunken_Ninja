#include "tree.hpp"

Tree::Tree(int label, list::Tree children)
  : label(label), children(children) {}

Tree::getLabel() {
  return label;
}

void Tree::addChild(Tree child) {
  children.push_back(child);
}

void Tree::removeChild(Tree child) {
  children.remove(child);
}