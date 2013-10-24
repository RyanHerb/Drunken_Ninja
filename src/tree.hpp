#include <iostream>
#include <cstdlib>
#include <list>


class Tree {

  private:
    const int label;
    std::list<Tree> children;

  public:
    Tree(int, std::list<Tree>);
    const int getLabel();
    void addChild(Tree child);
    void removeChild(Tree child);

};

bool operator==(const Tree& tree1, const Tree& tree2);
