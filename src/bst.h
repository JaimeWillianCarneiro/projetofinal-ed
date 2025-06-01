// bst.h
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace TREE_UTILS;

namespace BST {
    struct Node {
        string word;
        vector<int> documentIds;
        Node* parent;
        Node* left;
        Node* right;
    };


    struct BinarySearchTree {
        Node* root;
    };

    /**
     * @brief Initialize a binary search tree.
     * @return BST created.
     */
    BinarySearchTree* create();

    InsertResult insert(BinaryTree* tree, const string& word, int documentId);

    SearchResult search(BinaryTree* tree, const string& word);
    void destroy(BinaryTree* tree); // liberar memória
}

#endif