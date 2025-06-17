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
    // Retorna a altura de um nó (ou -1 se for nulo)
   
    // Atualiza a altura de um nó com base nas alturas dos filhos
    void updateHeight(Node* node) {
        if(node == nullptr) return;

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
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

    void fixInsert(BinaryTree* tree, Node* z){
        while (z->parent != nullptr && z->parent->isRed == 1) {
            if (z->parent == z->parent->parent->left) { // pai é filho da esquerda
                Node* y = z->parent->parent->right; // tio
                if (y->isRed == 1) {
                    // Caso 1: pai e tio são vermelhos → sobe a instabilidade
                    z->parent->isRed = 0;
                    y->isRed = 0;
                    z->parent->parent->isRed = 1;
                    z = z->parent->parent;
                }
                //  ============== Casos de rotacionar =======================
            }    
        }
    }

    bool checkBlackHeight(Node* node, int blackCount, int& expectedBlackCount) {
    if (node == nullptr) {
        // Stop condition: got to a leaf
        if (expectedBlackCount == -1) {
            expectedBlackCount = blackCount;
            return true;
        }
        return blackCount == expectedBlackCount;
    }

    // Count the black nodes in the path
    if (node->isRed == 0) blackCount++;

    // Verify the same for the left and right
    return checkBlackHeight(node->left, blackCount, expectedBlackCount) &&
           checkBlackHeight(node->right, blackCount, expectedBlackCount);
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
        fixInsert(tree, newNode);

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

    int getUncleColor(Node* z){
        if (z == nullptr || z->parent == nullptr || z->parent->parent == nullptr){
            return -1;
        }

        // Verify if the parent is a child to the left
        if(z->parent == z->parent->parent->left){

            if(z->parent->parent->right == nullptr){
                return -1;
            } else{
                return z->parent->parent->right->isRed;
            }

        } else{
            if(z->parent->parent->left == nullptr){
                return -1;
            } else{
                return z->parent->parent->left->isRed;
            }
        }

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



