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

void testInsertions(BinaryTree* tree) {
    cout << "\n Inserindo palavras...\n";
    insert(tree, "penso", 1);
    insert(tree, "logo", 1);
    insert(tree, "existo", 1);
    
    insert(tree, "seja", 2);
    insert(tree, "a", 2);
    insert(tree, "mudanca", 2);
    
    printTreeWithTitle(tree, "Arvore apos insercao inicial");
}

int main() {
    BinaryTree* tree = create();
    testInsertions(tree);
    return 0;
}