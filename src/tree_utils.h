#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <iostream>
#include <vector>
#include <climits>
#include <string> 

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace TREE_UTILS {

    
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


    
    struct Document { 
        std::string word;
        int docId;
    };

    extern std::vector<Document> allInsertedDocuments;
    extern std::vector<InsertResult> insertHistory;
    extern std::vector<double> timeHistory;

    
    struct Node {
        std::string word;
        std::vector<int> documentIds;
        Node* parent;
        Node* left;
        Node* right;
        int height; // Usado na AVL
        int isRed; // Usado na RBT

        double totalSearchTime = 0.0;
        int totalSearchComparisons = 0;
        int searchCount = 0;
    };



    struct BinaryTree {
        Node* root;
        Node* NIL; // Usado na RBT (não necessário para BST)
    };



    
    /**
     * @brief Realiza um percurso em-ordem (in-order traversal) na árvore para imprimir as palavras e seus documentos associados
     * @param node Nó raiz da subárvore a ser impressa (pode ser nullptr)
     * @details Esta função auxiliar recursiva percorre a árvore em ordem alfabética (esquerda-raiz-direita) e para cada nó encontrado:
     *          1. Imprime a palavra do nó
     *          2. Imprime a lista de IDs de documentos onde a palavra aparece, separados por vírgulas
     *          3. Coloca cada entrada em uma nova linha
     * @pre Caso o parâmetro node seja nullptr, a função retorna silenciosamente
     * @post Não modifica a estrutura da árvore ou seus dados
     * @note Formato de saída:
     *       palavra1: id1, id2, id3
     *       palavra2: id1, id4
     *       palavra3: id5
     */

    void printIndexInOrder(Node* node);


    /**
     * @brief Imprime todo o índice invertido em ordem alfabética
     * @param tree Ponteiro para a árvore binária contendo o índice
     * @details Percorre a árvore em ordem (in-order traversal) e para cada nó imprime:
     *          - A palavra
     *          - Lista de IDs de documentos onde a palavra aparece
     */
    void printIndex(BinaryTree* tree);


    /**
     * @brief Recursive Pre-Order traversal to print the node and its sons in directory format.
     * @param node Node to be processed.
     * @param height Height of the node.
     */
    void preOrderPrint(Node* node, int height);

    
     /**
     * @brief Print Tree in directory format.
     * @param tree BST to be printed.
     */
    void printTree(BinaryTree* tree);


      /**
     * @brief Realiza busca binária em um vetor de IDs de documentos
     * @param documentIds Vetor de IDs de documentos onde a palavra aparece
     * @param docId ID do documento a ser buscado
     * @param start Índice inicial do intervalo de busca
     * @param end Índice final do intervalo de busca
     * @return int Retorna:
     *            - A posição onde o ID deveria ser inserido (se não encontrado)
     *            - -1 se o ID já existe no vetor
     * 
     * @note Função auxiliar usada durante a inserção de documentos
     */
    int binarySearch(std::vector<int> documentIds, int docId, int start, int end);
   

    /**
     * @brief Use an alternative order to print right nodes first.
     * @param node Center node.
     * @param depth Node's depth.
     * @param maxWordForNivel Vector with gap to nodes in each level.
     * @param restos Auxiliar vector to print edges in correct order.
     */
    void inverseOrderTransversePrint(Node* node, int depth, vector<int> maxWordForNivel, vector<int> restos[]);

    /**
     * @brief Use bfs to get size of gaps to each node in each depth.
     * @param root Tree's root.
     */
    void bfsPrintLateral(Node* root);

    /**
     * @brief Print a tree in left to right.
     * @param tree Tree to print.
     */
    void printTreeLateral(BinaryTree* tree);

    /**
     * @brief Rotate parent and son in a specific side.
     * @param parent Parent of relashionship.
     * @param son Son of relashionship.
     * @param grandSide Parent's where the grandFather is.
     * @param rotateSide Side to apply rotate.
     */
    void sideRotate(Node* parent, Node* son, int grandSide, int rotateSide);



       /**
     * @brief Print Tree in directory format.
     * @param tree BST to be printed.
     */
    void printTree(BinaryTree* tree);

    int binarySearch(std::vector<int> documentIds, int docId, int start, int end);
    
    
     /**
     * @brief Calcula a altura de um nó na árvore AVL.
     * @param node Ponteiro para o nó cuja altura será calculada. Se nullptr, a altura é considerada -1.
     * @return int A altura do nó, onde:
     *             - -1 indica que o nó é nullptr (inexistente)
     *             - 0 indica um nó folha
     *             - Valores > 0 indicam a profundidade na árvore
     * @note A altura é calculada recursivamente como:
     *       altura = 1 + max(altura(esquerda), altura(direita))
     */int getHeight(Node* node);


        /**
     * @brief Calcula o fator de balanceamento de um nó AVL.
     * 
     * @param node Ponteiro para o nó a ser analisado.
     * @return int O fator de balanceamento, calculado como:
     *             altura(subárvore esquerda) - altura(subárvore direita)
     *             Valores possíveis:
     *             - -2: Desbalanceado para direita (rotação necessária)
     *             - -1: Levemente desbalanceado para direita
     *             -  0: Perfeitamente balanceado
     *             - +1: Levemente desbalanceado para esquerda
     *             - +2: Desbalanceado para esquerda (rotação necessária)
     * @warning Retorna 0 se o nó for nullptr.
     */int getBalanceFactor(Node* node);


    // void collectTreeStats(Node* node, int currentDepth, int& totalDepth, int& nodeCount, int& minDepth, int& maxImbalance);
    void collectTreeStats(Node* node, int currentDepth, int& totalDepth, int& nodeCount, int& minDepth, int& maxImbalance, int& maxDepthFound);
        /**
     * @brief Coleta estatísticas abrangentes sobre a árvore.
     * 
     * @param root Ponteiro para a raiz da árvore.
     * @return TreeStatistics Estrutura contendo:
     *             - height: Altura total da árvore
     *             - nodeCount: Número total de nós
     *             - averageDepth: Profundidade média dos nós
     *             - minDepth: Profundidade mínima até uma folha
     *             - maxImbalance: Maior fator de desbalanceamento encontrado
     * 
     * @note Esta função utiliza collectTreeStats internamente para percorrer a árvore.
     *       Complexidade: O(n), onde n é o número de nós.
     */
    TreeStatistics collectAllStats(Node* root);


    /**
     * @brief Exibe um relatório completo de estatísticas da árvore AVL.
     * 
     * @param tree Ponteiro para a estrutura da árvore binária.
     * @param lastInsert Dados da última operação de inserção (comparações e tempo).
     * @param totalTime Tempo total de indexação em milissegundos.
     * @param n_docs Número de documentos indexados.
     * 
     * @details O relatório inclui:
     *          - Seção Estrutural:
     *              * Altura da árvore
     *              * Contagem de nós
     *              * Profundidades média/mínima
     *              * Fator de balanceamento máximo
     *          - Seção de Desempenho:
     *              * Métricas de tempo (total/última inserção)
     *              * Comparações na última inserção
     *              * Documentos processados

    */void printAllStats(BinaryTree* tree, const InsertResult& lastInsert, double totalTime, int n_docs, SearchResult (*searchFunc)(BinaryTree*, const std::string&));


    /**
 * @brief Calcula e exibe estatísticas detalhadas de desempenho de busca para uma amostra de palavras.
 *
 * Esta função realiza um conjunto de buscas em uma amostra de palavras (até 100 por padrão)
 * extraídas dos documentos já indexados na árvore. Ela coleta métricas de tempo e comparações
 * para cada busca e, em seguida, calcula e imprime o tempo máximo, tempo total,
 * tempo médio, comparações totais e comparações médias por palavra para essa amostra.
 * É utilizada para fornecer uma visão instantânea do desempenho de busca no console.
 *
 * @param tree Ponteiro para a estrutura BinaryTree na qual as buscas serão realizadas.
 * @param n_docs O número de documentos que foram processados para construir a `tree` atual.
 * Utilizado para determinar quais palavras de `allInsertedDocuments` pertencem a esta árvore.
 * @param searchFunc Um ponteiro para a função de busca específica da árvore (ex: `AVL::search`, `BST::search`, `RBT::search`).
 * Esta função será usada para realizar as buscas na amostra.
 * @pre `searchFunc` não deve ser nulo e `tree` não deve ser nulo e sua raiz não deve ser nula para que as buscas sejam realizadas.
 * @post Imprime as estatísticas de busca para a amostra no console. Não modifica a estrutura da árvore.
 * @note A amostra de palavras é retirada de `allInsertedDocuments` e pode ser embaralhada e redimensionada
 * para um tamanho máximo (`MAX_SEARCH_SAMPLE_SIZE_FOR_PRINT`) para otimizar o tempo de exibição no console.
 */

 void printSearchStatsSample(BinaryTree* tree, int n_docs, SearchResult (*searchFunc)(BinaryTree*, const std::string&));
    /**
     * @brief Exporta as estatísticas atuais da árvore para um arquivo CSV.
     * @param tree Um ponteiro para a estrutura BinaryTree cujas estatísticas serão exportadas.
     * @param filename O nome do arquivo CSV onde as estatísticas serão salvas.
     * @param lastInsert Uma referência constante a uma estrutura InsertResult contendo estatísticas
     * da última inserção de palavra realizada.
     * @param totalTime O tempo total acumulado (em milissegundos) gasto para indexar todos
     * os documentos processados até o momento para construir a árvore atual.
     * @param n_docs O número total de documentos que foram indexados para construir a árvore atual.
    */
    void exportStatsToCSV(BinaryTree* tree, const std::string& filename,
                            const InsertResult& lastInsert, double totalTime, int n_docs);


    /**
     * @brief Exporta estatísticas evolutivas da árvore para um arquivo CSV.
     * @param max_docs O número máximo de documentos a serem considerados para a análise evolutiva.
     * A função gerará estatísticas para árvores construídas com 1 documento,
     * 2 documentos, ..., até `max_docs` documentos.
     * @param basePath O diretório base onde os documentos de texto de origem estão localizados (ex: "data/").
     * Isso é usado para identificar os arquivos de entrada (ex: "0.txt", "1.txt").
     * @param treeType Uma string indicando o tipo de árvore que está sendo analisada (ex: "AVL", "BST").
     * Esta informação é incluída na saída CSV.
    */
    void exportEvolutionStatsToCSV(int max_docs,
                                    const std::string& basePath,
                                    const std::string& treeType,
                                    SearchResult (*searchFunc)(BinaryTree*, const std::string&));


    /**
     * @brief Reconstrói uma árvore binária com palavras de um número específico de documentos.
     * @param tree Um ponteiro para a estrutura BinaryTree a ser reconstruída.
     * @param n O número de documentos (começando do ID 0) cujas palavras devem ser inseridas na árvore.
     * @param isAVL Um flag booleano indicando se a árvore que está sendo construída é uma árvore AVL (`true`)
     * ou uma Árvore Binária de Busca padrão (`false`). Isso determina qual função de inserção
     * (`AVL::insert` ou `BST::insert`) é utilizada.
     */
    void rebuildTreeUpToNDocs(BinaryTree* tree, int n, bool isAVL);


}

#endif // TREE_UTILS_H