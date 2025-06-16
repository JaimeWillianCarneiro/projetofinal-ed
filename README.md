# Trabalho A2: Índice Invertido e Análise Comparativa de Estruturas de Dados

Integrantes: Carlos Daniel de Souza Lima, Gabriela Barbosa Souza, Gabrielly Esteves Pinheiro Chácara, Jaime Willian Carneiro da Silva, Walléria Simões Correia.

## Introdução

Para a segunda entrega do projeto criamos a implementação de uma árvore binária de busca autobalanceada (AVL) para indexar palavras de vários documentos de texto. O sistema permite inserir palavras associadas aos documentos onde aparecer e realizar buscas por essas palavras, além de implementarmos algumas estatísticas relavantes para compará-la com a BST previamente criada.

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

---

## Instruções para Compilar e Executar
### Para compilar você pode utilizar o Makefile (no **Windows**):

- Para compilar
```bash
mingw32-make
```
- Para limpar os arquivos .o
```bash
mingw32-make clean
```

#### Para compilar manualmente
- Para compilar:
```bash
g++ -c .\src\main_bst.cpp -o main_bst.o
g++ -c .\src\bst.cpp -o bst.o
g++ -c .\src\tree_utils.cpp -o tree_utils.o
g++ -c .\src\data.cpp -o data.o
g++ -c .\src\main_avl.cpp -o main_avl.o
g++ -c .\src\avl.cpp -o avl.o
g++ -c .\src\tree_utils.cpp -o tree_utils.o
g++ -c .\src\data.cpp -o data.o
```
> Se estiver no Linux/macOS, troque `.\src\` por `./src/`

Linke todos os `.o` para criar o executável `avl.exe`:

> No Windows:
```bash
g++ main_avl.o avl.o tree_utils.o data.o -o avl.exe
```

> No Linux/macOS:
```bash
g++ main_avl.o avl.o tree_utils.o data.o -o avl
```

---

### Como usar
 Com os arquivos compilados, você escolherá  a *árvore* (por enquanto, bst ou avl), o *modo* (search ou stats), o *número de documentos a serem incluídos* e a *pasta com os dados* da seguinte forma:

```bash
./<arvore> <modo> <n_docs> <diretorio>
```
Exemplo de uso:
```bash
./avl stats 5 "./data/"
```
O programa carregará os arquivos em ordem numérica, neste caso, carregará de 0.txt até 4.txt. 

Digite "\q" ou dê Ctrl + C para encerrar.

---

## Estatísticas

Ao usar o modo *stats* o seguinte menu aparecerá:

```
  Selecione uma das opcoes (Insira apenas o numero):
  1. Tempo de insercao.
  2. Altura  e densidade da arvore.
  3. Tamanho dos galhos.
  4. Todas as estatisticas.
  Ou digite '\q' para sair (ou ctrl + c).
```
**Opção 1**: são mostrados os tempos médio e total de inserção das palavras dos documentos escolhidos.

**Opção 2**: são mostradas a altura da árvore criada e sua densidade.

**Opção 3**: o programa retorna os tamanhos do maior e menor galhos, diferença e razão entre eles e a profundidade média dos nós.

**Opção 4**: retorna todas as estatísticas citadas de uma única vez

---

## Testes

No terminal, execute o arquivo test_avl.cpp separadamente para validar o funcionamento da inserção e busca da árvore AVL:

```bash
g++ src/test_avl.cpp src/avl.cpp src/tree_utils.cpp -o test_avl
./test_avl
```
### Passo a passo:

1. Abra o terminal na pasta do projeto (projetofinal-ed\src).

2. Compile o projeto com o comando:

```bash
g++ -o test_avl test_avl.cpp avl.cpp tree_utils.cpp
```

