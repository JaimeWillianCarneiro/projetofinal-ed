#include "data.h"
#include "tree_utils.h"
#include "avl.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace TREE_UTILS;
using namespace AVL;

namespace DATA{

    void readDataFromFile(string address, int documentId, BinaryTree* tree){
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
                InsertResult new_insert = insert(tree, word, documentId);
            }
            myfile.close();
            return;
        } else {
            cout << "Erro ao abrir o arquivo: " << address << endl;
        }
    }
    
    void readFilesFromDirectory(int number_files, string directory, BinaryTree* tree){
        if (number_files <= 0) {
            cout << "Erro: número de arquivos inválido (" << number_files << ")." << endl;
            return;
        }

        
        for (int i = 0; i < number_files; i++){
            string address (directory);
            address += to_string(i);
            address += ".txt";
            
            readDataFromFile(address, i, tree);
        }
        return;
    }
}