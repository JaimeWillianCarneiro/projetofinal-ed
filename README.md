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

---

## Instruções para Compilar e Executar
- Para compilar, utilize o Makefile:

```bash
make
```

- Para limpar os arquivos .o

```bash
make clean
```
### Modo de busca:

```bash
./programa search <n_docs> <diretorio>
```
Exemplo:
```bash
./programa search 5 <./data>
```
O programa carregará os arquivos 0.txt até 4.txt e permitirá buscar palavras. Digite "sair" para encerrar.

---

## Testes

Execute o arquivo test_bst.cpp separadamente para validar o funcionamento da árvore:

```bash
g++ src/test_bst.cpp src/bst.cpp src/tree_utils.cpp -o test_bst
./test_bst
```
### Passo a passo:

1. **Abra o terminal na pasta do projeto (projetofinal-ed\src).**

2. **Compile o projeto com o comando:**

```bash
g++ -o test_bst test_bst.cpp bst.cpp tree_utils.cpp
```
