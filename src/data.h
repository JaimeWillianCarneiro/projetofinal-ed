// data.h (CORRIGIDO)
#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include "tree_utils.h" // Garanta que tree_utils.h está incluído para ver a variável global

using namespace std;
using namespace TREE_UTILS;

namespace DATA {
    typedef InsertResult (*InsertFunction)(BinaryTree*, const std::string&, int);

    // readDataFromFile NÃO RECEBE MAIS allInsertedDocs como parâmetro
    void readDataFromFile(std::string address, int documentId,
                          BinaryTree* tree,
                          InsertResult& stats,
                          std::vector<InsertResult>& insertHistory,
                          std::vector<double>& timeHistory,
                          InsertFunction insertFn);

    // readFilesFromDirectory TAMBÉM NÃO RECEBE MAIS allInsertedDocs como parâmetro
    void readFilesFromDirectory(int number_files, string directory,
                                BinaryTree* tree,
                                InsertResult& stats,
                                vector<InsertResult>& insertHistory,
                                vector<double>& timeHistory,
                                InsertFunction insertFn); // Removido allInsertedDocs daqui
}
#endif