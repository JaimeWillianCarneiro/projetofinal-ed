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
    if (!node) return;
    
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