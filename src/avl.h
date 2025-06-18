#ifndef AVL_H
#define AVL_H

#include <string>
#include "tree_utils.h"

using std::string;
using namespace TREE_UTILS;

namespace AVL {
    /**
     * @brief Initialize a empty node.
     * @return Created node.
     */
    Node* initializeNode();

    /**
     * @brief Initialize a binary tree.
     * @return AVL created.
     */
    BinaryTree* create();

    /**
     * @brief Insert a word in AVL and update or create a list of documents where this word appears.
     * @param tree BST where to insert the word.
     * @param word Alias for the word to be inserted.
     * @param documentId Id of the document where the word was found.
     * @return Benchmark datas to analyse the complexity of AVL.
     */
    InsertResult insert(BinaryTree* tree, const string& word, int documentId);

    /**
     * @brief Busca uma palavra na AVL.
     * @param tree Ponteiro para a árvore.
     * @param word Palavra a ser buscada.
     * @return SearchResult com os resultados da busca.
     */
    SearchResult search(BinaryTree* tree, const string& word);

    /**
     * @brief Libera a memória de um nó.
     * @param node Ponteiro para o nó.
     */
    void destroyNode(Node* node);

    /**
     * @brief Libera toda a memória da árvore AVL.
     * @param tree Ponteiro para a árvore.
     */
    void destroy(BinaryTree* tree);
}

#endif