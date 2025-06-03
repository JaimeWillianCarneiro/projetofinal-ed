#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

#include "bst.h"
#include "tree_utils.h"
#include "data.h"

using namespace std;
using namespace std::chrono;

// Prints usage instructions
void printUsage() {
    cout << "Uso correto:" << endl;
    cout << "./bst search <n_docs> <diretorio>" << endl;
    cout << "./bst stats <n_docs> <diretorio>" << endl;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 4) {
        printUsage();
        return 1;
    }

    // Parse command line arguments
    string command   = argv[1];       // Either "search" or "stats"
    int n_docs       = stoi(argv[2]); // Number of documents to process
    string directory = argv[3];       // Directory containing the documents

    // Validate command argument
    if (command != "search" && command != "stats") {
        cerr << "Erro: Comando inválido!" << endl;
        printUsage();
        return 1;
    }

    // Create an empty Binary Search Tree (BST)
    BinaryTree* tree = BST::create();

    // Read files from the specified directory and insert data into the BST
    DATA::readFilesFromDirectory(n_docs, tree);

    // If command is "search", allow user to query words
    if (command == "search") {
        string word;
        cout << "Digite uma palavra para buscar (ou 'sair' para encerrar): ";
        
        // Loop until user enters "sair" to exit
        while (cin >> word) {
            if (word == "sair") break;

            // Search the BST for the given word
            SearchResult result = BST::search(tree, word);

            // Print search results
            if (result.found) {
                cout << "Palavra '" << word << "' encontrada nos documentos: ";
                for (int id : result.documentIds) {
                    cout << id << " ";
                }
                cout << endl;
            } else {
                cout << "Palavra '" << word << "' não encontrada em nenhum documento." << endl;
            }

            // Print performance metrics
            cout << "Comparações feitas: " << result.numComparisons << endl;
            cout << "Tempo de execução (ms): " << result.executionTime << endl;

            cout << "\nDigite outra palavra (ou 'sair'): ";
        }
    } else {
        // Placeholder for future stats functionality
        cout << "Ainda não implementado: stats" << endl;
    }

    // Clean up memory allocated for the BST
    BST::destroy(tree);

    return 0; 
}
