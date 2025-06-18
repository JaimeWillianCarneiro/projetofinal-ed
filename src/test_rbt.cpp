#include <iostream>
#include "rbt.h"

using namespace std;
using namespace RBT;

// Teste de busca
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

int main() {
    BinaryTree* tree = create(); // Teste de criação da árvore 

    // Teste de inserção de várias palavras em diferentes documentos (insert)
    insert(tree, "penso", 1);
    insert(tree, "logo", 1);
    insert(tree, "existo", 1);

    insert(tree, "seja", 2);
    insert(tree, "a", 2);
    insert(tree, "mudanca", 2);
    insert(tree, "que", 2);
    insert(tree, "voce", 2);
    insert(tree, "deseja", 2);
    insert(tree, "ver", 2);
    insert(tree, "no", 2);
    insert(tree, "mundo", 2);

    insert(tree, "so", 3);
    insert(tree, "sei", 3);
    insert(tree, "que", 3);
    insert(tree, "nada", 3);
    insert(tree, "sei", 3);

    insert(tree, "a", 4);
    insert(tree, "felicidade", 4);
    insert(tree, "esta", 4);
    insert(tree, "nas", 4);
    insert(tree, "coisas", 4);
    insert(tree, "simples", 4);

    insert(tree, "o", 5);
    insert(tree, "olhar", 5);
    insert(tree, "diz", 5);
    insert(tree, "muito", 5);
    insert(tree, "um", 5);
    insert(tree, "olhar", 5);
    insert(tree, "pode", 5);
    insert(tree, "mudar", 5);
    insert(tree, "tudo", 5);

    insert(tree, "o", 6);
    insert(tree, "tempo", 6);
    insert(tree, "nao", 6);
    insert(tree, "para", 6);
    insert(tree, "de", 6);
    insert(tree, "tempo", 6);
    insert(tree, "ao", 6);
    insert(tree, "tempo", 6);

    insert(tree, "encontre", 7);
    insert(tree, "seu", 7);
    insert(tree, "caminho", 7);
    insert(tree, "ha", 7);
    insert(tree, "um", 7);
    insert(tree, "caminho", 7);
    insert(tree, "novo", 7);

    insert(tree, "ser", 8);
    insert(tree, "livre", 8);
    insert(tree, "e", 8);
    insert(tree, "preciso", 8);
    insert(tree, "deixe", 8);
    insert(tree, "ser", 8);
    insert(tree, "o", 8);
    insert(tree, "que", 8);
    insert(tree, "for", 8);

    insert(tree, "busque", 9);
    insert(tree, "a", 9);
    insert(tree, "sua", 9);
    insert(tree, "luz", 9);
    insert(tree, "a", 9);
    insert(tree, "luz", 9);
    insert(tree, "guia", 9);
    insert(tree, "o", 9);
    insert(tree, "passo", 9);

    printTree(tree);

    // Teste de busca de palavras presentes e ausentes na árvore (search)
    cout << "\nBuscas:" << endl;
    printSearchResult(search(tree, "tempo"), "tempo");
    printSearchResult(search(tree, "que"), "que");
    printSearchResult(search(tree, "elefante"), "elefante");
    printSearchResult(search(tree, "para"), "para");
    printSearchResult(search(tree, "alegria"), "alegria");
    printSearchResult(search(tree, "mudanca"), "mudanca");
    printSearchResult(search(tree, "sei"), "sei");
    printSearchResult(search(tree, "arvore"), "arvore");
    printSearchResult(search(tree, "existo"), "existo");
    printSearchResult(search(tree, "for"), "for");
    printSearchResult(search(tree, "caminho"), "caminho");
    printSearchResult(search(tree, "professor"), "professor");
    printSearchResult(search(tree, "o"), "o");
    printSearchResult(search(tree, "amor"), "amor");
    printSearchResult(search(tree, "encontre"), "encontre");
    printSearchResult(search(tree, "a"), "a");

    // Teste de liberação de memória (destroy)
    destroy(tree);
    return 0;
}