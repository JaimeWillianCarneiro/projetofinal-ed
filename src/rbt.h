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

    /**
     * @brief Busca uma palavra na RBT.
     * @param tree Ponteiro para a árvore.
     * @param word Palavra a ser buscada.
     * @return SearchResult com os resultados da busca.
     */
    SearchResult search(BinaryTree* tree, const string& word);

    /**
     * @brief Fix the color of the RBT.
     * @param tree Tree to be modified.
     * @param childNode New node created.
     * @param parent childNode's parent.
     * @param grandParentNode childNode's grand parent.
     */
    void fixInsert(BinaryTree* tree, Node* childNode, Node* parent, Node* grandParentNode);

    /**
     * @brief Check height of the RBT
     * @param node The current node (start with the root)
     * @param blackCount The current count of black nodes
     * @param expectedBlackCount The expected amount of black nodes (start with -1)
     * @return If the RBT is right
     */
    bool checkBlackHeight(Node* node, int blackCount, int& expectedBlackCount);

    /**
     * @brief Libera toda a memória da árvore RBT.
     * @param tree Ponteiro para a árvore.
     */
    void destroy(BinaryTree* tree);
}

#endif
