// test_bst.cpp
// testes unitários e exemplos para implementação da Árvore Binária de Busca

#include <iostream>
#include "bst.h"

using namespace std;
using namespace BST;

void printSearchResult(const SearchResult& result, const string& word) { // função para deixar o código mais simples
    cout << "busca por \"" << word << "\": ";
    if (result.found) { // caso a palavra seja encontrada 
        cout << "documentos: ";
        for (int id : result.documentIds) {  // printa os id's dos documentos achados
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "esta palavra nao esta inclusa" << endl; // caso a palavra nao esteja na arvore
    }
}

int main() {
    BinaryTree* tree = create(); // cria a arvore inicial vazia

    // insercao das palavras. peguei uma lista aleatoria de nomes de animais
    insert(tree, "cachorro", 1);
    insert(tree, "gato", 2);
    insert(tree, "elefante", 3);
    insert(tree, "gato", 4);      // repetida com outro documento
    insert(tree, "abelha", 2);
    insert(tree, "zebra", 5);
    insert(tree, "cobra", 3);
    insert(tree, "cachorro", 6);  // repetida com outro documento

    cout << "\n Impressao da arvore:" << endl; 
    printTree(tree);  // mostra a arvore completa

    cout << "\n Buscas:" << endl;
    printSearchResult(search(tree, "gato"), "gato");           // saida: 2 4
    printSearchResult(search(tree, "cachorro"), "cachorro");   // saida: 1 6
    printSearchResult(search(tree, "elefante"), "elefante");   // saida: 3
    printSearchResult(search(tree, "cobra"), "cobra");         // saida: 3
    printSearchResult(search(tree, "tigre"), "tigre");         // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "zebra"), "zebra");         // saida: 5
    printSearchResult(search(tree, "abelha"), "abelha");       // saida: 2

    destroy(tree); // destroi a arvore assim que o código termina de rodar
    return 0;
}
