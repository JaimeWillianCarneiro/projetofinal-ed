#include <iostream>
#include <vector>
#include <chrono>
#include "bst.h"
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace std::chrono;
using namespace TREE_UTILS;

namespace BST {
    Node* initializeNode() {
        Node* node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->height = -1;
        node->isRed = 0;
        return node;
    }

    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    InsertResult insert(BinaryTree* tree, const string& word, int documentId) {
        InsertResult insResult = InsertResult{0, 0.0};

        auto start = high_resolution_clock::now();
        if (tree == nullptr || word.empty()) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            insResult.executionTime = duration.count()/1000;
            return insResult;
        }

        // Tree haven't root
        Node* newNode = initializeNode();
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        if (tree->root == nullptr) {
            tree->root = newNode;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            insResult.executionTime = duration.count()/1000;
            return insResult;
        }

        // Apply binary search in bst until find the correct position to word.
        Node* parent = tree->root;
        Node* nextParent = nullptr;

        while (parent != nullptr) {
            insResult.numComparisons++;
            // Just update list of docs if newNodw already exists
            if (word == parent->word) {
                int indexDocId = binarySearch(parent->documentIds, documentId, 0, parent->documentIds.size()-1);
                if (indexDocId >= 0) {
                    parent->documentIds.insert(parent->documentIds.begin() + indexDocId, documentId);
                }
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - start);
                insResult.executionTime = duration.count()/1000;
                return insResult;
            } else if (word > parent->word) {
                nextParent = parent->right;
            } else {
                nextParent = parent->left;
            }
            // Break when find the correct leaf.
            if (nextParent == nullptr) {
                break;
            }
            parent = nextParent;
        }

        // Insert new node in correct position
        if (newNode->word > parent->word) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }
        newNode->parent = parent;

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        insResult.executionTime = duration.count()/1000;
        return insResult;
    }


    SearchResult search(BinaryTree* tree, const std::string& word) {
        SearchResult result{0, {}, 0.0, 0}; // Inicializa resultado vazio
    
        // Verifica árvore e palavra vazias
        if (tree == nullptr || tree->root == nullptr || word.empty()) {
            return result;
        }

        auto start = high_resolution_clock::now(); // Inicia contagem de tempo
        Node* current = tree->root;

        while (current != nullptr) {
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
                // Busca na subárvore direita
                current = current->right;
            }
        }
        
    // Finaliza cálculo do tempo

        auto end = high_resolution_clock::now();
        result.executionTime = duration_cast<microseconds>(end - start).count() / 1000.0;
        return result;
    }

    void destroyNode(Node* node) {
        if (node == nullptr) return;// Caso base da recursão

        // Destroi recursivamente subárvores
        destroyNode(node->left);
        destroyNode(node->right);
        // Libera memória do nó atual
        delete node;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return; // Verificação de segurança


        // Destrói todos os nós recursivamente
        destroyNode(tree->root);
        // Limpa ponteiros para evitar acesso acidental
        tree->root = nullptr;
        // Libera a estrutura principal da árvore
        delete tree;
    }
}