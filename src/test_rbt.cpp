// test_rbt.cpp
// Testes unitarios e exemplos para implementacao da Arvore Rubro-Negra (RBT)

#include <iostream>
#include "rbt.h"

using namespace std;
using namespace RBT;

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
    cout << "\n Inserindo: banana, maca, laranja, pera, uva\n";
    insert(tree, "banana", 1);
    insert(tree, "maca", 2);
    insert(tree, "laranja", 3);
    insert(tree, "pera", 4);
    insert(tree, "uva", 5);

    cout << "\n Arvore apos insercao inicial \n";
    RBT::printTree(tree);
    cout << "\n";

    cout << "\n Inserindo: abacate, kiwi, morango\n";
    insert(tree, "abacate", 6);
    insert(tree, "kiwi", 7);
    insert(tree, "morango", 8);

    cout << "\n Arvore apos novas insercoes \n";
    RBT::printTree(tree);
    cout << "\n";

    //Verifica se a árvore ainda é uma RBT válida
    if (isValidRBT(tree)) {
        cout << "A arvore satisfaz as propriedades de uma Red-Black Tree.\n";
    } else {
        cout << "A arvore viola as propriedades de uma Red-Black Tree.\n";
    }
}

void testSearches(BinaryTree* tree) {
    cout << "\n Buscas: \n";

    // Testes com palavras existentes
    printSearchResult(search(tree, "banana"), "banana");
    printSearchResult(search(tree, "maca"), "maca");
    printSearchResult(search(tree, "kiwi"), "kiwi");

    // Testes com palavras não existentes
    printSearchResult(search(tree, "abacaxi"), "abacaxi");
    printSearchResult(search(tree, "pessego"), "pessego");
    printSearchResult(search(tree, "figo"), "figo");
}

void testSpecialCases() {
    cout << "\n Casos especiais: rotacoes e recoloracoes da RBT\n";

    // Caso 1: recoloracao
    {
        cout << "\n Inserindo: pera, banana, uva\n";
        BinaryTree* tree = create();
        insert(tree, "pera", 1);
        insert(tree, "banana", 1);
        insert(tree, "uva", 1);

         cout << "\n Arvore antes da recoloracao \n";

        RBT::printTree(tree);
        cout << "\n";

        insert(tree, "maca", 1);

        cout << "\n Arvore apos recoloracao causada por inserir 'maca' \n";

        RBT::printTree(tree);
        cout << "\n";
        destroy(tree);
    }

    // Caso 2: rotacao simples a direita
    {
        cout << "\n Inserindo: melancia, goiaba, figo\n";
        BinaryTree* tree = create();
        insert(tree, "melancia", 1);
        insert(tree, "goiaba", 1);
        insert(tree, "figo", 1);

        cout << "\n Arvore apos rotacao direita \n";
        RBT::printTree(tree);
        cout << "\n";
        destroy(tree);
    }

    // Caso 3: rotacao simples a esquerda
    {
        cout << "\n Inserindo: figo, goiaba, melancia\n";
        BinaryTree* tree = create();
        insert(tree, "figo", 1);
        insert(tree, "goiaba", 1);
        insert(tree, "melancia", 1);

        cout << "\n Arvore apos rotacao esquerda \n";
        RBT::printTree(tree);
        cout << "\n";
        destroy(tree);
    }

    // Caso 4: rotacao dupla esquerda-direita
    {
        cout << "\n Inserindo: melancia, figo, goiaba\n";
        BinaryTree* tree = create();
        insert(tree, "melancia", 1);
        insert(tree, "figo", 1);
        insert(tree, "goiaba", 1);

        cout << "\n Arvore apos rotacao esquerda-direita \n";
        RBT::printTree(tree);
        cout << "\n";
        destroy(tree);
    }

    // Caso 5: rotacao dupla direita-esquerda
    {
        cout << "\n Inserindo: figo, melancia, goiaba\n";
        BinaryTree* tree = create();
        insert(tree, "figo", 1);
        insert(tree, "melancia", 1);
        insert(tree, "goiaba", 1);

        cout << "\n Arvore apos rotacao direita-esquerda \n";
        RBT::printTree(tree);
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
