#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h"

using std::string;
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
     * @brief Rotate parent and son in a specific side.
     * @param parent Parent of relashionship.
     * @param son Son of relashionship.
     * @param grandSide Parent's where the grandFather is.
     * @param rotateSide Side to apply rotate.
     */
    void sideRotate(Node* parent, Node* son, int grandSide, int rotateSide);

    /**
     * @brief Insert a word in RBT and update or create a list of documents where this word appears.
     * @param tree BST where to insert the word.
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
     * @brief Fix the color of the RBT
     * @param root Pointer to the tree
     * @param z Inserted node
     */
    void fixInsert(BinaryTree* tree, Node* z);

    /**
     * @brief Checks the color of the uncle of the node 
     * @param z Node you want to check
     * @return -1 if it doesnt have an uncle, 0 if black, 1 if red 
     */
    int getUncleColor(Node* z);

    /**
     * @brief Libera toda a memória da árvore RBT.
     * @param tree Ponteiro para a árvore.
     */
    void destroy(BinaryTree* tree);
}

#endif
