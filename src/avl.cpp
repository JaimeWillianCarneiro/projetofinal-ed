#ifndef AVL_H
#define AVL_H

#include <string>
#include "tree_utils.h"

using std::string;
using namespace TREE_UTILS;

namespace AVL {

    /**
     * @brief Cria uma árvore AVL vazia.
     * @return Ponteiro para a árvore criada.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore AVL e atualiza ou cria a lista de documentos onde essa palavra aparece.
     * @param tree Árvore AVL onde a palavra será inserida.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento onde a palavra foi encontrada.
     * @return Dados de benchmark para análise de desempenho.
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
     * @brief Libera toda a memória da árvore AVL.
     * @param tree Ponteiro para a árvore.
     */
    void destroy(BinaryTree* tree);

}

#endif
