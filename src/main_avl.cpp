#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "avl.h"
#include "tree_utils.h"
#include "data.h"

using namespace std;
using namespace TREE_UTILS;
using namespace AVL;

// Prints usage instructions
void printUsage() {
    cout << "Uso correto:" << endl;
    cout << "./bst search <n_docs> <diretorio>" << endl;
    cout << "./bst stats <n_docs> <diretorio>" << endl;
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

void printStatistics(BinaryTree* tree, const InsertResult& lastInsert, double totalTime, int n_docs) {
    if (!tree || !tree->root) {
        cout << "Arvore vazia!" << endl;
        return;
    }

    int totalDepth = 0, nodeCount = 0, minDepth = INT_MAX, maxImbalance = 0;
    collectTreeStats(tree->root, 0, totalDepth, nodeCount, minDepth, maxImbalance);

    cout << "\n=== ESTATISTICAS AVL ===" << endl;
    cout << "------ Estruturais ------" << endl;
    cout << "Altura da arvore: " << getHeight(tree->root) << endl;
    cout << "Nos totais: " << nodeCount << endl;
    cout << "Profundidade media: " << fixed << (double)totalDepth/nodeCount << endl;
    cout << "Fator de balanceamento maximo: " << maxImbalance << endl;
    
    cout << "\n------ Desempenho ------" << endl;
    cout << "Documentos indexados: " << n_docs << endl;
    cout << "Tempo total indexacao: " << totalTime << " ms" << endl;
    cout << "Ultima insercao:" << endl;
    cout << "  • Comparacoes: " << lastInsert.numComparisons << endl;
    cout << "  • Tempo: " << lastInsert.executionTime << " ms" << endl;
    cout << "=========================" << endl;
}





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