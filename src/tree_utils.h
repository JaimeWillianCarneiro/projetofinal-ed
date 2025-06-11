#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>
#include <climits>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace TREE_UTILS {
    struct Node {
        std::string word;
        std::vector<int> documentIds;
        Node* parent;
        Node* left;
        Node* right;
        int height;   // Usado na AVL
        int isRed;    // Usado na RBT
    };

    struct BinaryTree {
        Node* root;
        Node* NIL; // Usado na RBT (não necessário para BST)
    };

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
    void printTree(BinaryTree* tree);

    struct InsertResult {
        int numComparisons;
        double executionTime;
        // <Possíveis outras variáveis>
    };
    
    struct SearchResult {
        int found;
        std::vector<int> documentIds;
        double executionTime;
        int numComparisons;
        // <Possíveis outras variáveis>
    };

    /**
 * @brief Realiza busca binária em um vetor de IDs de documentos
 * @param documentIds Vetor de IDs de documentos onde a palavra aparece
 * @param docId ID do documento a ser buscado
 * @param start Índice inicial do intervalo de busca
 * @param end Índice final do intervalo de busca
 * @return int Retorna:
 *            - A posição onde o ID deveria ser inserido (se não encontrado)
 *            - -1 se o ID já existe no vetor
 * 
 * @note Função auxiliar usada durante a inserção de documentos
 */
    int binarySearch(std::vector<int> documentIds, int docId, int start, int end);



/**
 * @brief Realiza um percurso em-ordem (in-order traversal) na árvore para imprimir as palavras e seus documentos associados
 * @param node Nó raiz da subárvore a ser impressa (pode ser nullptr)
 * @details Esta função auxiliar recursiva percorre a árvore em ordem alfabética (esquerda-raiz-direita) e para cada nó encontrado:
 *          1. Imprime a palavra do nó
 *          2. Imprime a lista de IDs de documentos onde a palavra aparece, separados por vírgulas
 *          3. Coloca cada entrada em uma nova linha
 * @pre Caso o parâmetro node seja nullptr, a função retorna silenciosamente
 * @post Não modifica a estrutura da árvore ou seus dados
 * @note Formato de saída:
 *       palavra1: id1, id2, id3
 *       palavra2: id1, id4
 *       palavra3: id5
 */
    void printIndexInOrder(Node* node);

    /**
 * @brief Imprime todo o índice invertido em ordem alfabética
 * @param tree Ponteiro para a árvore binária contendo o índice
 * @details Percorre a árvore em ordem (in-order traversal) e para cada nó imprime:
 *          - A palavra
 *          - Lista de IDs de documentos onde a palavra aparece
*/
    void printIndex(BinaryTree* tree);

}

#endif // TREE_UTILS_H