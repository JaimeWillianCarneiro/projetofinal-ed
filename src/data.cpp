#include "data.h"
#include "tree_utils.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
using namespace std;
using namespace TREE_UTILS;
using namespace std::chrono;


namespace DATA{

    void readDataFromFile(string address, int documentId, BinaryTree* tree, InsertResult& stats,  InsertFunction insertFn){
        if(tree == nullptr) return;

        string word;
        ifstream myfile(address);
        if (myfile.is_open())
        {
            while (getline(myfile,word,' '))
            {
                // Check for invalid characters
                word.erase(remove_if(word.begin(), word.end(),
                [](unsigned char c) { return !isalnum(c); }), word.end());
                
                // Check for capital letters
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (word.empty()) continue;
                // Add the word to the tree

            if (!word.empty()) {
                auto start = high_resolution_clock::now();
                InsertResult result = insertFn(tree, word, documentId);
                auto end = high_resolution_clock::now();
                
                // Acumula estatísticas
                stats.numComparisons += result.numComparisons;
                stats.executionTime += duration_cast<microseconds>(end - start).count() / 1000.0;
            }            }
            myfile.close();
            return;
        } else {
            cout << "Erro ao abrir o arquivo: " << address << endl;
        }
    }
    
    void readFilesFromDirectory(int number_files, string directory, BinaryTree* tree, InsertResult& stats,  InsertFunction insertFn){
        for (int i = 0; i < number_files; i++){
            string address (directory);
            address += to_string(i);
            address += ".txt";
            string word;
            
            readDataFromFile(address, i, tree, stats, insertFn);
        }
        return;
    }
}