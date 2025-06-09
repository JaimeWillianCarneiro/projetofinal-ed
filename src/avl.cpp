#include "avl.h"
#include <chrono>
#include <algorithm>

using namespace std::chrono;
using namespace TREE_UTILS;


namespace AVL {

    // Retorna a altura de um nó (ou -1 se for nulo)
    int getHeight(Node* node) {
        return node ? node->height : -1;
    }

    // Atualiza a altura de um nó com base nas alturas dos filhos
    void updateHeight(Node* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    
    // Retorna o fator de balanceamento de um nó (esq - dir)
     int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }



    // Busca uma palavra na AVL e retorna se foi encontrada e em quais documentos
    SearchResult search(BinaryTree* tree, const string& word) {
         SearchResult result{0, {}, 0.0, 0};

    if (tree == nullptr || tree->root == nullptr) {
            return result;
    
    }
    auto start = high_resolution_clock::now(); // Inicia contagem de tempo

    Node* current = tree->root;
    while (current) {
        
        result.numComparisons++; // Conta cada comparação

        if (word == current->word) {
            // Palavra encontrada
            result.found = 1;
            result.documentIds = current->documentIds;
            break;
        } else if (word < current->word) {
             // Busca na subárvore esquerda
            current = current->left;
        } else {
            //  Busca na subárvore direita
            current = current->right;
        }
    }

     // Finaliza cálculo do tempo
    auto end = high_resolution_clock::now();
    result.executionTime = duration_cast<microseconds>(end - start).count() / 1000.0;

    return result;
}



    // Libera recursivamente os nós da árvore
     void destroyNode(Node* node) {
        if (!node) return;
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }

    // Libera toda a árvore AVL
    void destroy(BinaryTree* tree) {
        if (!tree) return;
        destroyNode(tree->root);
        delete tree;
    }
}



