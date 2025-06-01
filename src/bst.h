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
     * @brief Initialize a empty node.
     * @return Created node.
     */
    Node* initializeNode();

    /**
     * @brief Initialize a binary search tree.
     * @return BST created.
     */
    BinarySearchTree* create();

    /**
     * @brief Recursive Pre-Order traversal to print the node and its sons in directory format.
     * @param node Node to be processed.
     * @param height Height of the node.
     */
    void preOrderPrint(Node* node, int height);

    /**
     * @brief Print Tree in directory format.
     * @param tree BST to be printed.
     */
    void printTree(BinarySearchTree* tree);

    /**
     * @brief Insert a word in BST and update or create a list of documents where this word appears.
     * @param tree BST where to insert the word.
     * @param word Alias for the word to be inserted.
     * @param documentId Id of the document where the word was found.
     * @return Benchmark datas to analyse the complexity of BST.
     */
    InsertResult insert(BinarySearchTree* tree, const string& word, int documentId);


    /**
    * @brief Busca uma palavra na BST
    * @param tree Ponteiro para a árvore
    * @param word Palavra a ser buscada
    * @return SearchResult com resultados da busca
    */
    SearchResult search(BinarySearchTree* tree, const string& word);
    
    void destroy(BinarySearchTree* tree); // liberar memória
}

#endif