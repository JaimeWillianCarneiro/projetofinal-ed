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

    void preOrderPrint(Node* node, int height, string paths, string prefix) {
        // Stop condition
        if (node == nullptr) {
            return;
        }

        // Process father
        cout << paths << prefix << node->word << endl;
        if (prefix == "|-- ") {
            paths += "|   ";
        } else if (prefix == "*-- ") {
            paths += "    ";
        }

        prefix = "*-- ";
        // Process sons
        if (node->left != nullptr) {
            if (node->right != nullptr) {
                prefix = "|-- ";
            }
            preOrderPrint(node->left, height+1, paths, prefix);
            prefix = "*-- ";
        }
        preOrderPrint(node->right, height+1, paths, prefix);
    }
    
    // Implements pre-order transverse recursive to print Tree
    void printTree(BinaryTree* tree) {
        if (tree == nullptr) return;
        preOrderPrint(tree->root, 0, "", "");
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

}
