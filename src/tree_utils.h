#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;   // Usado na AVL
    int isRed;    // Usado na RBT
};


struct BinaryTree {
    Node* root;
    Node* NIL; // Usado na RBT (não necessário para BST)
};


struct InsertResult {
    int numComparisons;
    double executionTime;
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};



void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);
void freeTree(Node* node); // usad


#endif // TREE_UTILS_H