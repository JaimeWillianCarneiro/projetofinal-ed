#include "data.h"
#include "tree_utils.h"
#include "bst.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace TREE_UTILS;
using namespace BST;

namespace DATA{

    void readDataFromFile(string address, int documentId, BinaryTree* tree){
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

                // Add the word to the tree
                InsertResult new_insert = insert(tree, word, documentId);
            }
            myfile.close();
            return;
        }
    }
    
    void readFilesFromDirectory(int number_files, string directory, BinaryTree* tree){
        for (int i = 0; i < number_files; i++){
            string address (directory);
            address += to_string(i);
            address += ".txt";
            
            cout << address << endl;
            readDataFromFile(address, i, tree);
        }
        return;
    }
}