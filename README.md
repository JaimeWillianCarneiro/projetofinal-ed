# Trabalho A2: Índice Invertido e Análise Comparativa de Estruturas de Dados

Integrantes: Carlos Daniel de Souza Lima, Gabriela Barbosa Souza, Gabrielly Esteves Pinheiro Chácara, Jaime Willian Carneiro da Silva, Walléria Simões Correia.

---

## Índice
- [Introdução](#introdução)
- [Bibliotecas Utilizadas](#bibliotecas-utilizadas)
- [Instruções para Compilar e Executar](#instruções-para-compilar-e-executar)
  - [Para compilar manualmente](#para-compilar-manualmente)
- [Como usar](#como-usar)
  - [Exemplo de uso](#exemplo-de-uso)
- [Estatísticas](#estatísticas)
- [Testes](#testes)

---

## Introdução

Este projeto foca na implementação e análise comparativa da Árvore Binária de Busca (BST), da Árvore AVL e da Árvore Rubro-Negra (RBT). A análise explora o contraste entre a simplicidade da BST, que serve como nossa base de comparação (baseline), e as sofisticadas estratégias de autobalanceamento da AVL e RBT. As três estruturas foram aplicadas a um problema prático de criação de um índice invertido a partir de documentos de texto, permitindo uma avaliação de métricas de desempenho.

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
- `<cctype>` – Auxílio na formatação das palavras.
- `<cmath>` - Auxlio no cálculo das estatísticas
- `<random>` - Para geração de números aleatórios para amostra de busca
- `<climits>` - Fornece constantes que especificam os limites de tipos inteiros.

---

## Instruções para Compilar e Executar

Para compilar você pode utilizar o `Makefile` (no **Windows**):

- Compilar:
```bash
mingw32-make
```
- Deletar os arquivos `.o`:
```bash
mingw32-make clean
```

#### Para compilar manualmente
- Para compilar:
```bash
g++ -c .\src\tree_utils.cpp -o tree_utils.o
g++ -c .\src\data.cpp -o data.o
g++ -c .\src\main_bst.cpp -o main_bst.o
g++ -c .\src\bst.cpp -o bst.o
g++ -c .\src\main_avl.cpp -o main_avl.o
g++ -c .\src\avl.cpp -o avl.o
g++ -c .\src\main_rbt.cpp -o main_rbt.o
g++ -c .\src\rbt.cpp -o rbt.o
```
> Se estiver no Linux/macOS, troque `.\src\` por `./src/`

- Linke todos os `.o` para criar os executáveis `bst.exe`, `avl.exe`, `rbt.exe`:
> No Windows:
```bash
g++ main_bst.o bst.o tree_utils.o data.o avl.o rbt.o -o bst.exe
g++ main_avl.o avl.o tree_utils.o data.o bst.o rbt.o -o avl.exe
g++ main_rbt.o rbt.o tree_utils.o data.o avl.o bst.o -o rbt.exe
```
> No Linux/macOS:
```bash
g++ main_bst.o bst.o tree_utils.o data.o avl.o rbt.o -o bst
g++ main_avl.o avl.o tree_utils.o data.o bst.o rbt.o -o avl
g++ main_rbt.o rbt.o tree_utils.o data.o avl.o bst.o -o rbt
```

---

## Como usar
 Com os arquivos compilados, você já pode utilizar a interface:

```bash
./<arvore> <modo> <n_docs> <diretorio>
```
* `<arvore>`: O tipo de árvore a ser usado (`bst`, `avl` ou `rbt`).
* `<modo>`: O modo de operação (`search` para busca ou `stats` para estatísticas).
* `<n_docs>`: O número de documentos a serem lidos da pasta de dados (de 0.txt até n-1.txt).
* `<diretorio_dados>`: O caminho para a pasta que contém os arquivos `.txt`.

#### Exemplo de uso:
```bash
./avl stats 5 "./data/"
```
* O programa carregará os arquivos em ordem numérica, neste caso, carregará de 0.txt até 4.txt.

* Digite "\q" ou dê Ctrl + C para encerrar.

---

## Estatísticas

Ao usar o modo stats, o programa irá inserir todas as palavras dos documentos em ordem e mostrar o seguinte menu:

```
  Selecione uma das opcoes (Insira apenas o numero):
  1. Tempo de insercao.
  2. Altura  e densidade da arvore.
  3. Tamanho dos galhos.
  4. Estatisticas de Busca (Amostra).
  5. Todas as estatisticas.
  6. Exportar estatisticas para CSV.
  Ou digite '\q' para sair (ou ctrl + c).
```
**Opção 1**: são mostrados os tempos médio e total de inserção das palavras dos documentos escolhidos.

**Opção 2**: são mostradas a altura da árvore criada e sua densidade.

**Opção 3**: o programa retorna os tamanhos do maior e menor galhos, diferença e razão entre eles e a profundidade média dos nós.

**Opção 4**: retorna todas as estatísticas citadas de uma única vez

---

## Testes

O projeto inclui testes unitários para validar as funcionalidades de inserção e busca de cada árvore.
Compile e execute no terminal os arquivos contendo os testes unitários da seguinte forma:

* Para BST:
```bash
g++ -std=c++17 -Wall -o test_bst src/test_bst.cpp src/data.cpp src/tree_utils.cpp src/avl.cpp src/bst.cpp src/rbt.cpp
./test_bst
```

* Para AVL:
```bash
g++ -std=c++17 -Wall -o test_avl src/test_avl.cpp src/data.cpp src/tree_utils.cpp src/avl.cpp src/bst.cpp src/rbt.cpp
./test_avl
```

* Para RBT:
```bash
g++ -std=c++17 -Wall -o test_rbt src/test_rbt.cpp src/data.cpp src/tree_utils.cpp src/avl.cpp src/bst.cpp src/rbt.cpp
./test_rbt
```

- Para deletar os executáveis:
```bash
del test_bst.exe
```
```bash
del test_avl.exe
```
```bash
del test_rbt.exe
```