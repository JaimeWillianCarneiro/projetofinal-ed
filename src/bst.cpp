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

    BinarySearchTree* create() {
        // Create bst with null root node
        BinarySearchTree* bst = new BinarySearchTree;
        bst->root = nullptr;
        return bst;
    }

    void preOrderPrint(Node* node, int height) {
        // Stop condition
        if (node == nullptr) {
            return;
        }

        // Process father
        cout << string(height*2, ' ')<< "|-- " << node->word << endl;

        // Process sons
        preOrderPrint(node->left, height+1);
        preOrderPrint(node->right, height+1);
    }

    // Implements pre-order transverse recursive to print Tree
    void printTree(BinarySearchTree* tree) {
        if (tree == nullptr) {
            return;
        }

        preOrderPrint(tree->root, 0);
    }
    
}