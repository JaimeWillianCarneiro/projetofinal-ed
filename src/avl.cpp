#include <iostream>
#include <vector>
#include <chrono>
#include "avl.h"
#include "tree_utils.h"
#include <algorithm>

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace std::chrono;
using namespace TREE_UTILS;


namespace AVL {
    Node* initializeNode() {
        Node* node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 0;
        node->isRed = 0;
        return node;
    }

    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }
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

    InsertResult insert(BinaryTree* tree, const string& word, int documentId) {
        InsertResult insResult = InsertResult{0, 0.0};
        auto start = high_resolution_clock::now();
        if (tree == nullptr) {
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
            newNode->height = 0;
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
        newNode->height = 0;

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        insResult.executionTime = duration.count()/1000;
        return insResult;
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



