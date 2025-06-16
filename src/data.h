#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
// Incluir <algorithm> para remove_if e transform
#include <algorithm>
// Incluir <cctype> para ::tolower (ou isalnum)
#include <cctype>

#include "tree_utils.h" // Para Node, BinaryTree, InsertResult, Document, etc.

// Nao coloque 'using namespace std;' ou 'using namespace TREE_UTILS;'
// em arquivos .h para evitar poluicao de namespace.
// Use prefixos (std::, TREE_UTILS::) ou 'using' em .cpp.

namespace DATA {
    // A definição do typedef deve vir ANTES das funções que o utilizam.
    typedef TREE_UTILS::InsertResult (*InsertFunction)(TREE_UTILS::BinaryTree*, const std::string&, int);

    // Declarações das funções, com as assinaturas corretas (5 parâmetros)

    void readDataFromFile(std::string address, int documentId,
                          TREE_UTILS::BinaryTree* tree,
                          TREE_UTILS::InsertResult& stats,
                          InsertFunction insertFn);

    void readFilesFromDirectory(int number_files, std::string directory,
                                TREE_UTILS::BinaryTree* tree,
                                TREE_UTILS::InsertResult& stats,
                                InsertFunction insertFn);
}

#endif // DATA_H