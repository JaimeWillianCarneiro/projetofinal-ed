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

    void preOrderPrint(Node* node, int height, string paths, string prefix) {
        // Stop condition
        if (node == nullptr) {
            return;
        }

        // Process father
        string RED = "\033[31m";
        string BLACK = "\033[30m";
        string RESET = "\033[0m";
        if (node->isRed == 1) cout << paths << prefix << RED << node->word << RESET << endl;
        else cout << paths << prefix << BLACK << node->word << RESET << endl;
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

    int getIsRed(Node* node){
        return node != nullptr ? node->isRed : -1;
    }

    void fixInsert(BinaryTree* tree, Node* childNode, Node* parent, Node* grandParentNode){
        // Trivial cases if parent or grandParentNode are nullptr.
        if (childNode == nullptr || parent == nullptr || grandParentNode == nullptr) return;
        if (getIsRed(parent) == 0) return; // Don't need to fix.

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

    // Verifica se a altura preta eh constante em todo no nos caminhos ate uma folha
    bool validBlackHeight(Node* node) {
        if (!node) return true;

        int expectedBlackCount = -1;
        if (!checkBlackHeight(node, 0, expectedBlackCount))
            return false;

        return validBlackHeight(node->left) &&
            validBlackHeight(node->right);
    }

    // Verifica se algum no vermelho tem filho vermelho
    bool noDoubleRed(Node* node) {
        if (!node) return true;
        if (node->isRed == 1) {
            if ((node->left && node->left->isRed == 1) ||
                (node->right && node->right->isRed == 1))
                return false;
        }
        return noDoubleRed(node->left) && noDoubleRed(node->right);
    }

    // Verifica se arvore eh uma Red Black Tree valida
    bool isValidRBT(BinaryTree* tree) {
        if (!tree || !tree->root) return true;

        // Propriedade: raiz deve ser preta
        if (tree->root->isRed == 1)
            return false;

        // Propriedade: nenhum no vermelho tem filho vermelho
        if (!noDoubleRed(tree->root))
            return false;

        // Propriedade: todos os nos tem altura preta constante nos caminhos ate folhas
        return validBlackHeight(tree->root);
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
        fixInsert(tree, newNode, parent, parent->parent);
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