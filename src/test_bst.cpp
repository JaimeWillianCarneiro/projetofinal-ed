// test_bst.cpp
// Testes unitários e exemplos para implementação da Árvore Binária de Busca

#include <iostream>
#include "bst.h"

using namespace std;
using namespace BST;

void printSearchResult(const SearchResult& result, const string& word) {
    cout << "busca por \"" << word << "\": ";
    if (result.found) {
        cout << "documentos: ";
        for (int id : result.documentIds) {
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "esta palavra nao esta inclusa" << endl;
    }
}

void printTreeWithTitle(BinaryTree* tree, const string& title) {
    cout << "\n=== " << title << " ===\n";
    printTree(tree);
    cout << "------------------------\n";
}

void testInsertions1(BinaryTree* tree) {
    cout << "\n[1] Inserindo palavras...\n";
    insert(tree, "penso", 1);
    insert(tree, "logo", 1);
    insert(tree, "existo", 1);
    
    insert(tree, "seja", 2);
    insert(tree, "a", 2);
    insert(tree, "mudanca", 2);
    
    printTreeWithTitle(tree, "Arvore apos insercao inicial");
}

void testInsertions2(BinaryTree* tree) {
    cout << "\n[2] Inserindo palavras...\n";
    insert(tree, "a", 4);
    insert(tree, "felicidade", 4);
    insert(tree, "esta", 4);
    
    insert(tree, "o", 5);
    insert(tree, "olhar", 5);
    insert(tree, "diz", 5);
    
    insert(tree, "o", 6);
    insert(tree, "tempo", 6);
    insert(tree, "nao", 6);
    
    printTreeWithTitle(tree, "Arvore apos novas insercoes");
}

void testSearches(BinaryTree* tree) {
    cout << "\n***** TESTANDO BUSCAS *****\n";
    
    printSearchResult(search(tree, "tempo"), "tempo");
    printSearchResult(search(tree, "que"), "que");
    printSearchResult(search(tree, "elefante"), "elefante");
    
    // Testes com palavras repetidas
    printSearchResult(search(tree, "a"), "a");
    printSearchResult(search(tree, "o"), "o");
    
    // Testes com palavras não existentes
    printSearchResult(search(tree, "walleria"), "walleria");
    printSearchResult(search(tree, "jaime"), "jaime");
}

int main() {
    BinaryTree* tree = create();
    testInsertions1(tree);
    testInsertions2(tree);
    testSearches(tree);

    return 0;
}