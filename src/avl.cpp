#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "avl.h"
#include "tree_utils.h"
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

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
        if(node == nullptr) return;

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    
    // Retorna o fator de balanceamento de um nó (esq - dir)
     int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void sideRotate(Node* parent, Node* son, int grandSide, int rotateSide) {
        if (parent == nullptr || son == nullptr) return;

        // Swap son and parent, making the parent inherit the grandchildren on the opposite side of the rotation.
        if (rotateSide == 0) {
            parent->right = son->left;
            if (parent->right != nullptr) parent->right->parent = parent;
            son->left = parent;
        } else {
            parent->left = son->right;
            if (parent->left != nullptr) parent->left->parent = parent;
            son->right = parent;
        }
        // The parent's parent inherit the son as his son.
        son->parent = parent->parent;
        if (grandSide == 0) {
            son->parent->right = son;
        } else if (grandSide == 1) {
            son->parent->left = son;
        }
        parent->parent = son;
        // Update height of nodes.
        updateHeight(parent);
        updateHeight(son);
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
        newNode->height = 0;
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

        // Insert new node in correct position.
        if (newNode->word > parent->word) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }
        newNode->parent = parent;

        // Update height until find first imbalance Node.
        Node* nodeUpdateHeight = parent;
        Node* firstImbalanceNode = nullptr;
        int balanceFactor = getBalanceFactor(nodeUpdateHeight);
        while (balanceFactor != 0 && firstImbalanceNode == nullptr) { // When balanceFactor is zero, the add of newNode doesn't alter the height of nodeUpdateHeight and it's parents.
            // When find the first imbalance, the height of its parents doesnt change after rotate.
            if ((balanceFactor) / 2 != 0) {  // Balance factors(0 or 1) / 2 = round(x), with x < 1, them round(x) = 0.
                firstImbalanceNode = nodeUpdateHeight;
                break;
            }
            nodeUpdateHeight->height++;
            nodeUpdateHeight = nodeUpdateHeight->parent;
            if (nodeUpdateHeight == nullptr) break; // Find root -> stop.
            balanceFactor = getBalanceFactor(nodeUpdateHeight);
        }

        // Apply rotate if necessary
        if (firstImbalanceNode != nullptr) {
            int grandSide = 0, firstSide = 0, secondSide = 0; // 0 - left, 1 - right (default left).
            
            // firstImbalanceNode father there is, for default, on it's left.
            if (firstImbalanceNode->parent != nullptr) {
                if (firstImbalanceNode->parent->left == firstImbalanceNode) grandSide = 1;
            } else { //firstImbalanceNode is the root.
                grandSide = -1;
            }

            // Define the side of firsImbalance subtree where newNode was added (default is left).
            Node* sonToRotate = firstImbalanceNode->left;
            if (getBalanceFactor(firstImbalanceNode) < 0) { 
                firstSide = 1;
                sonToRotate = firstImbalanceNode->right;
            }

            // Define the side of the newNode was added in firstImbalanceNode subtree (default is left).
            Node* grandChildToRotate = sonToRotate->left;
            if (getBalanceFactor(sonToRotate) < 0) {
                secondSide = 1;
                grandChildToRotate = sonToRotate->right;
            }

            // If necessary, apply a second rotate.
            if (firstSide != secondSide) {
                sideRotate(sonToRotate, grandChildToRotate, static_cast<int>(!firstSide), static_cast<int>(!secondSide));
                Node* temp = sonToRotate;
                sonToRotate = grandChildToRotate;
                grandChildToRotate = temp;
            }
            sideRotate(firstImbalanceNode, sonToRotate, grandSide, static_cast<int>(!firstSide));
            if (grandSide == -1) tree->root = sonToRotate; // Update tree's root if firstImbalanceNode is the root.
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        insResult.executionTime = duration.count()/1000;
        return insResult;
    }


    // Busca uma palavra na AVL e retorna se foi encontrada e em quais documentos
    SearchResult search(BinaryTree* tree, const string& word) {
        SearchResult result{0, {}, 0.0, 0};

        if (tree == nullptr || tree->root == nullptr || word.empty()) {
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



