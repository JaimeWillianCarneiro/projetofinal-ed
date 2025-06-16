CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# ============================
# Alvo principal
# ============================
all: avl bst

# ============================
# AVL Executable
# ============================
# O executável 'avl' precisa de seus próprios objetos mais tree_utils.o, data.o, E bst.o
avl: main_avl.o avl.o tree_utils.o data.o bst.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_avl.o: src/main_avl.cpp src/avl.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

avl.o: src/avl.cpp src/avl.h src/tree_utils.h # Adicionado tree_utils.h para consistência
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================
# BST Executable
# ============================
# O executável 'bst' precisa de seus próprios objetos mais tree_utils.o, data.o, E avl.o
bst: main_bst.o bst.o tree_utils.o data.o avl.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_bst.o: src/main_bst.cpp src/bst.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bst.o: src/bst.cpp src/bst.h src/tree_utils.h # Adicionado tree_utils.h para consistência
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================
# Código Compartilhado (dependem de outros headers também)
# ============================
tree_utils.o: src/tree_utils.cpp src/tree_utils.h src/avl.h src/bst.h # Depende de ambos os headers
	$(CXX) $(CXXFLAGS) -c $< -o $@

data.o: src/data.cpp src/data.h src/tree_utils.h # Depende de tree_utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================
# Limpeza
# ============================
clean:
	del /Q *.o avl.exe bst.exe # Use .exe para Windows, se aplicável