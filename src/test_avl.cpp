// test_avl.cpp
// Testes unitarios e exemplos para implementacao da Arvore AVL

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
        cout << "esta palavra nao esta inclusa" << endl;
    }
}

void testInsertions(BinaryTree* tree) {
    insert(tree, "banana", 101);
    insert(tree, "maca", 102);
    insert(tree, "laranja", 103);
    insert(tree, "pera", 104);
    insert(tree, "uva", 105);

    cout << "\n Arvore apos insercao inicial \n";
    printTree(tree);
    cout << "\n";

    insert(tree, "abacate", 106);
    insert(tree, "kiwi", 107);
    insert(tree, "morango", 108);

    cout << "\n Arvore apos novas insercoes \n";
    printTree(tree);
    cout << "\n";
}

void testSearches(BinaryTree* tree) {
    cout << "\n Buscas: \n";

    // Testes com palavras existentes
    printSearchResult(search(tree, "banana"), "banana");
    printSearchResult(search(tree, "maca"), "maca");
    printSearchResult(search(tree, "laranja"), "laranja");

    // Testes com palavras não existentes
    printSearchResult(search(tree, "abacaxi"), "abacaxi");
    printSearchResult(search(tree, "30"), "30");
    printSearchResult(search(tree, "xyz"), "xyz");

}

void testSpecialCases() {
    cout << "\n Casos especiais: rotacoes da AVL\n";

    // Caso 1: rotacao simples a direita
    {
        cout << "\n Teste 1: rotacao a direita\n";
        BinaryTree* tree = create();

        cout << "\n Inserindo: 30, 20, 10\n";
        insert(tree, "30", 1);
        insert(tree, "20", 1);
        insert(tree, "10", 1);

        cout << "\n Arvore apos rotacao \n";
        printTree(tree);
        cout << "\n";

        destroy(tree);
    }

    // Caso 2: rotacao simples a esquerda
    {
        cout << "\n Teste 2: rotacao a esquerda\n";
        BinaryTree* tree = create();

        cout << "\n Inserindo: 10, 20, 30\n";
        insert(tree, "10", 1);
        insert(tree, "20", 1);
        insert(tree, "30", 1);

        cout << "\n Arvore apos rotacao \n";
        printTree(tree);
        cout << "\n";

        destroy(tree);
    }

    // Caso 3: rotacao dupla esquerda-direita
    {
        cout << "\n Teste 3: rotacao esquerda-direita\n";
        BinaryTree* tree = create();

        cout << "\n Inserindo: 30, 10, 20\n";
        insert(tree, "30", 1);
        insert(tree, "10", 1);
        insert(tree, "20", 1);

        cout << "\n Arvore apos rotacao \n";
        printTree(tree);
        cout << "\n";

        destroy(tree);
    }

    // Caso 4: rotacao dupla direita-esquerda
    {
        cout << "\n Teste 4: rotacao direita-esquerda\n";
        BinaryTree* tree = create();

        cout << "\n Inserindo: 10, 30, 20\n";
        insert(tree, "10", 1);
        insert(tree, "30", 1);
        insert(tree, "20", 1);

        cout << "\n Arvore apos rotacao \n";
        printTree(tree);
        cout << "\n";

        destroy(tree);
    }
}

int main() {
    BinaryTree* tree = create();

    testInsertions(tree);
    testSearches(tree);
    testSpecialCases();

    destroy(tree);
    return 0;
}
