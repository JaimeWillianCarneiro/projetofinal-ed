#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include "tree_utils.h"

using namespace std; 
using namespace TREE_UTILS;


namespace DATA {

    /**
     * @brief Read the n first files adding its words and ids into the tree
     * @param number_files Number of files to be read
     * @param tree The Binary Tree to be updated
     */
    void readFilesFromDirectory(int number_files, string directory, BinaryTree* tree);

    /**
     * @brief Read the data from the file specified by the address
     * @param address The path to the file
     * @param documentId The ID of the document to be added to the tree
     * @param tree The Binary Tree to be updated
     */
    void readDataFromFile(string address, int documentId, BinaryTree* tree);

}

#endif