#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include "avl.h"
#include "tree_utils.h"
#include "data.h"
#include <fstream>

using namespace std;
using namespace TREE_UTILS;
using namespace AVL;
using namespace DATA;
using namespace std::chrono;

void printUsage() {
    cout << "Uso correto:" << endl;
    cout << "./avl search <n_docs> <diretorio>" << endl;
    cout << "./avl stats <n_docs> <diretorio>" << endl;
}
//  print menu search options
void printMenuSearch() {
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
    cout << "5. Exportar estatisticas para CSV." << endl;  
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

    // Create an empty Binary Search Tree (AVL)
    BinaryTree* tree = create();
    InsertResult lastInsert = {0, 0.0};
    // vector<InsertResult> insertHistory;
    // vector<double> timeHistory;
    // vector<TREE_UTILS::Document> allInsertedDocs; 

    auto start = chrono::high_resolution_clock::now();
    
    // // Chamada corrigida com todos os parâmetros necessários
    // readFilesFromDirectory(n_docs, directory, tree, lastInsert, 
    //                      insertHistory, timeHistory, allInsertedDocs, AVL::insert);

    // readFilesFromDirectory(n_docs, directory, tree, lastInsert, insertHistory, timeHistory, AVL::insert);
    readFilesFromDirectory(n_docs, directory, tree, lastInsert, AVL::insert); // OU BST::insert
    auto end = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    // salvarEstatisticasEvolutiva("output/estatisticas_evolutiva_avl.csv", "AVL", max_docs);
    // Read files from the specified directory and insert data into the AVL
    // readFilesFromDirectory(n_docs, directory, tree);

    // If command is "search", allow user to query words
  if (command == "search") {
        string input;
        printMenuSearch();
        
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
            
            printMenuSearch();
        }
    } else  if (command == "stats"){
        string input;
        printMenuStats();
        while (true) {
            cout << "\nOpcao: ";
            cin >> input;
            TREE_UTILS::TreeStatistics stats = TREE_UTILS::collectAllStats(tree->root);
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
            
                        } 
            else if (input == "5"){
                // string filename;
                // cout << "Digite o nome do arquivo CSV (ex: estatisticas.csv): ";
                // cin >> filename;
                // exportStatsToCSV(tree, filename, lastInsert, totalTime, n_docs);
                // break;

                cout << "Exportando estatisticas evolutivas (1-" << n_docs << " docs)" << endl;
                TREE_UTILS::exportEvolutionStatsToCSV(n_docs, directory, "AVL");
            }
                        else if (input == "\\q") {
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