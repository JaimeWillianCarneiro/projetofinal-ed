#include <iostream>
#include <vector>
#include <chrono>
#include "bst.h"
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace std::chrono;
using namespace TREE_UTILS;

namespace BST {
    Node* initializeNode() {
        Node* node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
}