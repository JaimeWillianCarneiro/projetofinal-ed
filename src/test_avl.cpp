// test_avl.cpp
// Testes para Arvore AVL com impressao antes/depois das rotacoes

#include <iostream>
#include "avl.h"

using namespace std;
using namespace AVL;

void printSearchResult(const SearchResult& result, const string& word) {
    cout << "busca por \"" << word << "\": ";
    if (result.found) {
        cout << "documentos: ";
        for (int id : result.documentIds) {
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "nao encontrada" << endl;
    }
}

void printTreeWithTitle(BinaryTree* tree, const string& title) {
    cout << "\n=== " << title << " ===\n";
    printTree(tree);
    cout << "------------------------\n";
}

void testBusca(BinaryTree* tree) {
    cout << "\n***** TESTANDO BUSCAS *****\n";
    
    // Teste com palavras existentes
    printSearchResult(search(tree, "banana"), "banana");
    printSearchResult(search(tree, "maca"), "maca");
    printSearchResult(search(tree, "laranja"), "laranja");
    
    // Teste com palavras não existentes
    printSearchResult(search(tree, "abacaxi"), "abacaxi");
    printSearchResult(search(tree, "30"), "30"); 
    printSearchResult(search(tree, "xyz"), "xyz");
}

void testCasesComPalavras() {
    cout << "\n***** TESTES COM PALAVRAS *****\n";
    BinaryTree* tree = create();

    // Primeiras inserções
    insert(tree, "banana", 101);
    insert(tree, "maca", 102);
    insert(tree, "laranja", 103);
    insert(tree, "pera", 104);
    insert(tree, "uva", 105);
    
    printTreeWithTitle(tree, "Arvore apos insercao inicial");

    // Mais inserções 
    cout << "\nInserindo mais palavras...\n";
    insert(tree, "abacate", 106);
    insert(tree, "kiwi", 107);
    insert(tree, "morango", 108);
    
    printTreeWithTitle(tree, "Arvore apos novas insercoes");

    // Teste de busca
    testBusca(tree);
    
    destroy(tree);
}

void testRotationCases() {
    cout << "\n***** TESTANDO ROTACOES DA AVL *****\n";

    // Caso 1: Rotacao Simples a Direita 
    {
        cout << "\n>>> Caso 1: Rotacao a Direita <<<\n";
        BinaryTree* tree = create();
        
        cout << "\n[1] Inserindo '30'...\n";
        insert(tree, "30", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 30");
        
        cout << "\n[2] Inserindo '20'...\n";
        insert(tree, "20", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 20");
        
        cout << "\n[3] Inserindo '10' (DEVE CAUSAR ROTACAO A DIREITA)...\n";
        insert(tree, "10", 1);
        printTreeWithTitle(tree, "Arvore apos rotacao");

        destroy(tree);
    }

    // Caso 2: Rotacao Simples a Esquerda 
    {
        cout << "\n>>> Caso 2: Rotacao a Esquerda <<<\n";
        BinaryTree* tree = create();
        
        cout << "\n[1] Inserindo '10'...\n";
        insert(tree, "10", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 10");
        
        cout << "\n[2] Inserindo '20'...\n";
        insert(tree, "20", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 20");
        
        cout << "\n[3] Inserindo '30' (DEVE CAUSAR ROTACAO A ESQUERDA)...\n";
        insert(tree, "30", 1);
        printTreeWithTitle(tree, "Arvore apos rotacao");

        destroy(tree);
    }

    // Caso 3: Rotacao Dupla Esquerda-Direita 
    {
        cout << "\n>>> Caso 3: Rotacao Esquerda-Direita <<<\n";
        BinaryTree* tree = create();
        
        cout << "\n[1] Inserindo '30'...\n";
        insert(tree, "30", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 30");
        
        cout << "\n[2] Inserindo '10'...\n";
        insert(tree, "10", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 10");
        
        cout << "\n[3] Inserindo '20' (DEVE CAUSAR ROTACAO DUPLA ESQ-DIR)...\n";
        insert(tree, "20", 1);
        printTreeWithTitle(tree, "Arvore apos rotacao");

        destroy(tree);
    }

    // Caso 4: Rotacao Dupla Direita-Esquerda 
    {
        cout << "\n>>> Caso 4: Rotacao Direita-Esquerda <<<\n";
        BinaryTree* tree = create();
        
        cout << "\n[1] Inserindo '10'...\n";
        insert(tree, "10", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 10");
        
        cout << "\n[2] Inserindo '30'...\n";
        insert(tree, "30", 1);
        printTreeWithTitle(tree, "Arvore apos inserir 30");
        
        cout << "\n[3] Inserindo '20' (DEVE CAUSAR ROTACAO DUPLA DIR-ESQ)...\n";
        insert(tree, "20", 1);
        printTreeWithTitle(tree, "Arvore apos rotacao");

        destroy(tree);
    }
}

int main() {
    testRotationCases(); 
    testCasesComPalavras();  
    return 0;
}