#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "tree_utils.h" // Para Node, BinaryTree, InsertResult, Document, etc.


namespace DATA {
    

    /**
     * @brief Defines a function pointer type for word insertion into the tree.
     * @param tree A pointer to the BinaryTree structure where the word will be inserted.
     * @param word The word to be inserted.
     * @param documentId The ID of the document from which the word was extracted.
     * @return Returns a `TREE_UTILS::InsertResult` struct containing insertion statistics.
     */
    typedef TREE_UTILS::InsertResult (*InsertFunction)(TREE_UTILS::BinaryTree*, const std::string&, int);

    

    /**
     * @brief Read the data from the file specified by the address
     * @param address The path to the file
     * @param documentIdThe ID of the document to be added to the tree
     * @param tree Phe Binary Tree to be updated
     * @param stats A reference to a `TREE_UTILS::InsertResult` struct that will
     *  accumulate the total comparisons and execution time for all insertions
     * originating from *this specific file*.
     * @param insertFn insertFn A pointer to the tree-specific insertion function (e.g., `AVL::insert`).
     */
    void readDataFromFile(std::string address, int documentId,
                          TREE_UTILS::BinaryTree* tree,
                          TREE_UTILS::InsertResult& stats,
                          InsertFunction insertFn);
    
    /**
     * @brief Read the n first files adding its words and ids into the tree
     * @param number_files Number of files to be read
     * @param directory O caminho para o diretório que contém os arquivos de texto.
     * @param tree The Binary Tree to be updated
     * @param stats A reference to a `TREE_UTILS::InsertResult` struct that will accumulate
     * the total comparisons and execution time for insertions from *all* processed files.
     * @param insertFn Um ponteiro para a função de inserção específica da árvore (ex: `AVL::insert`).
     */    
    void readFilesFromDirectory(int number_files, std::string directory,
                                TREE_UTILS::BinaryTree* tree,
                                TREE_UTILS::InsertResult& stats,
                                InsertFunction insertFn);
}

#endif // DATA_H