#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::vector;

namespace TREE_UTILS {
    // struct Node {
    //     std::string word;
    //     std::vector<int> documentIds;
    //     Node* parent;
    //     Node* left;
    //     Node* right;
    //     int height;   // Usado na AVL
    //     int isRed;    // Usado na RBT
    // };


    // struct BinaryTree {
    //     Node* root;
    //     Node* NIL; // Usado na RBT (não necessário para BST)
    // };

    struct InsertResult {
        int numComparisons;
        double executionTime;
        // <Possíveis outras variáveis>
    };

    struct SearchResult {
        int found;
        std::vector<int> documentIds;
        double executionTime;
        int numComparisons;
        // <Possíveis outras variáveis>
    };

    // int binarySearch(vector<int> documentIds, int docId, int start, int end);
    // void printIndex(BinaryTree* tree);

    // void freeTree(Node* node); // usad
}

#endif // TREE_UTILS_H