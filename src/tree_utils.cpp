#include <iostream>
#include <vector>
#include <string>
#include "tree_utils.h"
#include <algorithm>
using std::cout;
using std::endl;
using namespace std;

namespace TREE_UTILS {
    // Função auxiliar para fazer in-order traversal e imprimir cada nó
    void printIndexInOrder(Node* node) {
        if (node == nullptr) return;

        // Esquerda
        printIndexInOrder(node->left);

        // Imprime palavra e lista de documentos
        cout << node->word << ": ";
        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            cout << node->documentIds[i];
            if (i != node->documentIds.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        // Direita
        printIndexInOrder(node->right);
    }

    // Função pública para imprimir o índice completo
    void printIndex(BinaryTree* tree) {
        if (tree == nullptr || tree->root == nullptr) {
            cout << "Árvore vazia." << endl;
            return;
        }
        printIndexInOrder(tree->root);
    }

    void preOrderPrint(Node* node, int height, string paths, string prefix) {
        // Stop condition
        if (node == nullptr) {
            return;
        }

        // Process father
        cout << paths << prefix << node->word << endl;
        if (prefix == "|-- ") {
            paths += "|   ";
        } else if (prefix == "*-- ") {
            paths += "    ";
        }

        prefix = "*-- ";
        // Process sons
        if (node->left != nullptr) {
            if (node->right != nullptr) {
                prefix = "|-- ";
            }
            preOrderPrint(node->left, height+1, paths, prefix);
            prefix = "*-- ";
        }
        preOrderPrint(node->right, height+1, paths, prefix);
    }
    
    // Implements pre-order transverse recursive to print Tree
    void printTree(BinaryTree* tree) {
        if (tree == nullptr) return;
        preOrderPrint(tree->root, 0, "", "");
    }

//     // Right -> Center -> Left.
//     void inverseOrderTransversePrint(Node* node, int depth, vector<int> maxWordForNivel, vector<int> restos[]) {
//     if (depth == maxWordForNivel.size()) {
//         depth--;
//         restos[1][depth] = restos[0][depth]/2;
        
//         for (int eachNivel = 0; eachNivel < maxWordForNivel.size()-1; eachNivel++) {
//             cout << string(maxWordForNivel[eachNivel] + 3, ' ');
//             if (restos[1][eachNivel] != 0) {
//                 restos[1][eachNivel]--;
//                 cout << "|";
//             } else cout << " ";
//         }
//         restos[1][depth]--;
//         cout << endl;
//         return;
//     }
//     // Ignore null nodes.
//     Node* right = nullptr;
//     Node* left = nullptr;
//     string word = "";
//     string side = "    ";
//     if (node != nullptr) {
//         right = node->right;
//         left = node->left;
//         word = node->word;
//         side = "--- ";
//     }
//     // Process right son first (right subtree allway appear first in the lines).
//     inverseOrderTransversePrint(right, depth+1, maxWordForNivel, restos);
//     if (restos[1][depth-1] == 0) restos[1][depth-1] = restos[0][depth-1]/2;

//     for (int eachNivel = 0; eachNivel < depth; eachNivel++) {
//         cout << string(maxWordForNivel[eachNivel] + 3, ' ');
//         if (restos[1][eachNivel] != 0) {
//             restos[1][eachNivel]--;
//             cout << "|";
//         } else cout << " ";
//     }
//     if (maxWordForNivel[depth] > 3) side.resize(maxWordForNivel[depth], ' ');
//     cout << side << word;
//     for (int eachNivel = depth+1; eachNivel < maxWordForNivel.size(); eachNivel++) {
//         cout << string(maxWordForNivel[eachNivel] + 3, ' ');
//         if (restos[1][eachNivel] != 0) {
//             restos[1][eachNivel]--;
//             if (node != nullptr) cout << "|";
//             else cout << " ";
//         } else cout << " ";
//     }
//     cout << endl;
//     restos[1][depth] = restos[0][depth]/2;
//     // After process node, process left subtree.
//     inverseOrderTransversePrint(left, depth+1, maxWordForNivel, restos);
// }

// void bfsPrintLateral(Node* root) {
//     if (root == nullptr) return;
//     int depth = -1;
//     vector<Node*> q;
//     vector<int> maxWordForNivel;
//     q.push_back(root);
//     bool again = (root != nullptr);
    
//     // Get max size word for each level.
//     while (again) {
//         maxWordForNivel.push_back(0);
//         again = false;
//         depth++;
//         int temp = q.size();
//         for (int each_item_q = 0; each_item_q < temp; each_item_q++) {
//             if (q[0] == nullptr) {
//                 q.erase(q.begin());
//                 continue;
//             }
//             again = true;
//             maxWordForNivel[depth] = maxWordForNivel[depth] < q[0]->word.size() ? q[0]->word.size() : maxWordForNivel[depth];
//             q.push_back(q[0]->left);
//             q.push_back(q[0]->right);
//             q.erase(q.begin());
//         }
//     }
//     depth--;
//     maxWordForNivel.pop_back();
//     Node* current = root;
//     vector<int> restos[2];
//     for (int i = 0, restoMaximo = 1; i <= maxWordForNivel.size(); i++) {
//         restos[0].insert(restos[0].begin(), restoMaximo);
//         restos[1].push_back(0);
//         restoMaximo *= 2;
//     }

//     // Use inverser order transverse to print
//     inverseOrderTransversePrint(current, 0, maxWordForNivel, restos);
// }

// // Use bfs with an 'inverse_order' transverse to print tree on left to right.
// void printTreeLateral(BinaryTree* tree) {
//     bfsPrintLateral(tree->root);
// }


int binarySearch(vector<int> documentIds, int docId, int start, int end) {
    if (documentIds.empty()) {
        cout << "Aviso: vetor de documentos vazio em binarySearch()." << endl;
        return 0;
    }
    
    // Stop condition.
    if (start > end) {
        return start;
    }

    int mid = (start + end) / 2;
    if (docId == documentIds[mid]) {
        return -1;
    }else if (docId > documentIds[mid]) {
        return binarySearch(documentIds, docId, mid+1, end);
    } else {
        return binarySearch(documentIds, docId, start, mid-1);
    }
}


    int getHeight(Node* node) {
    return node ? node->height : -1;
}




// Retorna o fator de balanceamento de um nó (esq - dir)
    int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
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


}
