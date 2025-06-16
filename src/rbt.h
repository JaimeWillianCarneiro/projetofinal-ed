// rbt.h
#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <vector>
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace TREE_UTILS;

namespace RBT {
    /**
     * @brief Initialize a empty node.
     * @return Created node.
     */
    Node* initializeNode();

    /**
     * @brief Initialize a binary tree.
     * @return RBT created.
     */
    BinaryTree* create();

    /**
     * @brief Insert a word in RBT and update or create a list of documents where this word appears.
     * @param tree RBT where to insert the word.
     * @param word Alias for the word to be inserted.
     * @param documentId Id of the document where the word was found.
     * @return Benchmark datas to analyse the complexity of RBT.
     */
    InsertResult insert(BinaryTree* tree, const string& word, int documentId);
}

#endif