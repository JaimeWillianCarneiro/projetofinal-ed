#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "tree_utils.h"
#include <algorithm>
#include "avl.h"
#include "bst.h"
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

      // Só atualiza minDepth se for FOLHA
    if (node->left == nullptr && node->right == nullptr) {
        minDepth = std::min(minDepth, currentDepth);
    }
    
    int balance = getBalanceFactor(node);
    maxImbalance = max(maxImbalance, abs(balance));

    collectTreeStats(node->left,  currentDepth + 1, totalDepth, nodeCount, minDepth, maxImbalance);
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
        stats.docCount = 0;         // Novo campo
        stats.insertionTime = 0.0; 
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
    stats.docCount = nodeCount;      // Preenchendo novo campo
    stats.insertionTime = 0.0;   
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


// Função auxiliar recursiva para acumular estatísticas de busca
void accumulateSearchStatsRecursive(Node* node, double& totalTime, 
                                  int& totalComparisons, int& totalSearches) {
    if (!node) return;
    
    // Percorre a subárvore esquerda
    accumulateSearchStatsRecursive(node->left, totalTime, totalComparisons, totalSearches);
    
    // Processa o nó atual
    if (node->searchCount > 0) {
        totalTime += node->totalSearchTime;
        totalComparisons += node->totalSearchComparisons;
        totalSearches += node->searchCount;
    }
    
    // Percorre a subárvore direita
    accumulateSearchStatsRecursive(node->right, totalTime, totalComparisons, totalSearches);
}


// Variáveis globais para histórico
std::vector<Document> allInsertedDocuments;
std::vector<InsertResult> insertHistory;
std::vector<double> timeHistory;




void exportEvolutionStatsToCSV(int max_docs, 
                             const std::string& basePath,
                             const std::string& treeType) {
    if (max_docs <= 0) {
        std::cerr << "Número de documentos inválido." << std::endl;
        return;
    }

    // Garantir caminho correto
    std::string path = basePath;
    if (!path.empty() && path.back() != '/') {
        path += "/";
    }

    // Solicitar nome do arquivo
    std::string filename;
    std::cout << "Digite o nome do arquivo para exportar (sem extensão): ";
    std::cin >> filename;
    
    std::string outputFilename = path + filename + ".csv";

    std::ofstream csvFile(outputFilename);
    if (!csvFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo " << outputFilename << std::endl;
        return;
    }

    // Cabeçalho do CSV
    csvFile << "Num Docs,Altura,Total Nos,Profundidade Media,"
            << "Profundidade Minima,Max Desbalanceamento,"
            << "Tempo Total (ms),Comparacoes Medias,Tipo Arvore\n";

    // Ponteiros para funções específicas
    BinaryTree* (*createFunc)() = nullptr;
    void (*destroyFunc)(BinaryTree*) = nullptr;
    InsertResult (*insertFunc)(BinaryTree*, const std::string&, int) = nullptr;

    // Configurar funções baseadas no tipo de árvore
    if (treeType == "AVL") {
        createFunc = AVL::create;
        destroyFunc = AVL::destroy;
        insertFunc = AVL::insert;
    } else {
        createFunc = BST::create;
        destroyFunc = BST::destroy;
        insertFunc = BST::insert;
    }

    // Criar árvore temporária
    BinaryTree* tempTree = createFunc();
    
    for (int n = 1; n <= max_docs && n <= allInsertedDocuments.size(); n++) {
        // Limpar e recriar árvore
        destroyFunc(tempTree);
        tempTree = createFunc();
        
        // Reinserir documentos
        for (int i = 0; i < n; i++) {
            const auto& doc = allInsertedDocuments[i];
            insertFunc(tempTree, doc.word, doc.docId);
        }
        
        // Coletar estatísticas
        TreeStatistics stats = collectAllStats(tempTree->root);
        
        // Escrever linha no CSV
        csvFile << n << ","
                << stats.height << ","
                << stats.nodeCount << ","
                << stats.averageDepth << ","
                << stats.minDepth << ","
                << stats.maxImbalance << ","
                << (n <= timeHistory.size() ? timeHistory[n-1] : 0) << ","
                << (n <= insertHistory.size() ? insertHistory[n-1].numComparisons : 0) << ","
                << treeType << "\n";
    }

    // Liberar memória
    destroyFunc(tempTree);
    csvFile.close();
    std::cout << "Estatísticas exportadas para " << outputFilename << std::endl;
}

}
