#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>
#include <climits>
#include <string> // Corrigi a duplicação de <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace TREE_UTILS {

    // --- PRIMEIRA PARTE: DEFINIÇÕES DE STRUCTS NECESSÁRIAS ---
    // Estas structs precisam ser definidas antes de serem usadas pelas variáveis globais
    struct InsertResult {
        int numComparisons;
        double executionTime;
    };

    struct SearchResult {
        int found;
        std::vector<int> documentIds;
        double executionTime;
        int numComparisons;
    };

    struct TreeStatistics {
        int height;
        int nodeCount;
        double averageDepth;
        int minDepth;
        int maxImbalance;
        int docCount;
        double insertionTime;
    };

    struct Document { // Esta struct precisa vir antes de allInsertedDocuments
        std::string word;
        int docId;
    };

    // --- SEGUNDA PARTE: DECLARAÇÕES EXTERNAS DE VARIÁVEIS GLOBAIS ---
    // Agora que Document e InsertResult estão definidas, essas podem vir
    extern std::vector<Document> allInsertedDocuments;
    extern std::vector<InsertResult> insertHistory;
    extern std::vector<double> timeHistory;

    // --- TERCEIRA PARTE: OUTRAS STRUCTS E DECLARAÇÕES DE FUNÇÕES ---
    // O restante das suas structs e funções vem aqui.
    struct Node {
        std::string word;
        std::vector<int> documentIds;
        Node* parent;
        Node* left;
        Node* right;
        int height;
        int isRed;

        double totalSearchTime = 0.0;
        int totalSearchComparisons = 0;
        int searchCount = 0;
    };

    struct BinaryTree {
        Node* root;
        Node* NIL;
    };

    // ... (o restante das declarações de funções como printIndexInOrder, printTree, etc.) ...
    void printIndexInOrder(Node* node);

    void printIndex(BinaryTree* tree);
    void printTree(BinaryTree* tree);
    // ... (todas as outras declarações de funções que você tinha) ...
    int binarySearch(std::vector<int> documentIds, int docId, int start, int end);
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    void collectTreeStats(Node* node, int currentDepth, int& totalDepth, int& nodeCount, int& minDepth, int& maxImbalance);
    TreeStatistics collectAllStats(Node* root);
    void printAllStats(BinaryTree* tree, const InsertResult& lastInsert, double totalTime, int n_docs);
    void exportStatsToCSV(BinaryTree* tree, const std::string& filename,
                         const InsertResult& lastInsert, double totalTime, int n_docs);
    void exportEvolutionStatsToCSV(int max_docs,
                                  const std::string& basePath,
                                  const std::string& treeType);
    void rebuildTreeUpToNDocs(BinaryTree* tree, int n, bool isAVL);
    void salvarEstatisticasEvolutivas(
        BinaryTree* tree,
        const std::vector<std::vector<std::string>>& documentos,
        InsertResult (*insertFunc)(BinaryTree*, const std::string&, int),
        const std::string& caminhoArquivoCSV
    );

} // Fim do namespace TREE_UTILS

#endif // TREE_UTILS_H