CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# ============================
# Alvo principal
# ============================
all: avl bst rbt

# ============================
# AVL Executable
# ============================
# O executável 'avl' precisa de seus próprios objetos mais tree_utils.o, data.o, E bst.o
avl: main_avl.o avl.o tree_utils.o data.o bst.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_avl.o: src/main_avl.cpp src/avl.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c src/main_avl.cpp -o $@

avl.o: src/avl.cpp src/avl.h src/tree_utils.h
	$(CXX) $(CXXFLAGS) -c src/avl.cpp -o $@

# ============================
# BST Executable
# ============================
# O executável 'bst' precisa de seus próprios objetos mais tree_utils.o, data.o, E avl.o
bst: main_bst.o bst.o tree_utils.o data.o avl.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_bst.o: src/main_bst.cpp src/bst.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c src/main_bst.cpp -o $@

bst.o: src/bst.cpp src/bst.h src/tree_utils.h
	$(CXX) $(CXXFLAGS) -c src/bst.cpp -o $@

# ============================
# RBT
# ============================
rbt: main_rbt.o rbt.o tree_utils.o data.o avl.o bst.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_rbt.o: src/main_rbt.cpp src/rbt.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c src/main_rbt.cpp -o $@

rbt.o: src/rbt.cpp src/rbt.h
	$(CXX) $(CXXFLAGS) -c src/rbt.cpp -o $@

# ============================
# Código Compartilhado
# ============================
tree_utils.o: src/tree_utils.cpp src/tree_utils.h src/avl.h src/bst.h
	$(CXX) $(CXXFLAGS) -c src/tree_utils.cpp -o $@

data.o: src/data.cpp src/data.h src/tree_utils.h
	$(CXX) $(CXXFLAGS) -c src/data.cpp -o $@

# ============================
# Limpeza
# ============================
clean:
	del /Q *.o avl.exe bst.exe rbt.exe