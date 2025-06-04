all: bst

bst: main_bst.o bst.o tree_utils.o data.o
	g++ main_bst.o bst.o tree_utils.o data.o -o bst

main_bst.o: .\src\main_bst.cpp .\src\bst.h .\src\tree_utils.h .\src\data.h
	g++ -c .\src\main_bst.cpp -o main_bst.o

bst.o: .\src\bst.cpp .\src\bst.h
	g++ -c .\src\bst.cpp -o bst.o

tree_utils.o: .\src\tree_utils.cpp .\src\tree_utils.h
	g++ -c .\src\tree_utils.cpp -o tree_utils.o

data.o: .\src\data.cpp .\src\data.h
	g++ -c .\src\data.cpp -o data.o

clean:
	rm -f *.o bst