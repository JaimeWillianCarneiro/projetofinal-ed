// bst.h
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace TREE_UTILS;

namespace BST {
    /**
     * @brief Initialize a empty node.
     * @return Created node.
     */
    Node* initializeNode();

    /**
     * @brief Initialize a binary  tree.
     * @return BST created.
     */
    BinaryTree* create();

    /**
     * @brief Insert a word in BST and update or create a list of documents where this word appears.
     * @param tree BST where to insert the word.
     * @param word Alias for the word to be inserted.
     * @param documentId Id of the document where the word was found.
     * @return Benchmark datas to analyse the complexity of BST.
     */
    InsertResult insert(BinaryTree* tree, const string& word, int documentId);

    /**
    * @brief Busca uma palavra na BST
    * @param tree Ponteiro para a árvore
    * @param word Palavra a ser buscada
    * @return SearchResult com resultados da busca
    */
   SearchResult search(BinaryTree* tree, const string& word);
    
    
/**
 * @brief Destrói completamente uma árvore binária e libera toda a memória associada
 * @param tree Ponteiro para a árvore a ser destruída. Se nullptr, a função não tem efeito.
 * @warning Não utilize a árvore após chamar esta função
 * @note A função é segura para chamadas com nullptr
 * @see create() Para criar uma nova árvore após a destruição
 */
    void destroy(BinaryTree* tree); 
}

#endif