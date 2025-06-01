#include <iostream>
#include <vector>
#include <string>
#include "tree_utils.h"

using std::cout, std::endl;

namespace TREE_UTILS {

    // Função auxiliar para fazer in-order traversal e imprimir cada nó
    void printIndexInOrder(Node* node) {
        if (node == nullptr) return;

        // Esquerda
        printIndexInOrder(node->left);

        // Imprime palavra e lista de documentos
        cout << node->word << ": ";
        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            cout << node->documentIds[i];
            if (i != node->documentIds.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        // Direita
        printIndexInOrder(node->right);
    }

    // Função pública para imprimir o índice completo
    void printIndex(BinaryTree* tree) {
        if (tree == nullptr || tree->root == nullptr) {
            cout << "Árvore vazia." << endl;
            return;
        }
        printIndexInOrder(tree->root);
    }



    int binarySearch(vector<int> documentIds, int docId, int start, int end) {
        // Stop condition.
        if (start > end) {
            return start;
        }

        int mid = (start + end) / 2;
        if (docId == documentIds[mid]) {
            return -1;
        }else if (docId > documentIds[mid]) {
            return binarySearch(documentIds, docId, mid+1, end);
        } else {
            return binarySearch(documentIds, docId, start, mid-1);
        }
    }

     void freeTree(Node* node) {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}
