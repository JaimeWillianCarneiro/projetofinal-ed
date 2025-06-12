#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include "tree_utils.h"

using namespace std; 
using namespace TREE_UTILS;


namespace DATA {
    using InsertFunction = InsertResult(*)(TREE_UTILS::BinaryTree*, const std::string&, int);
    /**
     * @brief Read the n first files adding its words and ids into the tree
     * @param number_files Number of files to be read
     * @param tree The Binary Tree to be updated
     */
            void readFilesFromDirectory(int number_files, std::string directory, TREE_UTILS::BinaryTree* tree, TREE_UTILS::InsertResult& stats, InsertFunction insertFn);

    /**
     * @brief Read the data from the file specified by the address
     * @param address The path to the file
     * @param documentId The ID of the document to be added to the tree
     * @param tree The Binary Tree to be updated
     */
    void readDataFromFile(std::string address, int documentId, TREE_UTILS::BinaryTree* tree, TREE_UTILS::InsertResult& stats, InsertFunction insertFn);

}

#endif