#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

#include "bst.h"
#include "tree_utils.h"
#include "data.h"

using namespace std;
using namespace std::chrono;
using namespace DATA;
using namespace TREE_UTILS;
using namespace BST;
// Prints usage instructions
void printUsage() {
    cout << "Uso correto:" << endl;
    cout << "./bst search <n_docs> <diretorio>" << endl;
    cout << "./bst stats <n_docs> <diretorio>" << endl;
}

// Prints menu options
void printMenu() {
    cout << "\nSelecione uma das opcoes (digite '\\o_<num_option>'):" << endl;
    cout << "1. Pesquisar uma palavra." << endl;
    cout << "2. Printar a arvore." << endl;
    cout << "3. Printar Indice Invertido." << endl;
    cout << "Ou digite '\\q' para sair (ou ctrl + c)." << endl;
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
        cerr << "Erro: Comando invalido!" << endl;
        printUsage();
        return 1;
    }

    // Create an empty Binary Search Tree (BST)
    BinaryTree* tree = create();

    // Read files from the specified directory and insert data into the BST
    readFilesFromDirectory(n_docs, directory, tree);

    // If command is "search", allow user to query words
    if (command == "search") {
        string word;
        printMenu();
        
        // Loop until user enters "sair" to exit
        while (cin >> word) {
            if (word == "\\o_1") {
                cout << "Digite uma palavra para buscar: ";
                cin >> word;
            } else if (word == "\\o_2") {
                printTree(tree);
            } else if (word == "\\o_3") {
                printIndex(tree);
            } else if (word == "\\q") {
                break;
            } else {
                cout << "Opcao invalida." << endl;
                printMenu();
                continue;
            }

            // Search the BST for the given word
            SearchResult result = search(tree, word);

            // Print search results
            if (result.found) {
                cout << "Palavra '" << word << "' encontrada nos documentos: ";
                for (int id : result.documentIds) {
                    cout << id << " ";
                }
                cout << endl;
            } else {
                cout << "Palavra '" << word << "' nao encontrada em nenhum documento." << endl;
            }

            // Print performance metrics
            cout << "Comparacoes feitas: " << result.numComparisons << endl;
            cout << "Tempo de execucao (ms): " << result.executionTime << endl;

            printMenu();
        }
    } else {
        // Placeholder for future stats functionality
        cout << "Ainda nao implementado: stats" << endl;
    }

    // Clean up memory allocated for the BST
    destroy(tree);

    return 0; 
}