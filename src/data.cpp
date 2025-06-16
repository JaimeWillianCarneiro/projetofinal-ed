#include "data.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "tree_utils.h" // Necessário para acessar TREE_UTILS::allInsertedDocuments

using namespace std;
using namespace TREE_UTILS; // Permite acesso direto a allInsertedDocuments
using namespace std::chrono;

namespace DATA {

    // readDataFromFile - DEVE TER 7 PARÂMETROS
    void readDataFromFile(string address, int documentId,
                          BinaryTree* tree,
                          InsertResult& stats,
                          vector<InsertResult>& insertHistory,
                          vector<double>& timeHistory,
                          InsertFunction insertFn) { // Removido allInsertedDocs daqui
        if(tree == nullptr) return;

        string word;
        ifstream myfile(address);
        if (myfile.is_open()) {
            while (getline(myfile, word, ' ')) {
                word.erase(remove_if(word.begin(), word.end(),
                    [](unsigned char c) { return !isalnum(c); }), word.end());
                transform(word.begin(), word.end(), word.begin(), ::tolower);

                if (!word.empty()) {
                    auto start = high_resolution_clock::now();
                    InsertResult result = insertFn(tree, word, documentId);
                    auto end = high_resolution_clock::now();

                    stats.numComparisons += result.numComparisons;
                    double elapsed = duration_cast<microseconds>(end - start).count() / 1000.0;
                    stats.executionTime += elapsed;

                    insertHistory.push_back(result);
                    timeHistory.push_back(elapsed);

                    // ESTA LINHA É CRÍTICA PARA PREENCHER O CSV
                    TREE_UTILS::allInsertedDocuments.push_back({word, documentId});
                }
            }
            myfile.close();
        } else {
            cout << "Erro ao abrir o arquivo: " << address << endl;
        }
    }

    // readFilesFromDirectory - DEVE TER 7 PARÂMETROS
    void readFilesFromDirectory(int number_files,
                                 string directory,
                                 BinaryTree* tree,
                                 InsertResult& stats,
                                 vector<InsertResult>& insertHistory,
                                 vector<double>& timeHistory,
                                 InsertFunction insertFn) { // Removido allInsertedDocs daqui
        // LIMPAR AS LISTAS GLOBAIS NO INÍCIO DE CADA EXECUÇÃO
        TREE_UTILS::allInsertedDocuments.clear();
        TREE_UTILS::insertHistory.clear();
        TREE_UTILS::timeHistory.clear();

        for (int i = 0; i < number_files; i++) {
            string address = directory + to_string(i) + ".txt";
            // CHAMADA PARA readDataFromFile - AGORA TEM 7 PARÂMETROS
            readDataFromFile(address, i, tree, stats, insertHistory, timeHistory, insertFn);
        }
    }
}