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
        return node;
    }

    // BinarySearchTree* create() {
    //     // Create bst with null root node
    //     BinarySearchTree* bst = new BinarySearchTree;
    //     bst->root = nullptr;
    //     return bst;
    // }
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }


    void preOrderPrint(Node* node, int height) {
        // Stop condition
        if (node == nullptr) {
            return;
        }

        // Process father
        cout << string(height*2, ' ')<< "|-- " << node->word << endl;

        // Process sons
        preOrderPrint(node->left, height+1);
        preOrderPrint(node->right, height+1);
    }
    
    // Implements pre-order transverse recursive to print Tree
    void printTree(BinaryTree* tree) {
        if (tree == nullptr) return;
        preOrderPrint(tree->root, 0);
    }

    // void printTree(BinarySearchTree* tree) {
    //     if (tree == nullptr) {
    //         return;
    //     }

    //     preOrderPrint(tree->root, 0);
    // }

    

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
            tree->root = newNode;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            insResult.executionTime = duration.count()/1000;
            return insResult;
        }

        // Apply binary search in bst until find the correct position to word.
        Node* parent = tree->root;
        Node* nextParent;
        while (parent != nullptr) {
            insResult.numComparisons++;
            // Just update list of docs if newNodw already exists
            if (word == parent->word) {
                int indexDocId = binarySearch(parent->documentIds, documentId, 0, parent->documentIds.size());
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



    //  Jaime



// SearchResult search(BinarySearchTree* tree, const std::string& word) {
//     SearchResult result;
//     result.found = 0;
//     result.executionTime = 0.0;
//     result.numComparisons = 0;
//     result.documentIds.clear();

//     if (tree == nullptr || tree->root == nullptr) {
//         return result;
//     }

//     auto start = high_resolution_clock::now();

//     Node* current = tree->root;

//     while (current != nullptr) {
//         result.numComparisons++;
//         if (word == current->word) {
//             result.found = 1;
//             result.documentIds = current->documentIds;
//             break;
//         } else if (word < current->word) {
//             current = current->left;
//         } else {
//             current = current->right;
//         }
//     }

//     auto end = high_resolution_clock::now();
//     auto duration = duration_cast<microseconds>(end - start);
//     result.executionTime = duration.count() / 1000.0; // milissegundos

//     return result;
//     }


    SearchResult search(BinaryTree* tree, const std::string& word) {
        SearchResult result{0, {}, 0.0, 0};
        
        if (tree == nullptr || tree->root == nullptr) {
            return result;
        }

        auto start = high_resolution_clock::now();
        Node* current = tree->root;

        while (current != nullptr) {
            result.numComparisons++;
            if (word == current->word) {
                result.found = 1;
                result.documentIds = current->documentIds;
                break;
            } else if (word < current->word) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        auto end = high_resolution_clock::now();
        result.executionTime = duration_cast<microseconds>(end - start).count() / 1000.0;
        return result;
    }

    void destroyNode(Node* node) {
        if (node == nullptr) return;
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root);
        tree->root = nullptr;
        delete tree;
    }





    

    

}