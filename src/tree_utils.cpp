#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "tree_utils.h"
#include <algorithm>
#include "avl.h"
#include "bst.h"
#include <math.h>
#include <cmath> 
#include <filesystem> // using std::cout;
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

    // Retorna a altura de um nó (ou -1 se for nulo)
    int getHeight(Node* node) {
        return node ? node->height : -1;
    }
   
    // Atualiza a altura de um nó com base nas alturas dos filhos
    void updateHeight(Node* node) {
        if(node == nullptr) return;

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // Retorna o fator de balanceamento de um nó (esq - dir)
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }



    void sideRotate(Node* parent, Node* son, int grandSide, int rotateSide) {
        if (parent == nullptr || son == nullptr) return;

        // Swap son and parent, making the parent inherit the grandchildren on the opposite side of the rotation.
        if (rotateSide == 0) {
            parent->right = son->left;
            if (parent->right != nullptr) parent->right->parent = parent;
            son->left = parent;
        } else {
            parent->left = son->right;
            if (parent->left != nullptr) parent->left->parent = parent;
            son->right = parent;
        }
        // The parent's parent inherit the son as his son.
        son->parent = parent->parent;
        if (grandSide == 0) {
            son->parent->right = son;
        } else if (grandSide == 1) {
            son->parent->left = son;
        }
        parent->parent = son;
        // Update height of nodes.
        updateHeight(parent);
        updateHeight(son);
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
    
     // Novos cálculos para print
    double tree_density = (stats.height >= 0 && stats.nodeCount > 0) ? (double)stats.nodeCount / (pow(2, stats.height + 1) - 1) : 0.0;
    int longest_branch = stats.height;
    int shortest_branch = stats.minDepth;
    int branch_difference = longest_branch - shortest_branch;
    double branch_ratio = (shortest_branch != 0) ? static_cast<double>(longest_branch) / shortest_branch : (longest_branch == 0 ? 1.0 : -1.0 /* Infinito ou N/A */);

    cout << "\n=== TODAS ESTATISTICAS ===" << endl;
    cout << "------ Estruturais ------" << endl;
    cout << "Altura da arvore: " << stats.height << endl;
    cout << "Nos totais: " << stats.nodeCount << endl;
    cout << "Profundidade media: " << stats.averageDepth << endl;
    cout << "Profundidade minima: " << stats.minDepth << endl;
    cout << "Fator de balanceamento maximo: " << stats.maxImbalance << endl;
      // --- Adicionado as linhas de impressão para as variáveis ---
    cout << "Densidade da arvore: " << tree_density << endl;
    cout << "Tamanho do maior galho: " << longest_branch << endl;
    cout << "Tamanho do menor galho: " << shortest_branch << endl;
    cout << "Diferenca entre galhos: " << branch_difference << endl; // Impressão adicionada
        
    if (shortest_branch != 0) {
            cout << "Razao maior/menor galho: " << branch_ratio << endl;
        } else {
            cout << "Razao maior/menor galho: N/A (menor galho eh zero ou indefinido)" << endl;
        }
    cout << "\n------ Desempenho ------" << endl;
    cout << "Documentos indexados: " << n_docs << endl;
    cout << "Tempo total indexacao: " << totalTime << " ms" << endl;
    
    // Cálculo do tempo médio de inserção aqui
    double average_insertion_time = (stats.nodeCount > 0) ? totalTime / stats.nodeCount : 0.0;
    cout << "Tempo medio de insercao por no: " << average_insertion_time << " ms" << endl;

    
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

        std::string path = basePath;
        if (!path.empty() && path.back() != '/') {
            path += "/";
        }

        std::string outputDirectory = "docs/"; 
        
        if (!std::filesystem::exists(outputDirectory)) {
            try {
                std::filesystem::create_directory(outputDirectory);
                cout << "Diretorio '" << outputDirectory << "' criado com sucesso." << endl;
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Erro ao criar diretorio '" << outputDirectory << "': " << e.what() << endl;
                return;
            }
        }

        std::string filename;
        std::cout << "Digite o nome do arquivo para exportar (sem extensão): ";
        std::cin >> filename;
        
        std::string outputFilename = outputDirectory + filename + ".csv";

        std::ofstream csvFile(outputFilename);
        if (!csvFile.is_open()) {
            std::cerr << "Erro ao abrir arquivo " << outputFilename << ". Não foi possível salvar." << std::endl;
            return;
        }

   
        csvFile << "Num_Docs,Altura,Total_Nos,Profundidade_Media,"
                  << "Profundidade_Minima,Max_Desbalanceamento,"
                  << "Tempo_Total_Indexacao,Tempo_Medio_Insercao,"
                  << "Densidade_Arvore,Maior_Galho,Menor_Galho,"
                  << "Total_Comparacoes_Indexacao,Tipo_Arvore\n";
        // Ponteiros para funções específicas
        BinaryTree* (*createFunc)() = nullptr;
        void (*destroyFunc)(BinaryTree*) = nullptr;
        InsertResult (*insertFunc)(BinaryTree*, const std::string&, int) = nullptr;

        if (treeType == "AVL") {
            createFunc = AVL::create;
            destroyFunc = AVL::destroy;
            insertFunc = AVL::insert;
        } else {
            createFunc = BST::create;
            destroyFunc = BST::destroy;
            insertFunc = BST::insert;
        }

        BinaryTree* tempTree = createFunc();
        
        for (int num_docs_iter = 1; num_docs_iter <= max_docs; ++num_docs_iter) {
            destroyFunc(tempTree);
            tempTree = createFunc();
            
            double current_cumulative_insertion_time = 0.0; 
            long long current_cumulative_comparisons = 0; // Nova variável para acumular as comparações
            
            for (size_t i = 0; i < allInsertedDocuments.size(); ++i) { 
                const auto& doc_entry = allInsertedDocuments[i];
                if (doc_entry.docId < num_docs_iter) { 
                    insertFunc(tempTree, doc_entry.word, doc_entry.docId);
                    
                    if (i < timeHistory.size()) {
                        current_cumulative_insertion_time += timeHistory[i];
                    }
                    if (i < insertHistory.size()) { // Acumula comparações
                        current_cumulative_comparisons += insertHistory[i].numComparisons;
                    }
                } else {
                    break; 
                }
            }
            
            TreeStatistics stats = collectAllStats(tempTree->root);
            
            double average_insertion_time = (stats.nodeCount > 0) ? current_cumulative_insertion_time / stats.nodeCount : 0.0;
            double tree_density = (stats.height >= 0 && stats.nodeCount > 0) ? (double)stats.nodeCount / (pow(2, stats.height + 1) - 1) : 0.0; 
            int longest_branch = stats.height;
            int shortest_branch = stats.minDepth;
            
            // Escrever linha no CSV
            csvFile << num_docs_iter << ","
                      << stats.height << ","
                      << stats.nodeCount << ","
                      << stats.averageDepth << ","
                      << stats.minDepth << ","
                      << stats.maxImbalance << ","
                      << current_cumulative_insertion_time << ","
                      << average_insertion_time << ","    
                      << tree_density << ","              
                      << longest_branch << ","            
                      << shortest_branch << ","           
                      << current_cumulative_comparisons << "," // Usa o total acumulado de comparações
                      << treeType << "\n";
        }

        destroyFunc(tempTree); 
        csvFile.close();
        
        std::cout << "Estatísticas exportadas para " << outputFilename << std::endl;
    }

    }


void printAllStats(BinaryTree* tree, const InsertResult& lastInsert, double totalTime, int n_docs) {
    TreeStatistics stats = collectAllStats(tree->root);
    
     // Novos cálculos para print
    double tree_density = (stats.height >= 0 && stats.nodeCount > 0) ? (double)stats.nodeCount / (pow(2, stats.height + 1) - 1) : 0.0;
    int longest_branch = stats.height;
    int shortest_branch = stats.minDepth;
    int branch_difference = longest_branch - shortest_branch;
    double branch_ratio = (shortest_branch != 0) ? static_cast<double>(longest_branch) / shortest_branch : (longest_branch == 0 ? 1.0 : -1.0 /* Infinito ou N/A */);

    cout << "\n=== TODAS ESTATISTICAS ===" << endl;
    cout << "------ Estruturais ------" << endl;
    cout << "Altura da arvore: " << stats.height << endl;
    cout << "Nos totais: " << stats.nodeCount << endl;
    cout << "Profundidade media: " << stats.averageDepth << endl;
    cout << "Profundidade minima: " << stats.minDepth << endl;
    cout << "Fator de balanceamento maximo: " << stats.maxImbalance << endl;
      // --- Adicionado as linhas de impressão para as variáveis ---
    cout << "Densidade da arvore: " << tree_density << endl;
    cout << "Tamanho do maior galho: " << longest_branch << endl;
    cout << "Tamanho do menor galho: " << shortest_branch << endl;
    cout << "Diferenca entre galhos: " << branch_difference << endl; // Impressão adicionada
        
    if (shortest_branch != 0) {
            cout << "Razao maior/menor galho: " << branch_ratio << endl;
        } else {
            cout << "Razao maior/menor galho: N/A (menor galho eh zero ou indefinido)" << endl;
        }
    cout << "\n------ Desempenho ------" << endl;
    cout << "Documentos indexados: " << n_docs << endl;
    cout << "Tempo total indexacao: " << totalTime << " ms" << endl;
    
    // Cálculo do tempo médio de inserção aqui
    double average_insertion_time = (stats.nodeCount > 0) ? totalTime / stats.nodeCount : 0.0;
    cout << "Tempo medio de insercao por no: " << average_insertion_time << " ms" << endl;

    
    cout << "Ultima insercao:" << endl;
    cout << "* Comparacoes: " << lastInsert.numComparisons << endl;
    cout << "* Tempo: " << lastInsert.executionTime << " ms" << endl;
    cout << "=========================" << endl;
}

}
