// test_avl.cpp
// testes unitários e exemplos para implementação da Árvore AVL

#include <iostream>
#include "avl.h"

using namespace std;
using namespace AVL;

// função para deixar o código mais simples, já que serão testadas muitas palavras
void printSearchResult(const SearchResult& result, const string& word) {
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
    cout << "\n Criando arvore..." << endl;
    BinaryTree* tree = create(); // cria a arvore inicial vazia

    // insercao das palavras. peguei uma lista de frases aleatorias e citacoes famosas
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

    cout << "\n Impressao dos indices das palavras:" << endl; 
    printIndex(tree); // imprime a lista das palavras inseridas em ordem alfabetica e seus respectivos indices

    cout << "\n Impressao da arvore:" << endl; 
    printTree(tree);  // mostra a arvore completa

    cout << "\n Buscas:" << endl;
    printSearchResult(search(tree, "tempo"), "tempo");         // saida: 6
    printSearchResult(search(tree, "que"), "que");             // saida: 2 3 8
    printSearchResult(search(tree, "elefante"), "elefante");   // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "para"), "para");           // saida: 6
    printSearchResult(search(tree, "alegria"), "alegria");     // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "mudanca"), "mudanca");     // saida: 2
    printSearchResult(search(tree, "sei"), "sei");             // saida: 3
    printSearchResult(search(tree, "arvore"), "arvore");       // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "existo"), "existo");       // saida: 1
    printSearchResult(search(tree, "for"), "for");             // saida: 8
    printSearchResult(search(tree, "caminho"), "caminho");     // saida: 7
    printSearchResult(search(tree, "professor"), "professor"); // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "o"), "o");                 // saida: 5 6 8 9
    printSearchResult(search(tree, "amor"), "amor");           // saida: "esta palavra nao esta inclusa"
    printSearchResult(search(tree, "encontre"), "encontre");   // saida: 7
    printSearchResult(search(tree, "a"), "a");                 // saida: 2 4 9

    destroy(tree); // destroi a arvore liberando espaço novamente
    return 0;
}
