# Trabalho A2: Índice Invertido e Análise Comparativa de Estruturas de Dados

Integrantes: Carlos Daniel de Souza Lima, Gabriela Barbosa Souza, Gabrielly Esteves Pinheiro Chácara, Jaime Willian Carneiro da Silva, Walléria Simões Correia.

## Introdução

Este projeto implementa uma árvore binária de busca (BST) para indexar palavras de vários documentos de texto. O sistema permite inserir palavras associadas aos documentos onde aparecer e realizar buscas por essas palavras.

---

## Bibliotecas Utilizadas

A implementação utiliza as seguintes bibliotecas:

- `<iostream>` – Entrada e saída padrão (cout, cin).
- `<vector>` – Utilizada para armazenar os IDs de documentos.
- `<chrono>` – Usada para medir o tempo de execução das operações.
- `<string>` – Manipulação de strings.
- `<fstream>` – Auxilia na leitura dos arquivos.
- `<algorithm>` – Utilizada (indiretamente) para busca binária, se necessário.
- `<cstring>` – Manipulação de strings.
- `<cctype>` – Auxília na formatação das palavras.

---

## Instruções para Compilar e Executar
### Para compilar você pode utilizar o Makefile (no `Windows`):

 - Para compilar
```bash
mingw32-make
```

- Para limpar os arquivos .o

```bash
mingw32-make clean
```

#### Para compilar manualmente
-  Para compilar:

```bash
g++ -c .\src\main_bst.cpp -o main_bst.o
g++ -c .\src\bst.cpp -o bst.o
g++ -c .\src\tree_utils.cpp -o tree_utils.o
g++ -c .\src\data.cpp -o data.o
```
> Se estiver no Linux/macOS, troque `.\src\` por `./src/`


Linke todos os `.o` para criar o executável `bst.exe` (no Windows):

```bash
g++ main_bst.o bst.o tree_utils.o data.o -o bst.exe
```

> No Linux/macOS, apenas use `bst` ao invés de `bst.exe`


### Modo de busca:

```bash
./bst search <n_docs> <diretorio>
```
Exemplo:
```bash
./bst search 5 "./data/"
```
O programa carregará os arquivos 0.txt até 4.txt e permitirá buscar palavras. Digite "sair" para encerrar.

---

## Testes

Execute o arquivo test_bst.cpp separadamente para validar o funcionamento da árvore:

```bash
g++ src/test_bst.cpp src/bst.cpp src/tree_utils.cpp -o test_bst
./test_bst
```
Aqui as funções são testadas com algumas frases aleatórias.