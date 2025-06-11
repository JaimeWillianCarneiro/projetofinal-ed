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
    cout << "\nSelecione uma das opcoes (Insira apenas o numero):" << endl;
    cout << "1. Pesquisar uma palavra." << endl;
    cout << "2. Printar a arvore." << endl;
    cout << "3. Printar Indice Invertido." << endl;
    cout << "Ou digite '\\q' para sair. (ou ctrl + c)" << endl;
}

void printMenuStats(){
    cout << "\nSelecione uma das opcoes (Insira apenas o numero):" << endl;
    cout << "1. Analisar estatísticas." << endl;
    cout << "2. Printar a arvore." << endl;
    cout << "3. Printar Indice Invertido." << endl;
    cout << "Ou digite '\\q' para sair. (ou ctrl + c)" << endl;

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
        string input;
        printMenu();
        
        while (true) {
            cout << "\nOpcao: ";
            cin >> input;

            if (input == "1") {
                cout << "Digite uma palavra para buscar: ";
                string word;
                cin >> word;
                
                SearchResult result = search(tree, word);
                
                if (result.found) {
                    cout << "Palavra '" << word << "' encontrada nos documentos: ";
                    for (int id : result.documentIds) {
                        cout << id << " ";
                    }
                    cout << endl;
                } else {
                    cout << "Palavra '" << word << "' nao encontrada." << endl;
                }
                cout << "Comparacoes: " << result.numComparisons << endl;
                cout << "Tempo (ms): " << result.executionTime << endl;
                
            } else if (input == "2") {
                printTree(tree);
                
            } else if (input == "3") {
                printIndex(tree);
                
            } else if (input == "\\q") {
                break;
                
            } else {
                cout << "Opcao invalida." << endl;
            }
            
            printMenu();
        }
    } else {
        cout << "Ainda nao implementado: stats" << endl;
    }

    destroy(tree);
    return 0;
 
}