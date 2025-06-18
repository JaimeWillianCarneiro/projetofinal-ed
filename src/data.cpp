#include "data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // Para std::remove_if e std::transform
#include <cctype>    // Para ::tolower e isalnum
#include <chrono>    // Para std::chrono
using namespace std;       // Para cout, endl, string, vector, etc.
using namespace TREE_UTILS; // Para Node, BinaryTree, InsertResult, Document, allInsertedDocuments, etc.
using namespace std::chrono; // Para high_resolution_clock, duration_cast

namespace DATA {

    void readDataFromFile(string address, int documentId,
                          BinaryTree* tree,
                          InsertResult& stats,
                          InsertFunction insertFn) { 
        if(tree == nullptr) return;

        string word;
        ifstream myfile(address);
        if (myfile.is_open()) {
            while (getline(myfile, word, ' ')) {
                
                word.erase(std::remove_if(word.begin(), word.end(),
                    [](unsigned char c) { return !std::isalnum(c); }), word.end()); 
                std::transform(word.begin(), word.end(), word.begin(), ::tolower); // tolower é global

                if (!word.empty()) {
                    auto start = high_resolution_clock::now();
                    // insertFn é um ponteiro para função
                    InsertResult result = insertFn(tree, word, documentId);
                    auto end = high_resolution_clock::now();

                    stats.numComparisons += result.numComparisons;
                    double elapsed = duration_cast<microseconds>(end - start).count() / 1000.0;
                    stats.executionTime += elapsed;

                    // Preenchendo as variáveis globais do namespace TREE_UTILS
                    TREE_UTILS::insertHistory.push_back(result);
                    TREE_UTILS::timeHistory.push_back(elapsed);
                    TREE_UTILS::allInsertedDocuments.push_back({word, documentId});
                }
            }
            myfile.close();
        } else {
            cout << "Erro ao abrir o arquivo: " << address << endl;
        }
    }

    void readFilesFromDirectory(int number_files, string directory,
                                BinaryTree* tree,
                                InsertResult& stats,
                                InsertFunction insertFn) { 
        // Limpar as variáveis globais do histórico antes de iniciar a nova leitura
        TREE_UTILS::allInsertedDocuments.clear();
        TREE_UTILS::insertHistory.clear();
        TREE_UTILS::timeHistory.clear();

        for (int i = 0; i < number_files; i++) {
            string address = directory + to_string(i) + ".txt";
          
            readDataFromFile(address, i, tree, stats, insertFn);
        }
    }
}