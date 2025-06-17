CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# ============================
# Alvo principal
# ============================
all: avl bst rbt

# ============================
# AVL
# ============================
avl: main_avl.o avl.o tree_utils.o data.o
	$(CXX) $(CXXFLAGS) -o avl main_avl.o avl.o tree_utils.o data.o

main_avl.o: src/main_avl.cpp src/avl.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c src/main_avl.cpp -o main_avl.o

avl.o: src/avl.cpp src/avl.h
	$(CXX) $(CXXFLAGS) -c src/avl.cpp -o avl.o

# ============================
# BST
# ============================
bst: main_bst.o bst.o tree_utils.o data.o
	$(CXX) $(CXXFLAGS) -o bst main_bst.o bst.o tree_utils.o data.o

main_bst.o: src/main_bst.cpp src/bst.h src/tree_utils.h src/data.h
	$(CXX) $(CXXFLAGS) -c src/main_bst.cpp -o main_bst.o

bst.o: src/bst.cpp src/bst.h
	$(CXX) $(CXXFLAGS) -c src/bst.cpp -o bst.o

# ============================
# RBT
# ============================
rbt: main_rbt.o rbt.o tree_utils.o data.o
	$(CXX) -o rbt main_rbt.o rbt.o tree_utils.o data.o

main_rbt.o: src/main_rbt.cpp src/rbt.h src/tree_utils.h src/data.h
	$(CXX) -c src/main_rbt.cpp -o main_rbt.o

rbt.o: src/rbt.cpp src/rbt.h
	$(CXX) -c src/rbt.cpp -o rbt.o

# ============================
# Código Compartilhado
# ============================
tree_utils.o: src/tree_utils.cpp src/tree_utils.h
	$(CXX) $(CXXFLAGS) -c src/tree_utils.cpp -o tree_utils.o

data.o: src/data.cpp src/data.h
	$(CXX) $(CXXFLAGS) -c src/data.cpp -o data.o

# ============================
# Limpeza
# ============================
clean:
	del /Q *.o avl.exe bst.exe rbt.exe