#include <iostream>
#include "rbt.h"
#include "tree_utils.h"
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace RBT;
using namespace TREE_UTILS;

int main() {
    BinaryTree* tree = create();

    string includes[] = {"3", "1", "5", "0", "2", "4", "6"};
    for (int eachI = 0; eachI < 7; eachI++) {
        insert(tree, includes[eachI], 0);
    }
    printTree(tree);
    return 0;
}