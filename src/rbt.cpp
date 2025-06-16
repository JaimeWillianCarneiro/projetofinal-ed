#include <iostream>
#include <vector>
#include <chrono>
#include "rbt.h"
#include "tree_utils.h"

using std::cin, std::cout, std::endl, std::string, std::vector;
using namespace std::chrono;
using namespace TREE_UTILS;

namespace RBT {
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
        Node* NIL = initializeNode();
        tree->NIL = NIL;
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
        newNode->isRed = 1;
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        if (tree->root == tree->NIL) {
            newNode->parent = tree->NIL;
            tree->root = newNode;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            insResult.executionTime = duration.count()/1000;
            return insResult;
        }

        // Apply binary search in rbt until find the correct position to word.
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
}