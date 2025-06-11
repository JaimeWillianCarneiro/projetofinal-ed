#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include "avl.h"
#include "tree_utils.h"
#include "data.h"

using namespace std;
using namespace TREE_UTILS;
using namespace AVL;
using namespace DATA;
using namespace std::chrono;

void printUsage() {
    cout << "Uso correto:" << endl;
    cout << "./bst search <n_docs> <diretorio>" << endl;
    cout << "./bst stats <n_docs> <diretorio>" << endl;
}

void printMenuSearch() {
    cout << "\nSelecione uma das opcoes (Insira apenas o numero):" << endl;
    cout << "1. Pesquisar uma palavra." << endl;
    cout << "2. Printar a arvore." << endl;
    cout << "3. Printar Indice Invertido." << endl;
    cout << "Ou digite '\\q' para sair. (ou ctrl + c)" << endl;
}

// Prints menu options
void printMenuStats() {
    cout << "\nSelecione uma das opcoes (Insira apenas o numero):" << endl;
    cout << "1. Ver todas as stats." << endl;
    cout << "2. Tempo de insercao." << endl;
    cout << "3. Numero de comparacoes por operacao" << endl;
    cout << "Ou digite '\\q' para sair. (ou ctrl + c)" << endl;
}

void bfsPrintHeight(Node* root) {
    if (root == nullptr) return;
    int height = -1;
    vector<Node*> q;
    vector<vector<string>> p;
    q.push_back(root);
    bool again = true;
    int maxWord = 0;
    while (again) {
        again = false;
        height++;
        vector<string> nivel;
        int temp = q.size();
        for (int each_item_q = 0; each_item_q < temp; each_item_q++) {
            if (q[0] == nullptr) {
                nivel.push_back("-1");
                q.push_back(nullptr);
                q.push_back(nullptr);
                q.erase(q.begin());
                continue;
            }
            again = true;
            maxWord = maxWord < q[0]->word.size() ? q[0]->word.size() : maxWord;
            nivel.push_back(to_string(q[0]->height));
            q.push_back(q[0]->left);
            q.push_back(q[0]->right);
            q.erase(q.begin());
        }
        p.push_back(nivel);
    }
    

    int leafs = pow(2, height);
    int gap = (maxWord + 1)*(leafs - 1);
    int complete;
    for (int n = 0; n <= height-1; n++) {
        gap /= 2;
        for (int i = 0; i < pow(2, n); i++) {
            if (p[n][i] == "-1") {
                cout << string((2 * gap + maxWord - 1), ' ');
                continue;
            }
            
            cout << string((gap/2 + 1), ' ');
            cout << string(gap/2 - maxWord/2, '_');
            if (i < p[n].size()) {
                complete = maxWord - p[n][i].size();
                cout << string(complete/2, ' ');
                cout << p[n][i];
                cout << string((complete + 1) / 2, ' ');
            }
            cout << string(gap/2 - maxWord/2, '_');
            cout << string((gap/2 + 2), ' ');
        }
        cout << endl;
    }

}

void printTreeHeight(BinaryTree* tree) {
    if(tree == nullptr) return;
    bfsPrintHeight(tree->root);
}


void bfsPrint(Node* root) {
    if (root == nullptr) return;
    int height = -1;
    vector<Node*> q;
    vector<vector<string>> p;
    q.push_back(root);
    bool again = true;
    int maxWord = 0;
    while (again) {
        again = false;
        height++;
        vector<string> nivel;
        int temp = q.size();
        for (int each_item_q = 0; each_item_q < temp; each_item_q++) {
            if (q[0] == nullptr) {
                nivel.push_back("*");
                q.push_back(nullptr);
                q.push_back(nullptr);
                q.erase(q.begin());
                continue;
            }
            again = true;
            maxWord = maxWord < q[0]->word.size() ? q[0]->word.size() : maxWord;
            nivel.push_back(q[0]->word);
            q.push_back(q[0]->left);
            q.push_back(q[0]->right);
            q.erase(q.begin());
        }
        p.push_back(nivel);
    }
    

    int leafs = pow(2, height);
    int gap = (maxWord + 1)*(leafs - 1);
    int complete;
    for (int n = 0; n <= height-1; n++) {
        gap /= 2;
        for (int i = 0; i < pow(2, n); i++) {
            if (p[n][i] == "*") {
                cout << string((2 * gap + maxWord - 1), ' ');
                continue;
            }
            cout << string((gap/2 + 1), ' ');
            cout << string(gap/2 - maxWord/2, '_');
            if (i < p[n].size()) {
                complete = maxWord - p[n][i].size();
                cout << string(complete/2, ' ');
                cout << p[n][i];
                cout << string((complete + 1) / 2, ' ');
            }
            cout << string(gap/2 - maxWord/2, '_');
            cout << string((gap/2 + 2), ' ');
        }
        cout << endl;
    }
}

void printTreeAlt(BinaryTree* tree) {
    if(tree == nullptr) return;
    bfsPrint(tree->root);
}


// Função para coletar estatísticas avançadas da árvore
void collectTreeStats(Node* node, int currentDepth, int& totalDepth, int& nodeCount, int& minDepth, int& maxImbalance) {
    if (node== nullptr) {
        return;
    }
    
    nodeCount++;
    totalDepth += currentDepth;
    minDepth = min(minDepth, currentDepth);
    
    int balance = getBalanceFactor(node);
    maxImbalance = max(maxImbalance, abs(balance));
    
    collectTreeStats(node->left, currentDepth + 1, totalDepth, nodeCount, minDepth, maxImbalance);
    collectTreeStats(node->right, currentDepth + 1, totalDepth, nodeCount, minDepth, maxImbalance);
}


    // Função unificada para coletar todas as estatísticas
TreeStatistics collectAllStats(Node* root) {
    TreeStatistics stats;
    if (root == nullptr) {
        stats.height = -1;
        stats.nodeCount = 0;
        stats.averageDepth = 0.0;
        stats.minDepth = 0;
        stats.maxImbalance = 0;
        return stats;
    }

    int totalDepth = 0, nodeCount = 0, minDepth = INT_MAX, maxImbalance = 0;
    collectTreeStats(root, 0, totalDepth, nodeCount, minDepth, maxImbalance);

    stats.height = getHeight(root);
    stats.nodeCount = nodeCount;
    stats.averageDepth = nodeCount > 0 ? (double)totalDepth / nodeCount : 0.0;
    stats.minDepth = minDepth;
    stats.maxImbalance = maxImbalance;

    return stats;
}



void printAllStats(BinaryTree* tree, const InsertResult& lastInsert, double totalTime, int n_docs) {
    TreeStatistics stats = collectAllStats(tree->root);
    
    cout << "\n=== TODAS ESTATISTICAS ===" << endl;
    cout << "------ Estruturais ------" << endl;
    cout << "Altura da arvore: " << stats.height << endl;
    cout << "Nos totais: " << stats.nodeCount << endl;
    cout << "Profundidade media: " << stats.averageDepth << endl;
    cout << "Profundidade minima: " << stats.minDepth << endl;
    cout << "Fator de balanceamento maximo: " << stats.maxImbalance << endl;
    
    cout << "\n------ Desempenho ------" << endl;
    cout << "Documentos indexados: " << n_docs << endl;
    cout << "Tempo total indexacao: " << totalTime << " ms" << endl;
    cout << "Ultima insercao:" << endl;
    cout << "* Comparacoes: " << lastInsert.numComparisons << endl;
    cout << "* Tempo: " << lastInsert.executionTime << " ms" << endl;
    cout << "=========================" << endl;
}

void printTreeHeightStats(BinaryTree* tree) {
    TreeStatistics stats = collectAllStats(tree->root);
    
    cout << "\n=== ESTATISTICAS DE ALTURA ===" << endl;
    cout << "Altura da arvore: " << stats.height << endl;
    cout << "Profundidade minima: " << stats.minDepth << endl;
    cout << "Razão altura/nós: " << (stats.nodeCount > 0 ? (double)stats.height / stats.nodeCount : 0) << endl;
    cout << "==============================" << endl;
}

void printBranchStats(BinaryTree* tree) {
    TreeStatistics stats = collectAllStats(tree->root);
    
    cout << "\n=== ESTATISTICAS DOS GALHOS ===" << endl;
    cout << "Maior profundidade (galho mais longo): " << stats.height << endl;
    cout << "Menor profundidade (galho mais curto): " << stats.minDepth << endl;
    cout << "Diferença: " << stats.height - stats.minDepth << endl;
    cout << "Profundidade media: " << stats.averageDepth << endl;
    cout << "=================================" << endl;
}

void printBasicStructureStats(BinaryTree* tree) {
    TreeStatistics stats = collectAllStats(tree->root);
    
    cout << "\n=== ESTATISTICAS ESTRUTURAIS ===" << endl;
    cout << "Nos totais: " << stats.nodeCount << endl;
    cout << "Altura da arvore: " << stats.height << endl;
    cout << "Fator de balanceamento maximo: " << stats.maxImbalance << endl;
    cout << "Densidade da arvore: " << fixed << setprecision(2) 
         << (stats.nodeCount > 0 ? (double)stats.nodeCount / pow(2, stats.height + 1) : 0) << endl;
    cout << "================================" << endl;
}



/*
int main() {
    
    BinaryTree* avl = create();

    string nodes[6] = {"3", "1", "5", "2", "4", "6"};
    for (int eachNode = 0; eachNode < 6; eachNode++) {
        cout << endl << endl;
        insert(avl, nodes[eachNode], 0);
        printTreeHeight(avl);
        printTreeAlt(avl);
    }

    cout << "\n\n\n\n";
    // printTree(avl);
    printTreeAlt(avl);
    printTreeHeight(avl);


    cout << "\n\n";
    InsertResult insResult = insert(avl, "0", 2);
    // printTree(avl);
    printTreeAlt(avl);
    printTreeHeight(avl);

    cout << "Comparacoes: " << insResult.numComparisons << "\nTempo: " << insResult.executionTime << "\n\n";
    insResult = insert(avl, "0.1", 1);
    // printTree(avl);
    printTreeAlt(avl);
    printTreeHeight(avl);

    cout << "Comparacoes: " << insResult.numComparisons << "\nTempo: " << insResult.executionTime << "\n\n";

    insResult = insert(avl, "0.2", 1);
    // printTree(avl);
    printTreeAlt(avl);
    printTreeHeight(avl);
    cout << "Comparacoes: " << insResult.numComparisons << "\nTempo: " << insResult.executionTime << "\n\n";

    insResult = insert(avl, "0.3", 1);
    // printTree(avl);
    printTreeAlt(avl);
    printTreeHeight(avl);
    cout << "Comparacoes: " << insResult.numComparisons << "\nTempo: " << insResult.executionTime << "\n\n";

    
}
    */






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
    // Modificado para capturar tempo total

    auto start = chrono::high_resolution_clock::now();
    
    readFilesFromDirectory(n_docs, directory, tree, lastInsert); // Você precisará atualizar esta função
    auto end = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Read files from the specified directory and insert data into the BST
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

            if (input == "1"){
                printAllStatistics(tree,  lastInsert, totalTime, n_docs);
            } else if (input == "2") {
                cout << "Tempo de inserção: " << endl;
                cout << " • Tempo médio " << endl;
                cout << " • Tempo total " <<  endl; 

            } else if (input == "3") {
                cout << "Tempo de busca: " << endl;
                cout << " • Tempo médio " << endl;
                cout << " • Tempo total " << totalTime << " ms" << endl;
            } else if (input == "4") {
                cout << " Número de comparações por operação" << endl;

            } else if (input == "5") {
                cout << " • Áltura da árvore" << endl;

            } else if (input == "6") {
                cout << "Tamanho dos galhos:" <<  endl;
                cout << " • Maior" << endl;
                cout << " • Menor" << endl;
            
            } else if (command == "\\q"){
                break;
            }
                
                else {
                cout << " Opcao invalida." << endl;
            }
            
            printMenuStats();
    
        } } else{
            cout << "Comando inválido";

            printUsage();

        }

    destroy(tree);
    return 0;
 
}