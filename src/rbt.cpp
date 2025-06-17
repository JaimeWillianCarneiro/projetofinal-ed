#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "rbt.h"
#include "tree_utils.h"
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace std::chrono;
using namespace TREE_UTILS;


namespace RBT {
    Node* initializeNode() {
        Node* node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 0;
        node->isRed = 1;
        return node;
    }

    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    int getIsRed(Node* node){
        return node != nullptr ? node->isRed : -1;
    }

    void fixInsert(BinaryTree* tree, Node* childNode, Node* parent, Node* grandParentNode){
        // Trivial cases if parent or grandParentNode are nullptr.
        if (childNode == nullptr || parent == nullptr || grandParentNode == nullptr) return;
        if (getIsRed(parent) == 0) return; // Don't need to fix.
        cout << "FIX " << childNode->word << endl;

        int grandSide = 0, firstSide = 0, secondSide = 0; // 0 - left, 1 - right (default left).
        Node* uncle = grandParentNode->right;

        // grandParentNode's father there is, for default, on it's left.
        if (grandParentNode->parent != nullptr) {
            if (grandParentNode->parent->left == grandParentNode) {
                grandSide = 1;
            }
        } else { // grandParentNode is the root.
            grandSide = -1;
        }

        // Define the side of grandParentNode's subtree where newNode was added (default is left).
        if (grandParentNode->left != parent) { 
            firstSide = 1;
            uncle = grandParentNode->left;
        }

        // Simple case of recoloring and push instability.
        if (getIsRed(uncle) == 1) {
            if (tree->root == grandParentNode) {
                parent->isRed = 0;
                uncle->isRed = 0;
                return;
            }
            parent->isRed = 0;
            uncle->isRed = 0;
            grandParentNode->isRed = 1;
            childNode = grandParentNode;
            parent = grandParentNode->parent;
            grandParentNode = parent != nullptr ? parent->parent : nullptr;
            return fixInsert(tree, childNode, parent, grandParentNode);
        }

        // Define the side of the newNode was added in parent subtree (default is left).
        if (parent->left != childNode) {
            secondSide = 1;
        }

        // If necessary, apply a second rotate.
        if (firstSide != secondSide) {
            sideRotate(parent, childNode, static_cast<int>(!firstSide), static_cast<int>(!secondSide));
            Node* temp = parent;
            parent = childNode;
            childNode = temp;
        }
        sideRotate(grandParentNode, parent, grandSide, static_cast<int>(!firstSide));
        grandParentNode->isRed = 1;
        parent->isRed = 0;
        if (grandSide == -1) tree->root = parent; // Update tree's root if parent is the root.
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
            newNode->isRed = 0;
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
            // Just update list of docs if newNode already exists
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
// ======================================= Tirei o balanceamento da AVL ==================================================
        fixInsert(tree, newNode, parent, parent->parent);
        printTree(tree);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        insResult.executionTime = duration.count()/1000;
        return insResult;
    }


    // Busca uma palavra na RBT e retorna se foi encontrada e em quais documentos
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

    // Libera toda a árvore RBT
    void destroy(BinaryTree* tree) {
        if (!tree) return;
        destroyNode(tree->root);
        delete tree;
    }
}