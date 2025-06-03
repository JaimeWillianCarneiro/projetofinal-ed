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
               
                // Check for capital letters
                cout << word << endl;
                transform(word.begin(), word.end(), word.begin(), ::tolower);

                // Add the word to the tree
                cout << word << endl;
                InsertResult new_insert = insert(tree, word, documentId);
                cout << "Inseri" << endl;
            }
            myfile.close();
            cout << "fechei" << endl;
            return;
        }
    }
    
    void readFilesFromDirectory(int number_files, BinaryTree* tree){
        for (int i = 0; i < number_files; i++){
            string address ("./data/");
            address += to_string(i);
            address += ".txt";
            
            cout << address << endl;
            readDataFromFile(address, i, tree);
        }
        return;
    }
}