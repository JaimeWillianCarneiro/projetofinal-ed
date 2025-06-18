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

void testInsertions1(BinaryTree* tree) {
    insert(tree, "penso", 1);
    insert(tree, "logo", 1);
    insert(tree, "existo", 1);
    
    insert(tree, "seja", 2);
    insert(tree, "a", 2);
    insert(tree, "mudanca", 2);

    cout << "\n Arvore apos insercao inicial \n";
    printTree(tree);
    cout << "\n";
}

void testInsertions2(BinaryTree* tree) {
    insert(tree, "a", 4);
    insert(tree, "felicidade", 4);
    insert(tree, "esta", 4);
    
    insert(tree, "o", 5);
    insert(tree, "olhar", 5);
    insert(tree, "diz", 5);
    
    insert(tree, "o", 6);
    insert(tree, "tempo", 6);
    insert(tree, "nao", 6);
    
    cout << "\n Arvore apos novas insercoes \n";
    printTree(tree);
    cout << "\n";
}

void testSearches(BinaryTree* tree) {
    cout << "\n Buscas: \n";
    
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

void testSpecialCases() {
    cout << "\n Casos especiais:\n";
    BinaryTree* tree = create();
    
    // Teste com árvore vazia
    cout << "\n Testando arvore vazia:\n";
    printSearchResult(search(tree, "amor"), "amor");
    
    cout << "\n Testando insercao ordenada (pior caso na BST):\n";
    insert(tree, "a", 100);
    insert(tree, "b", 100);
    insert(tree, "c", 100);
    insert(tree, "d", 100);

    cout << "\n Arvore com nos em ordem \n";
    printTree(tree);
    cout << "\n";
    destroy(tree);
}

int main() {
    BinaryTree* tree = create();
    testInsertions1(tree);
    testInsertions2(tree);
    testSearches(tree);
    testSpecialCases();

    return 0;
}