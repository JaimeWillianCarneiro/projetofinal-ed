#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <cmath>
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

// Prints menu stats options
void printMenuStats() {
    cout << "\nSelecione uma das opcoes (Insira apenas o numero):" << endl;
    cout << "1. Tempo de insercao." << endl;
    // cout << "2. Tempo de busca." << endl;
    // cout << "3. Numero de comparacoes por operacao." << endl;
    cout << "2. Altura  e densidade da arvore." << endl;
    cout << "3. Tamanho dos galhos." << endl;
    cout << "4. Todas as estatisticas." << endl;
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
    InsertResult lastInsert = {0, 0.0};
    //  std::vector<InsertResult> insertHistory;
    // std::vector<double> timeHistory;
    // std::vector<TREE_UTILS::Document> allInsertedDocs; // Certifique-se de que esta linha existe!

    auto start = chrono::high_resolution_clock::now();
    // Read files from the specified directory and insert data into the BST
    // readFilesFromDirectory(n_docs, directory, tree, lastInsert, insertHistory, timeHistory, BST::insert);
    readFilesFromDirectory(n_docs, directory, tree, lastInsert, BST::insert); // OU BST::insert
    auto end = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

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
    } 

    else  if (command == "stats"){
        string input;
        printMenuStats();
        while (true) {
            cout << "\nOpcao: ";
            cin >> input;
            TreeStatistics stats = collectAllStats(tree->root);

            if (input == "1"){
                cout << "Tempo de insercao: " << endl;
                cout << " * Tempo medio: " << totalTime/stats.nodeCount <<  endl;
                cout << " * Tempo total: " << totalTime << " ms" <<  endl;
            } 
            // else if (input == "2") {
            //     cout << "Tempo de busca: " << endl;
            //     cout << " * Tempo medio: " << endl;
            //     cout << " * Tempo total: " << totalTime << " ms" << endl;

            // } else if (input == "3") {
            //     cout << "Numero de comparacoes por operacao: " << endl;
            // } 
            else if (input == "2") {
                cout << "Altura da arvore: "  << stats.height << endl;
                cout << "Densidade da arvore: " << (stats.nodeCount > 0 ? (double)stats.nodeCount / pow(2, stats.height + 1) : 0)  << endl;

            } else if (input == "3") {
                cout << "Tamanho dos galhos: " <<  endl;
                cout << " * Maior galho: " << stats.height<< endl;
                cout << " * Menor galho: " << stats.minDepth  << endl;
                cout << "Diferenca: " << stats.height - stats.minDepth << endl;
                // Correção: verificar se minDepth não é zero antes de dividir
            if (stats.minDepth != 0) {
                cout << "Razao maior/menor galho: " << static_cast<double>(stats.height) / stats.minDepth << endl;
            } else {
                cout << "Razao maior/menor galho: N/A (menor galho eh zero)" << endl;
    }
                cout << "Profundidade media: "  << stats.averageDepth << endl;
            } else if (input == "4") {
                printAllStats(tree,  lastInsert, totalTime, n_docs);
            
                        } else if (input == "\\q") {
                break;
            } else {
                cout << "Opcao invalida." << endl;
            }
            
            printMenuStats();
        }
    } else {
        cout << "Comando invalido";
        printUsage();
    }
    destroy(tree);
    return 0;
 
}